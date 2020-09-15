// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlatChar.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BasicEnemy.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "AdvancedEnemy.h"
#include "MPCMovementComp.h"
#include "Engine/Engine.h"


// Sets default values
AMainPlatChar::AMainPlatChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Auto Posses the player at the beginning of play, Assigned to Player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//Create Main body for Player Character
	CharBody = CreateDefaultSubobject<UStaticMeshComponent>("Character_Body");
	RootComponent = CharBody;

	//Setup the Collsion Box
	CharacterColi = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	CharacterColi->SetupAttachment(CharBody);

	//Create The head for the player character and connecting it to the main body (Discontinued)
	//This was because it dettaches from the main body due to SetPhysics
	//CharHead = CreateDefaultSubobject<UStaticMeshComponent>("Character_Head");
	//CharHead->SetupAttachment(CharBody);

	//Create The springarm component to connenect the camera and the camera itself
	CamConnector = CreateDefaultSubobject<USpringArmComponent>("Camera_Arm");
	MainCam = CreateDefaultSubobject<UCameraComponent>("Main_Camera");

	//Connect the springarm to the main body and the connect the camera to the springarm
	CamConnector->SetupAttachment(CharBody);
	MainCam->SetupAttachment(CamConnector);

	//Set gthe necessary rotation and length for springarm
	CamConnector->SetRelativeRotation(FRotator(-20.0f,90.f,00.0f));
	CamConnector->TargetArmLength = 400.0f;

	//Causes CharBody to be affected by the Unreal Physics Engine
	CharBody->SetSimulatePhysics(true);

	//Set up Movement Component for movement
	MainMovementComp = CreateDefaultSubobject<UMPCMovementComp>("SMoveComp");
	MainMovementComp->UpdatedComponent = RootComponent;

	//Initialise Health Amount: 3 or 5 optimal
	Health = 5;

}

// Called when the game starts or when spawned
void AMainPlatChar::BeginPlay()
{
	Super::BeginPlay();
	//CanJump = true;
	
	CharacterColi->OnComponentBeginOverlap.AddDynamic(this, &AMainPlatChar::OnOverlapBegin);
}

// Called every frame
void AMainPlatChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Makes Check Whether character is dead or not and destroys the actor if so
	CharacterDeath();
	//Prints out Current Health
	if (GEngine) {

		FString DebugMessage = FString::Printf(TEXT("Current Health :  %i"), Health);
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DebugMessage);
	}
}

// Called to bind functionality to input
void AMainPlatChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Sets up the 2D movement for character along X axis
	PlayerInputComponent->BindAxis("XMovement", this, &AMainPlatChar::MovementX);

	PlayerInputComponent->BindAxis("YMovement", this, &AMainPlatChar::MovementY);

	PlayerInputComponent->BindAction("Shooting", IE_Pressed, this, &AMainPlatChar::ShootBullet);
}

//Movement on X Axis
void AMainPlatChar::MovementX(float XAMNT) {
	if (MainMovementComp && (MainMovementComp->UpdatedComponent == RootComponent)) {
		MainMovementComp->AddInputVector(GetActorForwardVector() * XAMNT * 500);
	}
}

//Movement on Y Axis
void AMainPlatChar::MovementY(float YAMNT) {
	if (MainMovementComp && (MainMovementComp->UpdatedComponent == RootComponent)) {
		MainMovementComp->AddInputVector(GetActorRightVector() * YAMNT * 500);
	}
}

//Fires a bullet from specified point on the character model
void AMainPlatChar::ShootBullet() {

	//Commented Out Code used for original Bullet Pool Class that was distontinued
	//Due to game breaking error that caused a crash
	//ABullet* BulletToFire = nullptr; // SelectedBulletPool->GetPooledObject();
	//if (BulletToFire != nullptr) {

	//If Bullet value is not null
	if (FiredShot != NULL) {
		//A Game World Must Exist For These Values
		if (GetWorld() != NULL) {
			TArray<FName> PlayerSockets = CharBody->GetAllSocketNames();

			if (PlayerSockets[0] == TEXT("BulletSocket")) {
				FActorSpawnParameters SPARAMS;
				FVector SocketLocation = CharBody->GetSocketLocation(PlayerSockets[0]);
				FRotator SocketRotation = CharBody->GetSocketRotation(PlayerSockets[0]);
				SPARAMS.Owner = this;

				ABullet* SpawnedEnemy = GetWorld()->SpawnActor<ABullet>(FiredShot, SocketLocation, SocketRotation, SPARAMS);

				//BulletToFire->SetActiveState(true);
				//BulletToFire->SetActorLocation(SocketLocation);
				//BulletToFire->SetActorRotation(SocketRoation);

				UE_LOG(LogTemp, Log, TEXT("Bullet Fired"));
			}
		}
		//else {
		//	UE_LOG(LogTemp, Log, TEXT("Failed: Out Of Bullets!"));
		//}
	}
}

//when pawn collides with an object with box collision cpmponent
void AMainPlatChar::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	//Checks whether the player has made contact with an enemy
	ABasicEnemy* EnemyCastB = Cast<ABasicEnemy>(OtherActor);
	AAdvancedEnemy* EnemyCastA = Cast<AAdvancedEnemy>(OtherActor);

	if (EnemyCastA != nullptr || EnemyCastB != nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Attacked! / You've Been Hit!"));
		--Health;
	}
}

//If Character/pawn has met death requirements
void AMainPlatChar::CharacterDeath() {
	if (Health < 1) {
		Destroy();
		FString DeathMessage = FString::Printf(TEXT("You Have Died! Reload Game"));
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DeathMessage);
	}
}