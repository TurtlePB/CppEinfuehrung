// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxCounter.h"

// Sets default values
ABoxCounter::ABoxCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!TriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("No boxCounter Trigger set"));
	}
	
}

// Called when the game starts or when spawned
void ABoxCounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TriggerVolume)
	{
		TArray<AActor*> OverlappingActors;
		TriggerVolume->GetOverlappingActors(OverlappingActors);
		if (OverlappingActors.IsEmpty() == true)
		{
			UE_LOG(LogTemp, Error, TEXT("HELP!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		}
	}

}

