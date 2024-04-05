#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/Trigger/TriggerDataTableRow.h"
#include "TriggerInterface.generated.h"

UINTERFACE()
class UTriggerInterface : public UInterface
{
	GENERATED_BODY()
};

class ITriggerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Active"))
	void ReceiveActive();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="InActive"))
	void ReceiveInActive();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="InTrigger"))
	void ReceiveInTrigger();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OutTrigger"))
	void ReceiveOutTrigger();

	virtual void Active();
	virtual void InActive();
	virtual void InTrigger();
	virtual void OutTrigger();

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OutTrigger"))
	void ReceiveOnSubData(const FDataTableRowHandle& InTableRowBase);
	virtual void OnSubData(const FDataTableRowHandle& InTableRowBase);
};