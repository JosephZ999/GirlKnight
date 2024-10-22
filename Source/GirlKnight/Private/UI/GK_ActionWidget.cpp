// Girl Knight by MoonDi

#include "GK_ActionWidget.h"
#include "GK_ActionSlotWidget.h"
#include "GK_GameMode.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UGK_ActionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (! GetWorld()) return;

	auto GameMode = GetWorld()->GetAuthGameMode<AGK_GameMode>();
	if (GameMode)
	{
		// bind to actions
	}
}

void UGK_ActionWidget::AddActionSlot(EPlayerActions InAction, int32 InPosition)
{
	auto NewSlotWidget = CreateWidget<UGK_ActionSlotWidget>(GetWorld(), SlotWidgetClass);
	if (NewSlotWidget)
	{
		auto OverlaySlot = Cast<UOverlaySlot>(SlotOverlay->AddChild(NewSlotWidget));
		if (OverlaySlot)
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		}

		NewSlotWidget->ReceiveSetIcon(InAction);
		NewSlotWidget->Index = InPosition;
		NewSlotWidget->SetRenderTranslation(GenerateSlotPosition(InPosition));
	}
	else
	{
		check(false);
	}
}

FVector2D UGK_ActionWidget::GenerateSlotPosition(int32 InPosition) const
{
	return FVector2D(SlotSize + SpaceBetweenSlots * (float)InPosition, 0.f);
}
