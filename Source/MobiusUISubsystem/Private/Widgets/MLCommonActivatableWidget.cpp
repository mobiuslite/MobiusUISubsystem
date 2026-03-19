// 


#include "Widgets/MLCommonActivatableWidget.h"

#include "Core/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUDRootWidget.h"

void UMLCommonActivatableWidget::GoBack()
{
	if (const AGameHUD* HUD = Cast<AGameHUD>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameHUD::StaticClass())))
	{
		HUD->GetRoot()->PopWidget(this);
	}
}

void UMLCommonActivatableWidget::SetRoot(class UHUDRootWidget* RootWidget)
{
	Root = RootWidget;
}

bool UMLCommonActivatableWidget::NativeOnHandleBackAction()
{
	if (bIsBackHandler)
	{
		DeactivateWidget();
		GoBack();
		return true;
	}
	
	return false;
}