// Fill out your copyright notice in the Description page of Project Settings.


#include "HW_BP_CPP.h"

// Sets default values
AHW_BP_CPP::AHW_BP_CPP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHW_BP_CPP::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation(); //Initialization position
}

// Called every frame
void AHW_BP_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHW_BP_CPP::SinMovement()
{
	//right Time 
	float Time = GetWorld()->GetTimeSeconds();

	//Calculation new pos with sin func
	float DeltaHeight = Amplitude * FMath::Sin(Frequency * Time);
	FVector NewLocation = InitialLocation;
	NewLocation.Z += DeltaHeight;


	//set new position object
	SetActorLocation(NewLocation);
}