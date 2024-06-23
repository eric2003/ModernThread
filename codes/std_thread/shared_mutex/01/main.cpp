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
        this->m_mtx.lock();
        this->m_arr.push_back( val );
        this->m_mtx.unlock();
    }
    std::size_t size() const
    {
        this->m_mtx.lock_shared();
        std::size_t ret = this->m_arr.size();
        this->m_mtx.unlock_shared();
        return ret;
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
