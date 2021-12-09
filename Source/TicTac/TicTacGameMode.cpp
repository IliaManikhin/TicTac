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

			//����� instance �����
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

// TODO ����������� ����� ���� ��� �������� ����� Board 
void ATicTacGameMode::ReplayGame()
{
	BoardRef->ResetBoard();
	CurrentPlayerId = Player1Id;
	UE_LOG(LogTemp, Warning, TEXT("Now turn of %i"), CurrentPlayerId);
	//GameHUDRef->SetInfoText(FName(TEXT("Player 1 [X] Turn...")));
	bIsGameRunning = true;
	UE_LOG(LogTemp, Warning, TEXT("Game is reset"));
}

void ATicTacGameMode::ShowResult(int Result)
{

}
