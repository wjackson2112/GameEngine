//
// Created by Will on 3/3/2023.
//

#include "Steamworks.h"

#include <iostream>

int Steamworks::init()
{
    if(!SteamAPI_Init())
        return 1;

    if ( !SteamInput()->Init( false ) )
        return 1;

    SteamInput()->SetInputActionManifestFilePath( "Y:\\Projects\\Spider\\cmake-build-debug\\spider\\steam_input_manifest.vdf"  );

    int numActive = SteamInput()->GetConnectedControllers(controllerHandles);

    InputActionSetHandle_t shipControlsSetHandle = SteamInput()->GetActionSetHandle( "ship_controls" );
    InputActionSetHandle_t shipControlsDigitalSetHandle = SteamInput()->GetDigitalActionHandle( "forward_thrust" );

    return 0;
}

void Steamworks::update()
{
    SteamAPI_RunCallbacks();
    int numActive = SteamInput()->GetConnectedControllers(controllerHandles);
    std::cout << "NumControllers: " << numActive << std::endl;
}