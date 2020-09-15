// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "MPCMovementComp.h"
#include "Containers/Array.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "MainPlatChar.generated.h"

UCLASS()
class GAMEPATDEVAS1_API AMainPlatChar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPlatChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Set Pointer For the Pawn Movement Component Set Up
	UMPCMovementComp* MainMovementComp;

	//Part of Discontinued Jumping Mechanic
	//Jump Check
	//bool CanJump;

	//Health for character initialise
	int Health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	//Add Character Body
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* CharBody;
	
	//Add Character Box Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* CharacterColi;

	//Add Character Head (Discontinued)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//UStaticMeshComponent* CharHead;

	//Add Character Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* MainCam;

	//Add Springarm for Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* CamConnector;


	//Created for the utilization of Bullet Pool
	//UPROPERTY(Category = "Bullet", EditAnyWhere, BlueprintReadWrite)
		//TSubclassOf<ABulletPool> SelectedBulletPool;
	
	//ABulletPool* SelectedBulletPool;

	UPROPERTY(Category = "Bullet", EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ABullet> FiredShot;
	
	//Movement Along X axis Function
	void MovementX(float XAMNT);
	
	//Movement Along Y axis Function
	void MovementY(float YAMNT);

	//Controls the character death Via DestroyActor()
	void CharacterDeath();

	//Function used to fire bullets
	void ShootBullet();

	//Overlapping Function
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
