// A slightly modified version of vector_constraint_initialization.cpp from the book

#include <iostream>
#include <memory>
#include <algorithm>
#include <list>
#include <iterator>

#if __has_include(<ranges>)
# include <ranges>
# define WITH_RANGES
#endif

namespace dmcpp {
    struct RangeError{};
    struct Incompatible{};

    template <std::default_initializable Value>
    class Vector {
    public:
        explicit Vector(int size) : size_{size}, data_{ new Value[size_]} {}

        Vector(std::initializer_list<Value> values) : Vector(values.size()) {
            *this = values;
        }

        Vector& operator =(std::initializer_list<Value> values) & {
            checkSize(values.size());
            std::copy(begin(values), end(values), &data_[0]);
            return *this;
        }

        void checkSize(int size) const {
            if(size_ != size) {
                throw Incompatible{};
            }
        }
    private:
        int size_;
        std::unique_ptr<Value[]> data_;

        void checkIndex(int i) const {
            if (i < 0 || i >= size_) {
                throw RangeError{};
            }
        }

        void copy(const Vector& other) {
            std::copy(std::copy(&other.data_[0], &other.data_[other.size_], data_[0]));
        }


    };
}

int main() {
    dmcpp::Vector v{1, 2, 3, 4, 5};
}