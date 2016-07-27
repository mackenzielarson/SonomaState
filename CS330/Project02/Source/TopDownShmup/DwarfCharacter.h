// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "DwarfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API ADwarfCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
    ADwarfCharacter();
    
    virtual void BeginPlay() override;
    
    virtual void Tick( float DeltaSeconds) override; 
    
    FTimerHandle CountdownTimerHandle;
    FTimerHandle CountdownTimerHandle2;
    
    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* AttackAnim;

    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* DeathAnim;
    
    virtual void StartAttack();
    virtual void StopAttack();
    virtual void Death(); 
	
    void AdvanceTimer();
    
    UPROPERTY(EditAnywhere)
    float DwarfHealth = 50;
    
    UPROPERTY(EditAnywhere)
    float DwarfDamage = 10;
    
    float TakeDamage(float Damage,	struct FDamageEvent const&	DamageEvent, AController*	EventInstigator,	AActor*	DamageCauser) override;
    
    bool Attack; 

    bool DieNow = false;
    bool DestroyNow; 
    
    int32 CountdownTime;
    
    int32 CountdownTime2;
    
    bool DwarfIsDead(); 
    bool DwarfDied = false;
    
};
