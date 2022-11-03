#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <vector>

#include "Component.h"
#include "IInputReceiver.h"
#include "Keys.h"

class InputComponent : public Component, public IInputReceiver
{
    std::vector<Key> flags;

public:
    InputComponent(std::vector<Key> keys);

    //IInputReceiver
    void mouseInputCallback(double xpos, double ypos) {};
    void keyInputCallback(int key, int scancode, int action, int mods) {};
};

#endif // INPUT_COMPONENT