// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "AdvancedEnemy.generated.h"

UCLASS()
class GAMEPATDEVAS1_API AAdvancedEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAdvancedEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Used to find which direction it will travel
	FVector MovingWith = FVector(5.0,0.f,0.f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Property for Mesh component for the Advanced Enemy body
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* AEnemyBody;

	//Property for Box Collision Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* AEnemyColi;

	//Variables for the Timer
	int32 MovementDelay;

	FTimerHandle MoveTimer;


	//Movement Functions 
	void MoveTo();

	void Moving();
	
	//Functions for the Timer
	void UpdateTimer();

	void CountDownFinished();

	//Function to Detect when the object has collided with another and return some values
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
