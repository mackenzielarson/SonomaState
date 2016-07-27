// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TopDownShmupCharacter.h" 
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Weapon.generated.h"

UCLASS()
class TOPDOWNSHMUP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Weapon)
    USkeletalMeshComponent* WeaponMesh;
	
    virtual void OnStartFire();
    virtual void OnStopFire();
    
    UPROPERTY(EditDefaultsOnly, Category=Sound)
    USoundCue* FireLoopSound;
    
    UPROPERTY(EditDefaultsOnly, Category=Sound)
    USoundCue* FireFinishSound;
    
    UPROPERTY(EditDefaultsOnly, Category = Effects)
    UParticleSystem* MuzzleFX;
    
    APawn* MyPawn;
    
    UPROPERTY(EditAnywhere)
    float WeaponDamage = 2;
    
    bool ShotFired; 

protected:
    UPROPERTY(Transient)
    UAudioComponent* FireAC;
    
    UPROPERTY(Transient)
    UParticleSystemComponent* MuzzleFlash;
    
    UAudioComponent* PlayWeaponSound(USoundCue* Sound);
};
