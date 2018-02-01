// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include  "Runnable.h"
#include  "RunnableThread.h"
#include  "Http.h"
#include  "Engine.h"
#include "HttpComponment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetDataDelegate, FString, NetValues);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AYSC_API UHttpComponment : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHttpComponment();
  

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	void RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	UFUNCTION(BlueprintCallable, Category = "HTTP")
		void StartHTTP(FString adress);
	UPROPERTY(BlueprintAssignable, Category = "HTTPDelegate")
		FGetDataDelegate HttpDelegate;
	/*UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "HTTP")
		AActor *object;*/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP")
		FString TestChar;*/
	//UFUNCTION(BlueprintCallable, Category = "HTTP")
		//void PrintTestString();

//public:
//	void GetData();
//	void RePeatGetData();



};

class GetHTTPData :public FRunnable
{
public://线程管理
	FRunnableThread *ManagerRunable;
	UHttpComponment *object;
	FString Addres;
	~GetHTTPData()
	{
		ManagerRunable->WaitForCompletion();
		//delete this;
		delete ManagerRunable;
		//delete this;
		ManagerRunable = NULL;
		UE_LOG(LogTemp, Warning, TEXT("xi gou cheng gong"));
	}
	GetHTTPData(FString adress)
	{
		Addres = adress;
	
	}

	virtual bool Init()override
	{
		return true;
	}





	// 通过 FRunnable 继承
	virtual uint32 Run() override
	{
		for (int i = 0; i < 100; i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Running"));

		}
		TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();
		httpRequest->SetURL(Addres);
		httpRequest->SetVerb(TEXT("GET"));
		httpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=utf-8"));
		httpRequest->OnProcessRequestComplete().BindUObject(object, &UHttpComponment::RepquestCompelete);
		httpRequest->ProcessRequest();
		return 0;

	}
	virtual void Exit() override
	{

		UE_LOG(LogTemp, Warning, TEXT("Exit"))
		

	}
	bool GetHTTPData::Createthread(GetHTTPData *HTTPDataObject)

	{  //创建线程
		ManagerRunable = FRunnableThread::Create(HTTPDataObject, TEXT("GetData"));
		return true;


	}
	//获取相应object的对象 一定要在线程创建前调用
	void GetHTTPData::GetObject(UHttpComponment *Pobject)
	{

		object = Pobject;

	}
	
	

	};
