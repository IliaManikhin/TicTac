// Created by Manikhin Ilia in 2021

#include "Board.h"
#include "Block.h"
#include "TicTacHUD.h"

UBlockGrid::UBlockGrid() = default;

void UBlockGrid::Init(const uint32 SizeOfGrid)
{
	Size = SizeOfGrid;
	//ќчищаем массив , с ожидаемым размером 
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

// ќчищаем поле, все блоки должны стать без значений
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
	// провер€м ≈сли блок не существует 
	if (!BlockSetup) return;
	auto* World = GetWorld();
	if (!World) return;

	Grid = NewObject<UBlockGrid>();  // шаблон дл€ конструировани€ объектов 
	Grid->Init(this->Size);  // размер назначим через BP_Board

	// ¬ложенный цикл дл€ спауна кубов , за одну итерацию внешнего спавним блоки с определенным промежутком во внутреннем цикле 
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

			// устанавливаем ID дл€ блоков, позже получим доступ к блоку
			 NewBlock->BoardRef = this;
			
			NewBlock->AttachToActor(NewBlock->BoardRef, FAttachmentTransformRules::KeepWorldTransform);
			NewBlock->BlockIndex = ++BlockIndex; // starts from 1 to 9

			Grid->Add(NewBlock);

			auto ID = Grid->GetBlockAt(i, j)->BlockID;
			
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


//≈сли на доске есть победна€ комбинаци€ , то какому игроку принадлежит 
void ABoard::CheckBoard()
{
	const bool MatchFound = IsMatchFound();

	//«начени€: 0 - победа Player1, 1 - победа Player2, -1 - ничь€
	if (MatchFound && GameModeRef->CurrentPlayerId == ATicTacGameMode::Player1Id)
	{
		// 1 потому что, мы переключаем ход игрока после клика на блок,
		//т.е. если есть победа, ход другого игрока не состоитс€ и мы фиксириуем игрок с каким ID сделал победный ход
		GameModeRef->ShowResult(1); 
	}

	if (MatchFound && GameModeRef->CurrentPlayerId == ATicTacGameMode::Player2Id)
	{
		GameModeRef->ShowResult(0);
	}

	//Ќа доске ничь€ 
	if (!MatchFound && RemainEmptyCells <= 0)
	{
		GameModeRef->ShowResult(-1);
	}
}

// ѕровер€ем есть ли на доске победна€ комбинаци€ символов 
bool ABoard::IsMatchFound()
{
	for (int i = 0; i < Size; i++)
	{
		//ѕровер€ем по горизонтали
		bool MatchFound = Grid->GetBlockAt(i, 0)->BlockID == Grid->GetBlockAt(i, 1)->BlockID &&
			Grid->GetBlockAt(i, 0)->BlockID == Grid->GetBlockAt(i, 2)->BlockID;
		if (MatchFound) { return true; }

		//ѕровер€ем по вертикали
		MatchFound = Grid->GetBlockAt(0, i)->BlockID == Grid->GetBlockAt(1, i)->BlockID &&
			Grid->GetBlockAt(0, i)->BlockID == Grid->GetBlockAt(2, i)->BlockID;
		if (MatchFound) { return true; }

		//ѕровер€ем диагонали
		MatchFound = Grid->GetBlockAt(0, 0)->BlockID == Grid->GetBlockAt(1, 1)->BlockID &&
			Grid->GetBlockAt(0, 0)->BlockID == Grid->GetBlockAt(2, 2)->BlockID;
		if (MatchFound) { return true; }

		MatchFound = Grid->GetBlockAt(0, 2)->BlockID == Grid->GetBlockAt(1, 1)->BlockID &&
			Grid->GetBlockAt(0, 2)->BlockID == Grid->GetBlockAt(2, 0)->BlockID;
		if (MatchFound) { return true; }
	}

	return false;
}
