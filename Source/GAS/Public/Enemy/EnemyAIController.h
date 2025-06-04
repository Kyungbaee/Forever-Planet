// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"


UCLASS()
class GAS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
    AEnemyAIController();
    void SetTargetPlayer(APawn* InTarget);

protected:
    virtual void Tick(float DeltaSeconds) override;

private:
    UPROPERTY()
    APawn* TargetPlayer;
};
