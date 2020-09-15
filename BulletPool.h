// Fill out your copyright notice in the Description page of Project Settings.
//This Actor class was discontinued

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "Containers/Array.h"
#include "BulletPool.generated.h"

UCLASS()
class GAMEPATDEVAS1_API ABulletPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletPool();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "Bullet", EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ABullet> SOICBullet;

	int BulletAmountStored = 50;

	//ABullet* GetPooledObject();

	TArray<ABullet*> CurrentBulletPool;

};
