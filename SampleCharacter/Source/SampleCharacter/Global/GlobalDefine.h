﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//임시 헤더 만들기
#include "GameObject/Component/Animation/AnimInstanceState.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/State/StateLocal.h"
#include "GameObject/State/StateNPC.h"
#include "GameObject/Skill/SKillLocal.h"
#include "GameObject/Parts/PartsLocal.h"


// 커스터마이징된 로그 (나중 릴리즈 빌드에선 끄는 용도이다)
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT(" ----Line(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_S(Verbosity)	UE_LOG(LogTemp, Verbosity, TEXT("----%s"), *LOG_CALLINFO)
#define LOG(Verbosity, Format, ...)	UE_LOG(LogTemp, Verbosity, TEXT("----%s ----%s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))