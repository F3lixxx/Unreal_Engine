// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"

// Декларируем делегат оповещающий о смерти
DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMAHealthComponent();
	
	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }
	

	// функцию, которая будет оповещать клиентов о смерти
	UFUNCTION(BlueprintCallable)
	bool IsDead() const;
	
	bool AddHealth(float NewHealth);
	bool IsHealthFull() const;

	
	FOnDeath OnDeath;	// объявляем делегат
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.0f;	// макс. здоровье
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;	// здоровье)))

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
