// Copyright Kyungbae Kim


#include "Effect/GE_InitAttributes.h"
#include "Attribute/MyAttributeSet.h"

UGE_InitAttributes::UGE_InitAttributes()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo HealthMod;
    HealthMod.Attribute = UMyAttributeSet::GetHealthAttribute();
    HealthMod.ModifierOp = EGameplayModOp::Additive;
    HealthMod.ModifierMagnitude = FScalableFloat(100.f);  // 초기 Health 값

    Modifiers.Add(HealthMod);

    FGameplayModifierInfo MaxHealthMod;
    MaxHealthMod.Attribute = UMyAttributeSet::GetMaxHealthAttribute();
    MaxHealthMod.ModifierOp = EGameplayModOp::Additive;
    MaxHealthMod.ModifierMagnitude = FScalableFloat(100.f);  // 초기 MaxHealth 값

    Modifiers.Add(MaxHealthMod);
}
