#include <Windows.h>
#include <iostream>

#include "SDK.hpp"
#include "SDK/Engine_classes.hpp"
#include "SDK/SP_Controller_classes.hpp"

DWORD MainThread(HMODULE Module)
{

    AllocConsole();
    FILE* Dummy;
    freopen_s(&Dummy, "CONOUT$", "w", stdout);
    freopen_s(&Dummy, "CONIN$", "r", stdin);


    SDK::UEngine* Engine = SDK::UEngine::GetEngine();
    SDK::UWorld* World = SDK::UWorld::GetWorld();

    SDK::APlayerController* MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;

    SDK::ASP_Controller_C* MyGameController = static_cast<SDK::ASP_Controller_C*>(MyController);

    SDK::ASP_Character_C* MyGameChar = static_cast<SDK::ASP_Character_C*>(MyController->Character);

    SDK::AMP_GameState_C* MyGameState = static_cast<SDK::AMP_GameState_C*>(MyGameController->MP_GameState);

    SDK::AMP_PlayerState_C* MyPlayerState = static_cast<SDK::AMP_PlayerState_C*>(MyGameController->PlayerState);

    std::cout << Engine->ConsoleClass->GetFullName() << std::endl;


    for (int i = 0; i < SDK::UObject::GObjects->Num(); i++)
    {
        SDK::UObject* Obj = SDK::UObject::GObjects->GetByIndex(i);

        if (!Obj)
            continue;

        if (!Obj->IsDefaultObject())
            continue;


        if (Obj->IsA(SDK::APawn::StaticClass()) || Obj->HasTypeFlag(SDK::EClassCastFlags::Pawn))
        {
            std::cout << Obj->GetFullName() << "\n";
        }
    }


    SDK::ULevel* Level = World->PersistentLevel;
    SDK::TArray<SDK::AActor*>& volatile Actors = Level->Actors;

    for (SDK::AActor* Actor : Actors)
    {

        if (!Actor || !Actor->IsA(SDK::EClassCastFlags::Pawn) || !Actor->IsA(SDK::APawn::StaticClass()))
            continue;

        SDK::APawn* Pawn = static_cast<SDK::APawn*>(Actor);

    }

    SDK::UInputSettings::GetDefaultObj()->ConsoleKeys[0].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"F2");

    SDK::UObject* NewObject = SDK::UGameplayStatics::SpawnObject(Engine->ConsoleClass, Engine->GameViewport);

    Engine->GameViewport->ViewportConsole = static_cast<SDK::UConsole*>(NewObject);


    //you can call a function here
    


    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
        break;
    }

    return TRUE;
}
