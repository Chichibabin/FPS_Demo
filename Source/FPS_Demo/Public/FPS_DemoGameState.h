#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Blueprint/UserWidget.h"
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
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    float GetRemainingTime() const;

    // ���¿�ʼ��Ϸ
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void RestartGame();

    // ��ҷ���ӳ��
    UPROPERTY(VisibleAnywhere, Category = "Score")
    TMap<int, int> PlayerScores;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int TotalScore;

    // ��Ϸ��������
    void HandleGameEnd();

    // ��Ϸ������UI
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> GameHUDWidgetClass;

    UPROPERTY()
    UUserWidget* GameHUDWidgetInstance;

    // ��Ϸ����UI
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    UPROPERTY()
    UUserWidget* GameOverWidgetInstance;

    

};