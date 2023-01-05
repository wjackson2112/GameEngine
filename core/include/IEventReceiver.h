//
// Created by Will on 7/20/2022.
//

#ifndef IEVENT_RECEIVER_H
#define IEVENT_RECEIVER_H

// TODO: This should probably templated out and made project specific
typedef enum {
    BALL_LOST,
    SOLID_HIT,
    POWER_SPEED_START,
    POWER_SPEED_END,
    POWER_STICKY_START,
    POWER_STICKY_END,
    POWER_PASSTHROUGH_START,
    POWER_PASSTHROUGH_END,
    POWER_INCREASE_START,
    POWER_INCREASE_END,
    POWER_CONFUSE_START,
    POWER_CONFUSE_END,
    POWER_CHAOS_START,
    POWER_CHAOS_END,
    INPUT_LEFT,
    INPUT_RIGHT,
    NEW_GAME,
    QUIT_GAME
} Event;

class IEventReceiver
{
public:
    IEventReceiver();
    virtual void eventCallback(Event event) {};
};

#endif //IEVENT_RECEIVER_H
