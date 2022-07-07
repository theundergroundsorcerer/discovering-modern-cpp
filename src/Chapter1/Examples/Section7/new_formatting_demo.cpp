#include <fmt/format.h>

namespace dmc {
    using namespace fmt::literals;
    void Print_average(float v1, float v2, const int language) {
        auto result = (v1 + v2) / 2.0f;
        switch (language) {
            case 0:
                fmt::print("The average of {v1} and {v2} is {result}.\n",
                           "v1"_a = v1, "v2"_a = v2, "result"_a = result);
                break;
            case 1:
                fmt::print("{result:.6f} ist der Durchschnitt von {v1} und {v2}.\n",
                           "v1"_a = v1, "v2"_a = v2, "result"_a = result);
                break;
            case 2:
                fmt::print("La moyenne de {v1} et {v2} est {result}.\n",
                           "v1"_a = v1, "v2"_a = v2, "result"_a = result);
                break;
            case 3:
                fmt::print("El promedio de {v1} y {v2} es {result}.\n",
                            "v1"_a = v1, "v2"_a = v2, "result"_a = result);
                break;
            default:
                fmt::print("{result} corrisponde alla media di {v1} e {v2}.\n",
                           "v1"_a = v1, "v2"_a = v2, "result"_a = result);
        };
    }
}

int main() {
    fmt::print("Integers\n");
    fmt::print("Decimal:\t{:d} {:d} {:06d} {:d} {:0d} {:+d} {:d}\n", 1, 2, 3, 0, 0, 4, -1);
    fmt::print("Decimal:\t{} {} {:06} {} {:0} {:+} {:d}\n", 1, 2, 3, 0, 0, 4, -1);
    fmt::print("Hexadecimal:\t{:x} {:x} {:X} {:#x}\n", 5, 10, 10, 6);
    fmt::print("Octal:\t\t{:o} {:#o} {:#o}\n", 10, 10, 4);
    fmt::print("Binary:\t\t{:b} {:#b} {:#b}\n", 10, 10, 4);

    fmt::print("Default:\t{} {:g} {:g}\n", 1.5, 1.5, 1.3e20);
    fmt::print("Rounding:\t{:f} {:.0f} {:.22f}\n",  1.5, 1.5, 1.3e20);
    fmt::print("Padding:\t{:010.2f} {:.2f} {:10.2f}\n", 1.5, 1.5, 1.5);
    fmt::print("Scientific:\t{:E} {:+e}\n", 1.5, 1.5);
    fmt::print("Hexadecimal:\t{:a} {:A}\n\n", 1.5, 1.3);
}