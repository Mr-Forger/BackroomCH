// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab/MeasureManager.h"

#include "TestPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Lab/Measure/MeasureComponent.h"

// Sets default values
AMeasureManager::AMeasureManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMeasureManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("플레이어 컨트롤러가 없습니다."));
	}
	//좌클릭 인풋
	PlayerController->InputComponent->BindAction("MeasureClick", IE_Pressed, this, &AMeasureManager::MeasureClick);

	//모드 진입 바인딩
	PlayerController->InputComponent->BindAction("MeasureToggle", IE_Pressed, this, &AMeasureManager::ToggleMeasureMode);

	PlayerController->InputComponent->BindAction("MeasureCancelClick", IE_Pressed, this, &AMeasureManager::UndoMarkerByClick);
	
	PlayerController->InputComponent->BindAction("ClearAllMarkerByClick", IE_Pressed, this, &AMeasureManager::ClearAllMarkerByClick);
	
	UE_LOG(LogTemp, Warning, TEXT("MeasureManager의 입력 실행."));
}


void AMeasureManager::ToggleMeasureMode()
{
	bIsMeasureMode = !bIsMeasureMode;
	UE_LOG(LogTemp, Display, TEXT("MeasureMode %s"), bIsMeasureMode ? TEXT("On") : TEXT("Off"));

	if (ATestPlayerController* PlayerController = Cast<ATestPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->CurrentMouseCursor = bIsMeasureMode ? EMouseCursor::Crosshairs : EMouseCursor::Default;
	}
}

void AMeasureManager::HandleMeasureButtonClick()
{
	ToggleMeasureMode();
	UE_LOG(LogTemp, Warning, TEXT("측정모드 진입\n"));
}

void AMeasureManager::MeasureClick()
{
	if (!bIsMeasureMode) return;
	
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!MyPawn) return;
	
	if (UMeasureComponent* MeasureComponent = MyPawn->FindComponentByClass<UMeasureComponent>())
	{
		MeasureComponent->StartLineTrace();
	}
}

void AMeasureManager::UndoMarkerByClick()
{
	if (!bIsMeasureMode) return;

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!MyPawn) return;

	if (UMeasureComponent* MeasureComponent = MyPawn->FindComponentByClass<UMeasureComponent>())
	{
		MeasureComponent->ClearLastSpawnMarker();
	}
}

void AMeasureManager::ClearAllMarkerByClick()
{
	if (!bIsMeasureMode) return;

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!MyPawn) return;

	if (UMeasureComponent* MeasureComponent = MyPawn->FindComponentByClass<UMeasureComponent>())
	{
		MeasureComponent->ClearAllMarker();
	}
}


