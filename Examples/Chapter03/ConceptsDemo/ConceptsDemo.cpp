// A toy program that demonstrates concepts usage based on C++20/concepts_accumulate_syntactic.cpp
#include <iterator>
#include <stdexcept>
#include <list>
#include <vector>
#include <iostream>

template <typename T>
concept Returnable = std::is_move_constructible_v<T> || std::is_copy_constructible_v<T>;

template <typename Iter, typename Value>
concept Summable = requires(Iter it, Value init) {
    requires std::input_iterator<Iter>;
    requires Returnable<Value>;
    requires std::same_as<decltype(init += *it), Value&>;
};

template <typename Iter, typename Value, typename Operator>
concept Accumulable = requires(Iter it, Value init, Operator op) {
    requires std::input_iterator<Iter>;
    requires Returnable<Value>;
    init = op(init, *it);
};

struct add {
    template <typename T>
    inline T operator()(const T& x, const T& y) const noexcept {
        return x + y;
    }
};

struct Dummy {};

struct Uncopyable{
    Uncopyable(int value) : value_{value} {}
    Uncopyable(const Uncopyable&) = delete;
    Uncopyable(Uncopyable&&) = default;
    operator int() const { return value_;}
    Uncopyable& operator=(const Uncopyable& other) {
        value_ += other.value_;
        return *this;
    }
private:
    int value_;
};

struct Unmovable {
    Unmovable(int value) : value_{value} {}
    Unmovable(const Unmovable&) = default;
    Unmovable(Unmovable&&) = delete;
    Unmovable& operator=(const Unmovable& other) {
        value_ += other.value_;
        return *this;
    }
    operator int() const { return value_;}
private:
    int value_;
};

template <typename Iter, typename Value>
Value accumulate(Iter it, Iter last, Value init) requires Summable<Iter, Value> {
    for(; it != last; ++it) {
        init += *it;
    }
    return init;
}

template <typename Iter, typename Value, typename Operator>
Value accumulate(Iter it, Iter last, Value init, Operator op) requires Accumulable<Iter, Value, Operator>
{
    for(; it != last; ++it) {
        init = op(init, *it);
    }
    return init;
}

int main() {
    std::list<int> li{8, 9, 2, 4, 5};
    std::vector<int> vi{8, 9, 2, 4, 5};
    std::vector<Dummy> vd(3);
    Uncopyable au[] = {8, 9, 2, 4, 5};
    Unmovable am[] = {8, 9, 2, 4, 5};
    int sl1 = accumulate(begin(vi), end(vi), 0);
    int sv1 = accumulate(begin(vi), end(vi), 0);

    std::cout << "Sum of list{8, 9, 2, 4, 5} is: " << sl1 << '\n';
    std::cout << "Sum of vector{8, 9, 2, 4, 5} is: " << sv1 << '\n';
}

