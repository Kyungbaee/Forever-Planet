// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameInstance/GASGameModeBase.h"

AGASGameModeBase::AGASGameModeBase()
{
    DefaultPawnClass = AGasPaperCharacter::StaticClass();
    PlayerStateClass = AGasCharacterPlayerState::StaticClass();
}