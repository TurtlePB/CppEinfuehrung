// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	TargetYaw = CurrentRotation.Yaw + TargetYaw;
	StartRotationYaw = CurrentRotation.Yaw;

	ActorThatCanOpen = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!TriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("No OpenDorr Trigger set"));
	}

	OpenDoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!OpenDoorSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find Open Door Sound!"));
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerVolume)
	{
		if (TriggerVolume->IsOverlappingActor(ActorThatCanOpen) || GetTotalMessOfActors() >= TriggerMass)
		{
			PlayOpenDoorSound();
			OpenDoor(DeltaTime);
			Timer = DoorCloseDelay;
		}
		else
		{
			Timer -= DeltaTime;
			if (Timer <= 0)
			{
				CloseDoor(DeltaTime);
				PlayOpenDoorSound();
			}
            
		}
	}
}


void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, TargetYaw, DoorOpenCloseSpeed * DeltaTime);
	GetOwner()-> SetActorRotation(CurrentRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, StartRotationYaw, DoorOpenCloseSpeed * DeltaTime);
	GetOwner()-> SetActorRotation(CurrentRotation);
}

float UOpenDoor::GetTotalMessOfActors()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), TotalMass);
	return TotalMass;
}

void UOpenDoor::PlayOpenDoorSound()
{
	if (OpenDoorSound)
	{
		OpenDoorSound->Play();
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Keine Sound Datei gesetzt, kann nichts abspielen!!!"))
	}
}



