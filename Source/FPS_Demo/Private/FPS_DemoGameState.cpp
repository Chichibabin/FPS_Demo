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

    // ���Widget���Ѿ�ָ��
    if (GameHUDWidgetClass)
    {
        GameHUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameHUDWidgetClass);
        if (GameHUDWidgetInstance)
        {
            GameHUDWidgetInstance->AddToViewport();
        }
    }

    GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &AFPS_DemoGameState::HandleGameEnd, GameDuration, false);
}

float AFPS_DemoGameState::GetRemainingTime() const
{
    float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(GameTimerHandle);
    return (RemainingTime > 0 ? RemainingTime : 0); // �����ʱ���Ѿ�����������0
}

void AFPS_DemoGameState::SetImportantTargets()
{
    if (Targets.Num() > 0)
    {
        // ϴ�������������Ԫ��
        for (int32 i = 0; i < Targets.Num(); i++)
        {
            int32 RandomIndex = FMath::RandRange(0, Targets.Num() - 1);
            Targets.Swap(i, RandomIndex);
        }

        // ����ǰN��Ŀ��Ϊ����ҪĿ�ꡱ
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

void AFPS_DemoGameState::UpdatePlayerScore(int PlayerId, int ScoreToAdd, bool bIsImportant)
{
    if (bIsImportant)
    {
        ScoreToAdd *= 2;  // �������ҪĿ�꣬��������
    }
    PlayerScores.FindOrAdd(PlayerId) += ScoreToAdd;
    TotalScore += ScoreToAdd;
}

void AFPS_DemoGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // ��Ϸ����ʱ��ӡ������ҷ���
    for (const auto& PlayerScore : PlayerScores)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %d Score: %d"), PlayerScore.Key, PlayerScore.Value);
    }
    UE_LOG(LogTemp, Warning, TEXT("Total Time: %f"), GameDuration);
    UE_LOG(LogTemp, Warning, TEXT("Total Score: %d"), TotalScore);
}


void AFPS_DemoGameState::HandleGameEnd()
{
    // ���Widget���Ѿ�ָ��
    if (GameOverWidgetClass)
    {
        GameOverWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
        if (GameOverWidgetInstance)
        {
            GameOverWidgetInstance->AddToViewport();
        }
    }

    // ��ͣ��Ϸ
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->SetPause(true); // ��ͣ��Ϸ

        // ��ʾ���ָ��
        PlayerController->bShowMouseCursor = true;

        // ������겢��������ģʽΪ UI ģʽ
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);
    }

    // �������Ҫ���� EndPlay��������������ʽ���ã����ṩһ������
    EndPlay(EEndPlayReason::Type::Quit);
}

void AFPS_DemoGameState::RestartGame()
{
    // ��ȡ��ҿ�������ȡ����ͣ
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // ȡ����ͣ
        PlayerController->SetPause(false);

        // �������ָ��
        PlayerController->bShowMouseCursor = false;

        // �ָ�����ģʽΪ��Ϸģʽ
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }

    // ���¼��ص�ǰ�ؿ�
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
