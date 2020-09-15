// Fill out your copyright notice in the Description page of Project Settings.


#include "MPCMovementComp.h"

void UMPCMovementComp::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//NULL check
	//ENsures that there is a pawn connected, the component is updtaed and that delta time is skipped
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}
	//Consumes Vector given through MainPlatChar in order to move the Pawn
	FVector MovementThisFrame = ConsumeInputVector() * DeltaTime;


	if (!MovementThisFrame.IsNearlyZero()) {
		FHitResult Hit;
		SafeMoveUpdatedComponent(MovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
	}
}
