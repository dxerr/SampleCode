// Fill out your copyright notice in the Description page of Project Settings.

#include "InputBindingBase.h"

void UInputBindingBase::Initialize()
{

}

void UInputBindingBase::SetBinding(UInputComponent* input)
{
	InputComponent = input;
}