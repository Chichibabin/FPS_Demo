#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPS_DemoGameState.generated.h"

class AShootingTarget;  // ǰ������

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

    // �洢����Ŀ�귽�������
    UPROPERTY(VisibleAnywhere, Category = "Gameplay")
    TArray<AShootingTarget*> Targets;

    // ������ҪĿ��ĺ���������ʵ�־����߼�
    void SetImportantTargets();

    // ������ҷ����ĺ���
    void UpdatePlayerScore(int PlayerId, int ScoreToAdd, bool bIsImportant);

    // ��Ϸʱ��
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    float GameDuration;  // ��Ϸʱ�����ƣ���λΪ��
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    int NumImportantTargets;  // ��ҪĿ������

    // ��ʱ�����
    FTimerHandle GameTimerHandle;

    // ��ҷ���ӳ��
    UPROPERTY(VisibleAnywhere, Category = "Score")
    TMap<int, int> PlayerScores;

    // ��Ϸ��������
    void HandleGameEnd();
};