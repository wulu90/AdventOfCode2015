#include <map>
#include <print>
#include <queue>
#include <set>

using namespace std;

enum class turn { player, boss };

struct spell {
    enum class type { magic_missile, drain, shield, poison, recharge };

    type t;
    int cost;
    int damage_to_boss;
    int hit_point_add;
    int armor_increase;
    int effect_last;
    int mana_add;
};

vector<spell> select_spell_option(int curr_mana, const vector<spell>& spell_vec, const map<spell::type, int> active_spells) {
    vector<spell> opt_spells;
    for (auto& spell : spell_vec) {
        if (spell.cost <= curr_mana &&
            (!active_spells.contains(spell.t) || (active_spells.contains(spell.t) && active_spells.at(spell.t) == 0))) {
            opt_spells.push_back(spell);
        }
    }

    return opt_spells;
};

void part1() {
    const int boss_hit_points = 51;
    const int boss_damage = 9;
    const int player_hit_points = 50;
    const int mana = 500;

    vector<spell> spell_vec{ {spell::type::magic_missile, 53, 4, 0, 0, 0, 0},
                            {spell::type::drain, 73, 2, 2, 0, 0, 0},
                            {spell::type::shield, 113, 0, 0, 7, 6, 0},
                            {spell::type::poison, 173, 3, 0, 0, 6, 0},
                            {spell::type::recharge, 229, 0, 0, 0, 5, 101} };

    map<spell::type, const spell&> spells{ {spell::type::magic_missile, spell_vec[0]},
                                          {spell::type::drain, spell_vec[1]},
                                          {spell::type::shield, spell_vec[2]},
                                          {spell::type::poison, spell_vec[3]},
                                          {spell::type::recharge, spell_vec[4]} };

    using node = tuple<int, int, turn, int, int,
        map<spell::type, int>>;    // cost_mana,remain_mana,player/boss,player_hit_p,boss_hit_p,active_spells
    priority_queue<node, vector<node>, greater<node>> pq;

    pq.push({ 0, mana, turn::player, player_hit_points, boss_hit_points, {} });

    set<node> visited;

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        if (visited.contains(curr)) {
            continue;
        }

        auto [curr_cost, curr_mana, curr_turn, curr_p, curr_b, curr_ac] = curr;

        if (curr_p <= 0) {
            continue;
        }

        if (curr_b <= 0) {
            println("{}", curr_cost);
            break;
        }

        int effect_damage = curr_ac.contains(spell::type::poison) ? spells.at(spell::type::poison).damage_to_boss : 0;
        curr_mana += curr_ac.contains(spell::type::recharge) ? spells.at(spell::type::recharge).mana_add : 0;
        int player_armor = curr_ac.contains(spell::type::shield) ? spells.at(spell::type::shield).armor_increase : 0;

        map<spell::type, int> tmp_ac;
        for (auto& [st, t] : curr_ac) {
            if (t != 0) {
                tmp_ac.insert({ st, t - 1 });
            }
        }
        curr_ac = tmp_ac;

        if (curr_turn == turn::player) {
            auto opts = select_spell_option(curr_mana, spell_vec, tmp_ac);

            if (opts.empty()) {    // lost
                continue;
            }

            for (auto& sp : opts) {
                int tmp_damage = 0;
                tmp_ac = curr_ac;

                switch (sp.t) {
                case spell::type::magic_missile:
                case spell::type::drain:
                    tmp_damage = effect_damage + sp.damage_to_boss;
                    // damage_to_boss += sp.damage_to_boss;
                    break;

                case spell::type::shield:
                case spell::type::poison:
                case spell::type::recharge:
                    tmp_ac.insert({ sp.t, sp.effect_last  });
                    break;
                }

                pq.push({ curr_cost + sp.cost, curr_mana - sp.cost, turn::boss, curr_p + sp.hit_point_add, curr_b - tmp_damage, tmp_ac });
            }

        }
        else {
            int damage_to_player = boss_damage - player_armor;

            pq.push({ curr_cost, curr_mana, turn::player, curr_p - damage_to_player, curr_b-effect_damage, tmp_ac });
        }

        visited.insert(curr);
    }
}

int main() {
    part1();
    return 0;
}