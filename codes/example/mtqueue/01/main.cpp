#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <condition_variable>

template<class T>
class MTQueue
{
private:
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::vector<T> m_arr;
public:
    T pop()
    {
        std::unique_lock lck( m_mtx );
        m_cv.wait( lck, [this]() {return !m_arr.empty(); } );
        T ret = std::move( m_arr.back() );
        m_arr.pop_back();
        return ret;
    }

    auto pop_hold()
    {
        std::unique_lock lck( m_mtx );
        m_cv.wait( lck, [this]() {return !m_arr.empty(); } );
        T ret = std::move( m_arr.back() );
        m_arr.pop_back();
        return std::pair( std::move( ret ), std::move( lck ) );
    }

    void push( T val )
    {
        std::unique_lock lck(m_mtx);
        m_arr.push_back( std::move( val ) );
        m_cv.notify_one();
    }

    void push_many(std::initializer_list<T> vals)
    {
        std::unique_lock lck(m_mtx);
        std::copy(
            std::move_iterator( vals.begin() ),
            std::move_iterator( vals.end() ),
            std::back_insert_iterator( m_arr ) );
        m_cv.notify_all();
    }
};

int main(int argc, char *argv[])
{
    MTQueue<int> foods;

    std::thread th1( [&]() {
        for ( int i = 0; i < 2; ++i )
        {
            auto food = foods.pop();
            std::cout << "th1 got food:" << food << std::endl;
        }
        });

    std::thread th2( [&]() {
        for ( int i = 0; i < 2; ++i )
        {
            auto food = foods.pop();
            std::cout << "th2 got food:" << food << std::endl;
        }
        });
    foods.push( 42 );
    foods.push( 233 );
    foods.push_many( { 666, 4399 } );

    th1.join();
    th2.join();

    return 0;
}
