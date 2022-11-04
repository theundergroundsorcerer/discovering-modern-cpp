// A small program demonstrating various patters of usage of variadic templates
#include <iostream>
#include "toy_utilities.h"
#include <tuple>

using namespace std::string_literals;
inline auto sum() { return 0; }

template <typename T, typename ...P>
decltype(auto) sum(T t, P ...p)
{
    return t + sum(p...);
}

template <typename ...P>
void count(P ...p) {
    std::cout << "You have " << sizeof...(P) << " parameters.\n";
}

#if 0
// doesn't compile
template <typename ...Args>
void print1(std::ostream& os, const Args& ...args) {
    (os << args << ",")...;
    os << '\n';
}
#endif

template <typename ...Args>
void dummy1(Args&...) {}

template <typename ...Args>
void print2(std::ostream& os, const Args& ...args) {
    dummy1((os << args << ", ")...);
    os << '\n';
}

template <typename ...Args>
void dummy2(Args...) {}

template <typename ...Args>
void print3(std::ostream& os, const Args& ...args) {
    dummy2((os << args << ", ", 0)...);
    os << '\n';
}

template <typename ...Args>
void print4(std::ostream& os, const Args&... args) {
    auto dummy = {(os << args << ", ", 0)...};
    os << '\n';
}

struct Printer {
    template <typename First, typename ...Rest>
    void operator()(const First& first, const Rest... rest) const {
        if constexpr(sizeof...(rest) == 0) {
            std::cout << first << '\n';
        } else {
            std::cout << first << ", ";
            (*this)(rest...);
        }
    }
};

template <typename ...Args>
struct Caller {
    Caller(Args&&... args) : tuple_(std::forward<Args>(args)...) {}

    template <typename F> auto call(F f) const {
        callHelp(f, std::make_index_sequence<sizeof...(Args)>{});
    }

    template <typename F, size_t ...I>
    auto callHelp(F f, std::index_sequence<I...>) const {
        return f(get<I>(tuple_)...);
    }
private:
    std::tuple<Args...> tuple_;
};

namespace dmcpp {
    struct Pstring {
        Pstring(const std::string& string) : string_{string} {}

        friend Pstring operator+(const Pstring& ps1, const Pstring& ps2) {
            return Pstring("(" + ps1.string_ + ps2.string_ + ")");
        }

        friend std::ostream& operator<<(std::ostream& os, const Pstring ps) {
            return os << ps.string_;
        }

        operator std::string() const { return string_; }
    private:
        std::string string_;
    };

    Pstring operator"" _ps(const char* string, std::size_t) {
        return Pstring(string);
    }
    template<typename ...P>
    auto sumFoldLeft(const P &...p) {
        return (0+ ... +p);
    }

    template<typename ...Strings>
    auto concatLeft(const Strings &...strings) {
        return (""s +...+ strings);
    }

    template<typename ...Strings>
    auto concatRight(const Strings &...strings) {
        return (strings +...+ ""s);
    }
}



int main() {
    using namespace dmcpp;

    auto s1 = sum(-7, 3.7f, 9u, -2.6);
    std::cout << "s1 is " << s1 << " and its type is " << type_name<decltype(s1)>() << '\n';

    auto s2 = sum(-2, -3, -5, 7.5);
    std::cout << "s2 is " << s2 << " and its type is " << type_name<decltype(s2)>() << '\n';

    count();
    count(1, 2, 3, 5, "hey");

    print2(std::cout, 3, 17.2, "Thingy", "Troll");
    print3(std::cout, 3, 17.2, "Thingy", "Troll");
    print4(std::cout, 3, 17.2, "Thingy", "Troll");

    auto data = Caller(3, 17.2, "Thingy"s, "Troll"s);
    data.call(Printer{});

    std::cout << "sum(-2, 3f, 4u, 5, 16.5) = " << sum(-2, 3.f, 4u, 5, 16.5) << '\n';
    std::cout << "sum() = " << sum() << '\n';

    std::cout << "concatLeft  -> " << concatLeft("we"s, "concat"s, "some"s, "strings"s) << '\n';
    std::cout << "concatRight -> " << concatRight("we"s, "concat"s, "some"s, "strings"s) << '\n';

    std::cout << "concatLeft  -> " << concatLeft("we"_ps, "concat"_ps, "some"_ps, "strings"_ps) << '\n';
    std::cout << "concatRight -> " << concatRight("we"_ps, "concat"_ps, "some"_ps, "strings"_ps) << '\n';

    std::cout << "concatLeft  -> " << concatLeft() << '\n';
    std::cout << "concatRight -> " << concatRight() << '\n';


}