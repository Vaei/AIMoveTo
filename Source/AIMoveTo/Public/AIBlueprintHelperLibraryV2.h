// Copyright (c) Jared Taylor. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIBlueprintHelperLibraryV2.generated.h"

/**
 * This is performed in this manner instead of creating a new node specifically because the UAISystem tracks
 * UAIAsyncTaskBlueprintProxy nodes and because UAIAsyncTaskBlueprintProxy is not exported and cannot be subclassed
 * @see UAISystem::AddReferenceFromProxyObject
 * @see UAISystem::RemoveReferenceToProxyObject
 */
UCLASS(meta=(ScriptName="AIHelperLibraryV2"))
class AIMOVETO_API UAIBlueprintHelperLibraryV2 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly = "TRUE"))
	static UAIAsyncTaskBlueprintProxy* CreateMoveToV2ProxyObject(
		UObject* WorldContextObject,
		APawn* Pawn,
		FVector Destination,
		AActor* TargetActor = nullptr,
		float AcceptanceRadius = 5.f,
		bool bUsePathfinding = true,
		bool bCanStrafe = true,
		bool bStopOnOverlap = false,
		bool bAllowPartialPaths = false,
		TSubclassOf<UNavigationQueryFilter> FilterClass = nullptr);
};
