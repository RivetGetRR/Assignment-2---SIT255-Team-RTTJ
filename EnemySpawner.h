// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BasicEnemy.h"
#include "AdvancedEnemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GAMEPATDEVAS1_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Create instance of Basic Enemy is order to spawn them, done through TSubclassOf
	UPROPERTY(Category = "Enemy", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ABasicEnemy> BEnemy;

	//Create instance of Advanced Enemy is order to spawn them, done through TSubclassOf
	UPROPERTY(Category = "Enemy", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AAdvancedEnemy> AEnemy;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Property for Mesh component for the Spawner body
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ESpawnerBody;


	//Properties for Spawn Control/the Spawn ARea Size
	UPROPERTY(Category = "EnemySpawn", EditAnywhere, BlueprintReadWrite)
		float SpawnAreaMaxWidth; //Width of the Area


	UPROPERTY(Category = "EnemySpawn", EditAnywhere, BlueprintReadWrite)
		float SpawnAreaMaxDepth; //Length of the Area


	UPROPERTY(Category = "EnemySpawn", EditAnywhere, BlueprintReadWrite)
		float SpawnHeight; //Height at which the objects will spawn

	//Varaibles used for Timer
	int32 SpawnDelay;

	FTimerHandle SpawnerTimer;

	//Used avoid possible detected error, used to initiale certain variables during BeginPlay
	void SetInitialValues();

	//Main Spawning Function
	void SpawnEnemy(int32 NMBR);

	//Timer Functions
	void UpdateTimer();

	void CoutdownFinished();

	//Produces a Random Location - Used for spawning
	FVector ProduceRandomLocation();

};
