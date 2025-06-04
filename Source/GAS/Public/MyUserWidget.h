// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Attribute/MyAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Components/ProgressBar.h"
#include "MyUserWidget.generated.h"

UCLASS()
class GAS_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void BindToAttributes(UAbilitySystemComponent* ASC, UMyAttributeSet* AttrSet);

protected:
    void OnHPChanged(const FOnAttributeChangeData& Data);

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY()
    UAbilitySystemComponent* ASC;

    UPROPERTY()
    UMyAttributeSet* AttributeSet;
};
