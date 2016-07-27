// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIEnemyController.h"
#include "TopDownShmupCharacter.h"
#include "DwarfCharacter.h" 
#include "AIDwarfController.generated.h"


enum class StateMachine : short
{
    Start,
    Chase,
    Attack,
    Dead
};

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAIDwarfController : public AAIEnemyController
{
	GENERATED_BODY()
	
public:
    
    AAIDwarfController();
    
    virtual void Tick(float DeltaSeconds) override;
    
    virtual void BeginPlay() override;
    
    StateMachine GetCurrentState() const;
    
    void SetCurrentState(StateMachine NewState);

    FVector DwarfLocation;
    FVector PlayerLocation;
    float DwarfPlayerDistance;
    
    ADwarfCharacter* Dwarf;
    ATopDownShmupCharacter* Player;
    
    bool Attack;
    
private:
    StateMachine CurrentState;
    void HandleNewState(StateMachine NewState);
};


FORCEINLINE StateMachine AAIDwarfController::GetCurrentState() const
{
    return CurrentState;
}

