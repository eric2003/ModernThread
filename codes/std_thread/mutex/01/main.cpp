#include <thread>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<int> arr;
    std::thread th1( [&]() {
        for ( int i = 0; i < 1000; ++i )
        {
            arr.push_back(1);
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 1000; ++i )
        {
            arr.push_back(2);
        }
        });
    th1.join();
    th2.join();

    return 0;
}
