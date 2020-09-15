// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "KillFloor.generated.h"

UCLASS()
class GAMEPATDEVAS1_API AKillFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Property for Mesh component for the Floor body
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MainFloor;

	//Property for Box Collision Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* FloorColi;
	
	//Function to Detect when the object has collided with another and return some values
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
