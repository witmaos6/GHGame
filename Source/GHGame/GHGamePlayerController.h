// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GHGamePlayerController.generated.h"

UCLASS()
class AGHGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGHGamePlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	bool bAKeyDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	bool bSKeyDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	bool bDKeyDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guage")
	float MaxGuage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guage")
	float Guage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Guage")
	bool bVisibleSkillWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WStatOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* StatOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WSkillWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* SkillWidget;

protected:
	virtual void BeginPlay() override;
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void AKeyPressed();

	void AKeyReleased();

	void SKeyPressed();

	void SKeyReleased();

	void DKeyPressed();

	void DKeyReleased();

	void ShowSkillWidget();

	void RemoveSkillWidget();
};
