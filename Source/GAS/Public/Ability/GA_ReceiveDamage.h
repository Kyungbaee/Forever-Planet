// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_ReceiveDamage.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGA_ReceiveDamage : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
    UGA_ReceiveDamage();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override;
};
