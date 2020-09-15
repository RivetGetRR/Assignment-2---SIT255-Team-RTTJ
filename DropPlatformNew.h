// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MainPlatChar.h"
#include "DropPlatformNew.generated.h"

UCLASS()
class GAMEPATDEVAS1_API ADropPlatformNew : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropPlatformNew();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Activated = false;

	bool DropNow = false;

	FVector Holder;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxColi;

	UPROPERTY(EditAnywhere)
		int32 DropCountDown;

	FTimerHandle DropperTH;


	void UpdateTimer();
	void DropDown();
	void DroppingFinished();


	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
