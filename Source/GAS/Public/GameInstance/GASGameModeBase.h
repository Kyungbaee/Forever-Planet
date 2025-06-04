// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Character/GasPaperCharacter.h"
#include "Playerstate/GasCharacterPlayerState.h"
#include "Enemy/EnemyGasPaperCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "EngineUtils.h"
#include "GASGameModeBase.generated.h"

UCLASS()
class GAS_API AGASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGASGameModeBase();
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AEnemyGasPaperCharacter> EnemyClass;
};
