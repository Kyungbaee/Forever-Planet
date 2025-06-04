// Copyright Kyungbae Kim


#include "Effect/GE_Cooldown.h"

UGE_Cooldown::UGE_Cooldown()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;
    DurationMagnitude = FScalableFloat(1.5f); // 1초 쿨다운

    // 태그 설정
    InheritableOwnedTagsContainer.AddTag(FGameplayTag::RequestGameplayTag("Cooldown.Attack"));
}
