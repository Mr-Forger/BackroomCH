// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab/Measure/MeasureComponent.h"

#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UMeasureComponent::UMeasureComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	StartPointLocation = FVector::ZeroVector;
	EndPointLocation = FVector::ZeroVector;

	// ...
}


// Called when the game starts
void UMeasureComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMeasureComponent::StartLineTrace()
{
	UE_LOG(LogTemp, Warning, TEXT("라인 트레이스"));
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwnerPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("소유 중인 폰을 찾을 수 없습니다"));
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	if (!IsValid(PlayerController)) return;
	
	FHitResult HitResult;

	bool bHitSuccess = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);
	if (bHitSuccess)
	{
		UE_LOG(LogTemp, Display, TEXT("라인 트레이스 성공! 위치는: %s"), *HitResult.Location.ToString());
		HandleMeasurePoint(HitResult.Location);
	}
	else
	{
			UE_LOG(LogTemp, Warning, TEXT("라인 트레이스 실패"));
	}
}

//가장 마지막에 찍은 마커 제거 후 좌표 초기화
void UMeasureComponent::ResetMeasureState()
{
	StartPointLocation = FVector::ZeroVector;
	EndPointLocation = FVector::ZeroVector;
	bIsStartPointSet = false;
	UE_LOG(LogTemp, Warning, TEXT("측정을 다시 시작해주세요."));
}


//가장 마지막에 찍은 마커 제거
void UMeasureComponent::ClearLastSpawnMarker()
{
	UE_LOG(LogTemp, Display, TEXT("측정 취소 요청"));
	const FName MarkerTag = FName("MeasureMarker");
	TArray<AActor*> SpawnedMarkers;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MarkerTag, SpawnedMarkers);
	if (bIsStartPointSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("시작점만 찍혔습니다. 삭제 가능"));
		ResetMeasureState();

		if (SpawnedMarkers.Num() > 0)
		{
			SpawnedMarkers[SpawnedMarkers.Num() - 1]->Destroy();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("시작점이 없거나 측정 완료 상태입니다."));
	}
}

void UMeasureComponent::ClearAllMarker()
{
	const FName MarkerTag = FName("MeasureMarker");
	
	TArray<AActor*> FoundMarkers;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MarkerTag, FoundMarkers);
	
	UE_LOG(LogTemp, Warning, TEXT("태그 '%s'를 가진 마커 %d개 찾음"), *MarkerTag.ToString(), FoundMarkers.Num());
	if (FoundMarkers.Num() > 0)
	{
		for (AActor* Marker : FoundMarkers)
		{
			if (Marker != nullptr)
			{
				Marker->Destroy();
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("마커 제거 완료"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("월드에 태그 '%s'를 가진 마커가 없습니다."), *MarkerTag.ToString());
	}
}


// Called every frame
void UMeasureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// 좌표 설정 및 로직 계산
void UMeasureComponent::HandleMeasurePoint(FVector ClickLocation)
{
	if (!bIsStartPointSet) // 초기 값이 false가 true로 바뀌니까 조건문 실행
	{
		StartPointLocation = ClickLocation;
		UE_LOG(LogTemp, Warning, TEXT("첫 번째 좌표 설정 완료 좌표는 (%s)"), *StartPointLocation.ToString());
		StartSpawnMarkerEvent(StartPointLocation);
		bIsStartPointSet = true;
	}
	else
	{
		EndPointLocation = ClickLocation;
		UE_LOG(LogTemp, Warning, TEXT("두 번째 좌표 설정 완료. 좌표는 (%s)"), *EndPointLocation.ToString());
		UE_LOG(LogTemp, Display, TEXT("두 번째 좌표 Z축을 고정합니다."));
		EndPointLocation = FixedLocationZ(EndPointLocation);
		
		StartSpawnMarkerEvent(EndPointLocation);
		
		UE_LOG(LogTemp, Warning, TEXT("변경된 두 번째 좌표는 (%s)"), *EndPointLocation.ToString());
		float Distance = MeasureDistance(StartPointLocation, EndPointLocation);
		UE_LOG(LogTemp, Display, TEXT("두 좌표 사이의 거리는 %fcm 입니다."), Distance);
		bIsStartPointSet = false;
	}
}

// Z축 고정 연산
FVector UMeasureComponent::FixedLocationZ(const FVector& Location)
{
	FVector NewLocation = Location;
	NewLocation.Z = StartPointLocation.Z;
	return NewLocation;
	
	
}

// 두 좌표(마커) 사이의 거리 연산 - 꼭 FixedLocationZ 함수 실행 후 이 함수가 실행되어야 한다.
float UMeasureComponent::MeasureDistance(const FVector& Start, const FVector& End)
{
	float Distance = FVector::Dist(Start, End);
	return Distance;
}


/** 응가
{
	int poop =  this is dirty thing what come out from JaeMin Choi asshole in Every day.
}
*/ 
