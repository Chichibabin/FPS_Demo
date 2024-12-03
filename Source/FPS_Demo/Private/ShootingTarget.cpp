#include "ShootingTarget.h"
#include "Components/StaticMeshComponent.h"

// ���캯��
AShootingTarget::AShootingTarget()
{
    // ��ʼ������
    ScoreValue = 10;  // ʾ������
    ScaleMultiplier = 0.5f;  // ʾ�����ű���

    // ��������ʼ���������
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    // ��������������¼�����
    MeshComp->SetSimulatePhysics(true);
    MeshComp->SetNotifyRigidBodyCollision(true);
    MeshComp->OnComponentHit.AddDynamic(this, &AShootingTarget::OnHit);
}

// ����Ϸ��ʼʱ����
void AShootingTarget::BeginPlay()
{
    Super::BeginPlay();
}

void AShootingTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // ��� OtherActor �Ƿ�Ϊ�ӵ��� AFPS_DemoProjectile
    AFPS_DemoProjectile* Projectile = Cast<AFPS_DemoProjectile>(OtherActor);
    if (Projectile)
    {
        // �����ӵ�
        if (OtherComp)
        {
            OtherComp->DestroyComponent();
        }

        // ��������߼�
        if (bIsImportantTarget)
        {
            // ����˫������
            UE_LOG(LogTemp, Warning, TEXT("Hit an important target! Double points awarded."));
            // ���˫�������߼�
        }
        else
        {
            // ������ͨ����
            UE_LOG(LogTemp, Warning, TEXT("Hit a regular target! Points awarded."));
            // �����ͨ�����߼�
        }


        if (!bHasBeenHitOnce)
        {
            // ��һ�α����У�����
            SetActorScale3D(GetActorScale3D() * ScaleMultiplier);
            bHasBeenHitOnce = true;
        }
        else
        {
            // �ڶ��α����У�����
            Destroy();
        }
    }
}
