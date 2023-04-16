// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"

#include "GHGameCharacter.h"
#include "GHGamePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASkill::ASkill()
{
	PrimaryActorTick.bCanEverTick = false;

	MaxGage = 30.f;
	Gage = 0.f;
	Rate = 20.f;
}

// Called when the game starts or when spawned
void ASkill::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkill::HoldingSkill(bool KeyDown, float DeltaSecond, AGHGameCharacter* Character)
{
	AGHGamePlayerController* PlayerController = Cast<AGHGamePlayerController>(Character->GetController());

	if(KeyDown && MaxGage >= Gage)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 1100.f;

		Gage += Rate * DeltaSecond;
		if(PlayerController)
		{
			PlayerController->SkillWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 600.f;

		Gage = 0;
		if (PlayerController)
		{
			PlayerController->SkillWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ASkill::CastingSkill(bool KeyDown, float DeltaSecond, AGHGameCharacter* Character)
{
	AGHGamePlayerController* PlayerController = Cast<AGHGamePlayerController>(Character->GetController());

	if(KeyDown && MaxGage >= Gage)
	{
		Gage += Rate * DeltaSecond;
		if (PlayerController)
		{
			PlayerController->SkillWidget->SetVisibility(ESlateVisibility::Visible);
		}
		if(MaxGage <= Gage)
		{
			FVector MoveToLocation = Character->GetCursorToWorld()->GetComponentLocation();
			Character->SetActorLocation(MoveToLocation);
		}
	}
	else
	{
		Gage = 0;
		if (PlayerController)
		{
			PlayerController->SkillWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
