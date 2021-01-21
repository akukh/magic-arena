#pragma once

class Character;
class Team;

class Factory {
public:
    virtual Character* create(Team* team) = 0;
    virtual ~Factory();
};

class Mage_factory : public Factory {
public:
    Character* create(Team* team);
};


class Warrior_factory : public Factory {
public:
    Character* create(Team* team);
};


class Priest_factory : public Factory {
public:
    Character* create(Team* team);
};