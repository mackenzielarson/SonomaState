// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownShmup.h"
#include "AIDwarfController.h"
#include "TopDownShmupCharacter.h"
#include "AIEnemyController.h"
#include "DwarfCharacter.h"
#include "Engine.h"


AAIDwarfController::AAIDwarfController()
{
    
}

void AAIDwarfController::BeginPlay()
{
    Super::BeginPlay();
    
    //Call the player
    Player = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
    
    //Set the dwarf into start mode
    SetCurrentState(StateMachine::Start);
    
    //move toward the player
    this->MoveToActor(Player);
}

void AAIDwarfController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    //Debug statements to check the player to dwarf distance
    //DwarfPlayerDistance = FVector::Dist(PlayerLocation, DwarfLocation);
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("distance: %f"), DwarfPlayerDistance));
    
    //Call the dwarf
    APawn* const Pawn = GetPawn();
    if(Pawn)
    {
        Dwarf = Cast<ADwarfCharacter>(Pawn);
        
        //If the distance between the dwarf and player is < 150 attack!
        if(FVector::Dist(Player->GetActorLocation(),Pawn->GetActorLocation()) < 150.0)
        {
            //Set up so that the attack animation will loop properly
            if(Attack != true){
                SetCurrentState(StateMachine::Attack);
                Attack = true;
            }
        }
        
        //If the distance between the dwarf and the player is > 150 chase the player
        else
        {
            SetCurrentState(StateMachine::Chase);
            Attack = false;
        }
        
        //If the dwarf is dead begin the death state
        if(Dwarf->DwarfIsDead())
        {
            SetCurrentState(StateMachine::Dead);
        }
        
        //IF THE PLAYER DIES, STOP ATTACKING HIS DEAD BODY
        if(Player->IsDead())
        {
            ADwarfCharacter* Character = Cast<ADwarfCharacter>(GetPawn());
            if (Character)
            {
                Character -> StopAttack();
                Destroy();
            }
        }

    }
    
}

void AAIDwarfController::SetCurrentState(StateMachine NewState)
{
    CurrentState = NewState;
    
    HandleNewState(NewState);
}

void AAIDwarfController::HandleNewState(StateMachine NewState)
{
    switch(NewState)
    {
        //When the game starts make the dwarf run to the character
        case StateMachine::Start:
        {
            SetCurrentState(StateMachine::Chase);
            break;
        }
        
        //Move the dwarf to the character when in chase mode and stop attacking if the attack animation is happening
        case StateMachine::Chase:
        {
            this->MoveToActor(Player);
            ADwarfCharacter* Character = Cast<ADwarfCharacter>(GetPawn());
            if (Character)
            {
                Character -> StopAttack();
            }
            break;
        }

        //When in the attack state, call start attack to start the attack animation and render damage
        case StateMachine::Attack:
        {
            ADwarfCharacter* Character = Cast<ADwarfCharacter>(GetPawn());
            if (Character)
            {
                Character -> StartAttack();
            }
            break;
        }
        
        //When the dwarf dies start going into death mode and call the death animation and things tied to it 
        case StateMachine::Dead:
        {
            ADwarfCharacter* Character = Cast<ADwarfCharacter>(GetPawn());
            if (Character)
            {
                Character -> Death();
            }
            break;
        }
            
    }
}

