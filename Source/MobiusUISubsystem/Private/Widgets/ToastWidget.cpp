// 


#include "Widgets/ToastWidget.h"

void UToastWidget::InitializeToast(const FString& Message)
{
	State = EToastState::Opening;
	StateTimer = TransitionTime;
	
	ToastMessage = Message;
}

bool UToastWidget::Tick(const float DeltaTime)
{
	bool bRemove = false;
	
	if ((StateTimer -= DeltaTime) < 0.0f)
	{
		switch (State)
		{
		case EToastState::Opening:
			{
				State = Idle;
				StateTimer = Lifespan;
			}
			break;
		case EToastState::Idle:
			{
				State = Closing;
				StateTimer = TransitionTime;
			}
			break;
		case EToastState::Closing:
			{
				State = None;
				bRemove = true;
			}
			break;
		}
		
		OnStateChange(State);
	}
	
	return bRemove;
}

void UToastWidget::OnStateChange_Implementation(EToastState NewState)
{
}
