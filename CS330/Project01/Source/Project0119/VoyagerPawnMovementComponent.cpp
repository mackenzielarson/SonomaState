//Voyager collision with planets and sun 
#include "Project0119.h"
#include "VoyagerPawnMovementComponent.h"


UVoyagerPawnMovementComponent::UVoyagerPawnMovementComponent() {
    VoyagerVelocity = 300.0f;
}

void UVoyagerPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Make sure that everything is still valid, and that we are allowed to move.
    if (PawnOwner || UpdatedComponent || !ShouldSkipUpdate(DeltaTime))
    {
        
    // Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * VoyagerVelocity;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
        
        // If we bumped into something, try to slide along it
        if (Hit.IsValidBlockingHit())
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collision Avoided!")));
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
        }
    }
};




