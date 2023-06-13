// Copyright (c) Jared Taylor. All Rights Reserved


#include "AIAsyncTaskBlueprintProxyV2.h"

#define LOCTEXT_NAMESPACE "AIAsyncTaskProxyV2"

//----------------------------------------------------------------------//
// UAIAsyncTaskBlueprintProxyV2
//----------------------------------------------------------------------//

UAIAsyncTaskBlueprintProxyV2::UAIAsyncTaskBlueprintProxyV2(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MyWorld = Cast<UWorld>(GetOuter());
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		SetFlags(RF_StrongRefOnFrame);
	}
}

void UAIAsyncTaskBlueprintProxyV2::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult)
{
	if (RequestID.IsEquivalent(MoveRequestId) && AIController.IsValid(true))
	{
		AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UAIAsyncTaskBlueprintProxyV2::OnMoveCompleted);

		if (MovementResult == EPathFollowingResult::Success)
		{
			OnSuccess.Broadcast(MovementResult);
		}
		else
		{
			OnFail.Broadcast(MovementResult);
		}
	}
}

void UAIAsyncTaskBlueprintProxyV2::OnNoPath()
{
	OnFail.Broadcast(EPathFollowingResult::Aborted);
}

void UAIAsyncTaskBlueprintProxyV2::OnAtGoal()
{
	OnSuccess.Broadcast(EPathFollowingResult::Success);
}

#undef LOCTEXT_NAMESPACE