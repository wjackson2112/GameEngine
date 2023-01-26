//
// Created by Will on 7/20/2022.
//

#ifndef IEVENT_RECEIVER_H
#define IEVENT_RECEIVER_H

// TODO: This should probably templated out and made project specific
typedef enum {
    NEW_GAME,
    WON_GAME,
    QUIT_GAME
} Event;

class IEventReceiver
{
public:
    IEventReceiver();
    virtual void eventCallback(Event event) {};
};

#endif //IEVENT_RECEIVER_H
