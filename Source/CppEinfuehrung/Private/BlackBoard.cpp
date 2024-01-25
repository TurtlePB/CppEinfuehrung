// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard.h"

// Sets default values for this component's properties
UBlackBoard::UBlackBoard()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBlackBoard::BeginPlay()
{
	Super::BeginPlay();

	requiredMassText = 0;
	totalMassText = 0;

	// ...
	
}


// Called every frame
void UBlackBoard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

