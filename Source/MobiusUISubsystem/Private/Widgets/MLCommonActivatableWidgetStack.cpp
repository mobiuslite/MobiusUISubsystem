// 


#include "Widgets/MLCommonActivatableWidgetStack.h"

#include "Core/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MLCommonActivatableWidget.h"

int UMLCommonActivatableWidgetStack::GetNumActiveWidgets() const
{
	int Result = 0;

	for (int i = 0; i < WidgetList.Num(); ++i)
	{
		TObjectPtr<UCommonActivatableWidget> Widget = WidgetList[i];
		if (const UCommonActivatableWidget* WidgetPtr = Widget.Get())
		{
			if (WidgetPtr->IsActivated())
			{
				Result++;
			}
		}
	}
	
	return Result;
}

bool UMLCommonActivatableWidgetStack::IsWidgetActiveByClass(
	const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass) const
{
	bool bResult = false;

	for (int i = 0; i < WidgetList.Num(); ++i)
	{
		TObjectPtr<UCommonActivatableWidget> Widget = WidgetList[i];
		if (const UCommonActivatableWidget* WidgetPtr = Widget.Get())
		{
			if (WidgetPtr->GetClass() == ActivatableWidgetClass)
			{
				bResult = true;
				break;
			}
		}
	}
	
	return bResult;
}

UCommonActivatableWidget* UMLCommonActivatableWidgetStack::GetActiveWidgetByClass(
	const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass) const
{
	UCommonActivatableWidget* bResult = nullptr;

	for (int i = 0; i < WidgetList.Num(); ++i)
	{
		TObjectPtr<UCommonActivatableWidget> Widget = WidgetList[i];
		if (UCommonActivatableWidget* WidgetPtr = Widget.Get())
		{
			if (WidgetPtr->GetClass() == ActivatableWidgetClass)
			{
				bResult = WidgetPtr;
				break;
			}
		}
	}
	
	return bResult;
}

void UMLCommonActivatableWidgetStack::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	if (UCommonActivatableWidget* NewRoot = GetRootContent())
	{
		if (UMLCommonActivatableWidget* MobiusWidget = Cast<UMLCommonActivatableWidget>(NewRoot))
		{
			if (const AGameHUD* HUD = Cast<AGameHUD>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameHUD::StaticClass())))
			{
				MobiusWidget->SetRoot(HUD->GetRoot());
			}
		}
	}
}
