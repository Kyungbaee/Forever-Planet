// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GA_Die.generated.h"

UCLASS()
class GAS_API UGA_Die : public UGameplayAbility
{
	GENERATED_BODY()

public:
    UGA_Die();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;
};
