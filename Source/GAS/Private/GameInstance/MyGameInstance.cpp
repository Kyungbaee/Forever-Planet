// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/MyGameInstance.h"
#include "AbilitySystemGlobals.h"
#include "Engine/World.h"

void UMyGameInstance::Init()
{
    Super::Init();

    UAbilitySystemGlobals::Get().InitGlobalData();
}