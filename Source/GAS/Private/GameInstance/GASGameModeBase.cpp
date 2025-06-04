// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameInstance/GASGameModeBase.h"

AGASGameModeBase::AGASGameModeBase()
{
    DefaultPawnClass = AGasPaperCharacter::StaticClass();
    PlayerStateClass = AGasCharacterPlayerState::StaticClass();
    HUDClass = AMyHUD::StaticClass();

    static ConstructorHelpers::FClassFinder<AEnemyGasPaperCharacter> EnemyBPClass(TEXT("/Game/Blueprints/KidRed/BP_AI_Substitute"));
    if (EnemyBPClass.Succeeded())
    {
        EnemyClass = EnemyBPClass.Class;
    }
}

void AGASGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority()) // 서버만
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        FVector SpawnLocation(-1950.f, 1600.f, 100.f);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AEnemyGasPaperCharacter* Enemy =  GetWorld()->SpawnActor<AEnemyGasPaperCharacter>(
            EnemyClass, SpawnLocation, SpawnRotation, SpawnParams
        );

        if (Enemy)
        {
            AEnemyAIController* AIController = Cast<AEnemyAIController>(Enemy->GetController());

            if (!AIController)
            {
                AIController = GetWorld()->SpawnActor<AEnemyAIController>(
                    AEnemyAIController::StaticClass(),
                    SpawnLocation,
                    SpawnRotation
                );
                AIController->Possess(Enemy);
            }
        }
    }
}

void AGASGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // 1프레임 딜레이 후 Pawn 가져오기 (바로는 GetPawn()이 null일 수 있음)
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, NewPlayer]()
        {
            if (APawn* PlayerPawn = NewPlayer->GetPawn())
            {
                for (TActorIterator<AEnemyAIController> It(GetWorld()); It; ++It)
                {
                    It->SetTargetPlayer(PlayerPawn);
                }
            }
        }, 0.5f, false); // 0.5초 후 1회 실행
}