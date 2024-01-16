// Fill out your copyright notice in the Description page of Project Settings.


#include "Scale.h"
#include "Components/PrimitiveComponent.h"
// Sets default values for this component's properties
UScale::UScale()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScale::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UScale::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DoorActor)
	{
		if (getTotalMassOfActors() != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Mass %f"), TotalMass)
		}
	}
}

float UScale::getTotalMassOfActors()
{
	TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	DoorActor->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), TotalMass);
	return TotalMass;
}


