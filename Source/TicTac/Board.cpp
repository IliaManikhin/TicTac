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

// ������� ����, ��� ����� ������ ����� ��� ��������
void UBlockGrid::ResetGrid() const
{
	for (const auto& Block : BlockArray)
	{
		Block->ResetBlock();
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
	// �������� ���� ���� �� ���������� 
	if (!BlockSetup) return;
	auto* World = GetWorld();
	if (!World) return;

	UE_LOG(LogTemp, Warning, TEXT("������� ����� ��� ����..."));

	Grid = NewObject<UBlockGrid>();  // ������ ��� ��������������� �������� 
	Grid->Init(this->Size);  // ������ �������� ����� BP_Board

	// ��������� ���� ��� ������ ����� , �� ���� �������� �������� ������� ����� � ������������ ����������� �� ���������� ����� 
	auto BlockIndex = 0;

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			const float XOffSet = i * BlockSpacing;
			const float YOffSet = j * BlockSpacing;
			const FVector BlockLocation = FVector(XOffSet, YOffSet, 0.0f) + GetActorLocation();

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;

			ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(
				BlockSetup,
				BlockLocation,
				FRotator(90.0f, 0.0f, 0.0f),
				SpawnParameters);

			// ������������� ID ��� ������, ����� ������� ������ � ���� 
			 NewBlock->BoardRef = this;
			
			NewBlock->AttachToActor(NewBlock->BoardRef, FAttachmentTransformRules::KeepWorldTransform);
			NewBlock->BlockIndex = ++BlockIndex; // starts from 1 to 9
		
			Grid->Add(NewBlock);

			auto ID = Grid->GetBlockAt(i, j)->BlockID;
			
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(ID));

			UE_LOG(LogTemp, Warning, TEXT("Block loc: %s"), *NewBlock->GetActorLocation().ToString());

		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Board created"));


}

void ABoard::SetPlayerTurn(const int32 CurrentPlayerId) const
{
	GameModeRef->CurrentPlayerId = CurrentPlayerId;

	if (CurrentPlayerId == ATicTacGameMode::Player1Id)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player One Turn"));
		
	}
	else if (CurrentPlayerId == ATicTacGameMode::Player2Id)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Two Turn"));
	}
}

void ABoard::ResetBoard()
{
	Grid->ResetGrid();
	RemainEmptyCells = Size * Size;
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

