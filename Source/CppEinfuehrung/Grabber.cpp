// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/BodyInstance.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::SetupInputComponents()
{
	MyInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (MyInputComponent)
	{
		MyInputComponent-> BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		MyInputComponent-> BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("keine UInputComponent gefunden"));
	}
}



// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("Hallo ich bin der Grabber!"));

	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!MyPhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("kein physicsHandle da"))
	}
	SetupInputComponents();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->SetTargetLocation(GetEndLineTrace());
	}
}

FVector UGrabber::GetEndLineTrace()
{
	if (GetWorld())
	{
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
		return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * TraceLength;
	}
	else
	{
		return FVector(0.f,0.f,0.f);
	}
}

FVector UGrabber::GetPlayerViewPointLocationStart()
{
	
	if (GetWorld())
	{
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
		return PlayerViewPointLocation;
	}
	else
	{
		return FVector(0.f,0.f,0.f);
	}
}



void UGrabber::Grab()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Grab!"));
	UE_LOG(LogTemp, Warning, TEXT("Grab!"));

	if (GetWorld())
	{
		FHitResult Hit;
		FCollisionQueryParams TraceParams(FName(TEXT("")),false, GetOwner());
		GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetPlayerViewPointLocationStart(), GetEndLineTrace(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	

		if (Hit.GetActor())
		{
			Hit.GetActor()->FindComponentByClass<UStaticMeshComponent>()->GetBodyInstance()->bLockXRotation= true;
			Hit.GetActor()->FindComponentByClass<UStaticMeshComponent>()->GetBodyInstance()->bLockZRotation= true;
			Hit.GetActor()->FindComponentByClass<UStaticMeshComponent>()->GetBodyInstance()->bLockYRotation= true;
			Hit.GetActor()->FindComponentByClass<UStaticMeshComponent>()->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);

			/*Hit.GetComponent()->GetBodyInstance()->bLockXRotation= true;
			Hit.GetComponent()->GetBodyInstance()->bLockYRotation= true;
			Hit.GetComponent()->GetBodyInstance()->bLockZRotation= true;*/
			
			/*Hit.GetComponent()->BodyInstance.bLockRotation = true;
			Hit.GetComponent()->BodyInstance.SetDOFLock(EDOFMode::SixDOF);*/
			MyPhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, Hit.Location);
			//FRotator HoldRotation = MyPhysicsHandle->GrabbedComponent->GetRelativeRotation();
			//MyPhysicsHandle->GrabbedComponent->SetRelativeRotation(HoldRotation);
		}
	}
}

void UGrabber::GrabRelease()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Released"));
	UE_LOG(LogTemp, Warning, TEXT("Released!"));
	if (MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
	}
}





