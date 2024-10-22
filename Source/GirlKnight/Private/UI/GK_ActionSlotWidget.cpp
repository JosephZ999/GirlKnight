// Girl Knight by MoonDi

#include "GK_ActionSlotWidget.h"

void UGK_ActionSlotWidget::SetIndex(int32 InIndex)
{
	if (InIndex == 0)
	{
		ReceiveSelected();
	}
	else if (Index == 0 && InIndex == -1)
	{
		ReceiveUnselected();
	}
	Index = InIndex;
}
