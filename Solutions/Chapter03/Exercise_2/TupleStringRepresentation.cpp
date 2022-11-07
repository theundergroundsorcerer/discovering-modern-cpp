// Solution to Exercise 3.12
// Two versions of the function provided
// Instead of to_tuple_string we have:
// toTupleStringRec - Recursive Verson
// toTupleString - Fake initializer list approach
#include <iostream>
#include <sstream>

std::string toTupleString() {
    return "()";
}

template <typename First, typename ...Last>
std::string toTupleString(const First& first, const Last& ...last) {
    std::ostringstream outputStream;
    outputStream << "(" << first;
    if constexpr (sizeof...(Last) > 0) {
        [[maybe_unused]] auto dummy = {(outputStream << "," << last, 0)...};
    }
    outputStream << ')';
    return outputStream.str();
}


void toTupleStringAux(std::ostringstream& outputStream) {}

template <typename Arg>
void toTupleStringAux(std::ostringstream& outputStream, Arg arg) {
    outputStream << arg;
}

template <typename First, typename ...Last>
void toTupleStringAux(std::ostringstream& outputStream, const First& first, const Last&... last ) {
    outputStream << first << ", ";
    toTupleStringAux(outputStream, last...);
}

template <typename ...Args>
std::string toTupleStringRec(Args... args) {
    std::ostringstream outStream;
    outStream << "(";
    toTupleStringAux(outStream, args...);
    outStream << ")";
    return outStream.str();
}

int main() {
    std::cout << toTupleString(1, 2.0, 3.5, "Heaven") << '\n';
    std::cout << toTupleString("one word") << '\n';
    std::cout << toTupleString() << '\n';

    std::cout << toTupleStringRec(1, 2.0, 3.5, "Heaven") << '\n';
    std::cout << toTupleStringRec("one word") << '\n';
    std::cout << toTupleStringRec() << '\n';
}