// Copyright Kyungbae Kim


#include "Character/GasPaperCharacter.h"
#include "GameInstance/CharacterAnimInstance.h"

AGasPaperCharacter::AGasPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    SetReplicatingMovement(true);

    AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
    MyAttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("MyAttributeSet"));
    AbilitySystemComp->AddAttributeSetSubobject(MyAttributeSet);
    AbilitySystemComp->SetIsReplicated(true);
    AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UPaperZDAnimInstance* AGasPaperCharacter::GetZDAnimInstance() const
{
    return Cast<UPaperZDAnimInstance>(GetAnimInstance());
}

void AGasPaperCharacter::BeginPlay()
{
    Super::BeginPlay();
}

float AGasPaperCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    FGameplayEventData EventData;
    EventData.EventTag = FGameplayTag::RequestGameplayTag("Event.Damage");
    EventData.EventMagnitude = DamageAmount;
    EventData.Target = this;
    EventData.Instigator = DamageCauser;

    if (UAbilitySystemComponent* ASC = GetMyAbilitySystemComponent())
    {
        ASC->HandleGameplayEvent(EventData.EventTag, &EventData);
    }

    return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AGasPaperCharacter::HandleZeroHealth()
{
    if (UAbilitySystemComponent* ASC = GetMyAbilitySystemComponent())
    {
        if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Type.Player")))
        {
            ASC->TryActivateAbilityByClass(UGA_Die::StaticClass());
        }
        else if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Type.Enemy")))
        {
            ASC->TryActivateAbilityByClass(UGA_Destroy::StaticClass());
        }
    }
}

void AGasPaperCharacter::InitAttributes()
{
    UAbilitySystemComponent* ASC = GetMyAbilitySystemComponent();

    if (!ASC) return;

    FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
    Context.AddSourceObject(this);

    FGameplayEffectSpecHandle NewHandle = ASC->MakeOutgoingSpec(
        UGE_InitAttributes::StaticClass(), 1.0f, Context);

    if (NewHandle.IsValid())
    {
        ASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
    }
}

UAbilitySystemComponent* AGasPaperCharacter::GetMyAbilitySystemComponent() const
{
    if (AGasCharacterPlayerState* PS = GetPlayerState<AGasCharacterPlayerState>())
    {
        return PS->GetAbilitySystemComponent();
    }
    return AbilitySystemComp;
}

UPaperFlipbookComponent* AGasPaperCharacter::GetFlipbookComponent() const
{
    return Cast<UPaperFlipbookComponent>(GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
}

void AGasPaperCharacter::TryAttack()
{
    if (UAbilitySystemComponent* ASC = GetMyAbilitySystemComponent())
    {
        if (!ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Cooldown.Attack")))
        {
            ASC->TryActivateAbilityByClass(UGA_Attack::StaticClass());
        }
    }
}

void AGasPaperCharacter::NotifyAttackEnded()
{
    UAbilitySystemComponent* ASC = GetMyAbilitySystemComponent();
    if (ASC)
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

void AGasPaperCharacter::SetIsAttacking(bool bNewState)
{
    if (bIsAttacking == bNewState)
        return;

    bIsAttacking = bNewState;

    // 직접 호출 시 AnimInstance도 갱신
    OnRep_IsAttacking();
}

void AGasPaperCharacter::OnRep_IsAttacking()
{
    if (UCharacterAnimInstance* Anim = Cast<UCharacterAnimInstance>(GetZDAnimInstance()))
    {
        Anim->SetIsAttacking(bIsAttacking);
    }
}

void AGasPaperCharacter::Multicast_SetHitColor_Implementation()
{
    if (UPaperFlipbookComponent* FlipbookComponent = GetFlipbookComponent())
    {
        FLinearColor HitColor(0.3f, 0.3f, 0.3f, 1.0f);
        FlipbookComponent->SetSpriteColor(HitColor);
    }
}

void AGasPaperCharacter::Multicast_ResetHitColor_Implementation()
{
    if (GetSprite())
    {
        GetSprite()->SetSpriteColor(FLinearColor::White);
    }
}

void AGasPaperCharacter::Multicast_SetKnockback_Implementation(bool bState)
{
    if (UCharacterAnimInstance* KnockbackAnim = Cast<UCharacterAnimInstance>(GetZDAnimInstance()))
    {
        KnockbackAnim->SetIsKnockback(bState);
    }
}

void AGasPaperCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 복제할 변수 등록
    DOREPLIFETIME(AGasPaperCharacter, bIsAttacking);
}