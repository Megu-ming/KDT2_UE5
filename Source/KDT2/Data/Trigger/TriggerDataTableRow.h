#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TriggerDataTableRow.generated.h"
/**
 * 
 */
USTRUCT()
struct KDT2_API FTriggerDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform StaticMeshTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Class;
};
