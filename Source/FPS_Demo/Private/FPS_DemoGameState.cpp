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

    // 如果Widget类已经指定
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
    return (RemainingTime > 0 ? RemainingTime : 0); // 如果计时器已经结束，返回0
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

void AFPS_DemoGameState::UpdatePlayerScore(int PlayerId, int ScoreToAdd, bool bIsImportant)
{
    if (bIsImportant)
    {
        ScoreToAdd *= 2;  // 如果是重要目标，分数翻倍
    }
    PlayerScores.FindOrAdd(PlayerId) += ScoreToAdd;
    TotalScore += ScoreToAdd;
}

void AFPS_DemoGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // 游戏结束时打印所有玩家分数
    for (const auto& PlayerScore : PlayerScores)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %d Score: %d"), PlayerScore.Key, PlayerScore.Value);
    }
    UE_LOG(LogTemp, Warning, TEXT("Total Time: %f"), GameDuration);
    UE_LOG(LogTemp, Warning, TEXT("Total Score: %d"), TotalScore);
}


void AFPS_DemoGameState::HandleGameEnd()
{
    // 如果Widget类已经指定
    if (GameOverWidgetClass)
    {
        GameOverWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
        if (GameOverWidgetInstance)
        {
            GameOverWidgetInstance->AddToViewport();
        }
    }

    // 暂停游戏
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->SetPause(true); // 暂停游戏

        // 显示鼠标指针
        PlayerController->bShowMouseCursor = true;

        // 解锁鼠标并设置输入模式为 UI 模式
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);
    }

    // 如果还需要调用 EndPlay，可以在这里显式调用，并提供一个理由
    EndPlay(EEndPlayReason::Type::Quit);
}

void AFPS_DemoGameState::RestartGame()
{
    // 获取玩家控制器并取消暂停
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // 取消暂停
        PlayerController->SetPause(false);

        // 隐藏鼠标指针
        PlayerController->bShowMouseCursor = false;

        // 恢复输入模式为游戏模式
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }

    // 重新加载当前关卡
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
