// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "GasPaperCharacter.h"
#include "MainGasPaperCharacter.generated.h"

UCLASS()
class GAS_API AMainGasPaperCharacter : public AGasPaperCharacter
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void JumpByGAS();
	void AttackByGAS();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* AttackAction;
};
