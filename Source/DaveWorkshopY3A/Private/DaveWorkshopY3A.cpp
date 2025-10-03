// Copyright Epic Games, Inc. All Rights Reserved.

#include "DaveWorkshopY3A.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void DaveWorkshopY3A::StartupModule()
{
    UE_LOG(LogRomanCore, Log, TEXT("RomanCore module starting up"));
}

void DaveWorkshopY3A::ShutdownModule()
{
    UE_LOG(LogRomanCore, Log, TEXT("RomanCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, DaveWorkshopY3A, "DaveWorkshopY3A" );
