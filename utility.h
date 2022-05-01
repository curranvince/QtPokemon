#ifndef UTILITY_H
#define UTILITY_H

#include <random>

#define TILE_WIDTH 35

enum class Direction {
    NONE,
    kNorth,
    kEast,
    kSouth,
    kWest,
};

struct Position {
    int x_;
    int y_;

    Position(int nX, int nY) {
        x_ = nX;
        y_ = nY;
    }

    Position & operator=(const Position &other) {
        this->x_ = other.x_;
        this->y_ = other.y_;
        return *this;
    }

    Position(const Position& other) {
        operator=(other);
    }

    bool operator==(const Position &other) const {
        return (this->x_ == other.x_ && this->y_ == other.y_);
    }

    bool operator!=(const Position &other) const {
        return (this->x_ != other.x_ || this->y_ != other.y_);
    }

    Position Convert() const { return Position{x_*TILE_WIDTH, y_*TILE_WIDTH}; }
};

class PositionHash {
public:
    /* Hash method adapted from: https://stackoverflow.com/questions/113511/best-implementation-for-hashcode-method-for-a-collection */
    std::size_t operator () (const Position& pos) const {
        return pos.x_+31*pos.y_;
    }
};

/* Singleton pattern adapted from: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern */
class Utility
{

private:
    std::mt19937 rng;

    Utility() { rng = std::mt19937((unsigned)time(0)); }

public:
    static Utility& Instance() {
        static Utility instance;
        return instance;
    }

    Utility(Utility const&)        = delete;
    void operator=(Utility const&) = delete;

    int GetRandom(int min, int max);

};

#endif // UTILITY_H
