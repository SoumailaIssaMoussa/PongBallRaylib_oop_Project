#ifndef CPUPADDLE_H
#define CPUPADDLE_H

#include "Paddle.h"

class CpuPaddle : public Paddle {
public:
    void Update(int ball_y);
};

#endif