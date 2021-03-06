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

	bool bIsAvailable; /** ???? ?????????? ??? ??? */

	// ?????????? ? ??????? ??? ?????? ?????? ? ?????? board
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
	uint32 BlockIndex; // ?????? ????? ?? grid

	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UFUNCTION()
	void ResetBlock();

	//????????????? ????????? ? ??????????? ?? ????????? 
	
	UFUNCTION()
	void SetEmptyMaterial() const;

	UFUNCTION()
	void SetCrossMaterial() const;

	UFUNCTION()
	void SetRoundMaterial() const;

	UPROPERTY(BlueprintReadOnly, Category = "SFX")
	bool isFireBlock;

	UPROPERTY(BlueprintReadOnly, Category = "SFX")
	bool isElectroBlock;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh;

};
