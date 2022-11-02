// A slightly modified version of vector_constraint_initialization.cpp from the book

#include <iostream>
#include <memory>
#include <algorithm>
#include <list>
#include <iterator>
#include <range/v3/all.hpp> // use ranges library instead of standard ranges

namespace dmcpp {
    struct RangeError{};
    struct Incompatible{};

    template <std::default_initializable Value>
    class Vector {
    public:
        explicit Vector(int size) : size_{size}, data_{ new Value[size_]} {}

        Vector(const Vector& other) : Vector(other.size_) {
            copy(other);
        }

        Vector& operator=(const Vector& other) & {
            checkSize(other.size_);
            copy(other);
            return *this;
        }


        Vector(Vector&& other) : size_{other.size_}, data_{std::move(other.data_)} {
            other.size_ = 0;
            other.data_ = nullptr;
        }

        Vector& operator=(Vector&& other) & {
            checkSize(other.size_);
            data_ = std::move(other.data_);
            other.data_ = nullptr;
            other.size_ = 0;
            return *this;
        }


        Vector(std::initializer_list<Value> values) : Vector(values.size()) {
            *this = values;
        }

        Vector& operator=(std::initializer_list<Value> values) & {
            checkSize(values.size());
            std::copy(begin(values), end(values), &data_[0]);
            return *this;
        }

        template <std::forward_iterator Iter>
        Vector(Iter first, Iter last) : Vector(ranges::distance(first, last)) {
            using std::copy;
            copy(first, last, &data_[0]);
        }

        template <ranges::forward_range Range>
        Vector(Range&& range) : Vector(ranges::begin(std::forward<Range>(range)), ranges::end(std::forward<Range>(range)) ) {}

        void checkSize(int size) const {
            if(size_ != size) {
                throw Incompatible{};
            }
        }

        int size() const {
            return size_;
        }

        const Value& operator[](int i) const & {
            checkIndex(i);
            return data_[i];
        }

        Value& operator[](int i) & {
            checkIndex(i);
            return data_[i];
        }

        Value operator[](int i) && {
            checkIndex(i);
            return std::move(data_[i]);
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
            std::copy(&other.data_[0], &other.data_[other.size_], &data_[0]);
        }
    };

    template <std::default_initializable Value>
    Vector<Value> operator+(const Vector<Value>& v1, const Vector<Value>& v2) {
        int size = v1.size();
        v2.checkSize(size);

        Vector<Value> sum(size);

        for(int i = 0; i < size; ++i) {
            sum[i] = v1[i] + v2[i];
        }

        return sum;
    }

    template <std::default_initializable Value>
    std::ostream& operator<<(std::ostream& os, const Vector<Value>& vector) {
        os << '[';
        if (vector.size() > 0) {
            os << vector[0];
        }

        for(int i = 1; i < vector.size(); ++i) {
            os << ',' << vector[i];
        }

        return os << ']';
    }

    template <std::forward_iterator Iter>
    Vector(Iter first, Iter last) -> Vector<std::iter_value_t<Iter>>;

    template <ranges::forward_range Range>
    Vector(Range&& r) -> Vector<std::iter_value_t<decltype(begin(r))> >;
}

int main() {
    std::list l{17, 4, 3, 9, 2};
    auto v1 = dmcpp::Vector(begin(l), end(l) );
    std::cout << "Vector initialized with iterators: " << v1 << '\n';

    auto v2 = dmcpp::Vector(l);
    std::cout << "Vector initialized with range (list): " << v2 << '\n';

    auto w = dmcpp::Vector<int>(ranges::iota_view{1, 101});
    std::cout << "Vector initialized with range (iota_view): " << w << '\n';
}