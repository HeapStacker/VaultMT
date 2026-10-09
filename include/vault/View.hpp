#pragma once

namespace vault {
    template <typename T, bool Copyable = false, bool Movable = false>
    class View {
        T *pointer{nullptr};

    public:
        View() = default;

        View(const View &other) noexcept {
            if constexpr (Copyable) pointer = other.pointer;
            else pointer = nullptr;
        }

        View(View &&other) noexcept {
            if constexpr (Movable) pointer = other.pointer;
            else pointer = nullptr;
        }

        View &operator=(const View &other) noexcept {
            if (this == &other) return *this;

            if constexpr (Copyable) pointer = other.pointer;
            else pointer = nullptr;

            return *this;
        }

        View &operator=(View &&other) noexcept {
            if (this == &other) return *this;

            if constexpr (Movable) pointer = other.pointer;
            else pointer = nullptr;

            return *this;
        }

        void assign(T *pointer) noexcept {
            this->pointer = pointer;
        }

        T *const get() const noexcept {
            return pointer;
        }
    };
} // namespace vault