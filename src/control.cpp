#include "control.h"
#include <Arduino.h>

#define STOP "S"
#define FORWARD "F"
#define BACKWARD "B"
#define LEFT "L"
#define RIGHT "R"

void left()
{
}

void right()
{
}

void forward()
{
}

void backward()
{
}

void stop()
{
}

void ctrl::control(const char *cmd)
{
    if (strcmp(cmd, STOP) == 0)
    {
        stop();
    }
    else if (strcmp(cmd, FORWARD) == 0)
    {
        forward();
    }
    else if (strcmp(cmd, BACKWARD) == 0)
    {
        backward();
    }
    else if (strcmp(cmd, LEFT) == 0)
    {
        left();
    }
    else if (strcmp(cmd, RIGHT) == 0)
    {
        right();
    }
}