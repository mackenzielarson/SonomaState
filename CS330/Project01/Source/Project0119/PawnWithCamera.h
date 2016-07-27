// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "VoyagerPawnMovementComponent.h"
#include "MyActorToSpawn.h"
#include "PawnWithCamera.generated.h"


UCLASS()
class PROJECT0119_API APawnWithCamera : public APawn
{
	GENERATED_BODY()
    
public:
	// Sets default values for this pawn's properties
	APawnWithCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    //Allow the voyager velocity to be editable in the pawn with camera tab
    UPROPERTY(VisibleAnywhere)
    class UVoyagerPawnMovementComponent* OurMovementComponent;
    virtual UVoyagerPawnMovementComponent* GetMovementComponent() const override;
    
    USpringArmComponent* OurCameraSpringArm;
    UCameraComponent* OurCamera;
    
    //Create an int of the number of planets (track how many times the space bar is pressed)
    int NumPlanets;
    
    //Spawn actor function called when the spacebar is pressed
    void SpawnActor();
    
    //Input variables
    FVector2D MovementInput;
    FVector2D CameraInput;
    
    //User Input functions
    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void PitchCamera(float AxisValue);
    void YawCamera(float AxisValue);
    
    
    //FUNCTION TO LOOK AT THE SUN
    void BearingMode();
    
    
    //VARIABLES FOR SUN LOCATION AND HOW TO ROTATE TO SUN
    FVector SphereVisualLocation;
    bool turnToSun;
    bool bZoomingIn;

    UPROPERTY(EditAnywhere, Category = "Bearing Mode")
    float BearingTime;
    
    float OrigDist;
    FVector MidPoint; 
    
    FRotator NewRotation;
    
};

