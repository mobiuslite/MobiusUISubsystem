// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToastWidget.generated.h"

UENUM()
enum EToastState
{
	None,
	
	Opening,
	Idle,
	Closing,
	
	COUNT
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MOBIUSUISUBSYSTEM_API UToastWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetLifespan() const { return Lifespan;}
	
	void InitializeToast(const FString& Message);
	//Return true marks toast for removal
	bool Tick(const float DeltaTime);
	
protected:
	
	UPROPERTY(BlueprintReadOnly)
	FString ToastMessage;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnStateChange(const EToastState NewState);
	
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EToastState> State;
	
	float StateTimer;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	float Lifespan = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TransitionTime = 0.25f;
};
