// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Knockback.generated.h"


UCLASS()
class GAS_API UGA_Knockback : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
    UGA_Knockback();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

protected:
    float KnockbackStrength = 500.f;
    float KnockbackDuration = 0.8f;
    float ElapsedTime;

    FTimerHandle KnockbackTimerHandle;

    FVector KnockbackDirection;
    FVector StartLocation;
    FVector TargetLocation;

    void TickKnockback();
    void EndKnockback();
};
