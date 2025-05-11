// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void UMyGameInstance::OnStart()
{
    Super::OnStart();

    if (GetWorld())
    {
        GetWorld()->ServerTravel("/Game/StarterContent/Maps/GasEntry");
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GetWorld() is NULL!"));
    }


    if (IsDedicatedServerInstance())
    {
        UE_LOG(LogTemp, Warning, TEXT("Dedicated Server started. Now traveling to GasEntry..."));

        // 반드시 Content 경로 기준!
        GetWorld()->ServerTravel("/Game/StarterContent/Maps/GasEntry");
    }
}