// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class CPPEINFUEHRUNG_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:    
	// Sets default values for this component's properties
	UOpenDoor();

	float StartRotationYaw;

	float Timer;
    
	UPROPERTY(EditAnywhere, Category="Door Yaw")
	float TargetYaw = 90.f;
    
	UPROPERTY(EditAnywhere, Category="Door Yaw")
	float DoorOpenCloseSpeed = 1.f;
    
	UPROPERTY(EditAnywhere, Category="Door Trigger")
	ATriggerVolume* TriggerVolume;

	UPROPERTY(VisibleAnywhere, Category="Door Trigger")
	AActor* ActorThatCanOpen;

	UPROPERTY(EditAnywhere, Category="Door Trigger")
	float DoorCloseDelay = 1.f;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:    
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

        
};
