// Copyright Kyungbae Kim


#include "Ability/GA_ReceiveDamage.h"
#include "Effect/GE_Damage.h"
#include "Character/GasPaperCharacter.h"
#include "AbilitySystemComponent.h"

UGA_ReceiveDamage::UGA_ReceiveDamage()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;

    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(FName("Event.Damage"));
    TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
    AbilityTriggers.Add(TriggerData);
}

void UGA_ReceiveDamage::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
    if (!HasAuthority(&ActivationInfo)) return;

    UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC) return;

    if (AGasPaperCharacter* MyChar = Cast<AGasPaperCharacter>(GetAvatarActorFromActorInfo()))
    {
        MyChar->Multicast_SetHitColor();
    }

    float DamageAmount = TriggerEventData ? TriggerEventData->EventMagnitude : 10.f;

    FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
    Context.AddSourceObject(this);

    FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(UGE_Damage::StaticClass(), 1.f, Context);
    if (SpecHandle.IsValid())
    {
        SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), -DamageAmount);
        ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
