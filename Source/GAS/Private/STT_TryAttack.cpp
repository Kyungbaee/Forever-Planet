// Copyright Kyungbae Kim


#include "STT_TryAttack.h"
#include "Character/GasPaperCharacter.h"

EStateTreeRunStatus USTT_TryAttack::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
    if (AGasPaperCharacter* MyChar = Cast<AGasPaperCharacter>(Context.GetOwner()))
    {
        MyChar->TryAttack();
        return EStateTreeRunStatus::Succeeded;
    }

    return EStateTreeRunStatus::Failed;
}