// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Measure/MeasureComponent.h"

ATestPlayerController::ATestPlayerController()
{
	
}

void ATestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("LookUp", this, &ATestPlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &ATestPlayerController::Turn);
	InputComponent->BindAction("MeasureClick", IE_Pressed, this, &ATestPlayerController::MeasureClick);
	InputComponent->BindAction("MeasureCancelClick", IE_Pressed, this, &ATestPlayerController::MeasureCancelClick);
	InputComponent->BindAction("ClearAllMarkerByClick", IE_Pressed, this, &ATestPlayerController::ClearAllMarkerByClick);
}

void ATestPlayerController::LookUp(float Value)
{
	AddPitchInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ATestPlayerController::Turn(float Value) 
{
	AddYawInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ATestPlayerController::MeasureClick()
{
	bIsMeasureMode = true;
	UE_LOG(LogTemp, Display, TEXT("마우스 왼쪽 버튼 클릭으로 함수가 실행 됩니다!"));
	UE_LOG(LogTemp, Display, TEXT("부울 변수의 현재 상태는: %s"), bIsMeasureMode ? TEXT("true") : TEXT("false"));

	if (!bIsMeasureMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("측정 모드가 아닙니다."));
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("측정 모드 입니다"))
	
	APawn* MyPawn = GetPawn(); // 조종 중인 폰 찾기
	if (MyPawn != nullptr) // 폰이 널포인터가 아니면 = 폰이 있으면
	{
		UMeasureComponent* MeasureComponent = MyPawn->FindComponentByClass<UMeasureComponent>();
		if (MeasureComponent != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("MeasureComponent를 찾았습니다.(%s)"), *MeasureComponent->GetName());
			MeasureComponent->StartLineTrace();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MeasureComponent를 못찾았습니다!"));
		}
	}
}

void ATestPlayerController::MeasureCancelClick()
{
	bIsMeasureMode = false;

	APawn* MyPawn = GetPawn();
	if (MyPawn != nullptr)
	{
		UMeasureComponent* MeasureComponent = MyPawn->FindComponentByClass<UMeasureComponent>();
		if (MeasureComponent != nullptr)
		{
			MeasureComponent->ClearLastSpawnMarker();
		}
	}
}

void ATestPlayerController::ClearAllMarkerByClick()
{
	UE_LOG(LogTemp, Warning, TEXT("마커 삭제를 시작합니다."));
	UMeasureComponent* MeasureComponent = GetPawn()->FindComponentByClass<UMeasureComponent>();
	MeasureComponent->ClearAllMarker();
	
	
}
