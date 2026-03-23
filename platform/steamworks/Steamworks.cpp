//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 3/3/2023.
//

#include "Steamworks.h"

#include <iostream>

int Steamworks::init()
{
    if(!SteamAPI_Init())
        return 1;

//    for(int i = 0; i < STEAM_CONTROLLER_MAX_DIGITAL_ACTIONS; i++)
//    {
//        digitalActionHandles[i] = 0;
//    }
//
//    for(int i = 0; i < INPUT_AS_MAX; i++)
//    {
//        actionSetHandles[i] = 0;
//    }

    // clear the action handles
    for ( int i = 0; i <eControllerDigitalAction_NumActions; i++ )
    {
        m_ControllerDigitalActionHandles[i] = 0;
        m_ControllerDigitalActionOrigins[i] = k_EInputActionOrigin_None;
    }
    for ( int i = 0; i <eControllerAnalogAction_NumActions; i++ )
    {
        m_ControllerAnalogActionHandles[i] = 0;
        m_ControllerAnalogActionOrigins[i] = k_EInputActionOrigin_None;
    }
    for ( int i = 0; i <eControllerActionSet_NumSets; i++ )
    {
        m_ControllerActionSetHandles[i] = 0;
    }
    m_ActiveControllerHandle = 0;

    // Digital game actions
    m_ControllerDigitalActionHandles[eControllerDigitalAction_TurnLeft] = SteamInput()->GetDigitalActionHandle( "turn_left" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_TurnRight] = SteamInput()->GetDigitalActionHandle( "turn_right" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_ForwardThrust] = SteamInput()->GetDigitalActionHandle( "forward_thrust" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_ReverseThrust] = SteamInput()->GetDigitalActionHandle( "backward_thrust" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_FireLasers] = SteamInput()->GetDigitalActionHandle( "fire_lasers" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_PauseMenu] = SteamInput()->GetDigitalActionHandle( "pause_menu" );

    m_ControllerDigitalActionHandles[eControllerDigitalAction_MenuUp] = SteamInput()->GetDigitalActionHandle( "menu_up" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_MenuDown] = SteamInput()->GetDigitalActionHandle( "menu_down" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_MenuLeft] = SteamInput()->GetDigitalActionHandle( "menu_left" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_MenuRight] = SteamInput()->GetDigitalActionHandle( "menu_right" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_MenuSelect] = SteamInput()->GetDigitalActionHandle( "menu_select" );
    m_ControllerDigitalActionHandles[eControllerDigitalAction_MenuCancel] = SteamInput()->GetDigitalActionHandle( "menu_cancel" );

    // Analog game actions
    m_ControllerAnalogActionHandles[eControllerAnalogAction_AnalogControls] = SteamInput()->GetAnalogActionHandle( "analog_controls" );

    // Action set handles
    m_ControllerActionSetHandles[eControllerActionSet_ShipControls] = SteamInput()->GetActionSetHandle( "ship_controls" );
    m_ControllerActionSetHandles[eControllerActionSet_MenuControls] = SteamInput()->GetActionSetHandle( "menu_controls" );

    // Action set layer handle
    m_ControllerActionSetHandles[eControllerActionSet_Layer_Thrust] = SteamInput()->GetActionSetHandle( "thrust_action_layer" );

    if ( !SteamInput()->Init( false ) )
        return 1;

    SteamInput()->SetInputActionManifestFilePath( "Y:\\Projects\\Spider\\cmake-build-debug\\spider\\steam_input_manifest.vdf"  );

    updateConnectedControllers();

//    digitalActionHandles[INPUT_DA_MENU_LEFT] = SteamInput()->GetDigitalActionHandle( "menu_left" );
//    digitalActionHandles[INPUT_DA_MENU_RIGHT] = SteamInput()->GetDigitalActionHandle( "menu_right" );
//    digitalActionHandles[INPUT_DA_MENU_UP] = SteamInput()->GetDigitalActionHandle( "menu_up" );
//    digitalActionHandles[INPUT_DA_MENU_DOWN] = SteamInput()->GetDigitalActionHandle( "menu_down" );
//
//    actionSetHandles[INPUT_AS_MENU] = SteamInput()->GetActionSetHandle( "menu_controls" );

    return 0;
}

void Steamworks::update()
{
    int numActive = updateConnectedControllers();
    ControllerDigitalActionData_t digitalData = SteamInput( )->GetDigitalActionData( m_ActiveControllerHandle, m_ControllerDigitalActionHandles[eControllerDigitalAction_PauseMenu] );
//    SteamInput()->GetDigitalActionData(0, leftHandle);
    SteamAPI_RunCallbacks();

    if(numActive < 1)
        return;

//    setActionSetHandle(0, INPUT_AS_MENU);
//
//    InputHandle_t activeController = controllerHandles[0];
//    InputActionSetHandle_t menuActionSet = actionSetHandles[INPUT_AS_MENU];

//
//    SteamInput()->ActivateActionSet(activeController, menuActionSet);
//


//    std::cout << data.bActive << " " << data.bState << std::endl;
}

void Steamworks::setActionSetHandle(int controller, InputActionSet actionSet)
{
    SteamInput()->ActivateActionSet(controllerHandles[controller], actionSetHandles[actionSet]);
}

int Steamworks::updateConnectedControllers()
{
    int numActive = SteamInput()->GetConnectedControllers(controllerHandles);
    std::cout << "NumControllers: " << numActive << std::endl;

    return numActive;
}