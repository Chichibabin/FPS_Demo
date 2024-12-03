#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../FPS_DemoProjectile.h"  // 包含子弹类的头文件
#include "ShootingTarget.generated.h"


UCLASS()
class FPS_DEMO_API AShootingTarget : public AActor
{
    GENERATED_BODY()

public:
    // 设置默认属性
    AShootingTarget();

    // 静态网格组件，用于方块的视觉展示
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    // 是否为“重要目标”的标志
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    bool bIsImportantTarget;

    // 获得的积分
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    int ScoreValue;  

    // 缩放倍数
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    float ScaleMultiplier;  

protected:
    // 游戏开始时调用
    virtual void BeginPlay() override;

public:
    // 子弹命中时调用的函数
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
    bool bHasBeenHitOnce = false;  // 标记是否已被击中过一次
};
