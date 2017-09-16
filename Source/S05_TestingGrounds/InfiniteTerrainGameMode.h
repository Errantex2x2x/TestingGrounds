// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;
class UActorPool;

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API AInfiniteTerrainGameMode : public AGameMode
{
	GENERATED_BODY()

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void AddToPool(ANavMeshBoundsVolume * VolumeToAdd);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PopulateBoundsVolumePool();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UActorPool * Pool;
	
protected:
	virtual void BeginPlay() override;

};
