// Copyright (c) Jared Taylor. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "UObject/Object.h"
#include "AIAsyncTaskBlueprintProxyV2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOAISimpleDelegateV2, EPathFollowingResult::Type, MovementResult);

/**
 * This is necessary only because UAIAsyncTaskBlueprintProxy is exported with MinimalAPI but nothing to export
 * the functions and therefore cannot be bound to.
 * This node is not tracked via UAISystem
 * @see UAISystem::AddReferenceFromProxyObject
 * @see UAISystem::RemoveReferenceToProxyObject
 */
UCLASS()
class AIMOVETO_API UAIAsyncTaskBlueprintProxyV2 : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FOAISimpleDelegateV2	OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOAISimpleDelegateV2	OnFail;

public:
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult);

	void OnNoPath();
	void OnAtGoal();

	TWeakObjectPtr<AAIController> AIController;
	FAIRequestID MoveRequestId;
	TWeakObjectPtr<UWorld> MyWorld;

	FTimerHandle TimerHandle_OnInstantFinish;
};
