// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> AttachedActor;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<USizeBox> ParentSizeBox;

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


};
