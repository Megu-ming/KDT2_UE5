#include "TriggerInterface.h"
//#include UE_INLINE_GENERATED_CPP_BY_NAME(TriggerInterface)

void ITriggerInterface::Active()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveActive(Actor);
}

void ITriggerInterface::InActive()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveInActive(Actor);
}

void ITriggerInterface::InTrigger()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveInTrigger(Actor);
}

void ITriggerInterface::OutTrigger()
{
	AActor* Actor = Cast<AActor>(this);
	if (!Actor)
	{
		ensure(false);
		return;
	}
	Execute_ReceiveOutTrigger(Actor);
}
