#pragma once
#include <memory>

#include "bleky/ecs/Exporter.hpp"

namespace vault {

    template <typename T>
    class EXPORTED Container {
        std::unique_ptr<T> item;
        bool polymorphic{false};

        void copy(const Container &other) {
            polymorphic = other.polymorphic;

            if (!other.item) {
                item.reset();
                return;
            }

            if (polymorphic) item = other.item->clone();
            else item = std::make_unique<T>(*other.item);
        }

    public:
        Container() = default;

        Container(const Container &other) {
            copy(other);
        }

        Container(Container &&other) noexcept : item(std::move(other.item)), polymorphic(other.polymorphic) {
            other.polymorphic = false;
        }

        Container &operator=(const Container &other) {
            if (this == &other) return *this;

            copy(other);

            return *this;
        }

        Container &operator=(Container &&other) noexcept {
            if (this == &other) return *this;
            item = std::move(other.item);
            polymorphic = other.polymorphic;
            other.polymorphic = false;
            return *this;
        }

        T &operator*() {
            return get();
        }

        const T &operator*() const {
            return get();
        }

        template <typename... Args>
        T &create(Args &&...args) {
            polymorphic = false;
            item = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
            return *item;
        }

        template <typename ConcreteType, typename... Args>
            requires std::derived_from<ConcreteType, T>
        T &polyCreate(Args &&...args) {
            static_assert(std::has_virtual_destructor_v<T>, "Polymorphic base type T must have a virtual destructor.");

            polymorphic = true;
            item = std::unique_ptr<T>(new ConcreteType(std::forward<Args>(args)...));

            return *item;
        }

        T &copyFrom(const T &item) {
            polymorphic = false;
            this->item = std::unique_ptr<T>(new T(item));
            return *this->item;
        }

        template <typename ConcreteType>
            requires std::derived_from<ConcreteType, T>
        T &polyCopyFrom(const ConcreteType &item) {
            static_assert(std::has_virtual_destructor_v<T>, "Polymorphic base type T must have a virtual destructor.");

            polymorphic = true;
            this->item = std::unique_ptr<T>(new ConcreteType(item));

            return *this->item;
        }

        T &get() {
            if (!item) BLEKY_THROW_ERROR("Item not assigned.");
            return *item;
        }

        const T &get() const {
            if (!item) BLEKY_THROW_ERROR("Item not assigned.");
            return *item;
        }

        void reset() {
            polymorphic = false;
            item.reset();
        }
    };
} // namespace vault