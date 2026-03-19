// 

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "MLCommonActivatableWidgetStack.generated.h"

/**
 * 
 */
UCLASS()
class MOBIUSUISUBSYSTEM_API UMLCommonActivatableWidgetStack : public UCommonActivatableWidgetStack
{
	GENERATED_BODY()
	
public:
	
	virtual void SynchronizeProperties() override;
};
