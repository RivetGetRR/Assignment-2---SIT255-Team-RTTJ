// Fill out your copyright notice in the Description page of Project Settings.
//This Actor class was discontinued
//Majority of code used was paraphrased using this example on youtube:
//(How to use Object Pooling in Unreal Engine 4, 2018) full reference in report

#include "BulletPool.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "Containers/Array.h"
#include "Engine/Engine.h"

// Sets default values
ABulletPool::ABulletPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ABulletPool::BeginPlay()
{
	Super::BeginPlay();
	/*
	if (SOICBullet != NULL) {
		if (GetWorld() != NULL) {
			for (int o = 0; o < BulletAmountStored; ++o) {
				ABullet* CurrentBullet = GetWorld()->SpawnActor<ABullet>(SOICBullet, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
				CurrentBullet->SetActiveState(false);
				CurrentBulletPool.Add(CurrentBullet);
				UE_LOG(LogTemp, Log, TEXT("TArray Size : %i"), CurrentBulletPool.Num());
				UE_LOG(LogTemp, Log, TEXT("Created Bullet And Stored in Pool, Number of Bullets : %i"), o + 1);
			}
		}
	}
	//Test
	ABullet* Test = GetPooledObject();
	*/
}

// Called every frame
void ABulletPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
ABullet* ABulletPool::GetPooledObject() {
	
	if (CurrentBulletPool[0] != nullptr) {
		for (int a = 0; a != CurrentBulletPool.Num(); ++a) {
			UE_LOG(LogTemp, Log, TEXT("Attempting the BOOLet: %i"), a + 1);
			if (CurrentBulletPool[a] != nullptr) {
				UE_LOG(LogTemp, Log, TEXT("BOOLet: %i"), a + 1);
				return CurrentBulletPool[a];
			}
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Attempted To Get"));
	return nullptr;
}
*/