#pragma once
#include <string>

class GameEngine;
class Player;

// 规则：所有卡牌都必须能“命名”并“使用”
class Card {
public:
    virtual ~Card() = default;

    virtual std::string name() const = 0;
    virtual void use(GameEngine& engine, Player& user, Player& target) = 0;
};