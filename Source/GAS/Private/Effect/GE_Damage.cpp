// Copyright Kyungbae Kim


#include "Effect/GE_Damage.h"
#include "Attribute/MyAttributeSet.h"

UGE_Damage::UGE_Damage()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo DamageMod;
    DamageMod.Attribute = UMyAttributeSet::GetHealthAttribute();
    DamageMod.ModifierOp = EGameplayModOp::Additive;

    FSetByCallerFloat SetByCaller;
    SetByCaller.DataTag = FGameplayTag::RequestGameplayTag(FName("Data.Damage"));
    DamageMod.ModifierMagnitude = FGameplayEffectModifierMagnitude(SetByCaller);
    Modifiers.Add(DamageMod);
}
