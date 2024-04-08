// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CoinGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API ACoinGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ACoinGameStateBase();
	virtual void BeginPlay() override;

	uint32 GetRemainCoinNum() const { return RemainCoinNum; };

private:
	TSubclassOf<class UCoinInfoUserWidget> CoinWidgetClass;
	UCoinInfoUserWidget* CoinInfoWidget;
	uint32 RemainCoinNum = 0;

};