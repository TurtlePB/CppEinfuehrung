// Fill out your copyright notice in the Description page of Project Settings.


#include "RealTimer.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ARealTimer::ARealTimer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARealTimer::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARealTimer::CountDown, 1.f, true, 0.0);
}

// Called every frame
void ARealTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARealTimer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARealTimer::CountDown()
{
	if (seconds != 0)
	{
		seconds = seconds - 1;
	}
	else
	{
		if (minutes == 0)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Demonstration");
		}
		else
		{
			minutes = minutes - 1;
			seconds = 59;
		}
	}
}

