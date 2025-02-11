#include <fstream>
#include <print>
#include <string>
#include <vector>

using namespace std;

struct prop {
    int hit_points;
    int damage;
    int armor;
};

struct item {
    int cost;
    int damage;
    int armor;
};

int parse(const string& str) {
    auto space = str.rfind(' ');
    int n      = 0;
    from_chars(str.data() + space + 1, str.data() + str.size(), n);
    return n;
}

vector<item> buy_one(const vector<item>& vec) {
    return vec;
}

vector<item> buy_one_optional(const vector<item>& vec) {
    auto res = vec;
    res.push_back({0, 0, 0});
    return res;
}

vector<item> buy_at_most_two(const vector<item>& vec) {
    vector<item> res;
    res.push_back({0, 0, 0});
    for (auto& it : vec) {
        res.push_back(it);
    }

    for (size_t i = 0; i < vec.size() - 1; ++i) {
        for (size_t j = i + 1; j < vec.size(); ++j) {
            res.push_back({vec[i].cost + vec[j].cost, vec[i].damage + vec[j].damage, vec[i].armor + vec[j].armor});
        }
    }

    return res;
}

vector<item> combination(const vector<item>& v1, const vector<item>& v2) {
    vector<item> res;
    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v2.size(); ++j) {
            res.push_back({v1[i].cost + v2[j].cost, v1[i].damage + v2[j].damage + v1[i].armor + v2[j].armor});
        }
    }
    return res;
}

bool player_win(const item& p, const prop& boss) {
    const static int player_hit = 100;

    auto damage_player_to_boss = p.damage - boss.armor;
    auto damage_boss_to_player = boss.damage - p.armor;

    auto player_round_count = boss.hit_points % damage_player_to_boss == 0 ? boss.hit_points / damage_player_to_boss
                                                                           : boss.hit_points / damage_player_to_boss + 1;
    auto boss_round_count =
        player_hit % damage_boss_to_player == 0 ? player_hit / damage_boss_to_player : player_hit / damage_boss_to_player + 1;

    return player_round_count <= boss_round_count;
}

void part1() {
    ifstream input("input/input21");
    prop boss;
    string line;
    getline(input, line);
    boss.hit_points = parse(line);
    getline(input, line);
    boss.damage = parse(line);
    getline(input, line);
    boss.armor = parse(line);

    vector<item> weapons{{8, 4, 0}, {10, 5, 0}, {25, 6, 0}, {40, 7, 0}, {74, 8, 0}};
    vector<item> armors{{13, 0, 1}, {31, 0, 2}, {53, 0, 3}, {75, 0, 4}, {102, 0, 5}};
    vector<item> rings{{25, 1, 0}, {50, 2, 0}, {100, 3, 0}, {20, 0, 1}, {40, 0, 2}, {80, 0, 3}};

    vector<item> players = buy_one(weapons);
    players              = combination(players, buy_one_optional(armors));
    players              = combination(players, buy_at_most_two(rings));

    int min_gold = INT32_MAX;
    for (auto& it : players) {
        if (player_win(it, boss)) {
            min_gold = min(min_gold, it.cost);
        }
    }

    println("{}", min_gold);
}

int main() {
    part1();
    return 0;
}
