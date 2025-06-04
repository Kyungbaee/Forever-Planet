// Copyright Kyungbae Kim


#include "Enemy/EnemyGasPaperCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h" 

AEnemyGasPaperCharacter::AEnemyGasPaperCharacter()
{
    AIControllerClass = AEnemyAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyGasPaperCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = 200.f;
    }
}

void AEnemyGasPaperCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (AbilitySystemComp)
    {
        AbilitySystemComp->InitAbilityActorInfo(this, this);

        if (!AbilitySystemComp->GetSet<UMyAttributeSet>())
        {
            AbilitySystemComp->AddAttributeSetSubobject(NewObject<UMyAttributeSet>(AbilitySystemComp));
        }

        InitAttributes();
        AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(UGA_Attack::StaticClass(), 1, 0));
        AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(UGA_Knockback::StaticClass(), 1, 0));
        AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(UGA_ReceiveDamage::StaticClass(), 1, 0));
        AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(UGA_Destroy::StaticClass(), 1, 0));

        AbilitySystemComp->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Type.Enemy")));
    }
}