#include <thread>
#include <future>
#include <iostream>
#include <string>

//void TestFuture( std::promise<std::string> &p)
void TestFuture( std::promise<std::string> p)
{
    std::cout << "begin TestFuture" << std::endl;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for( 3s );

    std::cout << "begin set value" << std::endl;
    p.set_value( "TestFuture set value" );
    std::this_thread::sleep_for( 3s );
    std::cout << "end TestFuture" << std::endl;
}

int main(int argc, char *argv[])
{
    std::promise<std::string> p;
    auto my_future = p.get_future();
    auto th = std::thread( TestFuture, std::move( p ) );
    std::cout << "begin my_future get() = " << std::endl;
    std::cout << "my_future get() = " << my_future.get() << std::endl;
    std::cout << "end my_future get() = " << std::endl;
    th.join();

    return 0;
}
