// Fill out your copyright notice in the Description page of Project Settings.

#include "Streaming/StreamingManager.h"

// Sets default values
AStreamingManager::AStreamingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStreamingManager::BeginPlay()
{
	Super::BeginPlay();
}

void AStreamingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
