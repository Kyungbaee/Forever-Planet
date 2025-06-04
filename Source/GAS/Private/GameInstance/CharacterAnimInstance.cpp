// Copyright Kyungbae Kim


#include "GameInstance/CharacterAnimInstance.h"

void UCharacterAnimInstance::OnTick_Implementation(float DeltaTime)
{
    if (const AActor* Owner = GetOwningActor())
    {
        if (const AGasPaperCharacter* Char = Cast<AGasPaperCharacter>(Owner))
        {
            IsAttacking = Char->IsAttacking();
        }
    }
}
