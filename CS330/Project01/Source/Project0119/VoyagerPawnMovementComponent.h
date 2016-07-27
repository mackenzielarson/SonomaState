// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "VoyagerPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT0119_API UVoyagerPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
    
    
public:
    
    UVoyagerPawnMovementComponent();
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
    
    UPROPERTY(EditAnywhere, Category = "VOYAGER VELOCITY")
    float VoyagerVelocity;
	
	
};
