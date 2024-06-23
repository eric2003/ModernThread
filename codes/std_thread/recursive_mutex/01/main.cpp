#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

std::recursive_mutex mtx;
void other()
{
    mtx.lock();
    mtx.unlock();
}

void func()
{
    mtx.lock();
    other();
    mtx.unlock();
}

int main(int argc, char *argv[])
{
    func();
    return 0;
}
