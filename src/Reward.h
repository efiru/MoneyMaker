#ifndef REWARD_H
#define REWARD_H

#include "Bancnota.h"
#include "Player.h"

template <typename T>
class Reward {
    T value;

public:
    explicit Reward(T val) : value(val) {}
    const T& getValue() const { return value; }

    void aplicaReward(T& target) const {
        target += value;
    }

    void aplicaReward(Player& player) const;
};


template <>
inline void Reward<int>::aplicaReward(Player& player) const {
    player.primesteClickuri(value);
}


template <>
inline void Reward<Bancnota>::aplicaReward(Player& player) const {
    player.primesteBancnotaNoua(value);
}

#endif