// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownShmup.h"
#include "TopDownShmupCharacter.h" 
#include "Weapon.h"
#include "Engine.h"
#include "ParticleDefinitions.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
    
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWeapon::OnStartFire()
{
    ShotFired = true;
    //When the weapon is firing, play the sound and shoot the gun! (flash the particle) 
    FireAC = PlayWeaponSound(FireLoopSound);
    MuzzleFlash = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, RootComponent, TEXT("MuzzleFlashSocket"), FVector(0,0,0), FRotator(0,0,0), EAttachLocation::KeepRelativeOffset, false);
}

void AWeapon::OnStopFire()
{
    if (ShotFired)
    {
        //When the weapon is called to stop firing, deactivate the sound and the particle effect (muzzle flash)
        FireAC->Deactivate();
        PlayWeaponSound(FireFinishSound);
        MuzzleFlash->DeactivateSystem();
    }
}

//How to play the sound when it is called
UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound)
{
    UAudioComponent* AC=NULL;
    if (Sound)
    {
        AC = UGameplayStatics::PlaySoundAttached(Sound,	RootComponent);
    }
    return AC;
}