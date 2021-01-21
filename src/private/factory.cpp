#include "factory.hpp"
#include "mage.hpp"
#include "priest.hpp"
#include "warrior.hpp"

Factory::~Factory() {}

Character* Mage_factory::create(Team* team) { return new Mage{team}; }

Character* Warrior_factory::create(Team* team) { return new Warrior{team}; }

Character* Priest_factory::create(Team* team) { return new Priest{team}; }