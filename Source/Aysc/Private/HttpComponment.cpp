// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpComponment.h"


// Sets default values for this component's properties
UHttpComponment::UHttpComponment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//object = NULL;
	//object->AddToRoot();

	// ...
}


// Called when the game starts
void UHttpComponment::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UHttpComponment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//回调函数 
void UHttpComponment::RepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	
	//广播到蓝图内在执行startHTTP函数之前绑定
	this->HttpDelegate.Broadcast(HttpResponse->GetContentAsString());
}

void UHttpComponment::PostRepquestCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	//UE_LOG(LogTemp, Warning, FString(FString::FromBlob(bSucceeded,32)));
}

void UHttpComponment::GetHTTP(FString adress)
{

	GetHTTPData *GetThread;
	//创建对象
	GetThread = new GetHTTPData(adress);
	GetThread->GetObject(this);
	//创建线程
	GetThread->Createthread(GetThread);
	//创建后销毁该对象 该对象调用析构函数 详见析构函数
	delete GetThread;
	GetThread = NULL;





	
}

void UHttpComponment::PostHTTP(FString adress,FString Content)

{
	PostHTTPData *Thread;
	Thread = new PostHTTPData(adress, Content);
	Thread->GetObject(this);
	Thread->CreateThread(Thread);
	delete Thread;
	Thread = NULL;

}


//
//
//void UHttpComponment::PrintTestString()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TestChar));
//}
//
//
//void UHttpComponment::RePeatGetData()
//{
//	FTimerHandle testHandle;
//	if (this != NULL)
//	{
//		GetWorld()->GetTimerManager().SetTimer(testHandle, this, &UHttpComponment::GetData, 0.3f, true);
//
//	}
//
//}
