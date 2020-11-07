//
//  no_print_map.cpp
//  GTest-PA3-fake
//
//  Created by dog on 2020/11/7.
//

#include <stdio.h>
#include "GameMap.h"

void GameMap::render_map_for_GTest(const Player* const players[], int num_players) const{
    // Render terrain_map onto display_map.
    for (int row = 0; row < num_rows; row += 1) {
        for (int col = 0; col < num_cols; col += 1) {
            int index = row * num_cols + col;
            display_map[index] = ((terrain_map[index] == TerrainState::BLOCKED) ? TERRAIN_BLOCKED_CHAR : TERRAIN_EMPTY_CHAR);
        }
    }

    // Render alive units onto display_map.
    for (int p = 0; p < num_players; p += 1) {
        int num_units = players[p]->get_num_units();
        Unit* const* const units = players[p]->get_units();
        for (int u = 0; u < num_units; u += 1) {
            if (units[u]->is_alive()) { display_map[units[u]->get_position_row() * num_cols + units[u]->get_position_col()] = units[u]->get_id(); }
        }
    }
}
