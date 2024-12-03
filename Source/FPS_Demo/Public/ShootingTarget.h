#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../FPS_DemoProjectile.h"  // �����ӵ����ͷ�ļ�
#include "ShootingTarget.generated.h"


UCLASS()
class FPS_DEMO_API AShootingTarget : public AActor
{
    GENERATED_BODY()

public:
    // ����Ĭ������
    AShootingTarget();

    // ��̬������������ڷ�����Ӿ�չʾ
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    // �Ƿ�Ϊ����ҪĿ�ꡱ�ı�־
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    bool bIsImportantTarget;

    // ��õĻ���
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    int ScoreValue;  

    // ���ű���
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    float ScaleMultiplier;  

protected:
    // ��Ϸ��ʼʱ����
    virtual void BeginPlay() override;

public:
    // �ӵ�����ʱ���õĺ���
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
    bool bHasBeenHitOnce = false;  // ����Ƿ��ѱ����й�һ��
};
