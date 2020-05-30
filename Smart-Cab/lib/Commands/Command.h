#pragma once


class Command
{
private:
    /* data */

    const char* command_name;
    const char* command_description;

public:
    Command(const char* name, const char* description);
    void (*func)(const void* param_1, const void* param_2)
    ~Command();
};

