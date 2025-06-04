// Copyright Kyungbae Kim


#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyGasPaperCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "STT_TryAttack.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::SetTargetPlayer(APawn* InTarget)
{
    TargetPlayer = InTarget;
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!HasAuthority() || !TargetPlayer) return; // 서버에서만 실행

    MoveToActor(TargetPlayer, 20.0f); // 가까이 이동

    // 거리 체크 후 공격 등 구현 가능
    float Distance = FVector::Dist(TargetPlayer->GetActorLocation(), GetPawn()->GetActorLocation());
    if (Distance < 100.0f)
    {
        if (AEnemyGasPaperCharacter* Enemy = Cast<AEnemyGasPaperCharacter>(GetPawn()))
        {
            UAbilitySystemComponent* ASC = Enemy->GetMyAbilitySystemComponent();
            if (!ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Cooldown.Attack")))
            {
                ASC->TryActivateAbilityByClass(UGA_Attack::StaticClass());
            }
        }
    }
}
