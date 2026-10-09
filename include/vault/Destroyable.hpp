#pragma once

namespace vault {
    class Destroyable {
        bool alive{true};

    protected:
        virtual void onDestroy() = 0;

    public:
        void destroy() {
            if (alive) {
                alive = false;
                onDestroy();
            }
        }

        Destroyable() = default;

        Destroyable(const Destroyable &other) noexcept : alive(other.alive) {
            if (!alive) destroy();
        }

        Destroyable(Destroyable &&other) noexcept : alive(other.alive) {
            if (!alive) destroy();
            other.destroy();
        }

        Destroyable &operator=(const Destroyable &other) noexcept {
            if (this == &other) return *this;

            alive = other.alive;
            if (!alive) destroy();

            return *this;
        }

        Destroyable &operator=(Destroyable &&other) noexcept {
            if (this == &other) return *this;

            alive = other.alive;
            if (!alive) destroy();

            other.destroy();

            return *this;
        }

        bool isAlive() const noexcept { return alive; }
    };
} // namespace vault