#include <memory>
#include <iostream>
#include <tuple>
#include <functional>
#include <vector>
#include <array>


using namespace std;

namespace CoreTests
{
    struct Component1
    {
        std::tuple<int, int, long long> position{ 1,2,3 };
    };

    struct Component2
    {
        std::string str{ "Ya!" };
    };
}