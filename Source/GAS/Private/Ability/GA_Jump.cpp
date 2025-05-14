// Copyright Kyungbae Kim


#include "Ability/GA_Jump.h"
#include "GameFramework/Character.h"

UGA_Jump::UGA_Jump()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGA_Jump::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData){

    if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor)) // 클라이언트에서도 실행
    {
        Character->Jump();
    }

    //if (HasAuthority())  // 서버가 필요한 처리 수행 기능
    //{

    //}

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_Jump::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
