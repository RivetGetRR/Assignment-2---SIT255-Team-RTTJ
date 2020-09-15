// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "BasicEnemy.h"
#include "AdvancedEnemy.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Main body for Enemy Spawner
	//Given visual body indictae to player location of spawner
	ESpawnerBody = CreateDefaultSubobject<UStaticMeshComponent>("Character_Body");
	RootComponent = ESpawnerBody;



		
	//initialise length of SpawnerTimer: through SpawnDelay
	SpawnDelay = 3;


}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SetInitialValues();
	GetWorldTimerManager().SetTimer(SpawnerTimer, this, &AEnemySpawner::UpdateTimer, 1.0f, true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemySpawner::SetInitialValues() {
	//Initialises all values used for spawning in the tanks: Area Values and Height
	//Done Dynamically by getting the actor location values
	//Done Here As to not cause errors
	SpawnAreaMaxWidth = GetActorLocation().X + 1500;
	SpawnAreaMaxDepth = GetActorLocation().Y + 1500;
	SpawnHeight = GetActorLocation().Z - 500;
}

void AEnemySpawner::UpdateTimer() {
	--SpawnDelay;
	//When SpawnDelay Reaches Zero
	if (SpawnDelay < 1) {
		
		CoutdownFinished();
	}

}

void AEnemySpawner::CoutdownFinished() {

	//Spawn Enemy using a randomized Number In oder to determine which
	SpawnEnemy(FMath::RandRange(1,5));
	SpawnDelay = 3;
}

FVector AEnemySpawner::ProduceRandomLocation() {
	//Produces random Fvector that will be used for Spawning the Enemies
	return FVector(FMath::RandRange(-SpawnAreaMaxWidth, SpawnAreaMaxWidth), FMath::RandRange(-SpawnAreaMaxDepth, SpawnAreaMaxDepth), SpawnHeight);
}
void AEnemySpawner::SpawnEnemy(int32 NMBR) {
	//Both the Enmey Types must have a value
	if (AEnemy != NULL && BEnemy != NULL) {
		//A Game World Must Exist For These Values
		if (GetWorld() != NULL) {

			//Spawn Advanced Enemy AEnemy when:
			if (NMBR == 5) {
				FActorSpawnParameters SPARAMS_A;
				SPARAMS_A.Owner = this;

				UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy of Type: Advanced")); 
				FVector SpawnedLocation = ProduceRandomLocation();
				FRotator SpawnedRotation = FRotator(0.0f,0.0f,0.0f); //No need for special rotation due to internal movement

				AAdvancedEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AAdvancedEnemy>(AEnemy, SpawnedLocation, SpawnedRotation, SPARAMS_A);
			}

			//Spawn Basic Enemy BEnemy when:
			if ((NMBR > 0) && (NMBR < 5)) {
				FActorSpawnParameters SPARAMS_B;
				SPARAMS_B.Owner = this;

				UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy of Type: Basic"));
				FVector SpawnedLocation = ProduceRandomLocation();
				FRotator SpawnedRotation = FRotator(0.0f, 0.0f, 0.0f); //No need for special rotation due to internal movement

				ABasicEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABasicEnemy>(BEnemy, SpawnedLocation, SpawnedRotation, SPARAMS_B);
			}


		}
	}
}


