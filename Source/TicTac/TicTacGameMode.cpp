// Created by Manikhin Ilia in 2021


#include "TicTacGameMode.h"
#include "Board.h"

ATicTacGameMode::ATicTacGameMode()
{

}


void ATicTacGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (BoardSetup)
	{
		auto* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters Parameters;
			Parameters.Owner = this;

			//Спаун instance доски
			BoardRef = World->SpawnActor<ABoard>(BoardSetup, FVector(-130.f, -130.f, 0.f), FRotator::ZeroRotator, Parameters);
			if (BoardRef)
			{
				BoardRef->GameModeRef = this;
				UE_LOG(LogTemp, Warning, TEXT(" Instance of board created!"))
			}
		}
	}

	AddGameHUD();

	ReplayGame();

}

// TODO реализовать после того как доделаем класс Board 
void ATicTacGameMode::ReplayGame()
{
	BoardRef->ResetBoard();
	CurrentPlayerId = Player1Id;
	UE_LOG(LogTemp, Warning, TEXT("Now turn of %i"), CurrentPlayerId);
	ResultToHud = 2;
	bIsGameRunning = true;
	UE_LOG(LogTemp, Warning, TEXT("Game is reset"));
}

void ATicTacGameMode::ShowResult(int Result)
{
	ResultToHud = Result;

	switch (Result)
	{
	case 0:
		UE_LOG(LogTemp, Warning, TEXT("Player 1 [X] won the match!"));
		//GameHUDRef->SetInfoText(FName(TEXT("Player 1 [X] won the match!")));
		break;
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("Player 2 [O] won the match!"));
		//GameHUDRef->SetInfoText(FName(TEXT("Player 2 [O] won the match!")));
		break;
	case -1:
		UE_LOG(LogTemp, Warning, TEXT("The match ended with a draw!"));
		//GameHUDRef->SetInfoText(FName(TEXT("The match ended with a draw!")));
		break;
	default:;
	}
	bIsGameRunning = false;
}

int32 ATicTacGameMode::GetResultToHud()
{
	UE_LOG(LogTemp, Warning, TEXT("Result to HUD we have here %i"), ResultToHud);

	return ResultToHud;
}

