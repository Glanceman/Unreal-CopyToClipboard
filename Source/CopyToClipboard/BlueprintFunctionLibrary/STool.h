// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STool.generated.h"

/**
 * 
 */
UCLASS()
class COPYTOCLIPBOARD_API USTool : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static void CopyImageToClipboard(const int32 width, const int32 height, const TArray<FColor>& ImageData);


	static void CopyImageToClipboard(UTexture2D* texture2d);
};
