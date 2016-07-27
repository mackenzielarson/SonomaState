// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownShmup.h"
#include "AssaultWeapon.h"
#include "Engine.h"
#include "DwarfCharacter.h" 

AAssaultWeapon::AAssaultWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Firing = false;
    
}

// Called when the game starts or when spawned
void AAssaultWeapon::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AAssaultWeapon::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    //If firing weapon inflict damage
    if(Firing)
    {
        WeaponTrace();
    }
    
}

void AAssaultWeapon::OnStartFire()
{
    Super::OnStartFire();
    Firing = true;
}

void AAssaultWeapon::OnStopFire()
{
    Super::OnStopFire();
    Firing = false;
    
}

void AAssaultWeapon::WeaponTrace()
{
    static FName WeaponFireTag =FName(TEXT("WeaponTrace"));
    static FName MuzzleSocket =	FName(TEXT("MuzzleFlashSocket"));
    
    //	Start from the muzzle's position
    FVector StartPos =	WeaponMesh->GetSocketLocation(MuzzleSocket);
    //	Get	forward	vector of MyPawn
    FVector Forward = MyPawn->GetActorForwardVector();
    //	Calculate end position using vector math
    FVector EndPos = StartPos + (Forward * WeaponRange);
    
    //	Perform	trace to retrieve hit info
    FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
    TraceParams.bTraceAsyncScene = true;
    TraceParams.bReturnPhysicalMaterial = true;
    
    //	This fires the ray and checks against all objects w/ collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos, FCollisionObjectQueryParams::AllObjects,	TraceParams);
    
    //	Did	this hit anything?
    if (Hit.bBlockingHit)
    {
    //	TODO: Actually do something
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, Hit.ImpactPoint, FRotator(0,0,0));
        ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(Hit.GetActor());
        if (Dwarf)
        {
            Dwarf -> TakeDamage(WeaponDamage, FDamageEvent(), GetInstigatorController(), this);
        }
    }
}
