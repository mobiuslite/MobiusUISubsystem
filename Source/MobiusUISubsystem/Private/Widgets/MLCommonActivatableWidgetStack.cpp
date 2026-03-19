// 


#include "Widgets/MLCommonActivatableWidgetStack.h"

#include "Core/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MLCommonActivatableWidget.h"

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
