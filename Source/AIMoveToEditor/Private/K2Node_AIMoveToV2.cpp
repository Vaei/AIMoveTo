// Copyright Epic Games, Inc. All Rights Reserved.

#include "K2Node_AIMoveToV2.h"

#include "AIBlueprintHelperLibraryV2.h"
#include "EditorCategoryUtils.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"

#define LOCTEXT_NAMESPACE "K2Node_AIMoveToV2"

UK2Node_AIMoveToV2::UK2Node_AIMoveToV2(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProxyFactoryFunctionName = GET_FUNCTION_NAME_CHECKED(UAIBlueprintHelperLibraryV2, CreateMoveToV2ProxyObject);
	ProxyFactoryClass = UAIBlueprintHelperLibraryV2::StaticClass();
	ProxyClass = UAIAsyncTaskBlueprintProxy::StaticClass();
}

FText UK2Node_AIMoveToV2::GetTooltipText() const
{
	return LOCTEXT("AIMoveToV2_Tooltip", "Order for Pawn with AIController to move to a specific location. Extra options over AI MoveTo.");
}

FText UK2Node_AIMoveToV2::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("AIMoveToV2", "AI MoveTo V2");
}

FText UK2Node_AIMoveToV2::GetMenuCategory() const
{
	return FEditorCategoryUtils::GetCommonCategory(FCommonEditorCategory::AI);
}

#undef LOCTEXT_NAMESPACE
