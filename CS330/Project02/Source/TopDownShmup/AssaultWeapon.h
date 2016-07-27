// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "AssaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAssaultWeapon : public AWeapon
{
	GENERATED_BODY()
    
    AAssaultWeapon();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
	
    virtual void OnStartFire() override;
    virtual void OnStopFire() override;
	
	UPROPERTY(EditAnywhere)
    float FireRate = 0.05f;
    
    UPROPERTY(EditAnywhere)
    float WeaponRange = 10000.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = Effects)
    UParticleSystem* HitFX;
    
    bool Firing;
    
protected:
    void WeaponTrace();
};
