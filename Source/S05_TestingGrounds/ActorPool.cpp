// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UActorPool::BeginPlay()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

AActor * UActorPool::Checkout()
{	
	if (Pool.Num() > 0)
		return Pool.Pop();
	else
		return nullptr;
}

void UActorPool::Return(AActor * ActorToReturn) 
{
	Add(ActorToReturn);
}

void UActorPool::Add(AActor * ActorToAdd)
{
	Pool.Push(ActorToAdd);
}
