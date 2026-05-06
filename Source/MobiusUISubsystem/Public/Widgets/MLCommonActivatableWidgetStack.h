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
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetNumActiveWidgets() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsWidgetActiveByClass(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass) const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCommonActivatableWidget* GetActiveWidgetByClass(const TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass) const;
	
	virtual void SynchronizeProperties() override;
};
