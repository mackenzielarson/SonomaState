//Voyager
//All voyager controlls included here along with what to spawn & when
#include "Project0119.h"
#include "PawnWithCamera.h"
#include "MyActorToSpawn.h"
#include "VoyagerPawnMovementComponent.h"
#include "Sun.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
    
    //To create "Voyager" and for it to have collision, we must make a camera inside of a sphere
    //This way we can zip about the universe and not collide with planets/the sun
    PrimaryActorTick.bCanEverTick = true;
    
    // Our root component will be a sphere that reacts to physics
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(100.0f);
    SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
    
    OurCameraSpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    OurCameraSpringArm->AttachTo(RootComponent);
    OurCameraSpringArm->RelativeRotation = FRotator(-10.0f, 0.0f, 0.0f);
    OurCameraSpringArm->TargetArmLength = 0.0f;
    OurCameraSpringArm->bEnableCameraLag = false;
    OurCameraSpringArm->CameraLagSpeed = 0.0f;
        
    //Create camera and attach spring arm
    OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    OurCamera->AttachTo(OurCameraSpringArm, USpringArmComponent::SocketName);
    
    // Create an instance of our movement component, and tell it to update our root component.
    OurMovementComponent = CreateDefaultSubobject<UVoyagerPawnMovementComponent>(TEXT("CustomMovementComponent"));
    OurMovementComponent->UpdatedComponent = RootComponent;
    
    //Take control of the default Player
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    
    //Set bearing mode time to 2 (default) it is editable from the editor
    BearingTime = 2.0f;
    SphereVisualLocation = (FVector(0.0f, 0.0f, -40.0f));
}


// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void APawnWithCamera::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    
    //Turn the camera toward the sun when bearing mode has been activated
    if(turnToSun)
    {
        FRotator Temporary = FMath::Lerp(GetActorRotation(), NewRotation, DeltaTime / BearingTime);
        RootComponent->SetWorldRotation(Temporary);
        if (GetActorRotation().Equals(NewRotation, 4))
        {
            turnToSun = false;
        }
    }
    
    
    //Zoom camera toward the point of origin of the sun (will appear below sun)
    if (bZoomingIn)
    {
        
        float CamDistToSun = FVector::Dist(SphereVisualLocation, GetActorLocation());
        if(CamDistToSun < 101)
        {
            bZoomingIn = false;
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("The voyager is too close to the sun! Cannot zoom any further.")));
            FString TheDistance = FString::SanitizeFloat(CamDistToSun);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *TheDistance);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Distance after zoom: ")));
           
        }
        else
        {
            FVector dist = FMath::Lerp(GetActorLocation(), MidPoint, DeltaTime / BearingTime);
            RootComponent->SetWorldLocation(dist);
            if (GetActorLocation().Equals(MidPoint, 4))
            {
                bZoomingIn = false;
                FString TheDistance = FString::SanitizeFloat(CamDistToSun);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *TheDistance);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Distance after zoom: ")));
            }
        }
        
    }
    
}


// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    
    //Hook up events for "SpawnActor"
    //Use spacebar to spawn actor (planet)
    InputComponent->BindAction("SpawnActor", IE_Pressed, this, &APawnWithCamera::SpawnActor);
    
    //Bearing mode
    //If right mouse button is pressed, enter bearing mode
    InputComponent->BindAction("RotateToSun", IE_Pressed, this, &APawnWithCamera::BearingMode);
    
    //Hook up every-frame handling for our four axes
    //Use W and S to move forward and back respectively
    //Use A and D to move left and right respectively
    InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
    
    //Camera pitch controlled by mouse y
    //Camera yaw controlled by mouse x
    InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
    InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);
    
}

//Bearing mode
void APawnWithCamera::BearingMode()
{
    //Message to indicate bearing mode has been activated
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("STARTING BEARING MODE!")));
    
    //Trigger turning and zooming when bearing mode is activated
    turnToSun = true;
    FVector VoyagerLocation = GetActorLocation();
    FVector NewRotationLocation = SphereVisualLocation - VoyagerLocation;
    NewRotation = NewRotationLocation.Rotation();
    
    
    bZoomingIn = true;
    //How to get half the original distance for zoom
    OrigDist = FVector::Dist(SphereVisualLocation, GetActorLocation());
    MidPoint.X = (SphereVisualLocation.X + GetActorLocation().X ) / 2;
    MidPoint.Y = (SphereVisualLocation.Y + GetActorLocation().Y ) / 2;
    MidPoint.Z = (SphereVisualLocation.Z + GetActorLocation().Z ) / 2;
}

//Passes movement component to voyagerpawnmovementcomonent this will check the collision
UVoyagerPawnMovementComponent* APawnWithCamera::GetMovementComponent() const
{
    return OurMovementComponent;
}

//Move forward/back
void APawnWithCamera::MoveForward(float AxisValue)
{
    //Get the movement of our camera and set it up for collision
    //If the camera will pass the axis value of the camera to the movementcomponent to check for collision at the same time as it moves
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        FVector movementVector = OurCamera->GetForwardVector();
        OurMovementComponent->AddInputVector(movementVector* AxisValue);
    }
}

//Move right/left
void APawnWithCamera::MoveRight(float AxisValue)
{
    //Again, pass where we are moving to at the movementcomponent
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
    }
}

//Function for camera pitch (up and down)
void APawnWithCamera::YawCamera(float AxisValue)
{
    FRotator NewCamRotation = GetActorRotation();
    NewCamRotation.Yaw += AxisValue;
    SetActorRotation(NewCamRotation);
}

//Function for camera yaw (side to side)
void APawnWithCamera::PitchCamera(float AxisValue)
{
    FRotator NewCamRotation = GetActorRotation();
    NewCamRotation.Pitch = FMath::Clamp(NewCamRotation.Pitch + AxisValue, -80.0f, 80.0f);
    SetActorRotation(NewCamRotation);
}

//Spawn Planet
void APawnWithCamera::SpawnActor()
{
    //Set up counter
    //If the number of planets is less then 8, spawn an actor
    //Pass "NumPlanets" to MyActorToSpawn to determine what "case" to use
    //Because we will be determining location and rotation in MyActorToSpawn, use ZeroVector and ZeroRotator
    //Add 1 to NumPlanets
    if(NumPlanets < 8)
    {
        AMyActorToSpawn *myNewActor = GetWorld()->SpawnActor<AMyActorToSpawn>(FVector::ZeroVector, FRotator::ZeroRotator);
        myNewActor->PlanetCase(NumPlanets);
        NumPlanets += 1;
    }
    //When the counter has reached 8, stop spawning planets
    //Output message to read that no more planets can be spawned
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("There are no more planets left to spawn!")));
    }

}







