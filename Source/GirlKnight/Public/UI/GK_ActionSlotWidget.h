// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GK_GameplayTypes.h"
#include "GK_ActionSlotWidget.generated.h"

/**
 *
 */
UCLASS()
class GIRLKNIGHT_API UGK_ActionSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	int32 Index = 0;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveSetIcon(EPlayerActions InActionType);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFadeIn();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFadeOut();
};
