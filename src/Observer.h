#ifndef OBSERVER_H
#define OBSERVER_H

class Player;

class Observer {
public:
    virtual void update(const Player& player) = 0;
    virtual ~Observer() = default;
};

#endif