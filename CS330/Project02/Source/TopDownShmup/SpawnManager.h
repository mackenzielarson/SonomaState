// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DwarfCharacter.h"
#include "SpawnManager.generated.h"

UCLASS()
class TOPDOWNSHMUP_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    //All in SPAWN CATEGORY
    
    //Used for specifiying the target points
    UPROPERTY(EditAnywhere, Category = Spawn)
    TArray<ATargetPoint*> SpawningPoints;
    
    //Used for specifiying the character to spawn
    UPROPERTY(EditAnywhere, Category = Spawn)
    TSubclassOf<class ACharacter> WhatToSpawn;
    
    UPROPERTY(EditAnywhere, Category = Spawn)
    float MinTime;
    
    UPROPERTY(EditAnywhere, Category = Spawn)
    float MaxTime;
    
    void DwarfSpawn();
    
    float Time;
    
    FTimerHandle RandomTimerHandle;

	
	
};
