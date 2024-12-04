#include "ShootingTarget.h" 
#include "FPS_DemoGameState.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AFPS_DemoGameState::AFPS_DemoGameState()
{
}

void AFPS_DemoGameState::BeginPlay()
{
    Super::BeginPlay();

    SetImportantTargets();

    GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &AFPS_DemoGameState::HandleGameEnd, GameDuration, false);
}

void AFPS_DemoGameState::SetImportantTargets()
{
    if (Targets.Num() > 0)
    {
        // 洗牌数组以随机化元素
        for (int32 i = 0; i < Targets.Num(); i++)
        {
            int32 RandomIndex = FMath::RandRange(0, Targets.Num() - 1);
            Targets.Swap(i, RandomIndex);
        }

        // 设置前N个目标为“重要目标”
        for (int32 i = 0; i < FMath::Min(NumImportantTargets, Targets.Num()); i++)
        {
            if (Targets[i])
            {
                Targets[i]->bIsImportantTarget = true;
                Targets[i]->MeshComp->SetMaterial(0, Targets[i]->ImportantMaterial);
            }
        }
    }
}

void AFPS_DemoGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // 游戏结束时打印所有玩家分数
    int TotalScore = 0;
    for (const auto& PlayerScore : PlayerScores)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %d Score: %d"), PlayerScore.Key, PlayerScore.Value);
        TotalScore += PlayerScore.Value;
    }
    UE_LOG(LogTemp, Warning, TEXT("Total Time: %f"), GameDuration);
    UE_LOG(LogTemp, Warning, TEXT("Total Score: %d"), TotalScore);
}


void AFPS_DemoGameState::UpdatePlayerScore(int PlayerId, int ScoreToAdd, bool bIsImportant)
{
    if (bIsImportant)
    {
        ScoreToAdd *= 2;  // 如果是重要目标，分数翻倍
    }
    PlayerScores.FindOrAdd(PlayerId) += ScoreToAdd;
}

void AFPS_DemoGameState::HandleGameEnd()
{
    // 游戏结束的逻辑
    // ShowGameOverScreen();

    // 如果还需要调用 EndPlay，可以在这里显式调用，并提供一个理由
    EndPlay(EEndPlayReason::Type::Quit);
}