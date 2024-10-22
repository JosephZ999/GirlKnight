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

private:
	int32 Index = INDEX_NONE;

public:
	int32 GetIndex() const { return Index; }
	void  SetIndex(int32 InIndex);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveSetIcon(EPlayerActions InActionType);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFadeIn();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFadeOut();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveSelected();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveUnselected();
};
