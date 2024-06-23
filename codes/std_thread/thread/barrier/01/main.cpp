#include <thread>
#include <barrier>
#include <iostream>
#include <string>

void TestBar( int i, std::barrier<> *bar)
{
    std::this_thread::sleep_for( std::chrono::seconds( i ) );
    std::cout << i << " begin wait" << std::endl;
    bar->wait( bar->arrive() );
    std::cout << i << " end wait" << std::endl;
}


int main(int argc, char *argv[])
{
    int count = 3;
    std::barrier bar( count );

    for ( int i = 0; i < count; ++ i )
    {
        std::thread th(&TestBar,i,&bar);
        th.detach();
    }
    std::cin.get();

    return 0;
}
