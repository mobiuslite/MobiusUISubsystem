// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UHUDRootWidget;
/**
 * 
 */
UCLASS()
class MOBIUSUISUBSYSTEM_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	
	AGameHUD();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHUDRootWidget* GetRoot() const { return Root; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PauseGame();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnPlayerStateAdded(const APlayerState* PlayerState);
	
	UFUNCTION(BlueprintCallable, meta=( WorldContext="WorldContextObject"))
	static void SetInputModeGameEnabled(const UObject* WorldContextObject, const bool bGameOnlyEnabled, const bool bFlushInput);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DefaultToSelf="Controller"))
	static AGameHUD* GetGameHUD(const AController* Controller);
	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHUDRootWidget> RootClass;
	
	UPROPERTY(Transient)
	UHUDRootWidget* Root;
	
	//If the player state is added before the root is added, hold to for when the root is added.
	UPROPERTY()
	const APlayerState* QueuedPlayerState;
};
