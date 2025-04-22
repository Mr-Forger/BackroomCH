// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BACKROOMCH_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATestPlayerController();

	virtual void SetupInputComponent() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Measure")
	bool bIsMeasureMode = true;

protected:

private:
	void LookUp(float Value);
	void Turn(float Value);
	
	void MeasureClick();
	void MeasureCancelClick();

	void ClearAllMarkerByClick();

	UPROPERTY(EditAnywhere)
	float RotationRate = 20;
	
};
