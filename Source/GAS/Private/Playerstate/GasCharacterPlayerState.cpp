// Copyright Kyungbae Kim


#include "Playerstate/GasCharacterPlayerState.h"

AGasCharacterPlayerState::AGasCharacterPlayerState()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* AGasCharacterPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}