// A slightly modified example of c++11/vector_template.cpp from the book
// In particular - size check is removed from the assignment operator in order
// to make move semantics possible
// Additional motivation is that if the size of vector can not be changed after it's initialization
// then it should be a part of the type definition - and have a size as a template parameter
// A default constructor has been added as well

#include <cassert>
#include <iostream>
#include <memory>
#include <algorithm>

template <typename T>
class Vector {
public:
    explicit Vector(int vectorSize = 0) : size{vectorSize}, data{vectorSize == 0 ? nullptr : new T[vectorSize]} {}

    Vector(const Vector& vector) : size{vector.size}, data{new T[size]} {
        std::copy(&vector.data[0], &vector.data[vector.size], &data[0]);
    }


    Vector(Vector&& vector)  noexcept : size{vector.size}, data{std::move(vector.data)} {
        vector.size = 0;
        vector.data = std::unique_ptr<T[]>{nullptr};
    }

    Vector& operator=(const Vector& vector) & {
        size = vector.size;
        data = std::unique_ptr{ new T[size]};
        std::copy(&vector.data[0], vector.data[vector.size], &data[0]);
        return *this;
    }

    Vector& operator=(Vector&& vector) & noexcept  {
        size = vector.size;
        data = std::move(vector.data);
        vector.size = 0;
        vector.data = std::unique_ptr<T[]>(nullptr);
        return *this;
    }

    [[nodiscard]] int Size() const { return size; }

    const T& operator[](int i) const & {
        checkIndex(i);
        return data[i];
    }

    T operator[](int i) const && {
        checkIndex(i);
        return data[i];
    }

    T& operator[](int i) & {
        checkIndex(i);
        return data[i];
    }

    Vector operator+(const Vector& vector) {
        checkSize(vector.size);
        Vector sum{vector.size};

        for(int i = 0; i < size; ++i) {
            sum[i] = data[i] + vector[i];
        }

        return sum;
    }

private:
    int size;
    std::unique_ptr<T[]> data;
    void checkSize(int possibleSize) const {
        assert(this->size == possibleSize);
    }

    void checkIndex(int i) const { assert( i >= 0 && i < size); }
};

template <typename Value>
std::ostream& operator<<(std::ostream& os, const Vector<Value>& vector) {
    os << '[';
    if (vector.Size() > 0)
        os << vector[0];

    for(int i = 1; i < vector.Size(); ++i) {
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

}