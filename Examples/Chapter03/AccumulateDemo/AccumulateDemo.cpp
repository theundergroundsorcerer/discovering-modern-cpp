// accumulate_example.cpp from the book with slight modifications
#include <iostream>

template <typename T>
struct ListEntry {
    explicit ListEntry(const T& value) : value{value}, next{nullptr} {}
    explicit ListEntry(T&& value) : value{std::move(value)}, next{nullptr} {}
    T value;
    ListEntry<T>* next;
};

template <typename T>
struct ListIterator {
    explicit ListIterator(ListEntry<T>* entry) : entry_{entry} {}

    bool operator ==(const ListIterator<T>& listIterator) const {
        return entry_ == listIterator.entry_;
    }

    bool operator !=(const ListIterator<T>& listIterator) const {
        return entry_ != listIterator.entry_;
    }

    ListIterator operator++() {
        entry_ = entry_->next;
        return *this;
    }

    bool operator++(int) {
        ListIterator<T> tmp(*this);
        entry_ = entry_->next;
        return tmp;
    }

    T& operator*() { return entry_->value; }
    const T& operator*() const {return entry_->value;}
private:
    ListEntry<T>* entry_;
};

template <typename T>
struct List {
    List() : first{nullptr}, last{nullptr} {}
    ~List() {
        while (first != nullptr) {
            ListEntry<T>* tmp = first->next;
            delete first;
            first = tmp;
        }
    }

    void append(const T& x) {
        last = ((first != nullptr) ? last->next : first) = new ListEntry<T>(x);
    }

    ListIterator<T> begin() { return ListIterator<T>(first); }
    ListIterator<T> end() { return ListIterator<T>(nullptr);}

    ListEntry<T>* first;
    ListEntry<T>* last;
};

template <typename T>
inline T sum(const T* array, int n) {
    T sum{0};
    for(int i = 0; i < n; ++i) {
        sum += array[i];
    }

    return sum;
}

template <typename T, unsigned N>
inline T sum(const T (&array)[N]) {
    T sum{0};
    for (int i = 0; i < N; ++i) {
        sum += array[i];
    }

    return sum;
}

template <typename T>
inline T sum(const List<T>& list) {
    T sum{0};
    for(ListEntry<T>* entry = list.first; entry != nullptr; entry = entry->next) {
        sum += entry->value;
    }

    return sum;
}

template <typename T>
inline T accumulateArray(T* arrayPosition, T* arrayEnd) {
    T sum{0};

    for(; arrayPosition != arrayEnd; ++arrayPosition) {
        sum += *arrayPosition;
    }

    return sum;
}

template <typename Iter, typename T>
inline T accumulate(Iter it, Iter end, T init) {
    for (; it != end; ++it) {
        init += *it;
    }

    return init;
}

auto main() -> int {
    int ai[]{2, 4, 7};
    double ad[]{2., 4.5, 7.};

    std::cout << "sum ai is " << sum(ai, 3) << '\n';
    std::cout << "sum ad is " << sum(ad, 3) << '\n';

    std::cout << "sum ai is " << sum(ai) << '\n';
    std::cout << "sum ad is " << sum(ad) << '\n';

    std::cout << "sum ai is " << accumulateArray(ai,&ai[3]) << '\n';
    std::cout << "sum ad is " << accumulateArray(ad, &ad[3]) << '\n';

    std::cout << "sum ai is " << accumulate(ai, ai+3, 0);
    std::cout << "sum ad is " << accumulate(ad, ad+3, 0.0);

    List<float> list;
    std::cout << "sum list [empty] is " << sum(list) << '\n';
    std::cout << "sum list [empty] is " << accumulate(list.begin(), list.end(), 0.0f);

    list.append(2.0f);
    list.append(4.0f);
    list.append(7.0f);

    std::cout << "sum list is " << sum(list) << '\n';
    std::cout << "sum list is " << accumulate(list.begin(), list.end(), 0.0f) << std::endl;
}