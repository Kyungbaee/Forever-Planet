// Copyright Kyungbae Kim


#include "Character/GasPaperCharacter.h"
#include "AbilitySystemComponent.h"
#include "Player/GasCharacterPlayerState.h"
#include "Ability/GA_Jump.h"
#include "Ability/GA_Attack.h"
#include "Ability/GA_Knockback.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "GameInstance/CharacterAnimInstance.h"

AGasPaperCharacter::AGasPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

UPaperZDAnimInstance* AGasPaperCharacter::GetZDAnimInstance() const
{
    return Cast<UPaperZDAnimInstance>(GetAnimInstance());
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

        OnTakeAnyDamage.AddDynamic(this, &AGasPaperCharacter::HandleAnyDamage);
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
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_Attack::StaticClass(), 1, 0));
            ASC->GiveAbility(FGameplayAbilitySpec(UGA_Knockback::StaticClass(), 1, 0));
        }

        OnTakeAnyDamage.AddDynamic(this, &AGasPaperCharacter::HandleAnyDamage);
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

void AGasPaperCharacter::AttackByGAS()
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

void AGasPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AGasPaperCharacter::JumpByGAS);
        EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &AGasPaperCharacter::AttackByGAS);
    }
}

void AGasPaperCharacter::HandleAnyDamage(
    AActor* DamagedActor,
    float Damage,
    const UDamageType* DamageType,
    AController* InstigatedBy,
    AActor* DamageCauser)
{
    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();
    if (!PS) return;

    UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
    if (!ASC) return;

    FGameplayEventData EventData;
    EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Knockback"));
    EventData.Instigator = DamageCauser;
    EventData.Target = this;

    ASC->HandleGameplayEvent(EventData.EventTag, &EventData);
}

void AGasPaperCharacter::NotifyAttackEnded()
{
    AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>();
    if (!PS) return;

    if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
    {
        TArray<FGameplayAbilitySpec> Specs = ASC->GetActivatableAbilities();
        for (FGameplayAbilitySpec& Spec : Specs)
        {
            UGA_Attack* AttackAbility = Cast<UGA_Attack>(Spec.GetPrimaryInstance());
            if (AttackAbility && AttackAbility->IsActive())
            {
                AttackAbility->OnAttackEnded();
                break;
            }
        }
    }
}
