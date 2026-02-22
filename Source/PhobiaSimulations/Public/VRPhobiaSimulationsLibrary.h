// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VRPhobiaSimulationsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PHOBIASIMULATIONS_API UVRPhobiaSimulationsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="FileManagement")
	static bool SaveJsonToFile(const FString& json, const FString& fileName);
};
