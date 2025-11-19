// Fill out your copyright notice in the Description page of Project Settings.


#include "VRDataCollector.h"

UVRDataCollector::UVRDataCollector()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UVRDataCollector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UVRDataCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVRFrameData newFrameData;
	AActor* owner = GetOwner();
	newFrameData.Timestamp = GetWorld()->GetTimeSeconds();
	
	newFrameData.PlayerPosition = owner->GetActorLocation();
	newFrameData.CameraPosition = Camera->GetComponentLocation();
	newFrameData.LeftHandPosition = LeftHand->GetComponentLocation();
	newFrameData.RightHandPosition = RightHand->GetComponentLocation();

	newFrameData.CameraRotation = Camera->GetComponentRotation();
	newFrameData.LeftHandRotation = LeftHand->GetComponentRotation();
	newFrameData.RightHandRotation = RightHand->GetComponentRotation();


	FrameLog.Add(newFrameData);
}

