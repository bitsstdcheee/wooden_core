#include "wooden_status.h"

#include <utility>
#include <vector>

game_status::game_status() {
    player_num = 0;
    players = new std::vector<int>;
}

game_status::game_status(int _player_num) {
    player_num = _player_num;
    players = new std::vector<int>(_player_num);
    for (int i = 1; i <= _player_num; i++) {
        qi[i] = 0;
        tag_died[i] = false;
        for (int j = 0; j <= NUM_SKL; j++) {
            skl_count[i][j] = 0;
        }
    }
}

game_status::game_status(int& _player_num, const std::vector<int>* _players,
                         const std::map<int, float>& _qi,
                         const std::map<int, bool>& _tag_died,
                         const std::map<int, std::map<int, int> >& _skl_count) {
    player_num = _player_num;
    // (*players) = std::move(_players);
    players = new std::vector<int>(_player_num);
    for (int i = 0; i < int(_players->size()); i++) {
        (*players)[i] = (*_players).at(i);
    }
    (qi) = _qi;
    (tag_died) = _tag_died;
    (skl_count) = _skl_count;
}
