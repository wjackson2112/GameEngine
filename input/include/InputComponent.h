#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <vector>

#include "Component.h"
#include "IInputReceiver.h"
#include "Inputs.h"

class InputComponent : public Component, public IInputReceiver
{
    std::vector<Key> flags;

public:
    InputComponent(std::vector<Key> keys);

    //IInputReceiver
    void mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods) {};
    void keyInputCallback(Key key, int scancode, Action action, Modifier mods) {};
};

#endif // INPUT_COMPONENT