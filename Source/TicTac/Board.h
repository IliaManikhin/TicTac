// Created by Manikhin Ilia in 2021

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "GameFramework/Actor.h"
#include "TicTacGameMode.h"
#include "Board.generated.h"

UCLASS()
class UBlockGrid final : public UObject
{
	GENERATED_BODY()

public:
	UBlockGrid();

	UFUNCTION()
	void Init(const uint32 SizeOfGrid);

	UFUNCTION()
	ABlock* GetBlockAt(const uint32 Row, const uint32 Column) const;

	UFUNCTION()
	void Add(ABlock* Block);

	UFUNCTION()
	void ResetGrid() const;


private:
	//������ ��� ������
	UPROPERTY()
		TArray<ABlock*> BlockArray;

	UPROPERTY()
		uint32 Size;

};

UCLASS()
class TICTAC_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

	// �������� � �����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		TSubclassOf<class ABlock> BlockSetup; // ������ ����� ��� ���� BP , � ����� ������� ������� 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid") // ������ ����� 
		int32 Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid") // ���������� ����� ������� 
		float BlockSpacing;

	UPROPERTY()
		int RemainEmptyCells;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "References")
	ATicTacGameMode* GameModeRef;

private:
	UPROPERTY()
	UBlockGrid* Grid;

	UFUNCTION()
	void CreateBoard();

};
