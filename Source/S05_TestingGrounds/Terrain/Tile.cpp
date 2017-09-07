// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "DrawDebugHelpers.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	FVector Min = FVector(0, -2000, 0);
	FVector Max = FVector(4000, 2000, 0);
	FBox Bounds = FBox(Min, Max);

	int SpawnNum = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < SpawnNum; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor *NewProp = GetWorld()->SpawnActor<AActor>(ToSpawn);
		NewProp->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		NewProp->SetActorRelativeLocation(SpawnPoint);
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

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool bHasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location, Location, 
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));

	FColor ResultColor = bHasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), Location,0, Radius,FQuat::Identity, ResultColor, true,100);

	return bHasHit;
}

