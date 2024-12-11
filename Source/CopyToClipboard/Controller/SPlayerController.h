// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COPYTOCLIPBOARD_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool MockCopyImage();
	UFUNCTION(BlueprintCallable)
	bool MockCopyTexture();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	UTexture2D* texture;
};
