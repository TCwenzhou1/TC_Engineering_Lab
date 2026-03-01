/* 你先写这个版本（先不做网络，不做AI实现）：

你要写出来的最小骨架（你来填）

class Card（含纯虚函数 use(GameEngine&, Player&, Player&)）

class Skill（含纯虚函数 onEvent(...)，事件先用字符串占位）

class Player（name, hp, hand）

class IController（虚函数 decideAction(...)）

class GameEngine（players, run()） */


#include <iostream>
#include <vector>
#include <string>
#include <memory>

class GameEngine; // 前向声明

// -------------------------
// Player
// -------------------------
class Player {
public:
    std::string name;
    int hp = 4;

    // 手牌：使用 unique_ptr 管理多态对象（Card的派生类）
    std::vector<std::unique_ptr<class Card>> hand;

    Player(std::string n, int h = 4) : name(std::move(n)), hp(h) {}

    void addCard(std::unique_ptr<class Card> c) {
        hand.push_back(std::move(c));
    }
};

// -------------------------
// Card (抽象基类)
// -------------------------
class Card {
public:
    virtual ~Card() = default; // 必须有虚析构：通过基类指针释放派生类

    virtual std::string name() const = 0;

    // 最简版：使用者 + 目标 + 引擎（未来可扩展为事件系统）
    virtual void use(GameEngine& engine, Player& user, Player& target) = 0;
};

// -------------------------
// 一个具体牌：AttackCard
// -------------------------
class AttackCard : public Card {
public:
    std::string name() const override { return "Attack"; }

    void use(GameEngine& /*engine*/, Player& user, Player& target) override {
        std::cout << user.name << " uses Attack on " << target.name << "!\n";
        target.hp -= 1;
        if (target.hp < 0) target.hp = 0;
    }
};

// -------------------------
// Skill (抽象基类：先占位)
// -------------------------
class Skill {
public:
    virtual ~Skill() = default;
    virtual std::string name() const = 0;

    // 事件系统先用字符串占位，后续会升级成 enum + 结构体事件
    virtual void onEvent(GameEngine& engine, const std::string& eventName, Player& owner) = 0;
};

// -------------------------
// Controller：输入来源抽象（人/AI/网络）
// -------------------------
struct Action {
    // 最小动作：使用第几张牌，对第几个玩家
    int cardIndex = -1;
    int targetIndex = -1;
};

class IController {
public:
    virtual ~IController() = default;
    virtual Action decideAction(GameEngine& engine, Player& self) = 0;
};

// 一个简单控制器：永远出第0张牌打第1个玩家（演示用）
class SimpleAIController : public IController {
public:
    Action decideAction(GameEngine& engine, Player& self) override;
};

// -------------------------
// GameEngine
// -------------------------
class GameEngine {
public:
    std::vector<Player> players;
    std::vector<std::unique_ptr<IController>> controllers;

    void addPlayer(Player p, std::unique_ptr<IController> c) {
        players.push_back(std::move(p));
        controllers.push_back(std::move(c));
    }

    void runOneTurn(int idx) {
        Player& self = players[idx];
        if (self.hp <= 0) return;

        Action act = controllers[idx]->decideAction(*this, self);

        if (act.cardIndex < 0 || act.cardIndex >= (int)self.hand.size()) {
            std::cout << self.name << " does nothing.\n";
            return;
        }
        if (act.targetIndex < 0 || act.targetIndex >= (int)players.size()) {
            std::cout << self.name << " has no valid target.\n";
            return;
        }
        if (act.targetIndex == idx) {
            std::cout << self.name << " cannot target self.\n";
            return;
        }

        Player& target = players[act.targetIndex];

        // 使用卡牌（多态调用）
        self.hand[act.cardIndex]->use(*this, self, target);

        // 演示：出完牌就丢弃（最简）
        self.hand.erase(self.hand.begin() + act.cardIndex);

        // 输出状态
        std::cout << "Status: " << players[0].name << "(hp=" << players[0].hp << "), "
                  << players[1].name << "(hp=" << players[1].hp << ")\n";
    }
};

// controller 的定义放在 engine 之后，因为用到了 engine.players
Action SimpleAIController::decideAction(GameEngine& engine, Player& self) {
    (void)self;
    Action a;
    if (!engine.players.empty()) {
        a.cardIndex = 0;
        a.targetIndex = 1; // 先固定攻击第2个玩家
    }
    return a;
}

// -------------------------
// main
// -------------------------
int main() {
    GameEngine engine;

    Player p1("P1", 4);
    Player p2("P2", 4);

    // 给 P1 一张攻击牌（演示）
    p1.addCard(std::make_unique<AttackCard>());

    engine.addPlayer(std::move(p1), std::make_unique<SimpleAIController>());
    engine.addPlayer(std::move(p2), std::make_unique<SimpleAIController>());

    // 跑一回合：P1 出 Attack 打 P2
    engine.runOneTurn(0);

    return 0;
}