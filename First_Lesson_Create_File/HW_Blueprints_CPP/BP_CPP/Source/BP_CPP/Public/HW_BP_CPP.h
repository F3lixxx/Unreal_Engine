// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW_BP_CPP.generated.h"

UCLASS()
class BP_CPP_API AHW_BP_CPP : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHW_BP_CPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SinMovement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 1.0f;

private:
	FVector InitialLocation;
};