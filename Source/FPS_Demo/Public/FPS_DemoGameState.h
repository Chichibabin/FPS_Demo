#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPS_DemoGameState.generated.h"

UCLASS()
class FPS_DEMO_API AFPS_DemoGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    // ���幹�캯��
    AFPS_DemoGameState();

    // ������Ϸ��ʼ���ͽ�������
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // ������ҪĿ��ĺ���
    void SetImportantTargets();

    // ������ҷ����ĺ���
    void UpdatePlayerScore(int PlayerId, int ScoreToAdd, bool bIsImportant);

    // ��Ϸʱ��
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    float GameDuration;  // ��Ϸʱ�����ƣ���λΪ��

    // ��ʱ�����
    FTimerHandle GameTimerHandle;

    // ��ҷ���ӳ��
    UPROPERTY(VisibleAnywhere, Category = "Score")
    TMap<int, int> PlayerScores;

    // ��Ϸ��������
    void HandleGameEnd();
};