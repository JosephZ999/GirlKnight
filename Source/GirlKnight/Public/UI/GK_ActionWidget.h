// Girl Knight by MoonDi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GK_GameplayTypes.h"
#include "GK_ActionWidget.generated.h"

class UGK_ActionSlotWidget;
class UOverlay;

/**
 *
 */
UCLASS()
class GIRLKNIGHT_API UGK_ActionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (BindWidget))
	UOverlay* SlotOverlay;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGK_ActionSlotWidget> SlotWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Slots")
	float SlotSize = 100.f;

	UPROPERTY(EditAnywhere, Category = "Slots")
	float SpaceBetweenSlots = 10.f;

private:
	UPROPERTY()
	TArray<UGK_ActionSlotWidget*> ActionSlots;

protected:
	virtual void NativeOnInitialized() override;

private:
	void	  AddActionSlot(EPlayerActions InAction, int32 InPosition);
	FVector2D GenerateSlotPosition(int32 InPosition) const;
};
