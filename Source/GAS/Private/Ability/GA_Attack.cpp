// Copyright Kyungbae Kim

#include "Ability/GA_Attack.h"
#include "Effect/GE_Cooldown.h"
#include "Character/GasPaperCharacter.h"
#include "GameInstance/CharacterAnimInstance.h"

UGA_Attack::UGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;

	CooldownGameplayEffectClass = UGE_Cooldown::StaticClass();
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("Cooldown.Attack"));
}

void UGA_Attack::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (AGasPaperCharacter* MyChar = Cast<AGasPaperCharacter>(ActorInfo->AvatarActor))
	{
		MyChar->SetIsAttacking(true);
	}
}

void UGA_Attack::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AGasPaperCharacter* MyChar = Cast<AGasPaperCharacter>(ActorInfo->AvatarActor))
	{
		MyChar->SetIsAttacking(false);
	}
}

void UGA_Attack::OnAttackEnded()
{
	if (IsActive())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
	}
}
