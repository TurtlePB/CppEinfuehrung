// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Transporter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPEINFUEHRUNG_API UTransporter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTransporter();

	UPROPERTY(EditAnywhere, Category = "Transporter")
	ATriggerVolume* TriggerVolume;

	UPROPERTY(EditAnywhere, Category = "Transporter")
	float TriggerMass;

	UPROPERTY(EditAnywhere, Category = "Transporter")
	float RequiredMass;
	
private:
	float GetTotalMass();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
