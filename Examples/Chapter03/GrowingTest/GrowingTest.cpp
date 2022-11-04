#include <iostream>
#include <tuple>
#include <exception>
#include <toy_utilities.h>

template <typename ...Tuples>
using tupleCatType = decltype(std::tuple_cat(std::declval<Tuples>()...));

using SmallSet = std::tuple<int, float>;
using CompactSet = tupleCatType<SmallSet, std::tuple<short, double> >;


struct IdentityTest {
    template <typename T>
    static void eval() {
        T zero{0}, one{1}, nine{9};
        if(zero + nine != nine) {
            throw std::logic_error{"Addition wrong"};
        }
        if (one * nine != nine) {
            throw std::logic_error{"Multiplication wrong"};
        }
        std::cout << "Test passed for " << type_name<T>() << std::endl;
    }
};

template <typename Fun>
void foreachType(std::tuple<>, Fun) {}

template <typename First, typename ...Others, typename Fun>
void foreachType(std::tuple<First, Others...>, Fun f) {
    Fun::template eval<First>();
    foreachType(std::tuple<Others...>{}, f);
}


int main() {
    foreachType(CompactSet{}, IdentityTest{});
}