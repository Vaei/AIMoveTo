// Copyright (c) Jared Taylor. All Rights Reserved


#include "AIBlueprintHelperLibraryV2.h"

#include "AIController.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIBlueprintV2, Warning, All);

#define LOCTEXT_NAMESPACE "AIBlueprintHelperLibraryV2"

UAIAsyncTaskBlueprintProxyV2* UAIBlueprintHelperLibraryV2::CreateMoveToV2ProxyObject(UObject* WorldContextObject,
	APawn* Pawn, FVector Destination, AActor* TargetActor, float AcceptanceRadius, bool bUsePathfinding,
	bool bCanStrafe, bool bStopOnOverlap, bool bAllowPartialPaths, TSubclassOf<UNavigationQueryFilter> FilterClass)
{
	if (WorldContextObject == nullptr)
	{
		if (Pawn != nullptr)
		{
			WorldContextObject = Pawn;
		}
		else
		{
			UE_LOG(LogAIBlueprintV2, Warning, TEXT("Empty (None) world context as well as Pawn passed in while trying to create a MoveTo proxy"));
			return nullptr;
		}
	}
	
	if (Pawn == nullptr)
	{
		// maybe we can extract the pawn from the world context
		const AAIController* AsController = Cast<AAIController>(WorldContextObject);
		if (AsController)
		{
			Pawn = AsController->GetPawn();
		}
	}
	
	if (!Pawn)
	{
		return nullptr;
	}
	
	UAIAsyncTaskBlueprintProxyV2* MyObj = nullptr;
	AAIController* AIController = Cast<AAIController>(Pawn->GetController());
	if (AIController)
	{
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
		MyObj = NewObject<UAIAsyncTaskBlueprintProxyV2>(World);

		FAIMoveRequest MoveReq;
		MoveReq.SetAcceptanceRadius(AcceptanceRadius);
		MoveReq.SetReachTestIncludesAgentRadius(bStopOnOverlap);
		if (TargetActor)
		{
			MoveReq.SetGoalActor(TargetActor);
		}
		else
		{
			MoveReq.SetGoalLocation(Destination);
		}
		MoveReq.SetNavigationFilter(AIController->GetDefaultNavigationFilterClass());

		// V2
		{
			MoveReq.SetUsePathfinding(bUsePathfinding);
			MoveReq.SetCanStrafe(bCanStrafe);
			MoveReq.SetAllowPartialPath(bAllowPartialPaths);
			if (FilterClass)
			{
				// Keep the default if none specified
				MoveReq.SetNavigationFilter(FilterClass);
			}
		}
	
		const FPathFollowingRequestResult ResultData = AIController->MoveTo(MoveReq);
		switch (ResultData.Code)
		{
		case EPathFollowingRequestResult::RequestSuccessful:
			MyObj->AIController = AIController;
			MyObj->AIController->ReceiveMoveCompleted.AddDynamic(MyObj, &UAIAsyncTaskBlueprintProxyV2::OnMoveCompleted);
			MyObj->MoveRequestId = ResultData.MoveId;
			break;
		
		case EPathFollowingRequestResult::AlreadyAtGoal:
			World->GetTimerManager().SetTimer(MyObj->TimerHandle_OnInstantFinish, MyObj, &UAIAsyncTaskBlueprintProxyV2::OnAtGoal, 0.1f, false);
			break;
		
		case EPathFollowingRequestResult::Failed:
		default:
			World->GetTimerManager().SetTimer(MyObj->TimerHandle_OnInstantFinish, MyObj, &UAIAsyncTaskBlueprintProxyV2::OnNoPath, 0.1f, false);
			break;
		}
	}
	return MyObj;
}

#undef LOCTEXT_NAMESPACE