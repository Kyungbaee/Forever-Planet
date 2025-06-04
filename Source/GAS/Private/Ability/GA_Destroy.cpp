// Copyright Kyungbae Kim

#include "Ability/GA_Destroy.h"

UGA_Destroy::UGA_Destroy()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UGA_Destroy::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid()) return;

	AActor* OwnerActor = ActorInfo->AvatarActor.Get();

	// 죽음 태그 부여
	ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(
		FGameplayTag::RequestGameplayTag("State.Dead"));

	if (OwnerActor->HasAuthority())
	{
		TWeakObjectPtr<AActor> WeakOwner = OwnerActor;

		OwnerActor->SetActorHiddenInGame(true);            // 화면에서 숨기기
		OwnerActor->SetActorEnableCollision(false);        // 콜리전 제거

		UE_LOG(LogTemp, Warning, TEXT(">> Server is calling Destroy()"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(">> Client is calling Destroy()"));
	}

	// 딜레이 후 Destroy
	FTimerHandle TimerHandle;
	OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, [OwnerActor]()
		{
			OwnerActor->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Enemy destroyed after death."));
		}, 0.5f, false); // 2초 후

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
