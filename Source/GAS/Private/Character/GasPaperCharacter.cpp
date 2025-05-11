// Copyright Kyungbae Kim


#include "Character/GasPaperCharacter.h"
#include "AbilitySystemComponent.h"
#include "Player/GasCharacterPlayerState.h"
#include "GA_Jump.h"

AGasPaperCharacter::AGasPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGasPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

    // Enhanced Input 세팅
    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AGasPaperCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();
    if (PS)
    {
        UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
        if (ASC)
        {
            ASC->InitAbilityActorInfo(PS, this); // 클라이언트에서 ASC 초기화
        }
    }
}

void AGasPaperCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();
    if (PS)
    {
        UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
        if (ASC)
        {
            ASC->InitAbilityActorInfo(PS, this);

            // 서버에서 Ability 부여
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_Jump::StaticClass(), 1, 0));
        }
    }
}

void AGasPaperCharacter::JumpByGAS()
{
    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();

    if (PS)
    {
        UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
        if (ASC)
        {
            ASC->TryActivateAbilityByClass(UGA_Jump::StaticClass());
        }
    }
}

void AGasPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AGasPaperCharacter::JumpByGAS);
    }
}