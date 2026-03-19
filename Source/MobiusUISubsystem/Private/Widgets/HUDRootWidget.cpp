// 


#include "Widgets/HUDRootWidget.h"
#include "CommonActivatableWidget.h"
#include "Widgets/MLCommonActivatableWidget.h"
#include "Widgets/MLCommonActivatableWidgetStack.h"

UCommonActivatableWidget* UHUDRootWidget::PushWidget(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!WidgetStack) return nullptr;
	
	UCommonActivatableWidget* NewWidget = WidgetStack->AddWidget(ActivatableWidgetClass);
	if (UMLCommonActivatableWidget* MLWidget = Cast<UMLCommonActivatableWidget>(NewWidget))
	{
		MLWidget->SetRoot(this);
	}
	
	return NewWidget;
}

void UHUDRootWidget::PopWidget(UCommonActivatableWidget* Widget) const
{
	if (!WidgetStack) return;
	
	WidgetStack->RemoveWidget(*Widget);
}
