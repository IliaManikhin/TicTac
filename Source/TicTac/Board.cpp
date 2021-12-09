// Created by Manikhin Ilia in 2021

#include "Board.h"
#include "Block.h"
#include "TicTacHUD.h"

UBlockGrid::UBlockGrid() = default;

void UBlockGrid::Init(const uint32 SizeOfGrid)
{
	Size = SizeOfGrid;
	BlockArray.Empty(Size * Size); 
}

ABlock* UBlockGrid::GetBlockAt(const uint32 Row, const uint32 Column) const
{
	return BlockArray[Row * Size + Column];
}

void UBlockGrid::Add(ABlock * Block)
{
	BlockArray.Add(Block);
}

// Очищаем поле, все блоки должны стать без значений
void UBlockGrid::ResetGrid() const
{
	for (const auto& Block : BlockArray)
	{
		//Block->ResetBlock();
	}
}

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	CreateBoard();
}

void ABoard::CreateBoard()
{
	// проверям Если блок не существует 
	if (!BlockSetup) return;
	auto* World = GetWorld();
	if (!World) return;

	UE_LOG(LogTemp, Warning, TEXT("Создаем доску для игры..."));


}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

