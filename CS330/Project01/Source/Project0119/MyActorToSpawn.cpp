//Planets 
#include "Project0119.h"
#include "MyActorToSpawn.h"


// Template to get the materials to appear for each planet
// Found at: wiki.unrealengine.com/Dynamic_Load_Object#Get_Object.27s_Path
template <typename ObjClass>
static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path){
    return Cast<ObjClass>(StaticLoadObject( ObjClass::StaticClass(), NULL,*Path.ToString()));
}

AMyActorToSpawn::AMyActorToSpawn(){
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    //Set up our sphere to spawn each time
    SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    RootComponent = SphereComponent;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    
    //If the sphere is built, set it to rotate around the sun (40)
    if (SphereVisualAsset.Succeeded()) {
        SphereComponent->SetStaticMesh(SphereVisualAsset.Object);
    }
}

void AMyActorToSpawn::BeginPlay()
{
    Super::BeginPlay();
}

void AMyActorToSpawn::Tick(float DeltaTime){
    
    Super::Tick( DeltaTime );
    
    //How planet rotation works
    FVector planetLocation = SphereComponent -> GetRelativeTransform().GetLocation();
    FQuat planetRotQuat = SphereComponent -> GetRelativeTransform().GetRotation();

    FRotator planetRot(planetRotQuat);
    
    //Will revolve around the unit direction
    FVector UnitDirection;
    UnitDirection = FVector(0.0f, 0.0f, -40.0f);
    //Get the distance from the sun
    float distance;
    planetLocation.ToDirectionAndLength(UnitDirection, distance);
    
    //Rotation math
    float rp = FMath::Sqrt(planetLocation.X * planetLocation.X + planetLocation.Y * planetLocation.Y)/planetLocation.Z;
    float phi = FMath::Atan(rp);
    float theta = FMath::Atan2(planetLocation.Y, planetLocation.X);
    //Will set the speed of each planet's rotation
    theta -= 10*DeltaTime/8;
    
    planetRot.Yaw -= 180*DeltaTime/8;
    float magnitude = planetLocation.Size();
    
    //New planet location based on above math
    planetLocation.X = magnitude * FMath::Sin(phi)*FMath::Cos(theta);
    planetLocation.Y = magnitude * FMath::Sin(phi)*FMath::Sin(theta);
    planetLocation.Z = magnitude * FMath::Cos(phi);
    
    //Set the rotation and location of each planet
    SphereComponent->SetRelativeLocationAndRotation(planetLocation, planetRot);
    
}

void AMyActorToSpawn::PlanetCase(int NumberPlanet){
    //set up pointer to point at material
    UMaterial * material;
    //Using switch statement because for and while loops are crashing my program each time I use it.
    //Switch number (how many cases it will take) determined in PawnWithCamera.cpp
    switch (NumberPlanet) {
        case 0:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Mercury Spawned!")));
            //Set the scale of the planet, based on specs provided by professor
            SphereComponent->SetWorldScale3D(FVector(0.5f));
            //Set the location of the planet, based on specs provided
            //Z value is set to "0" to have a flat rotation
            SphereComponent->SetRelativeLocation(FVector(100.0, 100.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel");
            //break out of the case
            break;
        }
        case 1:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Venus Spawned!")));
            SphereComponent->SetWorldScale3D(FVector(1.0f));
            SphereComponent->SetRelativeLocation(FVector(150.0f, 150.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Wood_Pine.M_Wood_Pine");
            break;
        }
        case 2:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Earth Spawned!")));
            SphereComponent->SetWorldScale3D(FVector(1.0f));
            SphereComponent->SetRelativeLocation(FVector(200.0f, 200.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean");
            break;
        }
        case 3:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Mars Spawned!")));
            SphereComponent->SetWorldScale3D(FVector(1.0f));
            SphereComponent->SetRelativeLocation(FVector(300.0f, 300.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Metal_Rust.M_Metal_Rust");
            break;
        }
        case 4:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Juipter Spawned!")));
            SphereComponent->SetWorldScale3D(FVector(2.5f));
            SphereComponent->SetRelativeLocation(FVector(450.0f, 450.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Metal_Copper.M_Metal_Copper");
            break;
        }
        case 5:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Saturn Spawned!")));
            SphereComponent->SetWorldScale3D(FVector(2.5f));
            SphereComponent->SetRelativeLocation(FVector(600.0f, 600.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Rock_Sandstone.M_Rock_Sandstone");
            break;
        }
        case 6:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Uranus Spawned!")));
            SphereComponent->SetWorldScale3D(FVector(1.5f));
            SphereComponent->SetRelativeLocation(FVector(800.0f, 800.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Water_Lake.M_Water_Lake");
            break;
        }
        case 7:
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Neptune Spawned!")));
            SphereComponent->SetWorldScale3D(FVector(1.5f));
            SphereComponent->SetRelativeLocation(FVector(1000.0f, 1000.0f, 0.0f));
            material = LoadObjFromPath<UMaterial> ("/Game/StarterContent/Materials/M_Metal_Brushed_Nickel.M_Metal_Brushed_Nickel");
            break;
        }
    }
    //Will set the material in each case for each planet above after each case is broken out of 
    SphereComponent->SetMaterial(0, material);
    
}





