#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#endif
#include <map>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Inputs.h"
//#include "IInputReceiver.h"
#include "InputEvent.h"
#include "IEventReceiver.h"

enum InputMode
{
    IM_MKB,
    IM_GAMEPAD
};

struct ActionBinding
{
private:
    enum {
        BIND_MOUSEBUTTON,
        BIND_KEY,
        BIND_GAMEPADBUTTON,
        BIND_GAMEPADAXIS
    } bindType;

public:
    union {
        MouseButton button;
        Key key;
        GamepadButton gamepadButton;
        GamepadAxis gamepadAxis;
    };

    int mods;
    ButtonAction action;
    Event event;

    ActionBinding(MouseButton button, ButtonAction action, Event event, int mods = 0)
        : button(button)
        , action(action)
        , mods(mods)
        , event(event)
        , bindType(BIND_MOUSEBUTTON)
    {}

    ActionBinding(Key key, ButtonAction action, Event event, int mods = 0)
            : key(key)
            , action(action)
            , event(event)
            , mods(mods)
            , bindType(BIND_KEY)
    {}

    ActionBinding(GamepadButton gamepadButton, ButtonAction action, Event event)
            : gamepadButton(gamepadButton)
            , action(action)
            , event(event)
            , mods(0)
            , bindType(BIND_GAMEPADBUTTON)
    {}

    ActionBinding(GamepadAxis gamepadAxis, ButtonAction action, Event event)
            : gamepadAxis(gamepadAxis)
            , action(action)
            , event(event)
            , mods(0)
            , bindType(BIND_GAMEPADAXIS)
    {}

    [[nodiscard]] bool isMouseBind() const { return bindType == BIND_MOUSEBUTTON; }
    [[nodiscard]] bool isKeyBind() const { return bindType == BIND_KEY; }
    [[nodiscard]] bool isGamepadBind() const { return bindType == BIND_GAMEPADBUTTON || bindType == BIND_GAMEPADAXIS; }
    [[nodiscard]] bool isGamepadButtonBind() const { return bindType == BIND_GAMEPADBUTTON; }
    [[nodiscard]] bool isGamepadAxisBind() const { return bindType == BIND_GAMEPADAXIS; }
};

class InputManager
{
	static InputManager* instance;
    InputMode inputMode = IM_MKB;

    std::vector<ActionBinding> bindings;

    glm::vec2 cursorPos = glm::vec2(0, 0);
    std::vector<ButtonAction> mouseState = std::vector<ButtonAction>(MOUSE_BUTTON_LAST, BUTTON_ACTION_NONE);

    GLFWgamepadstate prevState, currState;

    MouseButton lastMouseButton = MOUSE_BUTTON_NONE;
    ButtonAction lastMouseAction = BUTTON_ACTION_NONE;

	// This is a singleton so the constructor is private
	InputManager() = default;

public:
	static InputManager *getInstance();

    void addBinding(MouseButton button, ButtonAction action, Event event, int mods = 0);
    void addBinding(Key button, ButtonAction action, Event event, int mods = 0);
    void addBinding(GamepadButton button, ButtonAction action, Event event);
    void addBinding(GamepadAxis axis, ButtonAction action, Event event);

    void clearBindings();

    bool getLastMouseState(MouseButton button) { return mouseState[button]; }
    float getLastGamepadAxesState(GamepadAxis axis) { return currState.axes[axis]; }

    inline InputMode getInputMode() { return inputMode; };

    static glm::vec2 getCursorPosition() {return getInstance()->cursorPos;};
    static void setCursorPosition(double xpos, double ypos);
    static void setCursorPosition(glm::vec2);

	static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#ifdef __EMSCRIPTEN__
    static EM_BOOL em_keydown(int eventType, const EmscriptenKeyboardEvent *e, void *userData);
#endif

    void pollGamepad();
};

#endif
