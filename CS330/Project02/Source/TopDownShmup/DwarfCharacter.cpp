// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownShmup.h"
#include "DwarfCharacter.h"
#include "AIDwarfController.h"
#include "TopDownShmupCharacter.h"

ADwarfCharacter::ADwarfCharacter()
{
    AIControllerClass =	AAIDwarfController::StaticClass();
    
    //Set time for timers
    //Count down time will correspond to destroying the dwarf
    CountdownTime = 1;
    
    //Count down time 2 will correspond to dwarf's attack animation
    CountdownTime2 = 2;
}

void ADwarfCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    //Set the timer for the dwarf's destruction
    GetWorldTimerManager().SetTimer(CountdownTimerHandle2, this, &ADwarfCharacter::AdvanceTimer, 1.0f, true);
}

void ADwarfCharacter::Tick( float DeltaTime)
{
    Super::Tick(DeltaTime); 
}

void ADwarfCharacter::StartAttack()
{
    //set the timer for the attack animation
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ADwarfCharacter::StartAttack, 1.0f, true);
    Attack = true;
    //play the attack animation
    PlayAnimMontage(AttackAnim);
    if (Attack == true)
    {
        //Timer loop that when hammer is swung every two seconds it inflicts damage on the player.
        --CountdownTime2;
        if (CountdownTime2 < 1)
            {
                ATopDownShmupCharacter* Player = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
                if(Player){
                    Player->TakeDamage(DwarfDamage, FDamageEvent(), GetInstigatorController(), this);
                }
                //set the count down timer back to 2 to continue the loop
                CountdownTime2 = 2;
            
                //When dwarf is "dead" stop swinging hammer and attacking and prepare to destroy itself
                if (DieNow == true)
                {
                    Attack = false;
                    //Call stop attack to kill any attack animation that may be running
                    StopAnimMontage(AttackAnim);
                    //clear the timer handle
                    GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
    
                }
            }
    }
   
}

void ADwarfCharacter::StopAttack()
{
    //when stop attack is called, stop playing the attack animation and clear the timer for it (as a back up if it is running)
    StopAnimMontage(AttackAnim);
    Attack = false;
    GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
    
}

void ADwarfCharacter::Death()
{
    DestroyNow = true;
}

bool ADwarfCharacter::DwarfIsDead()
{
    return DwarfDied;
}

//Timer will begin after the death animation has occured
//After 2 seconds the dwarf will dissappear
void ADwarfCharacter::AdvanceTimer()
{
    if (DestroyNow == true)
    {
        --CountdownTime;
        if (CountdownTime < 1)
        {
            //Call destroy to remove the dwarf from the world
            Destroy();
            GetWorldTimerManager().ClearTimer(CountdownTimerHandle2);
        }
    }
}

float ADwarfCharacter::TakeDamage(float Damage,	struct FDamageEvent const&	DamageEvent, AController* EventInstigator, AActor*	DamageCauser)
{
    float ActualDamage = Super::TakeDamage(Damage,	DamageEvent, EventInstigator,	DamageCauser);
    if (ActualDamage >	0.0f)
    {
        //if the dwarf health is less than the actual damage, the dwarf died
        DwarfHealth -= ActualDamage;
        if (DwarfHealth <= 0.0f)
        {
            //	Dwarf is dead
            bCanBeDamaged =	false;	//	Don't	allow	further	damage
           
            PlayAnimMontage(DeathAnim);
            UnPossessed();

            //Pull the dwarf out of attack mode and into death mode
            DieNow = true;
            DwarfDied = true; 
        }
    }
    //Debug messages for the dwarf health 
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Dwarf Health: %f"), DwarfHealth));
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Plauer Damage Inflicted: %f"), ActualDamage));
    return ActualDamage;
}