// Copyright Epic Games, Inc. All Rights Reserved.

#include "GHGamePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GHGameCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AGHGamePlayerController::AGHGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	bAKeyDown = false;
	bSKeyDown = false;
	bDKeyDown = false;

	Speed = 600.f;
	MaxGuage = 10.f;
	Guage = 0.f;
}

void AGHGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (WStatOverlay)
	{
		StatOverlay = CreateWidget<UUserWidget>(this, WStatOverlay);

		StatOverlay->AddToViewport();
		StatOverlay->SetVisibility(ESlateVisibility::Visible);
	}

	if (WSkillWidget)
	{
		SkillWidget = CreateWidget<UUserWidget>(this, WSkillWidget);

		SkillWidget->AddToViewport();
		SkillWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGHGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	if(bAKeyDown && MaxGuage >= Guage)
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = Speed + 500.f;

		ShowSkillWidget();
		Guage += (25.f * DeltaTime);
	}
	else
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = Speed - 500.f;

		RemoveSkillWidget();
	}
}

void AGHGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AGHGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AGHGamePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("A", IE_Pressed, this, &AGHGamePlayerController::AKeyPressed);
	InputComponent->BindAction("A", IE_Released, this, &AGHGamePlayerController::AKeyReleased);

	InputComponent->BindAction("S", IE_Pressed, this, &AGHGamePlayerController::SKeyPressed);
	InputComponent->BindAction("S", IE_Released, this, &AGHGamePlayerController::AKeyReleased);

	InputComponent->BindAction("D", IE_Pressed, this, &AGHGamePlayerController::DKeyPressed);
	InputComponent->BindAction("D", IE_Released, this, &AGHGamePlayerController::AKeyReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AGHGamePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AGHGamePlayerController::MoveToTouchLocation);
}

void AGHGamePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AGHGameCharacter* MyPawn = Cast<AGHGameCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AGHGamePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AGHGamePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AGHGamePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AGHGamePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AGHGamePlayerController::AKeyPressed()
{
	bAKeyDown = true;
}

void AGHGamePlayerController::AKeyReleased()
{
	bAKeyDown = false;

	Guage = 0.f;
}

void AGHGamePlayerController::SKeyPressed()
{
	bSKeyDown = true;
}

void AGHGamePlayerController::SKeyReleased()
{
	bSKeyDown = false;
}

void AGHGamePlayerController::DKeyPressed()
{
	bDKeyDown = true;
}

void AGHGamePlayerController::DKeyReleased()
{
	bDKeyDown = false;
}

void AGHGamePlayerController::ShowSkillWidget()
{
	if(SkillWidget)
	{
		SkillWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGHGamePlayerController::RemoveSkillWidget()
{
	if(SkillWidget)
	{
		SkillWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
