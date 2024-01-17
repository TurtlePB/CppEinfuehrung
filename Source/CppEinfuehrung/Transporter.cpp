// Fill out your copyright notice in the Description page of Project Settings.


#include "Transporter.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UTransporter::UTransporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTransporter::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("No Transporter Trigger set"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("No Transporter Trigger set"));
	}
	
}


// Called every frame
void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerVolume)
	{
		if (GetTotalMass() >= RequiredMass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Required mass achieved!"));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Required mass achieved!"));
		}
	}
}

float UTransporter::GetTotalMass()
{
	float totalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);
	
	for (AActor* Actor: OverlappingActors)
	{
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), totalMass);
	return totalMass;
}


