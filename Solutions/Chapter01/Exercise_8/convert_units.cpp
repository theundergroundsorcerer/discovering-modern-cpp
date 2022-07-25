// Solution to exercise 8, Chapter 1 in Discovering Modern C++
// Converts between SI units and Anglo-American units
// Correctness is tested using assert
#include <cassert>
#include <iostream>

constexpr double kMeterInFoot = 0.3048;
constexpr double kKilogramInLb =  0.45359237;
constexpr double kNewtonInPoundForce = 4.4482216152605;

double FootToMeter(double foot) {
    return kMeterInFoot * foot;
}

double MeterToFoot(double meter) {
    return  meter / kMeterInFoot;
}

double LbToKilogram(double lb) {
    return kKilogramInLb * lb;
}

double KilogramToLb(double kg) {
    return kg / kKilogramInLb;
}

double PoundForceToNewton(double lbf) {
    return lbf * kNewtonInPoundForce;
}

double NewtonToPoundForce(double newton) {
    return newton / kNewtonInPoundForce;
}



double FahrenheitToCelsius(double fahrenheit) {
    return 5.0 * (fahrenheit - 32.0) / 9.0;
}

double CelsiusToFahrenheit(double celsius) {
    return 1.8 * celsius + 32.0;
}

constexpr double kEpsilon = 1.0e-4;

int main() {
    assert(std::abs(MeterToFoot(1.0) - 3.28084) < kEpsilon );
    std::cout << "1m is approximately " << MeterToFoot(1.0) << "ft\n";

    assert(std::abs(FootToMeter(1.0) - 0.3048) < kEpsilon);
    std::cout << "1ft is approximately " << FootToMeter(1.0) << "m\n";

    assert(std::abs(KilogramToLb(1.0) - 2.20462) < kEpsilon);
    std::cout << "1kg is approximately " << KilogramToLb(1.0) << "lb\n";

    assert(std::abs(LbToKilogram(1.0) - 0.453592) < kEpsilon);
    std::cout << "1lb is approximately " << LbToKilogram(1.0) << "kg\n";

    assert(std::abs(NewtonToPoundForce(1.0) - 0.224809) < kEpsilon);
    std::cout << "1N is approximately " << NewtonToPoundForce(1.0) << "lbf\n";

    assert(std::abs(PoundForceToNewton(1.0) - 4.44822) < kEpsilon);
    std::cout << "1N is approximately " << PoundForceToNewton(1.0) << "N\n";

    assert(std::abs(CelsiusToFahrenheit(100.0) - 212.0) < kEpsilon);
    std::cout << "100C is approximately" << CelsiusToFahrenheit(100.0) << "F\n";

    assert(std::abs(FahrenheitToCelsius(100.0) - 37.7778) < kEpsilon);
    std::cout << "100F is approximately " << FahrenheitToCelsius(100.0) << "C\n";

    return 0;
}