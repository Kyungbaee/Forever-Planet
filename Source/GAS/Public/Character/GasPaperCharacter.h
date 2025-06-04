// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperZDAnimInstance.h"
#include "PaperFlipbookComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "AbilitySystemComponent.h"
#include "Playerstate/GasCharacterPlayerState.h"
#include "Effect/GE_InitAttributes.h"
#include "Attribute/MyAttributeSet.h"
#include "Ability/GA_Jump.h"
#include "Ability/GA_Attack.h"
#include "Ability/GA_Knockback.h"
#include "Ability/GA_ReceiveDamage.h"
#include "Ability/GA_Die.h"
#include "Ability/GA_Destroy.h"
#include "Net/UnrealNetwork.h"
#include "MyHUD.h"
#include "GasPaperCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxHealthChanged, float, NewMaxHealth, float, OldMaxHealth);

UCLASS(Abstract)
class GAS_API AGasPaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	AGasPaperCharacter();
	UPaperZDAnimInstance* GetZDAnimInstance() const;
	UPaperFlipbookComponent* GetFlipbookComponent() const;

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void HandleZeroHealth();
	void InitAttributes();
	void TryAttack();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetHitColor();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ResetHitColor();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetKnockback(bool bState);

	UFUNCTION(BlueprintCallable)
	void NotifyAttackEnded();

	UPROPERTY(ReplicatedUsing = OnRep_IsAttacking)
	bool bIsAttacking;

	bool IsAttacking() const { return bIsAttacking; }
	void SetIsAttacking(bool bNewState);


	UFUNCTION()
	void OnRep_IsAttacking();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	UAbilitySystemComponent* GetMyAbilitySystemComponent() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UMyAttributeSet* MyAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* CharacterSprite;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnMaxHealthChanged OnMaxHealthChanged;
};
