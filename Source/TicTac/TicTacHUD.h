// Created by Manikhin Ilia in 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TicTacHUD.generated.h"

/**
 * 
 */
UCLASS()
class TICTAC_API UTicTacHUD : public UUserWidget
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestFunction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void OnReplayButtonClicked();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void ShowPlayerID();

	int32 IDOfPlayerWhosTurn;

	
	
};
