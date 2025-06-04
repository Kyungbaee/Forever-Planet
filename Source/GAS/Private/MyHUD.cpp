// Copyright Kyungbae Kim


#include "MyHUD.h"

AMyHUD::AMyHUD()
{
    static ConstructorHelpers::FClassFinder<UMyUserWidget> WidgetClassFinder(TEXT("/Game/Widget/WBP_PlayerHUD"));
    if (WidgetClassFinder.Succeeded())
    {
        HUDWidgetClass = WidgetClassFinder.Class;
    }
}

void AMyHUD::InitHUD(UAbilitySystemComponent* ASC, UMyAttributeSet* AttrSet)
{
    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UMyUserWidget>(GetWorld(), HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            HUDWidget->BindToAttributes(ASC, AttrSet);
        }
    }
}