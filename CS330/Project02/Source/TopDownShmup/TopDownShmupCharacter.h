// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "TopDownShmupCharacter.generated.h"


UCLASS(Blueprintable)
class ATopDownShmupCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

    UPROPERTY(EditAnywhere, Category=Weapon)
    TSubclassOf<class AWeapon>WeaponClass;
    
public:
	ATopDownShmupCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
   
    FORCEINLINE class AWeapon* GetWeapon() { return MyWeapon; }
    
    virtual void BeginPlay() override;
    
    void OnStartFire();
    void OnStopFire();
    
    //SET PLAYER HEALTH
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
    float PlayerHealth = 100;
    
    //SET PLAYER DAMAGE
    UPROPERTY(EditAnywhere, Category = Health)
    float PlayerDamage = 10;
    
    float TakeDamage(float Damage,	struct FDamageEvent const&	DamageEvent, AController*	EventInstigator, AActor*	DamageCauser) override;

    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* PlayerDeath;
    
    //timer
    void AdvanceTimer();
    int32 CountdownTime;
    FTimerHandle CountdownTimerHandle;
    
    bool PlayerDied;
    bool IsDead();
    
    bool Firing; 

       
private:
    AWeapon* MyWeapon;
};

