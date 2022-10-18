// This program demonstrates lookup resolution by ADL and using declarations
// This is not a demo from the original book

#include <iostream>
#include <utility>

namespace mock1 {
    struct MockType{};

    template <typename LinOp>
    void initialize(LinOp& A) {
        std::cout << "mock1::initialize was called.\n";
    }

    MockType operator+(const MockType& A, const MockType& B) {
        std::cout << "mock1::operator+ was called.\n";
        return MockType{};
    }

    std::ostream& operator << (std::ostream& os, const MockType& A) {
        os << "mock1::MockType";
        return os;
    }
}

namespace mock3 {
    namespace types1 {
        struct MockType1a {};
        struct MockType1b {};
        struct MockType1c {};

        template <typename MockType>
        int someFunction(const MockType& M) { return 0; }

        template <typename MockType1, typename MockType2>
        MockType2 operator*(const MockType1&, const MockType2&) {
            std::cout << "mock3::types1::operator* was called\n";
            return MockType2{};
        }
    }

    namespace types2 {
        struct MockType2a {};
        struct MockType2b {};
        struct MockType2c {};

        template <typename MockType>
        int someFunction(const MockType& M) { return 1; }

        template <typename MockType1, typename MockType2>
        MockType2 operator*(const MockType1&, const MockType2&) {
            std::cout << "mock3::types2::operator* was called\n";
            return MockType2{};
        }
    }
}

namespace mock2 {
    struct Matrix{};

    std::ostream& operator << (std::ostream& os, const Matrix& A) {
        os << "mock2::MockType";
        return os;
    }
}

namespace mock4 {
    struct MockType {};
#if 0
    void swap(MockType& m1, MockType& m2) {
        std::cout << "mock4::swap was called.\n";
    }
#endif
}

int main() {
    mock1::MockType A, B;
    mock1::initialize(A);
    initialize(B);
    A + B;

    mock2::Matrix C, D;
    mock1::initialize(C);;

    std::cout << A << ' ' << B << ' ' << C << ' ' << D << '\n';
#if 0
    // won't compiles
    initialize(D);
#endif

    mock3::types1::MockType1a m1a;
    mock3::types1::MockType1b m1b;
    m1a * m1b;

    mock3::types1::MockType1c m1c;
    mock3::types2::MockType2a m2a;

    mock4::MockType mt1, mt2;

    using std::swap;
    swap(mt1, mt2);


}