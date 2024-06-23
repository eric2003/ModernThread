#include <thread>
#include <iostream>
#include <string>

class TestLambda
{
public:
    void Start()
    {
        std::thread th( [this]() {
            std::cout << "this->name = " << this->name << "\n";
            }
        );
        th.join();
    }
    std::string name = "TestLambda";
};

int main(int argc, char *argv[])
{
    TestLambda testLambda;
    testLambda.name = "haha";
    testLambda.Start();

    return 0;
}
