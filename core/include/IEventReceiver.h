//
// Created by Will on 7/20/2022.
//

#ifndef IEVENT_RECEIVER_H
#define IEVENT_RECEIVER_H

struct Event
{
public:
    enum
    {
        EVT_NONE,
        EVT_NEW_GAME,
        EVT_WON_GAME,
        EVT_QUIT_GAME,
        EVT_WIREFRAME_MODE,
        EVT_SWITCH_INPUT_MODE,
        EVT_PRESS,
        EVT_DRAG,
        EVT_RELEASE,
        EVT_EVENT_LAST
    };

    operator int(){ return value; }
    operator int() const{ return value; }

    Event() : value(EVT_NONE) {}
    explicit Event(int v) : value(v) {}
private:
    int value;
};

class IEventReceiver
{
public:
    IEventReceiver();
    virtual void eventCallback(Event event) {};
};

#endif //IEVENT_RECEIVER_H
