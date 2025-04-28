// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeasureManager.generated.h"

class ATestPlayerController;
class UUserWidget;

UCLASS()
class BACKROOMLAB_API AMeasureManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeasureManager();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI Setup")
	TSubclassOf<UUserWidget> MeasureWidget;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="UI Instance", meta = (AllowPrivateAccess = "true"))
	UUserWidget* MeasureWidgetInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Measure")
	bool bIsMeasureMode = false;

	UFUNCTION(BlueprintCallable, Category="Measure")
	void ToggleMeasureMode();
	
	UFUNCTION(BlueprintCallable, Category = "Measure Actions") // BP에서 호출 가능하게!
	void HandleMeasureButtonClick();


	void MeasureClick();
	void UndoMarkerByClick();
	void ClearAllMarkerByClick();

	
};
