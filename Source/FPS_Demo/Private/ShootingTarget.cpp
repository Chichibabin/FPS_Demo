#include "ShootingTarget.h"
#include "Components/StaticMeshComponent.h"

// 构造函数
AShootingTarget::AShootingTarget()
{
    // 初始化参数
    ScoreValue = 10;  // 示例分数
    ScaleMultiplier = 0.5f;  // 示例缩放倍数

    // 创建并初始化网格组件
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    // 启用物理和命中事件监听
    MeshComp->SetSimulatePhysics(true);
    MeshComp->SetNotifyRigidBodyCollision(true);
    MeshComp->OnComponentHit.AddDynamic(this, &AShootingTarget::OnHit);
}

// 当游戏开始时调用
void AShootingTarget::BeginPlay()
{
    Super::BeginPlay();
}

void AShootingTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 检查 OtherActor 是否为子弹类 AFPS_DemoProjectile
    AFPS_DemoProjectile* Projectile = Cast<AFPS_DemoProjectile>(OtherActor);
    if (Projectile)
    {
        // 销毁子弹
        if (OtherComp)
        {
            OtherComp->DestroyComponent();
        }

        // 处理积分逻辑
        if (bIsImportantTarget)
        {
            // 增加双倍积分
            UE_LOG(LogTemp, Warning, TEXT("Hit an important target! Double points awarded."));
            // 添加双倍积分逻辑
        }
        else
        {
            // 增加普通积分
            UE_LOG(LogTemp, Warning, TEXT("Hit a regular target! Points awarded."));
            // 添加普通积分逻辑
        }


        if (!bHasBeenHitOnce)
        {
            // 第一次被击中，缩放
            SetActorScale3D(GetActorScale3D() * ScaleMultiplier);
            bHasBeenHitOnce = true;
        }
        else
        {
            // 第二次被击中，销毁
            Destroy();
        }
    }
}
