// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MeasureComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class BACKROOMLAB_API UMeasureComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeasureComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, Category="Measure Event", meta=(DisplayName = "Spawn Marker"))
	void StartSpawnMarkerEvent(const FVector& SpawnLocation);
	
	// UFUNCTION()
	// void StartPoint(FVector Location);

	UFUNCTION()
	void HandleMeasurePoint(FVector ClickLocation);
	
	void CancelMeasurement();


private:
	FVector StartPointLocation;
	FVector EndPointLocation;
	bool bIsStartPointSet = false;

	FVector FixedLocationZ(const FVector& Location);
	float MeasureDistance(const FVector& Start, const FVector& End);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MeasureMarkerBPClass;
		
};
