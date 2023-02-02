#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <vector>
#include <queue>

#include "Component.h"
#include "IInputReceiver.h"
#include "InputManager.h"
#include "Inputs.h"

struct InputEvent
{
    double timeSeconds;

private:
    bool keyEvent;
public:
    Key key;
    MouseButton button;

    glm::vec2 position;

    Action action;
    Modifier mods;

    InputEvent() = default;

    InputEvent(Key key, Action action, Modifier mods)
    : position(glm::vec2(0,0))
    , key(key)
    , button(MOUSE_BUTTON_NONE)
    , action(action)
    , mods(mods)
    , keyEvent(true)
    {
        timeSeconds = glfwGetTime();
    }

    InputEvent(glm::vec2 position, MouseButton button, Action action, Modifier mods)
    : position(position)
    , key(KEY_UNKNOWN)
    , button(button)
    , action(action)
    , mods(mods)
    , keyEvent(true)
    {
        timeSeconds = glfwGetTime();
    }

    inline bool isKeyEvent() { return keyEvent; }
    inline bool isMouseEvent() { return !keyEvent; }
};

class InputComponent : public Component, public IInputReceiver
{
    std::queue<InputEvent> inputEvents;

public:
    InputComponent(InputConfig config);
    ~InputComponent();

    inline bool hasEvents() { return !inputEvents.empty(); }

    InputEvent dequeueEvent();

    //Component
    virtual void lateUpdate(float deltaTime) override;

    //IInputReceiver
    void mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods) override;
    void keyInputCallback(Key key, int scancode, Action action, Modifier mods) override;
};

#endif // INPUT_COMPONENT