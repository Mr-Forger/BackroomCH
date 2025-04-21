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

// void UMeasureComponent::StartPoint(FVector Location)
// {
// 	StartPointLocation = Location;
// 	UE_LOG(LogTemp, Display, TEXT("현재 시작 지점 좌표는 (%s) 입니다."), *StartPointLocation.ToString());
// 	bIsStartPointSet = true;
// }


void UMeasureComponent::HandleMeasurePoint(FVector ClickLocation)
{
	if (!bIsStartPointSet) // 초기 값이 false가 true로 바뀌니까 조건문 실행
	{
		StartPointLocation = ClickLocation;
		UE_LOG(LogTemp, Warning, TEXT("첫 번째 좌표 설정 완료 좌표는 (%s)"), *StartPointLocation.ToString());
		bIsStartPointSet = true;
	}
	else
	{
		EndPointLocation = ClickLocation;
		UE_LOG(LogTemp, Warning, TEXT("두 번째 좌표 설정 완료. 좌표는 (%s)"), *EndPointLocation.ToString());
		UE_LOG(LogTemp, Display, TEXT("두 번째 좌표 Z축을 고정합니다."));
		EndPointLocation = FixedLocationZ(EndPointLocation);
		UE_LOG(LogTemp, Warning, TEXT("변경된 두 번째 좌표는 (%s)"), *EndPointLocation.ToString());
		float Distance = MeasureDistance(StartPointLocation, EndPointLocation);
		UE_LOG(LogTemp, Display, TEXT("두 좌표 사이의 거리는 %fcm 입니다."), Distance);
		bIsStartPointSet = false;
	}
}

void UMeasureComponent::CancelMeasurement()
{
	StartPointLocation = FVector::ZeroVector;
	EndPointLocation = FVector::ZeroVector;
	UE_LOG(LogTemp, Warning, TEXT("측정을 취소하고 모든 상태를 초기화했습니다."));
	bIsStartPointSet = false;
}

FVector UMeasureComponent::FixedLocationZ(const FVector& Location)
{
	FVector NewLocation = Location;
	NewLocation.Z = StartPointLocation.Z;
	return NewLocation;
	
	
}

float UMeasureComponent::MeasureDistance(const FVector& Start, const FVector& End)
{
	float Distance = FVector::Dist(Start, End);
	return Distance;
}

