#include <iostream>

struct global {};
struct same{};

namespace  c1 {
    struct c1c {};
    struct same {};

    namespace c2 {
        struct c2c {};
        struct same {};

        struct cc {
            global x;
            c1c y;
            c2c z;
        };

        struct csame {
            ::same x;
            c1::same y;
            same z;
        };
    }
}

auto main() -> int {
    namespace c3 = c1::c2;
    c3::cc object;
    c3::csame sameObject;
}