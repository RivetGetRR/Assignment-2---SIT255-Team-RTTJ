// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MPCMovementComp.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPATDEVAS1_API UMPCMovementComp : public UPawnMovementComponent
{
	GENERATED_BODY()
	
		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
