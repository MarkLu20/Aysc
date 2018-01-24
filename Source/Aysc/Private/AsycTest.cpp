// Fill out your copyright notice in the Description page of Project Settings.

#include "AsycTest.h"
#include "Engine.h"
#include "Kismet/KismetStringLibrary.h"


UAsycTest *UAsycTest::DealData(FString ServerURL, FString UserName, FString Password, ActionType actionType)
{
	UAsycTest *Instance = NewObject<UAsycTest>();
	Instance->DelaDataAction(ServerURL, UserName, Password, actionType);

	return Instance;

}

void UAsycTest::DelaDataAction(FString ServerAddr, FString UserName, FString Password, ActionType actionType)
{
	//创建请求指针

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	//请求的url
	HttpRequest->SetURL(ServerAddr);
	if (actionType == ActionType::POST)
	{   
		
	//SetVerb为请求的类型 
		HttpRequest->SetContentAsString(TEXT("TestPostString"));
		HttpRequest->SetVerb(TEXT("POST"));
	}
	if (actionType == ActionType::GET)
	{
		HttpRequest->SetVerb(TEXT("GET"));
	}
    //设置header
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=utf-8"));
	// *****************绑定请求后的函数（回调函数 ）***返回的信息在回调函数中
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsycTest::RequestComplete);
	//发起请求
	HttpRequest->ProcessRequest();

}

// FHttpRequestPtr request指针 HttpResponse 返回内容的指针  bSucceeded 成功与否
void UAsycTest::RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!bSucceeded)
	{
		OnNetError.Broadcast();
		return;
	}
	if (HttpResponse->GetResponseCode() == 200)
	{
		if (HttpResponse->GetContentAsString() == "Success")
		{
			OnLoginSuccess.Broadcast();
		}

		else if (HttpResponse->GetContentAsString() == "UserNameError")
		{
			OnUserNameError.Broadcast();
		}
		else if (HttpResponse->GetContentAsString() == "PasswordError")
		{
			OnPasswordError.Broadcast();
		}
		else
		{
			OnNetError.Broadcast();
		}
	}
	else
	{
		OnNetError.Broadcast();
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, HttpResponse->GetContentAsString());


}
