#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <vector>
#include <queue>

#include "Component.h"
#include "IInputReceiver.h"
#include "InputManager.h"
#include "Inputs.h"

struct KeyEvent
{
    double timeSeconds;
    Key key;
    Action action;
    Modifier mods;

    KeyEvent() = default;

    KeyEvent(Key key, Action action, Modifier mods)
    : key(key)
    , action(action)
    , mods(mods)
    {
        timeSeconds = glfwGetTime();
    }
};

struct MouseEvent
{
    double timeSeconds;
    glm::vec2 position;
    MouseButton button;
    Action action;
    Modifier mods;

    MouseEvent() = default;

    MouseEvent(glm::vec2 position, MouseButton button, Action action, Modifier mods)
    : position(position)
    , button(button)
    , action(action)
    , mods(mods)
    {
        timeSeconds = glfwGetTime();
    }
};

class InputComponent : public Component, public IInputReceiver
{
    std::queue<KeyEvent> keyEvents;
    std::queue<MouseEvent> mouseEvents;

public:
    InputComponent(InputConfig config);

    inline bool hasKeyEvents() { return !keyEvents.empty(); };
    inline bool hasMouseEvents() { return !mouseEvents.empty(); };

    KeyEvent dequeueKeyEvent();
    MouseEvent dequeueMouseEvent();

    //Component
    virtual void lateUpdate(float deltaTime) override;

    //IInputReceiver
    void mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods) override;
    void keyInputCallback(Key key, int scancode, Action action, Modifier mods) override;
};

#endif // INPUT_COMPONENT