// Fill out your copyright notice in the Description page of Project Settings.

#include "AsycTest.h"


UAsycTest *UAsycTest::Login(FString ServerURL, FString UserName, FString Password)
{
	UAsycTest *Instance = NewObject<UAsycTest>();
	Instance->PostLogin(ServerURL,UserName,Password);

	return Instance;

}

void UAsycTest::PostLogin(FString ServerAddr, FString UserName, FString Password)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsycTest::OnLoginComplete);
	HttpRequest->SetURL(ServerAddr);
	HttpRequest->SetContentAsString(UserName + " " + Password);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=utf-8"));
	HttpRequest->ProcessRequest();
}


void UAsycTest::OnLoginComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!bSucceeded)
	{
		OnNetError.Broadcast();
		return;
	}
	if (HttpResponse->GetResponseCode()==200)
	{
		if (HttpResponse->GetContentAsString()=="Success")
		{
			OnLoginSuccess.Broadcast();
		}

		else if (HttpResponse->GetContentAsString()=="UserNameError")
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
}
