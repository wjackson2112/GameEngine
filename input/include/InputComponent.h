#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <vector>
#include <queue>

#include "Component.h"
#include "IInputReceiver.h"
#include "InputManager.h"
#include "Inputs.h"

enum InputEventType
{
    IET_KEY,
    IET_MOUSE,
    IET_GAMEPAD,
    IET_MAX
};

struct InputEvent
{
    double timeSeconds;

private:
    InputEventType eventType;
public:
    Key key;
    MouseButton mouseButton;
    GamepadButton padButton;
    GamepadAxis axis;
    float axisValue;

    glm::vec2 position;

    Action action;
    Modifier mods;

    InputEvent() = default;

    InputEvent(Key key, Action action, Modifier mods)
    : position(glm::vec2(0,0))
    , key(key)
    , mouseButton(MOUSE_BUTTON_NONE)
    , action(action)
    , mods(mods)
    , padButton(GAMEPAD_BUTTON_NONE)
    , axis(GAMEPAD_AXIS_NONE)
    , axisValue(0.0f)
    , eventType(IET_KEY)
    {
        timeSeconds = glfwGetTime();
    }

    InputEvent(glm::vec2 position, MouseButton mouseButton, Action action, Modifier mods)
    : position(position)
    , key(KEY_UNKNOWN)
    , mouseButton(mouseButton)
    , action(action)
    , mods(mods)
    , padButton(GAMEPAD_BUTTON_NONE)
    , axis(GAMEPAD_AXIS_NONE)
    , axisValue(0.0f)
    , eventType(IET_MOUSE)
    {
        timeSeconds = glfwGetTime();
    }

    InputEvent(GamepadButton padButton, GamepadAxis axis, float axisValue, Action action)
    : position(glm::vec2(0,0))
    , key(KEY_UNKNOWN)
    , mouseButton(MOUSE_BUTTON_NONE)
    , action(action)
    , mods(MOD_NONE)
    , padButton(padButton)
    , axis(axis)
    , axisValue(axisValue)
    , eventType(IET_GAMEPAD)
    {
        timeSeconds = glfwGetTime();
    }

    inline bool isKeyEvent() { return eventType == IET_KEY; }
    inline bool isMouseEvent() { return eventType == IET_MOUSE; }
    inline bool isGamepadEvent() { return eventType == IET_GAMEPAD; }
};

class InputComponent : public Component, public IInputReceiver
{
    std::queue<InputEvent> inputEvents;
    GLFWgamepadstate prevState, currState;

public:
    InputComponent(InputConfig config);
    ~InputComponent();

    inline bool hasEvents() { return !inputEvents.empty(); }

    InputEvent dequeueEvent();

    //Component
    virtual void earlyUpdate(float deltaTime) override;
//    virtual void update(float deltaTime) override;
    virtual void lateUpdate(float deltaTime) override;

    //IInputReceiver
    void keyInputCallback(Key key, int scancode, Action action, Modifier mods) override;
    void mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods) override;
    void gamepadInputCallback(GamepadButton padButton, GamepadAxis axis, float axisValue, Action action) override;
};

#endif // INPUT_COMPONENT