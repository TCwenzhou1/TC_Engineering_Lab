#pragma once
#include "cards/card.hpp"

class AttackCard final : public Card {
public:
    std::string name() const override;
    void use(GameEngine& engine, Player& user, Player& target) override;
};

#include "cards/attack_card.hpp"
#include <iostream>

// 注意：这里先假设 Player 有 name/hp；你后续会把 Player 拆到 player.hpp/.cpp
#include <string>

class Player {
public:
    std::string name;
    int hp = 4;
};

class GameEngine {};

std::string AttackCard::name() const {
    return "Attack";
}

void AttackCard::use(GameEngine&, Player& user, Player& target) {
    std::cout << user.name << " uses Attack on " << target.name << "!\n";
    target.hp -= 1;
    if (target.hp < 0) target.hp = 0;
}