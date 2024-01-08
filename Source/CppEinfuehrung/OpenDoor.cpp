// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

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
		UE_LOG(LogTemp, Error, TEXT("No OpenDorr Trigger set"))
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerVolume)
	{
		if (TriggerVolume->IsOverlappingActor(ActorThatCanOpen))
		{
			OpenDoor(DeltaTime);
			Timer = DoorCloseDelay;
		}
		else
		{
			Timer -= DeltaTime;
			if (Timer <= 0)
			{
				CloseDoor(DeltaTime);
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

