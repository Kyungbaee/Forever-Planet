// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Attribute/MyAttributeSet.h"
#include "MyUserWidget.h"
#include "MyHUD.generated.h"

UCLASS()
class GAS_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    AMyHUD();
    void InitHUD(UAbilitySystemComponent* ASC, UMyAttributeSet* AttrSet);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMyUserWidget> HUDWidgetClass;

    UPROPERTY()
    UMyUserWidget* HUDWidget;
};
