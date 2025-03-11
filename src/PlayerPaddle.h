#ifndef PLAYERPADDLE_H
#define PLAYERPADDLE_H

#include "Paddle.h"

class PlayerPaddle : public Paddle {
public:
    void Update() override;
};

#endif