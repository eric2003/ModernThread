#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <shared_mutex>

class MTVector
{
public:
    void push_back( int val )
    {
        std::unique_lock grd( this->m_mtx );
        this->m_arr.push_back( val );
    }
    std::size_t size() const
    {
        std::shared_lock grd( this->m_mtx );
        return this->m_arr.size();
    }
private:
    std::vector<int> m_arr;
    mutable std::shared_mutex m_mtx;
};

int main(int argc, char *argv[])
{
    MTVector arr;
    std::thread th1( [&]() {
        for ( int i = 0; i < 100000; ++i )
        {
            arr.push_back( i );
        }
        });
    std::thread th2( [&]() {
        for ( int i = 0; i < 100000; ++i )
        {
            arr.push_back( 100000 + i );
        }
        });
    th1.join();
    th2.join();

    std::cout << " arr.size() = " << arr.size() << std::endl;

    return 0;
}
