// Fill out your copyright notice in the Description page of Project Settings.


#include "Transporter.h"

#include "BlackBoard.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UTransporter::UTransporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	if (!BlackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("No Blackboard set"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("No Blackboard set"));
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
		}
	}
}

 float UTransporter::GetTotalMass()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//UE_LOG(LogTemp, Warning, TEXT("total Mass: %f"), TotalMass)
	return TotalMass;
}

void UTransporter::GetText()
{
	UBlackBoard* BlackBoardComponent = BlackBoard->FindComponentByClass<UBlackBoard>();

	BlackBoardComponent->totalMassText = GetTotalMass();
	BlackBoardComponent->requiredMassText = RequiredMass;
}


