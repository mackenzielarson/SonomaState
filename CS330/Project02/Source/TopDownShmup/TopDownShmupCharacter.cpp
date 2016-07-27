// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.


#include "TopDownShmup.h"
#include "DwarfCharacter.h"
#include "Engine.h"
#include "TopDownShmupCharacter.h"
#include "TopDownShmupPlayerController.h"


ATopDownShmupCharacter::ATopDownShmupCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    //Set the initial countdown time
    CountdownTime = 1;
    
}


void ATopDownShmupCharacter::BeginPlay()
{
    
    
    //	Call	base	class	BeginPlay
    Super::BeginPlay();
    
    //Set Up Timer
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATopDownShmupCharacter::AdvanceTimer, 1.0f, true);
 
    //	Spawn	the	weapon,	if	one	was	specified
    if (WeaponClass)
    {
        UWorld*	World =	GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner =	this;
            SpawnParams.Instigator = Instigator;
            //	Need to	set	rotation like this because otherwise gun points	down
            //	NOTE: This should probably be a	blueprint parameter
            FRotator Rotation(0.0f,	0.0f, -90.0f);
            //	Spawn the Weapon
            MyWeapon =	World->SpawnActor<AWeapon>(WeaponClass,	FVector::ZeroVector, Rotation, SpawnParams);
            if (MyWeapon)
            {
                //	This is	attached to	"WeaponPoint" which is defined in	the	skeleton
                //	NOTE: This should probably be a blueprint parameter
                MyWeapon->WeaponMesh->AttachTo(GetMesh(), TEXT("WeaponPoint"));
                //Attach weapon
                APawn* const Pawn = Cast<APawn>(this);
                if (Pawn)
                {
                    MyWeapon->MyPawn = Pawn;
                }

            }
        }
    }
}

void ATopDownShmupCharacter::AdvanceTimer()
{
    //If the player dies, start timer and deactivate his mesh as he is dying
    //if he is in death animation it will freeze him
    if ( PlayerDied == true)
    {
        --CountdownTime;
        if (CountdownTime < 1)
        {
            // We're done counting down, so stop running the timer.
            GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
           //Deactivate Mesh
            Mesh -> Deactivate(); 
        }
    }
}

void ATopDownShmupCharacter::OnStartFire()
{
    MyWeapon->OnStartFire();
    Firing = true;
}

void ATopDownShmupCharacter::OnStopFire()
{
    MyWeapon->OnStopFire();
    Firing = false;
}

bool ATopDownShmupCharacter::IsDead()
{
    return PlayerDied; 
}

float ATopDownShmupCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    //Take damage
    float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    if (ActualDamage >	0.0f)
    {
        //Track damage... if damage is less than 0 then you died!
        PlayerHealth -= ActualDamage;
        if (PlayerHealth <= 0.0f)
        {
            // Player is dead
            bCanBeDamaged =	false;	//	Don't	allow	further	damage
            
            //stop firing weapon
            MyWeapon->OnStopFire();
            
            //play the death animation
            PlayAnimMontage(PlayerDeath);
           
            //Stop the player from moving if he is dead (set ignore movement / input to true)
            ATopDownShmupPlayerController* ifdeadmovement = Cast<ATopDownShmupPlayerController>(GetController());
            ifdeadmovement->SetIgnoreLookInput(true);
            ifdeadmovement->SetIgnoreMoveInput(true);
            
            PlayerDied = true;
            
        }
    }
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Player Health: %f"), PlayerHealth));
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Dwarf Damage Inflicted: %f"), ActualDamage));
    return ActualDamage;
}