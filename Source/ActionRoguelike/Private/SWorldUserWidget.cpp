// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor ))
	{
		RemoveFromParent();
		UE_LOG(LogTemp, Warning, TEXT("Removing USWorldUserWidget because AttachedActor isn't valid"));
		return;
	}
	
	FVector2D ScreenPos = FVector2D::ZeroVector;

	FVector WorldPos =  AttachedActor->GetActorLocation() + WorldOffset;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), WorldPos, ScreenPos, true);

	if (ParentSizeBox)
	{
		ParentSizeBox->SetRenderTranslation(ScreenPos);
	}
}
