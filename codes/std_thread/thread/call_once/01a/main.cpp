#include <thread>
#include <iostream>
#include <string>

void SystemInit()
{
    std::cout << "Call SystemInit" << std::endl;
}

void CallOnceSystemInit()
{
    static std::once_flag flag;
    std::call_once( flag, SystemInit );
}

int main(int argc, char *argv[])
{
    CallOnceSystemInit();
    CallOnceSystemInit();
    CallOnceSystemInit();

    return 0;
}
