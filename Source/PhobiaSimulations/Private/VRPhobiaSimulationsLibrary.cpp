// Fill out your copyright notice in the Description page of Project Settings.
#include <iostream>
#include <fstream> 

#include "VRPhobiaSimulationsLibrary.h"

bool UVRPhobiaSimulationsLibrary::SaveJsonToFile(const FString& json, const FString& fileName)
{
	//FString TextToSave = TEXT("Hello Unreal");
	FString FilePath = FPaths::ProjectSavedDir() + fileName;

	return FFileHelper::SaveStringToFile(json, *FilePath);
}