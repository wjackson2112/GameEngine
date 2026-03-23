//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by will on 8/20/25.
//

#ifndef ACTION_H
#define ACTION_H
#include "IEventReceiver.h"

enum ActionState
{
    AS_IDLE,
    AS_PRESSED,
    AS_DRAGGING
};

template<typename T>
class Action : public IEventReceiver {
protected:
    T* gameMode = nullptr;

public:
    ~Action() {}
    ActionState state = AS_IDLE;

    Action(T* gameMode) : gameMode(gameMode) {}
};

#endif //ACTION_H
