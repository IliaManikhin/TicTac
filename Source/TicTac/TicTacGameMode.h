// Created by Manikhin Ilia in 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacGameMode.generated.h"

/**
 * 
 */
UENUM()
enum class EPlayerChoice
{
	Player_1,
	Player_2
};

UCLASS()
class TICTAC_API ATicTacGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:
	// �����������
	ATicTacGameMode();

	// �������� 

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	EPlayerChoice PlayerTurn;

	static constexpr int32 Player1Id = 100;
	static constexpr int32 Player2Id = 200;
	int32 CurrentPlayerId;

	// ����� board 
	UPROPERTY(EditAnywhere, Category = "Board")
	TSubclassOf<class ABoard> BoardSetup;

	UPROPERTY(VisibleDefaultsOnly, Category = "References")
	class ABoard* BoardRef;

	//������ �� ��� HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	class UTicTacHUD* GameHUDRef;

	//�������

	// Event ��� ������ � Game Mode ��� ����������� BP TicTacHUD
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void AddGameHUD();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void OnDetectedDraw();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ReplayGame();

	UFUNCTION()
	void ShowResult(int Result);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	int32 GetResultToHud();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	int32 GetPlayerID();

	int32 ResultToHud = 2;

	FORCEINLINE bool IsGameRunning() const { return bIsGameRunning; }

private:

	UPROPERTY()
	bool bIsGameRunning;


};
