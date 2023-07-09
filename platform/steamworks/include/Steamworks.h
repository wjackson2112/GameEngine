//
// Created by Will on 3/3/2023.
//

#ifndef STEAMWORKS_H
#define STEAMWORKS_H

#include "steam_api.h"

#define MAX_CONTROLLERS 1

// TODO: This sort of thing needs to live with the game, not the engine
enum InputDigitalAction
{
    INPUT_DA_MENU_LEFT,
    INPUT_DA_MENU_RIGHT,
    INPUT_DA_MENU_UP,
    INPUT_DA_MENU_DOWN,
    INPUT_DA_MAX
};

enum InputActionSet
{
    INPUT_AS_MENU,
    INPUT_AS_MAX
};

//#define MAX_CONTROLLERS 4

enum ECONTROLLERDIGITALACTION
{
    eControllerDigitalAction_TurnLeft,
    eControllerDigitalAction_TurnRight,
    eControllerDigitalAction_ForwardThrust,
    eControllerDigitalAction_ReverseThrust,
    eControllerDigitalAction_FireLasers,
    eControllerDigitalAction_PauseMenu,

    eControllerDigitalAction_MenuUp,
    eControllerDigitalAction_MenuDown,
    eControllerDigitalAction_MenuLeft,
    eControllerDigitalAction_MenuRight,
    eControllerDigitalAction_MenuSelect,
    eControllerDigitalAction_MenuCancel,

    eControllerDigitalAction_NumActions
};

enum ECONTROLLERANALOGACTION
{
    eControllerAnalogAction_AnalogControls,

    eControllerAnalogAction_NumActions
};

enum ECONTROLLERACTIONSET
{
    eControllerActionSet_ShipControls,
    eControllerActionSet_MenuControls,
    eControllerActionSet_Layer_Thrust,

    eControllerActionSet_NumSets
};

class Steamworks
{
    InputHandle_t controllerHandles[STEAM_CONTROLLER_MAX_COUNT];

    InputDigitalActionHandle_t digitalActionHandles[STEAM_CONTROLLER_MAX_DIGITAL_ACTIONS];
    InputActionSetHandle_t actionSetHandles[INPUT_AS_MAX];

    // An array of handles to Steam Controller events that player can bind to controls
    InputDigitalActionHandle_t m_ControllerDigitalActionHandles[eControllerDigitalAction_NumActions];

    // An array of handles to Steam Controller events that player can bind to controls
    InputAnalogActionHandle_t m_ControllerAnalogActionHandles[eControllerAnalogAction_NumActions];

    // An array of handles to different Steam Controller action set configurations
    InputActionSetHandle_t m_ControllerActionSetHandles[eControllerActionSet_NumSets];

    // A handle to the currently active Steam Controller.
    InputHandle_t m_ActiveControllerHandle;

    // Origins for all the Steam Input actions. The 'origin' is where the action is currently bound to,
    // ie 'jump' is currently bound to the Steam Controller 'A' button.
    EInputActionOrigin m_ControllerDigitalActionOrigins[eControllerDigitalAction_NumActions];
    EInputActionOrigin m_ControllerAnalogActionOrigins[eControllerAnalogAction_NumActions];

public:
    int init();
    void update();

    void setActionSetHandle(int controller, InputActionSet actionSet);
    int updateConnectedControllers();
};

#endif //STEAMWORKS_H
