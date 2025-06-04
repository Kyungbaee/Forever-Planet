// Copyright Kyungbae Kim


#include "Attribute/MyAttributeSet.h"
#include "Character/GasPaperCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Ability/GA_Destroy.h"
#include "Ability/GA_Die.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UMyAttributeSet::UMyAttributeSet()
{
    MaxHealth = 100.f;
    //Health = 100.f;
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        if (GetHealth() <= 0.f)
        {
            if (AActor* Victim = Cast<AActor>(Data.Target.GetAvatarActor()))
            {
                if (AGasPaperCharacter* Char = Cast<AGasPaperCharacter>(Victim))
                {
                    Char->HandleZeroHealth();
                }
            }
        }
    }
}


void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    AActor* Owner = GetTypedOuter<AActor>();
    if (AGasPaperCharacter* Char = Cast<AGasPaperCharacter>(Owner))
    {
        Char->OnHealthChanged.Broadcast(Health.GetCurrentValue(), OldHealth.GetCurrentValue());
    }
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    AActor* Owner = GetTypedOuter<AActor>();
    if (AGasPaperCharacter* Char = Cast<AGasPaperCharacter>(Owner))
    {
        Char->OnMaxHealthChanged.Broadcast(MaxHealth.GetCurrentValue(), OldMaxHealth.GetCurrentValue());
    }
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}