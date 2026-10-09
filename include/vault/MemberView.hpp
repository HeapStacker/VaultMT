#pragma once
#include <cstddef>
#include <stdexcept>

namespace vault {

    // WARNING: BE VERY CAREFUL WITH UTILISING THIS CLASS.
    // ONLY CAREFULLY USE IT ON IT'S SIBLINGS
    template <typename Member>
    class MemberView {
        Member *pointer{nullptr};

        void assignPointer(const MemberView &other) noexcept {
            if (other.pointer == nullptr) throw std::runtime_error("Vault: assignPointer: Cannot assign nullptr to MemberView.");

            auto ptr = reinterpret_cast<std::byte *>(other.pointer);
            auto diff = ptr - reinterpret_cast<std::byte *>(&other);
            this->pointer = reinterpret_cast<Member *>(reinterpret_cast<std::byte *>(this) + diff);
        }

    public:
        MemberView(Member *pointer) noexcept : pointer(pointer) {
            if (pointer == nullptr) throw std::runtime_error("Vault: ctor: Cannot assign nullptr to MemberView.");
        }

        MemberView(const MemberView &other) noexcept {
            assignPointer(other);
        }

        MemberView(MemberView &&other) noexcept : pointer(other.pointer) {
            assignPointer(other);

            other.pointer = nullptr;
        }

        MemberView &operator=(const MemberView &other) noexcept {
            if (this == &other) return *this;

            assignPointer(other);

            return *this;
        }

        MemberView &operator=(MemberView &&other) noexcept {
            if (this == &other) return *this;

            assignPointer(other);

            other.pointer = nullptr;

            return *this;
        }

        void assign(Member *pointer) noexcept {
            if (pointer == nullptr) throw std::runtime_error("Vault: assign: Cannot assign nullptr to MemberView.");
            this->pointer = pointer;
        }

        Member *const get() const noexcept {
            return pointer;
        }
    };
} // namespace vault