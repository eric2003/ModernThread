#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

int main(int argc, char *argv[])
{
    std::vector<int> arr1;
    std::vector<int> arr2;
    std::mutex mtx1;
    std::mutex mtx2;
    std::thread th1( [&]() {
        for ( int i = 0; i < 10000; ++i )
        {
            {
                std::lock_guard grd( mtx1 );
                arr1.push_back(i);
            }
            {
                std::lock_guard grd( mtx2 );
                arr2.push_back(i);
            }
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 10000; ++i )
        {
            {
                std::lock_guard grd( mtx1 );
                arr1.push_back(i+10000);
            }
            {
                std::lock_guard grd( mtx2 );
                arr2.push_back(i+10000);
            }
        }
        });
    th1.join();
    th2.join();
    int kkk = 1;

    return 0;
}
