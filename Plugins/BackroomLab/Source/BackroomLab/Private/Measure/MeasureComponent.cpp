// Fill out your copyright notice in the Description page of Project Settings.


#include "Measure/MeasureComponent.h"

// Sets default values for this component's properties
UMeasureComponent::UMeasureComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMeasureComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMeasureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMeasureComponent::StartPoint(FVector Location)
{
	StartPointLocation = Location;
	UE_LOG(LogTemp, Display, TEXT("현재 시작 지점 좌표는 (%s) 입니다."), *StartPointLocation.ToString());
}

void UMeasureComponent::CancelMeasurement()
{
	StartPointLocation = FVector::ZeroVector;
	UE_LOG(LogTemp, Warning, TEXT("취소하였습니다. 측정 좌표는 (%s)."), *StartPointLocation.ToString());
}

