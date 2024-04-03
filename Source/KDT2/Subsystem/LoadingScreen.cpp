#include "LoadingScreen.h"
#include "MoviePlayer.h"
#include "UMG.h"

void ULoadingScreenSubsystem::SetLoadingScreenClass(TSubclassOf<UUserWidget> InWidgetClass)
{
	WidgetClass = InWidgetClass;
}

void ULoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
}

void ULoadingScreenSubsystem::OnPreLoadMap(const FString& MapName)
{
	if (WidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget class not set"));
		//check(false);
		return;
	}
	
	UUserWidget* Widget = CreateWidget(GetWorld(), WidgetClass);
	if (IsMoviePlayerEnabled())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 5.f;
		LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
	/*else
	{
		Widget->AddToViewport();
	}*/
}
