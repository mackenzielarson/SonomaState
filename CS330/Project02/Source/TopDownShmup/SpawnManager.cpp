// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownShmup.h"
#include "SpawnManager.h"
#include "DwarfCharacter.h" 

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
    
    //Let's spawn some dwarves!
    DwarfSpawn();
    
    //Randomly select a time beween the min and max that is set in unreal and set the timer accordingly
    Time = FMath::RandRange(MinTime, MaxTime);
    GetWorldTimerManager().SetTimer(RandomTimerHandle,Time,false);
}

// Called every frame
void ASpawnManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    //As time has elapsed, reset the timer and spawn another dwarf from a different location (target point)
    if(GetWorldTimerManager().GetTimerElapsed(RandomTimerHandle) >= Time - 0.1)
    {
        Time = FMath::RandRange(MinTime, MaxTime);
        GetWorldTimerManager().SetTimer(RandomTimerHandle, Time, false);
        DwarfSpawn();
    }

}

void ASpawnManager::DwarfSpawn()
{
    // Check for a valid World:
    UWorld* const World = GetWorld();
    if (World)
    {
        // Set the spawn parameters
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;
        
        // Get a rotation for the spawned item at the target location (rotation will fix itself in the world)
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        
        //This is where we will randomly select a target to spawn the new dwarf from
        //Spawning points are the target points LOL 
        float RandomSpawn = FMath::RandRange(0, SpawningPoints.Num() - 1);
        ATargetPoint* TARGET = SpawningPoints[RandomSpawn];

        // Spawn the dwarf into the world based on the information above and the set libraries from Unreal
        ADwarfCharacter* Dwarf = World->SpawnActor<ADwarfCharacter>(WhatToSpawn, TARGET->GetActorLocation(), Rotation, SpawnParams);
        if (Dwarf)
        {
            Dwarf->SpawnDefaultController();
        }

    }

}