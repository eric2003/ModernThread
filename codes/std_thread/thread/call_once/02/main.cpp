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
    SystemInit();
    SystemInit();

    for ( int i = 0; i < 3; ++ i )
    {
        std::thread th(SystemInit);
        th.join();
    }

    return 0;
}
