// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Bullet.generated.h"

UCLASS()
class GAMEPATDEVAS1_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Move = FVector(0.0f, 35.0f, 0.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Property for Main mesh body
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BulletBody;

	//Property for Box Collision Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* BulletColi;


	int32 TimeTillReturn;

	FTimerHandle PoolTimer;

	void DeActivate();

	void UpdateTimer();

	void CountDownFinished();

	//Function to Detect when the object has collided with another and return some values
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
