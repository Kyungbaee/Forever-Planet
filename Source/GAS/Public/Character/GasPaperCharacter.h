// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperFlipbookComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "AbilitySystemComponent.h"
#include "GasPaperCharacter.generated.h"

UCLASS(Abstract)
class GAS_API AGasPaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	AGasPaperCharacter();
	UPaperZDAnimInstance* GetZDAnimInstance() const;

protected:
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void JumpByGAS();
	void AttackByGAS();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UAbilitySystemComponent* GetASC() const;
	UPaperFlipbookComponent* GetFlipbookComponent() const;

	UFUNCTION()
	void HandleAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void NotifyAttackEnded();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetHitColor();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* AttackAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComp;
};
