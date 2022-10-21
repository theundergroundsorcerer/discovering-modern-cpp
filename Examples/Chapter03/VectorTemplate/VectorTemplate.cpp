// A slightly modified example of c++11/vector_template.cpp from the book
// In particular - size_ check is removed from the assignment operator in order
// to make move semantics possible
// Additional motivation is that if the size_ of vector can not be changed after it's initialization
// then it should be a part of the type definition - and have a size_ as a template parameter
// A default constructor has been added as well

#include <cassert>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>

template <typename T>
class Vector {
public:
    explicit Vector(int vectorSize = 0) : size_{vectorSize}, data_{vectorSize == 0 ? nullptr : new T[vectorSize]} {}

    Vector(const Vector& vector) : size_{vector.size_}, data_{new T[size_]} {
        std::copy(&vector.data_[0], &vector.data_[vector.size_], &data_[0]);
    }


    Vector(Vector&& vector)  noexcept : size_{vector.size_}, data_{std::move(vector.data_)} {
        vector.size_ = 0;
        vector.data_ = std::unique_ptr<T[]>{nullptr};
    }

    Vector& operator=(const Vector& vector) & {
        size_ = vector.size_;
        data_ = std::unique_ptr{new T[size_]};
        std::copy(&vector.data_[0], vector.data_[vector.size_], &data_[0]);
        return *this;
    }

    Vector& operator=(Vector&& vector) & noexcept  {
        size_ = vector.size_;
        data_ = std::move(vector.data_);
        vector.size_ = 0;
        vector.data_ = std::unique_ptr<T[]>(nullptr);
        return *this;
    }

    [[nodiscard]] int size() const { return size_; }

    const T& operator[](int i) const & {
        checkIndex(i);
        return data_[i];
    }

    T operator[](int i) const && {
        checkIndex(i);
        return data_[i];
    }

    T& operator[](int i) & {
        checkIndex(i);
        return data_[i];
    }

    Vector operator+(const Vector& vector) {
        checkSize(vector.size_);
        Vector sum{vector.size_};

        for(int i = 0; i < size_; ++i) {
            sum[i] = data_[i] + vector[i];
        }

        return sum;
    }

private:
    int size_;
    std::unique_ptr<T[]> data_;
    void checkSize(int possibleSize) const {
        assert(this->size_ == possibleSize);
    }

    void checkIndex(int i) const { assert( i >= 0 && i < size_); }
};

class VectorBoolProxy {
public:
    VectorBoolProxy(std::byte& byte, int p) : byte_{byte}, mask_{static_cast<std::byte>(1 << p)} {}
    operator bool() const { return (byte_ & mask_) == mask_; }
    VectorBoolProxy& operator=(bool b) {
        if (b) {
            byte_ |= mask_;
        } else {
            byte_ &= ~mask_;
        }

        return *this;
    }
private:
    std::byte& byte_;
    std::byte mask_;
};

template <>
class Vector<bool> {
public:
    explicit Vector(int size) : size_{size}, data_{new std::byte[(size_ + 7) / 8]} {}

    bool operator[](int i) const {
        return VectorBoolProxy{data_[i/8], i%8};
    }

    VectorBoolProxy operator[](int i) {
        return VectorBoolProxy{data_[i/8], i%8};
    }

    [[nodiscard]] int size() const { return size_;}

private:
    int size_;
    std::unique_ptr<std::byte[]> data_;
};

template <typename Value>
std::ostream& operator<<(std::ostream& os, const Vector<Value>& vector) {
    os << '[';
    if (vector.size() > 0)
        os << vector[0];

    for(int i = 1; i < vector.size(); ++i) {
        os << ", " << vector[i];
    }

    return os << "]";
}



int main() {
    Vector<float> v1{4};
    v1[0] = v1[0] = 1.0;
    v1[2] = v1[3] = -3.0;

    std::cout << v1 << std::endl;
    Vector<float> v2 = v1;

    auto w = std::move(v1 + v2);
    std::cout << w << std::endl;

    Vector<float> v4{5};
    std::cout << v4 << std::endl;

    Vector<float> v5{5};
    v5[0] = v5[0] = v5[0] = v5[0] = v5[0] = 1;
    w = v4 + v5;
    std::cout << w << std::endl;

    Vector<bool> boolVector{13};
    for(int i = 0; i < 13; ++i) {
        bool value = static_cast<bool>(i & 1);
        boolVector[i] = value;
    }

    std::cout << boolVector << '\n';

}