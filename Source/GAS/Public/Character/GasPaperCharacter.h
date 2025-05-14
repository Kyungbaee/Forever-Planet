// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
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

	void JumpByGAS();
	void AttackByGAS();
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UFUNCTION()
	void HandleAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void NotifyAttackEnded();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* AttackAction;
};
