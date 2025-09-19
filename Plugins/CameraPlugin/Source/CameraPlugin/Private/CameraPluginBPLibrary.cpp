// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraPluginBPLibrary.h"
#include "CameraPlugin.h"

UCameraPluginBPLibrary::UCameraPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UCameraPluginBPLibrary::CameraPluginSampleFunction(float Param)
{
	return -1;
}

