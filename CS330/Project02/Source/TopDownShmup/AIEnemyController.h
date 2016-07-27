// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
	
    virtual void Tick(float DeltaTime) override;
};
