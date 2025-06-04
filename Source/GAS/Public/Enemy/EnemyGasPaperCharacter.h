// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "Character/GasPaperCharacter.h"
#include "EnemyGasPaperCharacter.generated.h"

UCLASS()
class GAS_API AEnemyGasPaperCharacter : public AGasPaperCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyGasPaperCharacter();

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
};
