//EXTRA CTEDIT

#include "TopDownShmup.h"
#include "Lab08HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "TopDownShmupCharacter.h"
#include "DwarfCharacter.h"

//HUD to display the player's health

ALab08HUD::ALab08HUD()
{
    static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
    HUDFont = HUDFontOb.Object;
}

void ALab08HUD::DrawHUD()
{
    FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
    
    Super::DrawHUD();
    
    //Call the player and the player's health from topdownshmupcharacter
    ATopDownShmupCharacter* Character = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    float PlayerHealth = Character->PlayerHealth;
    
    DrawText(TEXT("Objective: Kill all space dwarves! Save the president."), FColor::White, 50, 50, HUDFont);
    
    if(PlayerHealth > 30)
    {
        FString Health = FString::Printf(TEXT("Player Health: %f"), PlayerHealth);
        DrawText(Health, FColor::White, 50, 80, HUDFont);
    }
    
    //Warn player that they are close to death when their health is less than 30
    if (PlayerHealth <= 30)
    {
        FString Health = FString::Printf(TEXT("Player Health: %f DANGER ZONE!"), PlayerHealth);
        DrawText(Health, FColor::Red, 50, 80, HUDFont);
    }

    //If the player has died, display a game over message on the screen! 
    if(Character->IsDead())
    {
        FVector2D GameOverSize;
        GetTextSize(TEXT("GAME OVER"), GameOverSize.X, GameOverSize.Y, HUDFont);
        DrawText(TEXT("GAME OVER"), FColor::White, (ScreenDimensions.X - GameOverSize.X) / 2.0f, (ScreenDimensions.Y - GameOverSize.Y) / 2.0f, HUDFont);
        
    }

}