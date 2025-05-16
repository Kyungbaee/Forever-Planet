// Copyright Kyungbae Kim


#include "Ability/GA_Knockback.h"
#include "Character/GasPaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "GameInstance/CharacterAnimInstance.h"

UGA_Knockback::UGA_Knockback()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 트리거 방식 설정: 이벤트 태그 "Event.Knockback"이 들어오면 자동 발동
    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(FName("Event.Knockback"));
    TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
    AbilityTriggers.Add(TriggerData);

    // 기타 태그들
    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Knockback")));
    ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Knockback")));
}

void UGA_Knockback::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    if (!ActorInfo || !ActorInfo->AvatarActor.IsValid()) return;

    AActor* Avatar = ActorInfo->AvatarActor.Get();
    const AActor* CauserConst = Cast<AActor>(TriggerEventData->Instigator.Get());
    AActor* Causer = const_cast<AActor*>(CauserConst);

    if (!Causer || !Avatar)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (AGasPaperCharacter* MyChar = Cast<AGasPaperCharacter>(ActorInfo->AvatarActor))
    {
        if (UCharacterAnimInstance* AnimInstance = Cast<UCharacterAnimInstance>(MyChar->GetZDAnimInstance()))
        {
            AnimInstance->SetIsKnockback(true);
        }
    }

    StartLocation = Avatar->GetActorLocation();
    FVector Direction = (StartLocation - Causer->GetActorLocation()).GetSafeNormal();
    TargetLocation = StartLocation + Direction * KnockbackStrength;
    ElapsedTime = 0.f;


    // Tick 시작
    GetWorld()->GetTimerManager().SetTimer(KnockbackTimerHandle, this, &UGA_Knockback::TickKnockback, 0.01f, true);
}

void UGA_Knockback::TickKnockback()
{
    ElapsedTime += 0.01f;
    float Alpha = FMath::Clamp(ElapsedTime / KnockbackDuration, 0.f, 1.f);

    FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);

    if (AActor* Avatar = GetAvatarActorFromActorInfo())
    {
        Avatar->SetActorLocation(NewLocation, true);
    }

    if (Alpha >= 1.f)
    {
        EndKnockback();
    }
}

void UGA_Knockback::EndKnockback()
{
    GetWorld()->GetTimerManager().ClearTimer(KnockbackTimerHandle);

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

    AGasPaperCharacter* MyChar = Cast<AGasPaperCharacter>(GetAvatarActorFromActorInfo());
    if (MyChar && MyChar->GetSprite())
    {
        MyChar->GetSprite()->SetSpriteColor(FLinearColor::White);
    }
}