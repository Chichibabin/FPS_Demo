#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPS_DemoGameState.generated.h"

UCLASS()
class FPS_DEMO_API AFPS_DemoGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    // 定义构造函数
    AFPS_DemoGameState();

    // 定义游戏初始化和结束函数
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // 设置重要目标的函数
    void SetImportantTargets();

    // 更新玩家分数的函数
    void UpdatePlayerScore(int PlayerId, int ScoreToAdd, bool bIsImportant);

    // 游戏时间
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    float GameDuration;  // 游戏时间限制，单位为秒

    // 计时器句柄
    FTimerHandle GameTimerHandle;

    // 玩家分数映射
    UPROPERTY(VisibleAnywhere, Category = "Score")
    TMap<int, int> PlayerScores;

    // 游戏结束处理
    void HandleGameEnd();
};