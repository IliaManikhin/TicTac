// Created by Manikhin Ilia in 2021


#include "TicTacGameMode.h"

ATicTacGameMode::ATicTacGameMode()
{

}


void ATicTacGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (BoardSetup)
	{
		auto* World = GetWorld();
	}

	AddGameHUD();

	

}

void ATicTacGameMode::ReplayGame()
{
}

void ATicTacGameMode::ShowResult(int Result)
{
}
