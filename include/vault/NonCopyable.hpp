#pragma once
#include <type_traits>
#include <utility>

// public headers...
#include "Destroyable.hpp"

namespace vault {
    template <typename Type>
    class NonCopyable {
        Type value;

    public:
        NonCopyable() = default;

        NonCopyable(const NonCopyable &other) noexcept {
            value = Type();
        }

        NonCopyable(NonCopyable &&other) noexcept : value(std::move(other.value)) {
            if constexpr (std::is_base_of<Destroyable, Type>::value) other.get().destroy();
        }

        NonCopyable &operator=(const NonCopyable &other) noexcept {
            if (this == &other) return *this;

            value = Type();

            return *this;
        }

        NonCopyable &operator=(NonCopyable &&other) noexcept {
            if (this == &other) return *this;

            value = std::move(other.value);
            if constexpr (std::is_base_of<Destroyable, Type>::value) other.get().destroy();

            return *this;
        }

        Type &get() noexcept {
            return value;
        }
    };
} // namespace vault