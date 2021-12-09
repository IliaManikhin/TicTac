// Created by Manikhin Ilia in 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class TICTAC_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	bool bIsAvailable; /** Блок кликабелен или нет */

	// Используем в массиве для спауна блоков в классе board
	UPROPERTY(EditAnywhere, Category = "References")
	class ABoard* BoardRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterial* EmptyBlockMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialInstance* CrossBlockMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialInstance* RoundBlockMaterial;

	UPROPERTY()
	uint32 BlockID;

	UPROPERTY()
	uint32 BlockIndex; // Индекс блока на grid

	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UFUNCTION()
	void ResetBlock();

	//устанавливаем Материалы в зависимости от состояния 
	
	UFUNCTION()
	void SetEmptyMaterial() const;

	UFUNCTION()
	void SetCrossMaterial() const;

	UFUNCTION()
	void SetRoundMaterial() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh;

};
