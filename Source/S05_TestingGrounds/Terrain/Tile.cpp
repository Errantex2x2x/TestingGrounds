// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "DrawDebugHelpers.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FVector Min = FVector(0, -2000, 0);
	FVector Max = FVector(4000, 2000, 0);
	Bounds = FBox(Min, Max);
}


void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
 	int SpawnNum = FMath::RandRange(MinSpawn, MaxSpawn);
	float RandomScale = FMath::RandRange(MinScale, MaxScale);

	for (int i = 0; i < SpawnNum; i++)
	{
		FVector SpawnPoint;

		if (GetEmptyLocation(SpawnPoint, Radius * RandomScale))
		{
			PlaceActor(ToSpawn, SpawnPoint, FMath::RandRange(0, 180), RandomScale);
		}
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	Location = ActorToWorld().TransformPosition(Location);

	FHitResult HitResult;
	bool bHasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location, Location, 
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));

	FColor ResultColor = bHasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), Location,0, Radius,FQuat::Identity, ResultColor, true,100);

	return !bHasHit;
}

bool ATile::GetEmptyLocation(FVector & SpawnPoint, float Radius)
{
	int MaxTries = 5;
	bool bFoundPlace = false;
	do 
	{
		SpawnPoint = FMath::RandPointInBox(Bounds);
		bFoundPlace = CanSpawnAtLocation(SpawnPoint, Radius);
		MaxTries--;
	} 
	while (!bFoundPlace && MaxTries > 0);

	return bFoundPlace;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	AActor *NewProp = GetWorld()->SpawnActor<AActor>(ToSpawn);
	NewProp->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewProp->SetActorRelativeLocation(SpawnPoint);
	NewProp->SetActorRotation(FQuat::MakeFromEuler(FVector(0, 0, Rotation)));
	NewProp->SetActorScale3D(FVector(Scale));
}
