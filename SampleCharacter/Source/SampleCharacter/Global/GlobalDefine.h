// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Ŀ���͸���¡�� �α� (���� ������ ���忡�� ���� �뵵�̴�)
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT(" ----Line(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_S(Verbosity)	UE_LOG(LogTemp, Verbosity, TEXT("----%s"), *LOG_CALLINFO)
#define LOG(Verbosity, Format, ...)	UE_LOG(LogTemp, Verbosity, TEXT("----%s ----%s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))