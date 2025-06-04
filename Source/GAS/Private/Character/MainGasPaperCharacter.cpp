// Copyright Kyungbae Kim


#include "Character/MainGasPaperCharacter.h"


void AMainGasPaperCharacter::BeginPlay()
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


void AMainGasPaperCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();
    if (PS)
    {
        UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
        if (ASC)
        {
            ASC->InitAbilityActorInfo(PS, this); // 클라이언트에서 ASC 초기화
            InitAttributes();

            if (APlayerController* PC = Cast<APlayerController>(GetController()))
            {
                if (AMyHUD* MyHUD = Cast<AMyHUD>(PC->GetHUD()))
                {
                    MyHUD->InitHUD(ASC, MyAttributeSet);
                }
            }
        }
    }
}

void AMainGasPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainGasPaperCharacter::JumpByGAS);
        EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainGasPaperCharacter::AttackByGAS);
    }
}


void AMainGasPaperCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();
    if (PS)
    {
        UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
        if (ASC)
        {
            ASC->InitAbilityActorInfo(PS, this);

            if (!ASC->GetSet<UMyAttributeSet>())
            {
                ASC->AddAttributeSetSubobject(NewObject<UMyAttributeSet>(ASC));
            }

            InitAttributes();

            // 서버에서 Ability 부여
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_Jump::StaticClass(), 1, 0));
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_Attack::StaticClass(), 1, 0));
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_Knockback::StaticClass(), 1, 0));
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_ReceiveDamage::StaticClass(), 1, 0));
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_Die::StaticClass(), 1, 0));

            ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Type.Player")));

            if (APlayerController* PC = Cast<APlayerController>(GetController()))
            {
                if (AMyHUD* MyHUD = Cast<AMyHUD>(PC->GetHUD()))
                {
                    MyHUD->InitHUD(ASC, MyAttributeSet);
                }
            }
        }
    }
}

void AMainGasPaperCharacter::JumpByGAS()
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

void AMainGasPaperCharacter::AttackByGAS()
{
    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();

    if (PS)
    {
        UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
        if (ASC)
        {
            ASC->TryActivateAbilityByClass(UGA_Attack::StaticClass());
        }
    }
}