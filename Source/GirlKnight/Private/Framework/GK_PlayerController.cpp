// Girl Knight by MoonDi

#include "GK_PlayerController.h"
#include "Engine/World.h"
#include "GK_GameMode.h"
#include "Components/InputComponent.h"

#include "GK_GameplayTypes.h"

void AGK_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto World = GetWorld();
	if (! World) return;

	GameMode = World->GetAuthGameMode<AGK_GameMode>();
	if (! GameMode) return;

	GameMode->OnPlayerCharacterCreate;
	GameMode->OnEnemyCharacterCreate;
	GameMode->OnGameStart;
	GameMode->OnGameWin;
	GameMode->OnGameOver;
	GameMode->OnEnemyDead;
	GameMode->OnPlayerAttack;
	GameMode->OnEnemyAttack;

	GameMode->StartGame();
}

void AGK_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("ArrowUp", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowUpPressed);
		InputComponent->BindAction("ArrowDown", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowDownPressed);
		InputComponent->BindAction("ArrowLeft", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowLeftPressed);
		InputComponent->BindAction("ArrowRight", EInputEvent::IE_Pressed, this, &ThisClass::OnArrowRightPressed);
	}
}

void AGK_PlayerController::StartBattle()
{
	if (! GameMode) return;

	GameMode->StartBattle();
}

//-----------------------------------------------// Input Actions
void AGK_PlayerController::OnArrowUpPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Up);
	}
}

void AGK_PlayerController::OnArrowDownPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Down);
	}
}

void AGK_PlayerController::OnArrowLeftPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Left);
	}
}

void AGK_PlayerController::OnArrowRightPressed()
{
	if (GameMode)
	{
		GameMode->DoAction(EPlayerActions::Right);
	}
}

//-----------------------------------------------// Delegate Handles