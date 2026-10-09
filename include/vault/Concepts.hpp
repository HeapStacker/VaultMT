#pragma once

#include <concepts>

namespace vault {
    // 1. Forward deklaracija
    template <typename T>
    class Container;

    // 2. Čisti C++20 Concept (ne treba nikakvo nasljeđivanje!)
    template <typename T>
    concept IsCloneable = requires(const T &a) {
        { a.clone() } -> std::same_as<vault::Container<T>>;
    };
} // namespace vault