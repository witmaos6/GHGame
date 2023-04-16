// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill.generated.h"

UCLASS()
class GHGAME_API ASkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float MaxGage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
	float Gage;

	float Rate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HoldingSkill(bool KeyDown, float DeltaSecond, class AGHGameCharacter* Character);

	void CastingSkill(float DeltaSecond, AGHGameCharacter* Character);
};
