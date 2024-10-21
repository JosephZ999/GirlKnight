// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GK_PlayerController.generated.h"

class AGK_GameMode;

/**
 *
 */
UCLASS()
class GIRLKNIGHT_API AGK_PlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AGK_GameMode* GameMode = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartBattle();

private:
	// Inputs
	void OnArrowUpPressed();
	void OnArrowDownPressed();
	void OnArrowLeftPressed();
	void OnArrowRightPressed();

private:
	//-----------------------------------------------// Delegate Handles
};
