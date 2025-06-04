// Copyright Kyungbae Kim

#include "Ability/GA_Die.h"

UGA_Die::UGA_Die()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UGA_Die::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid()) return;

	AActor* OwnerActor = ActorInfo->AvatarActor.Get();

	// 죽음 태그 부여
	ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(
		FGameplayTag::RequestGameplayTag("State.Dead"));

	// 딜레이 후 Actor 숨기기
	FTimerHandle TimerHandle;
	OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, [OwnerActor]()
		{
			OwnerActor->SetActorHiddenInGame(true);
			OwnerActor->SetActorEnableCollision(false);
			UE_LOG(LogTemp, Warning, TEXT("Player hidden after death."));
		}, 3.0f, false); // 3초 후

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
