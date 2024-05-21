#ifndef IINPUT_RECEIVER_H
#define IINPUT_RECEIVER_H

#include "Inputs.h"
#include "InputEvent.h"

class IInputReceiver
{
public:
	virtual void mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods) {};
	virtual void keyInputCallback(Key key, int scancode, Action action, Modifier mods) {};
    virtual void gamepadInputCallback(GamepadButton padButton, GamepadAxis axis, float axisValue, Action action) {};

    virtual void inputCallback(InputEvent event) {};
};

#endif
