// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Scale.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPEINFUEHRUNG_API UScale : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScale();

	UPROPERTY(EditAnywhere, Category="Scale")
	AActor* DoorActor;
	UPROPERTY(BlueprintReadOnly)
	float TotalMass;
private:
	float getTotalMassOfActors();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};