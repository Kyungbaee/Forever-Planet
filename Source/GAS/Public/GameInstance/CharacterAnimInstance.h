// Copyright Kyungbae Kim

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDAnimNotify.h"
#include "CharacterAnimInstance.generated.h"

UCLASS()
class GAS_API UCharacterAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    bool IsAttacking = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Knockback")
    bool IsKnockback = false;

    UFUNCTION(BlueprintCallable)
    void SetIsAttacking(bool bValue) { IsAttacking = bValue; }

    UFUNCTION(BlueprintCallable)
    void SetIsKnockback(bool bValue) { IsKnockback = bValue; }
};
