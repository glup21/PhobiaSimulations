// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "VRDataComponent.generated.h"

class UMotionControllerComponent;

USTRUCT(BlueprintType)
struct FVRFrameData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float Timestamp;

	UPROPERTY()
	FVector PlayerPosition;

	UPROPERTY()
	FVector CameraPosition;

	UPROPERTY()
	FVector LeftHandPosition;

	UPROPERTY()
	FVector RightHandPosition;

	UPROPERTY()
	FRotator CameraRotation;

	UPROPERTY()
	FRotator LeftHandRotation;

	UPROPERTY()
	FRotator RightHandRotation;

	UPROPERTY()
	FVector LeftHandLinearVelocity;

	UPROPERTY()
	FVector RightHandLinearVelocity;

	UPROPERTY()
	FVector CameraLinearVelocity;

	UPROPERTY()
	FVector LeftHandAngularVelocity;

	UPROPERTY()
	FVector RightHandAngularVelocity;

	UPROPERTY()
	FVector CameraAngularVelocity;

	UPROPERTY()
	FVector CameraForwardVector;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOBIASIMULATIONS_API UVRDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRDataComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	APawn* owner;

	FRotator LastLeftHandRotation;
	FRotator LastRightHandRotation;
	FRotator LastCameraRotation;

public:	
	TArray<FVRFrameData> FrameLog;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	UMotionControllerComponent* LeftHand;
	//FComponentReference LeftHand;

	UPROPERTY(EditAnywhere)
	UMotionControllerComponent* RightHand;
	//FComponentReference RightHand;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
};
