// Created by Manikhin Ilia in 2021


#include "Block.h"
#include "Board.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DummyRoot"));
	RootComponent = DummyRoot;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>("BlockModel");
	BlockMesh->SetupAttachment(DummyRoot);

	// ������ ��������� ����� �� ���� 
	// ����� OnClicked ����� ���� ������ �� ��������� ���� �� ���� ������ LMouse � � PlayerController ��������� ������ ����
	BlockMesh->OnClicked.AddDynamic(this, &ABlock::BlockClicked);

	bIsAvailable = true;
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

}

void ABlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	if (!bIsAvailable || !BoardRef->GameModeRef->IsGameRunning()) return;

	// ����� ������ ����� ������ ��� � ReplayGame ��������������� enum �� �������� 1�� ������
	// ����� ������������� ��� ������� ������ � ��� �����
	if (BoardRef->GetPlayerTurnId() == ATicTacGameMode::Player1Id)
	{
		BlockID = ATicTacGameMode::Player1Id;
		BlockMesh->SetMaterial(0, CrossBlockMaterial);
		BoardRef->SetPlayerTurn(ATicTacGameMode::Player2Id);
	}
	else if (BoardRef->GetPlayerTurnId() == ATicTacGameMode::Player2Id)
	{
		BlockID = ATicTacGameMode::Player2Id;
		BlockMesh->SetMaterial(0, RoundBlockMaterial);
		BoardRef->SetPlayerTurn(ATicTacGameMode::Player1Id);
	}

	bIsAvailable = false;
	// ����������� ���������� ���������� ������ �����, ����� ������� ���� 
	BoardRef->RemainEmptyCells--;
	if (BoardRef->RemainEmptyCells < 0)
	{
		BoardRef->RemainEmptyCells = 0;
	}

	//��������� ������� ��������� ����
	BoardRef->CheckBoard();

	UE_LOG(LogTemp, Warning, TEXT("Block clicked"));
}

void ABlock::ResetBlock()
{
	bIsAvailable = true;
	BlockID = BlockIndex;
	UE_LOG(LogTemp, Warning, TEXT("block id [%s] "), *FString::FromInt(BlockID));
	SetEmptyMaterial();
}

void ABlock::SetEmptyMaterial() const
{
	BlockMesh->SetMaterial(0, EmptyBlockMaterial);
}

void ABlock::SetCrossMaterial() const
{
	BlockMesh->SetMaterial(0, CrossBlockMaterial);
}

void ABlock::SetRoundMaterial() const
{
	BlockMesh->SetMaterial(0, RoundBlockMaterial);
}


