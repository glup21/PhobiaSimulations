// Fill out your copyright notice in the Description page of Project Settings.

#include "VRDataComponent.h"
#include "GameFramework/Pawn.h"
#include "MotionControllerComponent.h"
#include "UObject/UnrealType.h"

// Sets default values for this component's properties
UVRDataComponent::UVRDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FString LogStruct(const void* StructPtr, UScriptStruct* Struct)
{
	FString Output;

	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		FProperty* Property = *It;
		FString Name = Property->GetNameCPP();

		FString Value;
		Property->ExportText_InContainer(0, Value, StructPtr, StructPtr, nullptr, 0);

		Output += Name + TEXT(": ") + Value + TEXT(" | ");
	}

	return Output;
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
	Camera = owner->FindComponentByClass<UCameraComponent>();
	ensureMsgf(LeftHand && RightHand, TEXT("Failed to find both VR hands"));
	
}


// Called every frame
void UVRDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVRFrameData newFrameData;

	if (!owner)
	{
		return; 
	}

	if (!Camera)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera component not found"));
		return;
	}

	if (!LeftHand || !RightHand)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hands not initialized"));
		return;
	}
	float deltaTime = GetWorld()->GetDeltaSeconds();
	newFrameData.Timestamp = GetWorld()->GetTimeSeconds();

	// Location
	newFrameData.PlayerPosition = owner->GetActorLocation();
	newFrameData.CameraPosition = Camera->GetComponentLocation();
	newFrameData.LeftHandPosition = LeftHand->GetComponentLocation();
	newFrameData.RightHandPosition = RightHand->GetComponentLocation();

	// Rotation
	newFrameData.CameraRotation = Camera->GetComponentRotation();
	newFrameData.LeftHandRotation = LeftHand->GetComponentRotation();
	newFrameData.RightHandRotation = RightHand->GetComponentRotation();

	// Linear velocity
	newFrameData.LeftHandLinearVelocity = LeftHand->GetComponentVelocity();
	newFrameData.RightHandLinearVelocity = RightHand->GetComponentVelocity();
	newFrameData.CameraLinearVelocity = Camera->GetComponentVelocity();

	// Angular velocity
	FRotator LeftDeltaRot = LeftHand->GetComponentRotation() - LastLeftHandRotation;
	FRotator RightDeltaRot = RightHand->GetComponentRotation() - LastRightHandRotation;
	FRotator CameraDeltaRot = Camera->GetComponentRotation() - LastCameraRotation;
	newFrameData.LeftHandAngularVelocity = FVector(LeftDeltaRot.Roll / DeltaTime,
		LeftDeltaRot.Pitch / DeltaTime,
		LeftDeltaRot.Yaw / DeltaTime);
	newFrameData.RightHandAngularVelocity = FVector(RightDeltaRot.Roll / DeltaTime,
		RightDeltaRot.Pitch / DeltaTime,
		RightDeltaRot.Yaw / DeltaTime);
	newFrameData.CameraAngularVelocity = FVector(CameraDeltaRot.Roll / DeltaTime,
		CameraDeltaRot.Pitch / DeltaTime,
		CameraDeltaRot.Yaw / DeltaTime);

	// Misc
	newFrameData.CameraForwardVector = Camera->GetForwardVector();

	FString text = newFrameData.PlayerPosition.ToString();
	UE_LOG(LogTemp, Display, TEXT("%s"), *LogStruct(&newFrameData, FVRFrameData::StaticStruct()));

	FrameLog.Add(newFrameData);
}

