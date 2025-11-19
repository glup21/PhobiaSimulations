#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "VRDataCollector.generated.h"

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

};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PHOBIASIMULATIONS_API UVRDataCollector : public UActorComponent
{
	GENERATED_BODY()

public:
	UVRDataCollector();

protected:
	void BeginPlay() override;
    TArray<FVRFrameData> FrameLog;

public:
	void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

    UPROPERTY(EditAnywhere)
	UMotionControllerComponent* LeftHand;

    UPROPERTY(EditAnywhere)
	UMotionControllerComponent* RightHand;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
};
