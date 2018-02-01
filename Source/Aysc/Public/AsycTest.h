// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsycTest.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ActionType :uint8
{
	POST  UMETA(DisplayName="POST"),
	GET  UMETA(DisplayName="GET")
};
USTRUCT(BlueprintType)
 struct FReTurnValues
{
	GENERATED_BODY()
	
	//UAsycTest *AsyTest;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 UAsycTest *AsyTest;*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	 FString JsonValue;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyTestDeleage);
UCLASS(Blueprintable)
class AYSC_API UAsycTest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	
public :
	UFUNCTION(BlueprintCallable, Category = "Sanmu", meta = (BlueprintInernetnalUseronly = "true"))
		static UAsycTest *DealData(FString ServerURL, FString UserName, FString Password, ActionType actionType);
	UPROPERTY(BlueprintAssignable)
		FMyTestDeleage OnLoginSuccess;
	UPROPERTY(BlueprintAssignable)
		FMyTestDeleage OnUserNameError;
	UPROPERTY(BlueprintAssignable)
		FMyTestDeleage OnPasswordError;
	UPROPERTY(BlueprintAssignable)
		FMyTestDeleage OnNetError;
 


	UFUNCTION(BlueprintCallable)
	void DelaDataAction(FString ServerAddr, FString UserName, FString Password, ActionType actionType);


	void RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	
public:
	 FString Josnvalues;
	
	
	
	
};
