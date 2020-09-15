// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "BasicEnemy.generated.h"

UCLASS()
class GAMEPATDEVAS1_API ABasicEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//used to get a random number to determine direction and movement of Enemy
	int32 SetDirection;

	//Stores the simple movment pattern as FVector
	FVector MovingAs;


	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Property for Mesh component for the Enemy body
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* EnemyBody;

	//Property for Box Collision Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* EnemyColi;
	

	//Movement Functions
	void MovementTo();

	void Moving();

	//Function to Detect when the object has collided with another and return some values
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
