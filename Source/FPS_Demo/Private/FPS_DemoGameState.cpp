#include "FPS_DemoGameState.h"
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

void AFPS_DemoGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // ��Ϸ����ʱ��ӡ������ҷ���
    int TotalScore = 0;
    for (const auto& PlayerScore : PlayerScores)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %d Score: %d"), PlayerScore.Key, PlayerScore.Value);
        TotalScore += PlayerScore.Value;
    }
    UE_LOG(LogTemp, Warning, TEXT("Total Time: %f"), GameDuration);
    UE_LOG(LogTemp, Warning, TEXT("Total Score: %d"), TotalScore);
}

void AFPS_DemoGameState::SetImportantTargets()
{
    // �������N������Ϊ����ҪĿ�ꡱ
    // ʵ��ϸ�������ڷ�������ɺ͹����߼�
}

void AFPS_DemoGameState::UpdatePlayerScore(int PlayerId, int ScoreToAdd, bool bIsImportant)
{
    if (bIsImportant)
    {
        ScoreToAdd *= 2;  // �������ҪĿ�꣬��������
    }
    PlayerScores.FindOrAdd(PlayerId) += ScoreToAdd;
}

void AFPS_DemoGameState::HandleGameEnd()
{
    // ��Ϸ�������߼�
    // ShowGameOverScreen();

    // �������Ҫ���� EndPlay��������������ʽ���ã����ṩһ������
    EndPlay(EEndPlayReason::Type::Quit);
}