// Fill out your copyright notice in the Description page of Project Settings.

#include "VRDataComponent.h"
#include "GameFramework/Pawn.h"
#include "MotionControllerComponent.h"
#include <String>

// Sets default values for this component's properties
UVRDataComponent::UVRDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVRDataComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("text"));
	owner = Cast<APawn>(GetOwner());
	if (!owner)
	{
		UE_LOG(LogTemp, Error, TEXT("VrDataCollector has no Pawn owner"));
		return;
	}

	// Get components from owner
	LeftHand = owner->FindComponentByClass<UMotionControllerComponent>();
	RightHand = nullptr;

	// If you have multiple MotionControllerComponents, distinguish them:
	TArray<UMotionControllerComponent*> Controllers;
	owner->GetComponents(Controllers);

	for (UMotionControllerComponent* MC : Controllers)
	{
		if (MC->GetTrackingSource() == EControllerHand::Left)
		{
			LeftHand = MC;
		}
		else if (MC->GetTrackingSource() == EControllerHand::Right)
		{
			RightHand = MC;
		}
	}

	ensureMsgf(LeftHand && RightHand, TEXT("Failed to find both VR hands"));
	
}


// Called every frame
void UVRDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVRFrameData newFrameData;

	if (!owner)
	{
		return; // nothing to do
	}

	// Try to find Camera once
	if (!Camera)
	{
		Camera = owner->FindComponentByClass<UCameraComponent>();
		if (!Camera)
		{
			UE_LOG(LogTemp, Warning, TEXT("Camera component not found"));
			return;
		}
	}

	if (!LeftHand || !RightHand)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hands not initialized"));
		return;
	}

	newFrameData.Timestamp = GetWorld()->GetTimeSeconds();

	newFrameData.PlayerPosition = owner->GetActorLocation();
	newFrameData.CameraPosition = Camera->GetComponentLocation();
	newFrameData.LeftHandPosition = LeftHand->GetComponentLocation();
	newFrameData.RightHandPosition = RightHand->GetComponentLocation();

	newFrameData.CameraRotation = Camera->GetComponentRotation();
	newFrameData.LeftHandRotation = LeftHand->GetComponentRotation();
	newFrameData.RightHandRotation = RightHand->GetComponentRotation();

	FString text = newFrameData.PlayerPosition.ToString();
	UE_LOG(LogTemp, Display, TEXT("%s"), *text);

	FrameLog.Add(newFrameData);
}

