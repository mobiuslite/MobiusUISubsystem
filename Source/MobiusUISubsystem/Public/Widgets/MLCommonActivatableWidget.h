// 

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MLCommonActivatableWidget.generated.h"

/**
 * If you want a widget as the game's root, make sure to disable "Supports Activation Focus" to stop inputs from being consumed
 */
UCLASS()
class MOBIUSUISUBSYSTEM_API UMLCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void GoBack();
	
	void SetRoot(class UHUDRootWidget* RootWidget);
	
	virtual bool NativeOnHandleBackAction() override;
	virtual void NativeConstruct() override;
	
	void OnLocalPlayerStateReady(const APlayerState* PlayerState);
	
protected:
	
	bool bStateReadySent;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnLocalPlayerStateReady(const APlayerState* PlayerState);
	
	UPROPERTY(BlueprintReadOnly)
	UHUDRootWidget* Root;
};
