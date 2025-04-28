// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackroomManager.generated.h"

class AMeasureManager;

UCLASS()
class BACKROOMLAB_API ABackroomManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackroomManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Measure Setup")
	TSubclassOf<AMeasureManager> MeasureManagerSpawnClass;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Manager Instance", meta=(AllowPrivateAccess= "true"))
	AMeasureManager* SpawnMeasureManagerInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
