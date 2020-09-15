// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "MainPlatChar.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Creates the Static Mesh component for the main body and set it as the RootComponent
	BulletBody = CreateDefaultSubobject<UStaticMeshComponent>("Main Body");
	RootComponent = BulletBody;

	//Create Box collision for Enenmy and attach it to main body mesh EnemyBody
	BulletColi = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	BulletColi->SetupAttachment(BulletBody);

	TimeTillReturn = 5;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(PoolTimer, this, &ABullet::UpdateTimer, 1.0f, true);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + Move);
}


void ABullet::DeActivate() {
	Destroy();
}


void ABullet::UpdateTimer() {
	--TimeTillReturn;
	if (TimeTillReturn < 1) {
		CountDownFinished();
	}
}

void ABullet::CountDownFinished() {
	DeActivate();
}


void ABullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	AMainPlatChar* Player = Cast<AMainPlatChar>(OtherActor);
	if (Player == nullptr && OtherActor != this) {
		DeActivate();
	}

}
