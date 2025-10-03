#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class DaveWorkshopY3A : public IModuleInterface
{
public:
    static inline DaveWorkshopY3A& Get()
    {
        return FModuleManager::LoadModuleChecked<DaveWorkshopY3A>("DaveWorkshopY3A");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("DaveWorkshopY3A");
    }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};