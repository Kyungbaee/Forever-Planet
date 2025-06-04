// Copyright Kyungbae Kim


#include "MyUserWidget.h"

void UMyUserWidget::BindToAttributes(UAbilitySystemComponent* InASC, UMyAttributeSet* InAttrSet)
{
    if (!InASC || !InAttrSet) return;

    ASC = InASC;
    AttributeSet = InAttrSet;

    ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute())
        .AddUObject(this, &UMyUserWidget::OnHPChanged);

    float InitHP = AttributeSet->GetHealth();
    float InitMaxHP = AttributeSet->GetMaxHealth();
    if (HealthBar && InitMaxHP > 0)
    {
        float Ratio = InitHP > 0 ? InitHP / InitMaxHP : 1.0f;
        HealthBar->SetPercent(Ratio);
    }
}

void UMyUserWidget::OnHPChanged(const FOnAttributeChangeData& Data)
{
    if (!AttributeSet) return;

    float NewHP = Data.NewValue;
    float MaxHP = AttributeSet->GetMaxHealth();

    if (HealthBar && MaxHP > 0.f)
    {
        HealthBar->SetPercent(NewHP / MaxHP);
    }
}