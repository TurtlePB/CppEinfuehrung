// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RealTimer.generated.h"

UCLASS()
class CPPEINFUEHRUNG_API ARealTimer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARealTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CountDown();

	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadOnly)
	int minutes = 25;
	
	UPROPERTY(BlueprintReadOnly)
	int seconds = 0;
	
};
