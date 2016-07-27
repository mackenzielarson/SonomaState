// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VoyagerPawnMovementComponent.h"
#include "MyActorToSpawn.generated.h"

UCLASS()
class PROJECT0119_API AMyActorToSpawn : public AActor
{
	GENERATED_BODY()
    
   	UStaticMeshComponent* SphereComponent;
    
public:	
	// Sets default values for this actor's properties
	AMyActorToSpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    void PlanetCase(int NumberPlanet);
    
    FVector SphereVisualLocation;
	
};
