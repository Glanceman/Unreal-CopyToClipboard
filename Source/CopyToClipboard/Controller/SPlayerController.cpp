// Fill out your copyright notice in the Description page of Project Settings.


#include "./SPlayerController.h"
#include "../BlueprintFunctionLibrary/STool.h"

void ASPlayerController::MockCopyImage()
{
	int32 width = 256;
	int32 height = 256;
	TArray<FColor> imageData;
	imageData.SetNum(width * height);

	for (int32 i = 0; i < imageData.Num();i++) {
		imageData[i] = FColor::Red;
	}

	USTool::CopyImageToClipboard(width, height, imageData);
}

void ASPlayerController::MockCopyTexture()
{
	if (IsValid(texture)) {
		USTool::CopyImageToClipboard(texture);
	}

}
