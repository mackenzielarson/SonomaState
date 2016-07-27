// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmup.h"
#include "TopDownShmupPlayerController.h"
#include "TopDownShmupCharacter.h"
#include "AI/Navigation/NavigationSystem.h"

ATopDownShmupPlayerController::ATopDownShmupPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownShmupPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

    UpdateMouseLook();
	
}

void ATopDownShmupPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

    //Fire
    InputComponent->BindAction("Fire", IE_Pressed, this, &ATopDownShmupPlayerController::OnStartFire);
    InputComponent->BindAction("Fire", IE_Released, this, &ATopDownShmupPlayerController::OnStopFire);
    
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATopDownShmupPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATopDownShmupPlayerController::MoveToTouchLocation);
    
    //WASD controlls
    InputComponent->BindAxis("MoveForward", this, &ATopDownShmupPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ATopDownShmupPlayerController::MoveRight);
}

//Turn the player to look at the mouse location
void ATopDownShmupPlayerController::UpdateMouseLook()
{
    //Do nothing if the player is dead-- do not allow the player to rotate to look at the mouse
    //If this is true it was set in Character.cpp when you died
    if(IsLookInputIgnored() && IsMoveInputIgnored())
    {
        //Do nothing
    }
    //If you are alive, turn to look at the mouse
    else
    {
        APawn* const Pawn = GetPawn();
        FHitResult Hit;
        if(Pawn)
        {
            GetHitResultUnderCursor(ECC_Visibility, false, Hit);
        }
        if(Hit.bBlockingHit)
        {
            FVector getDistance = Hit.ImpactPoint - Pawn->GetActorLocation();
            getDistance.Z = 0.0f;
            getDistance.Normalize();
            FRotator getRotation = getDistance.Rotation();
            Pawn->SetActorRotation(getRotation);
        }
    }
}

//Movement WASD
//If Value is non-zero it tells the player to move along the global forward vector (along the x axis)
void ATopDownShmupPlayerController::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        APawn* const Pawn =	GetPawn();
        if (Pawn)
        {
            Pawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
        }
    }
}

//If Value is non-zero it tells the player to move along the global forward vector (along the y axis)
void ATopDownShmupPlayerController::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        APawn* const Pawn =	GetPawn();
        if (Pawn)
        {
            Pawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
        }
    }
}

void ATopDownShmupPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ATopDownShmupPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ATopDownShmupPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATopDownShmupPlayerController::OnStartFire()
{
    ATopDownShmupCharacter* Character = Cast<ATopDownShmupCharacter>(GetPawn());
    if(Character)
    {
        //If the player is NOT dead, fire the weapon.
        //If the player is dead, do NOT fire the weapon
        if(!Character->IsDead())
        {
            Character->GetWeapon()->OnStartFire();
        }
    }

}

void ATopDownShmupPlayerController::OnStopFire()
{
    ATopDownShmupCharacter* Character = Cast<ATopDownShmupCharacter>(GetPawn());
    if(Character)
    {
        //If the player is NOT dead, fire the weapon.
        //If the player is dead, do NOT fire the weapon
        if(!Character->IsDead())
        {
            Character->GetWeapon()->OnStopFire();
        }
    }
}

