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
	
};
