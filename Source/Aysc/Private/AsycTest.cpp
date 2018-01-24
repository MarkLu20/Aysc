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
	//��������ָ��

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	//�����url
	HttpRequest->SetURL(ServerAddr);
	if (actionType == ActionType::POST)
	{   
		
	//SetVerbΪ��������� 
		HttpRequest->SetContentAsString(TEXT("TestPostString"));
		HttpRequest->SetVerb(TEXT("POST"));
	}
	if (actionType == ActionType::GET)
	{
		HttpRequest->SetVerb(TEXT("GET"));
	}
    //����header
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=utf-8"));
	// *****************�������ĺ������ص����� ��***���ص���Ϣ�ڻص�������
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsycTest::RequestComplete);
	//��������
	HttpRequest->ProcessRequest();

}

// FHttpRequestPtr requestָ�� HttpResponse �������ݵ�ָ��  bSucceeded �ɹ����
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
