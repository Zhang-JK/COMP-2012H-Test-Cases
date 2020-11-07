
//include "gtest/gtest.h"
#include "include/gtest/gtest.h"
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <cstdio>
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "GameMap.h"
#include "GameEngine.h"
#include "Player.h"
#include "Unit.h"

#include "Swordsman.h"
#include "Pikeman.h"
#include "Knight.h"
#include "Archer.h"



void load_test_map_player(GameEngine& test_game){
    string game_map_filename="GTest.map";
    test_game.game_map.load_terrain_map(game_map_filename);
    test_game.game_map.render_map_for_GTest(test_game.players, 0);

    string players_units_filename="GTest.player";
    test_game.load_players_and_units(players_units_filename);
    test_game.game_map.render_map_for_GTest(test_game.players, test_game.num_players);

}

//***************************
// task1 : game_over()
//***************************
TEST(is_game_over, one_player_left) {
    GameEngine test_1;
    load_test_map_player(test_1);
    
    EXPECT_FALSE(test_1.is_game_over());
    
    //Set player[0] dead
    for(int i=0;i<test_1.players[0]->num_units;++i){
        test_1.players[0]->units[i]->health=0;
    }
    EXPECT_TRUE(test_1.is_game_over());
}

TEST(is_game_over, zero_player_left) {
    GameEngine test_2;
    load_test_map_player(test_2);
    
    EXPECT_FALSE(test_2.is_game_over());
    
    //Set player[0],[1] both dead
    for(int i=0;i<test_2.players[0]->num_units;++i){
        test_2.players[0]->units[i]->health=0;
    }
    for(int i=0;i<test_2.players[1]->num_units;++i){
        test_2.players[1]->units[i]->health=0;
    }
    EXPECT_TRUE(test_2.is_game_over());
}


//***************************
// task2 : update_terrain_map
//***************************
TEST(update_terrain_map, set_occupied) {
    GameEngine test_3;
    load_test_map_player(test_3);
    
    int row=1,col=1;
    test_3.game_map.update_terrain_map(row, col, GameMap::TerrainState::OCCUPIED);
    EXPECT_EQ(test_3.game_map.terrain_map[row*30+col],GameMap::TerrainState::OCCUPIED);
    
    row=13;
    col=28;
    test_3.game_map.update_terrain_map(row, col, GameMap::TerrainState::OCCUPIED);
    EXPECT_EQ(test_3.game_map.terrain_map[row*30+col],GameMap::TerrainState::OCCUPIED);
    
    row=3;
    col=7;
    test_3.game_map.update_terrain_map(row, col, GameMap::TerrainState::OCCUPIED);
    EXPECT_EQ(test_3.game_map.terrain_map[row*30+col],GameMap::TerrainState::OCCUPIED);
    
}

TEST(update_terrain_map, set_blocked) {
    GameEngine test_4;
    load_test_map_player(test_4);
    
    int row=1,col=1;
    test_4.game_map.update_terrain_map(row, col, GameMap::TerrainState::BLOCKED);
    EXPECT_EQ(test_4.game_map.terrain_map[row*30+col],GameMap::TerrainState::BLOCKED);
    
    row=1;
    col=2;
    test_4.game_map.update_terrain_map(row, col, GameMap::TerrainState::BLOCKED);
    EXPECT_EQ(test_4.game_map.terrain_map[row*30+col],GameMap::TerrainState::BLOCKED);
    
    row=3;
    col=7;
    test_4.game_map.update_terrain_map(row, col, GameMap::TerrainState::BLOCKED);
    EXPECT_EQ(test_4.game_map.terrain_map[row*30+col],GameMap::TerrainState::BLOCKED);
    
    row=3;
    col=10;
    test_4.game_map.update_terrain_map(row, col, GameMap::TerrainState::BLOCKED);
    EXPECT_EQ(test_4.game_map.terrain_map[row*30+col],GameMap::TerrainState::BLOCKED);
    
    row=13;
    col=28;
    test_4.game_map.update_terrain_map(row, col, GameMap::TerrainState::BLOCKED);
    EXPECT_EQ(test_4.game_map.terrain_map[row*30+col],GameMap::TerrainState::BLOCKED);
    
}

TEST(update_terrain_map, set_empty) {
    GameEngine test_5;
    load_test_map_player(test_5);
    
    int row=1,col=1;
    test_5.game_map.update_terrain_map(row, col, GameMap::TerrainState::EMPTY);
    EXPECT_EQ(test_5.game_map.terrain_map[row*30+col],GameMap::TerrainState::EMPTY);
    
    row=13;
    col=28;
    test_5.game_map.update_terrain_map(row, col, GameMap::TerrainState::EMPTY);
    EXPECT_EQ(test_5.game_map.terrain_map[row*30+col],GameMap::TerrainState::EMPTY);
    
    row=3;
    col=7;
    test_5.game_map.update_terrain_map(row, col, GameMap::TerrainState::EMPTY);
    EXPECT_EQ(test_5.game_map.terrain_map[row*30+col],GameMap::TerrainState::EMPTY);
    
    row=3;
    col=6;
    test_5.game_map.update_terrain_map(row, col, GameMap::TerrainState::EMPTY);
    EXPECT_EQ(test_5.game_map.terrain_map[row*30+col],GameMap::TerrainState::EMPTY);
    
}

//***************************
//task3 : is_valid_path
//***************************
TEST(is_valid_path, move_outside_map) {
    GameEngine test_6;
    load_test_map_player(test_6);
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(-1, 0, 0, 0, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(-55, 16, 0, 0, 10000));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(6, 203, 0, 0, 10000));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(1, 1, -2, 0, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(1, 1, 0, -2, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(1, 1, -2, -2, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(13, 28, 2, 0, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(13, 28, 0, 2, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(6, 17, -6, 0, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(6, 17, 0, -17, 20));
    
    EXPECT_TRUE(test_6.game_map.is_valid_path(6, 17, 7, 0, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(6, 17, 8, 0, 10));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(6, 17, 100, -30, 999999));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(6, 17, 50, 88, 999999));
    
    EXPECT_FALSE(test_6.game_map.is_valid_path(6, 17, -999, 100001, 999999));
    
}

TEST(is_valid_path, beyond_move_range) {
    GameEngine test_7;
    load_test_map_player(test_7);
    
    EXPECT_FALSE(test_7.game_map.is_valid_path(1, 1, 7, 8, 10));
    
    EXPECT_FALSE(test_7.game_map.is_valid_path(1, 1, 3, 4, 6));
    
    EXPECT_TRUE(test_7.game_map.is_valid_path(1, 1, 7, 8, 15));
    
    EXPECT_TRUE(test_7.game_map.is_valid_path(11, 26, -9, -20, 29));
    
    EXPECT_FALSE(test_7.game_map.is_valid_path(11, 26, -9, -20, 28));
    
}

TEST(is_valid_path, test_blocked) {
    GameEngine test_8;
    load_test_map_player(test_8);
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(1, 1, -1, 0, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(4, 9, 0, 0, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(4, 8, 0, 1, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(4, 10, 0, -1, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(5, 9, -1, 0, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(10, 13, -6, -4, 20));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(3, 5, 0, -1, 10));
    
}

TEST(is_valid_path, test_occupied) {
    GameEngine test_8;
    load_test_map_player(test_8);
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(4, 7, 0, 0, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(4, 8, 0, -1, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(5, 7, -1, 0, 10));
    
    EXPECT_FALSE(test_8.game_map.is_valid_path(1, 1, 3, 6, 10));
    
    EXPECT_TRUE(test_8.game_map.is_valid_path(4, 7, 0, 1, 10));
    
    EXPECT_TRUE(test_8.game_map.is_valid_path(4, 7, 0, 5, 10));
    
}

//***************************
//task4 : get_unit_by_id()
//***************************
TEST(get_unit_by_id, test) {
    GameEngine test_9;
    load_test_map_player(test_9);
    
    EXPECT_EQ(test_9.players[0]->get_unit_by_id('A'),test_9.players[0]->units[0]);
    
    EXPECT_EQ(test_9.players[0]->get_unit_by_id('B'),test_9.players[0]->units[1]);
    
    EXPECT_EQ(test_9.players[0]->get_unit_by_id('C'),test_9.players[0]->units[2]);
    
    EXPECT_EQ(test_9.players[0]->get_unit_by_id('D'),test_9.players[0]->units[3]);
    
    EXPECT_EQ(test_9.players[0]->get_unit_by_id('E'),nullptr);
    
    EXPECT_EQ(test_9.players[0]->get_unit_by_id('X'),nullptr);
    
    EXPECT_EQ(test_9.players[1]->get_unit_by_id('A'),nullptr);
    
    EXPECT_EQ(test_9.players[1]->get_unit_by_id('Q'),nullptr);
    
    EXPECT_EQ(test_9.players[1]->get_unit_by_id('X'),test_9.players[1]->units[0]);
    
    EXPECT_EQ(test_9.players[1]->get_unit_by_id('Y'),test_9.players[1]->units[1]);
    
    EXPECT_EQ(test_9.players[1]->get_unit_by_id('Z'),test_9.players[1]->units[2]);

}


//***************************
//task5 : has_units_alive()
//***************************

TEST(has_units_alive, test) {
    GameEngine test_10;
    load_test_map_player(test_10);
    
    EXPECT_TRUE(test_10.players[0]->has_units_alive());
    EXPECT_TRUE(test_10.players[1]->has_units_alive());
    
    for(int i=0;i<test_10.players[0]->num_units;++i){
        EXPECT_TRUE(test_10.players[0]->has_units_alive());
        EXPECT_TRUE(test_10.players[1]->has_units_alive());
        test_10.players[0]->units[i]->health=0;
    }
    EXPECT_FALSE(test_10.players[0]->has_units_alive());
    EXPECT_TRUE(test_10.players[1]->has_units_alive());
    
    for(int i=0;i<test_10.players[1]->num_units;++i){
        EXPECT_FALSE(test_10.players[0]->has_units_alive());
        EXPECT_TRUE(test_10.players[1]->has_units_alive());
        test_10.players[1]->units[i]->health=0;
    }
    EXPECT_FALSE(test_10.players[0]->has_units_alive());
    EXPECT_FALSE(test_10.players[1]->has_units_alive());
}

//***************************
//task6 : has_units_ready()
//***************************

TEST(has_units_ready, test) {
    GameEngine test_11;
    load_test_map_player(test_11);
    
    //First, set all of them ready (it's not initialized ready)
    for(int i=0;i<test_11.players[0]->num_units;++i){
        test_11.players[0]->units[i]->ready_state=true;
    }
    for(int i=0;i<test_11.players[1]->num_units;++i){
        test_11.players[1]->units[i]->ready_state=true;
    }
    
    EXPECT_TRUE(test_11.players[0]->has_units_ready());
    EXPECT_TRUE(test_11.players[1]->has_units_ready());
    
    for(int i=0;i<test_11.players[0]->num_units;++i){
        EXPECT_TRUE(test_11.players[0]->has_units_ready());
        EXPECT_TRUE(test_11.players[1]->has_units_ready());
        test_11.players[0]->units[i]->ready_state=false;
    }
    
    EXPECT_FALSE(test_11.players[0]->has_units_ready());
    EXPECT_TRUE(test_11.players[1]->has_units_ready());
    
    for(int i=0;i<test_11.players[1]->num_units;++i){
        EXPECT_FALSE(test_11.players[0]->has_units_ready());
        EXPECT_TRUE(test_11.players[1]->has_units_ready());
        test_11.players[1]->units[i]->ready_state=false;
    }
    
    EXPECT_FALSE(test_11.players[0]->has_units_ready());
    EXPECT_FALSE(test_11.players[1]->has_units_ready());
    
    for(int i=0;i<test_11.players[0]->num_units;++i){
        test_11.players[0]->units[i]->ready_state=true;
        EXPECT_TRUE(test_11.players[0]->has_units_ready());
        EXPECT_FALSE(test_11.players[1]->has_units_ready());
    }
    
}

//***************************
//task7 : ready_all_units()
//***************************

TEST(ready_all_units, test) {
    GameEngine test_12;
    load_test_map_player(test_12);
    
    //set false for one unit each time, then ready all
    for(int i=0;i<test_12.players[0]->num_units;++i){
        test_12.players[0]->units[i]->ready_state=false;
        EXPECT_FALSE(test_12.players[0]->units[i]->ready_state);
        test_12.players[0]->ready_all_units();
        EXPECT_TRUE(test_12.players[0]->units[i]->ready_state);
    }
    
    //set all of them false, then ready all
    for(int i=0;i<test_12.players[0]->num_units;++i){
        test_12.players[0]->units[i]->ready_state=false;
    }
    test_12.players[0]->ready_all_units();
    
    
    for(int i=0;i<test_12.players[0]->num_units;++i){
        EXPECT_TRUE(test_12.players[0]->units[i]->ready_state);
    }
    
    //set both players to false, then ready all units
    for(int i=0;i<test_12.players[0]->num_units;++i){
        test_12.players[0]->units[i]->ready_state=false;
        EXPECT_FALSE(test_12.players[0]->units[i]->ready_state);
    }
    for(int i=0;i<test_12.players[1]->num_units;++i){
        test_12.players[1]->units[i]->ready_state=false;
        EXPECT_FALSE(test_12.players[0]->units[i]->ready_state);
    }
    test_12.players[0]->ready_all_units();
    
    for(int i=0;i<test_12.players[0]->num_units;++i){
        EXPECT_TRUE(test_12.players[0]->units[i]->ready_state);
    }
    for(int i=0;i<test_12.players[1]->num_units;++i){
        EXPECT_FALSE(test_12.players[1]->units[i]->ready_state);
    }
    
    //finally, set both players' all units to be ready
    test_12.players[0]->ready_all_units();
    test_12.players[1]->ready_all_units();
    for(int i=0;i<test_12.players[0]->num_units;++i){
        EXPECT_TRUE(test_12.players[0]->units[i]->ready_state);
    }
    for(int i=0;i<test_12.players[1]->num_units;++i){
        EXPECT_TRUE(test_12.players[1]->units[i]->ready_state);
    }
    
}

//***************************
//task8 : get_name()
//***************************
TEST(get_name, test) {
    GameEngine test_13;
    load_test_map_player(test_13);
    
    EXPECT_EQ(test_13.players[0]->get_name(), test_13.players[0]->name);
    EXPECT_EQ(test_13.players[1]->get_name(), test_13.players[1]->name);
}


//***************************
//task9 : get_num_units()
//***************************
TEST(get_num_units, test) {
    GameEngine test_14;
    load_test_map_player(test_14);
    
    EXPECT_EQ(test_14.players[0]->get_num_units(), test_14.players[0]->num_units);
    EXPECT_EQ(test_14.players[1]->get_num_units(), test_14.players[1]->num_units);
}

//***************************
//task10 : get_units()
//***************************
TEST(get_units, test) {
    GameEngine test_15;
    load_test_map_player(test_15);
    
    EXPECT_EQ(test_15.players[0]->get_units(), test_15.players[0]->units);
    EXPECT_EQ(test_15.players[1]->get_units(), test_15.players[1]->units);
}


//***************************
//task11 : receive_damage_actual()
//***************************
TEST(receive_damage_actual, damage_less_than_health) {
    GameEngine test_16;
    load_test_map_player(test_16);
    
    //Give 8.0 damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(8.0);
        EXPECT_EQ(test_16.players[0]->units[i]->health,2);
    }
    //Give 2.0 damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(2.0);
        EXPECT_EQ(test_16.players[0]->units[i]->health,0);
    }
    //revive player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->health=10;
    }
    
    //Give 3.4 (3) damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(3.4);
        EXPECT_EQ(test_16.players[0]->units[i]->health,7);
    }
    //Give 2.6 (3) damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(2.6);
        EXPECT_EQ(test_16.players[0]->units[i]->health,4);
    }
    //Give 1.5 (2) damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(1.5);
        EXPECT_EQ(test_16.players[0]->units[i]->health,2);
    }
    //revive player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->health=10;
    }
}

TEST(receive_damage_actual, damage_more_than_health) {
    GameEngine test_16;
    load_test_map_player(test_16);
    
    //Give 10.0 damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(10.0);
        EXPECT_EQ(test_16.players[0]->units[i]->health,0);
    }
    //Give 2.0 damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(2.0);
        EXPECT_EQ(test_16.players[0]->units[i]->health,0);
    }
    //revive player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->health=10;
    }
    
    //Give 6.4 (6) damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(6.4);
        EXPECT_EQ(test_16.players[0]->units[i]->health,4);
    }
    //Give 5.6 (6) damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(5.6);
        EXPECT_EQ(test_16.players[0]->units[i]->health,0);
    }
    //Give 1.5 (2) damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(1.5);
        EXPECT_EQ(test_16.players[0]->units[i]->health,0);
    }
    //revive player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->health=10;
    }
    
    //Give 15.0 damage to player[0]
    for(int i=0;i<test_16.players[0]->num_units;++i){
        test_16.players[0]->units[i]->receive_damage_actual(15.0);
        EXPECT_EQ(test_16.players[0]->units[i]->health,0);
    }
}

//***************************
//task12 : begin_turn()
//***************************
TEST(begin_turn, test) {
    GameEngine test_17;
    load_test_map_player(test_17);
    
    for(int i=0;i<test_17.players[0]->num_units;++i){
        test_17.players[0]->units[i]->begin_turn();
        EXPECT_TRUE(test_17.players[0]->units[i]->ready_state);
    }
    
    for(int i=0;i<test_17.players[1]->num_units;++i){
        test_17.players[1]->units[i]->begin_turn();
        EXPECT_TRUE(test_17.players[1]->units[i]->ready_state);
    }
    
}


//***************************
//task13 : end_turn()
//***************************
TEST(end_turn, test) {
    GameEngine test_17;
    load_test_map_player(test_17);
    
    for(int i=0;i<test_17.players[0]->num_units;++i){
        test_17.players[0]->units[i]->end_turn();
        EXPECT_FALSE(test_17.players[0]->units[i]->ready_state);
    }
    
    for(int i=0;i<test_17.players[1]->num_units;++i){
        test_17.players[1]->units[i]->end_turn();
        EXPECT_FALSE(test_17.players[1]->units[i]->ready_state);
    }
}


//***************************
//task14 : move_delta()
//***************************
TEST(move_delta, test) {
    GameEngine test_18;
    load_test_map_player(test_18);
    
    for(int i=0;i<test_18.players[0]->num_units;++i){
        int ori_row=test_18.players[0]->units[i]->position_row;
        int ori_col=test_18.players[0]->units[i]->position_col;
        test_18.players[0]->units[i]->move_delta(-1, 1);
        EXPECT_EQ(test_18.players[0]->units[i]->position_row, ori_row-1);
        EXPECT_EQ(test_18.players[0]->units[i]->position_col, ori_col+1);
    }
    
    for(int i=0;i<test_18.players[1]->num_units;++i){
        int ori_row=test_18.players[1]->units[i]->position_row;
        int ori_col=test_18.players[1]->units[i]->position_col;
        test_18.players[1]->units[i]->move_delta(-2, -5);
        EXPECT_EQ(test_18.players[1]->units[i]->position_row, ori_row-2);
        EXPECT_EQ(test_18.players[1]->units[i]->position_col, ori_col-5);
    }
    
}


//***************************
//task15 : attack_unit()
//***************************
TEST(attack_unit, test) {
    GameEngine test_19;
    load_test_map_player(test_19);
    
}


//***************************
//task16 : heal()
//***************************
TEST(heal, no_more_than_health) {
    GameEngine test_20;
    load_test_map_player(test_20);
    
    //Set player[0]'s health to 1, then heal()*3
    for(int i=0;i<test_20.players[0]->num_units;++i){
        test_20.players[0]->units[i]->health=1;
        test_20.players[0]->units[i]->heal();
        EXPECT_EQ(test_20.players[0]->units[i]->health, 4);
        test_20.players[0]->units[i]->heal();
        EXPECT_EQ(test_20.players[0]->units[i]->health, 7);
        test_20.players[0]->units[i]->heal();
        EXPECT_EQ(test_20.players[0]->units[i]->health, 10);
    }
    
    //Set player[1]'s health to 2, then heal()*2
    for(int i=0;i<test_20.players[1]->num_units;++i){
        test_20.players[1]->units[i]->health=2;
        test_20.players[1]->units[i]->heal();
        EXPECT_EQ(test_20.players[1]->units[i]->health, 5);
        test_20.players[1]->units[i]->heal();
        EXPECT_EQ(test_20.players[1]->units[i]->health, 8);
    }
}

TEST(heal, more_than_health) {
    GameEngine test_20;
    load_test_map_player(test_20);
    
    //Set player[0]'s health to 7, then heal()*3
    for(int i=0;i<test_20.players[0]->num_units;++i){
        test_20.players[0]->units[i]->health=7;
        test_20.players[0]->units[i]->heal();
        EXPECT_EQ(test_20.players[0]->units[i]->health, 10);
        test_20.players[0]->units[i]->heal();
        EXPECT_EQ(test_20.players[0]->units[i]->health, 10);
        test_20.players[0]->units[i]->heal();
        EXPECT_EQ(test_20.players[0]->units[i]->health, 10);
    }
    
    //Set player[1]'s health to 6, then heal()*4
    for(int i=0;i<test_20.players[1]->num_units;++i){
        test_20.players[1]->units[i]->health=6;
        test_20.players[1]->units[i]->heal();
        EXPECT_EQ(test_20.players[1]->units[i]->health, 9);
        test_20.players[1]->units[i]->heal();
        EXPECT_EQ(test_20.players[1]->units[i]->health, 10);
        test_20.players[1]->units[i]->heal();
        EXPECT_EQ(test_20.players[1]->units[i]->health, 10);
    }
}


//***************************
//task17 : get_id()
//***************************
TEST(get_id, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->get_id(), test_21.players[0]->units[i]->id);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->get_id(), test_21.players[1]->units[i]->id);
    }
}

//***************************
//task18 : get_unit_type()
//***************************

TEST(get_unit_type, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->get_unit_type(), test_21.players[0]->units[i]->unit_type);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->get_unit_type(), test_21.players[1]->units[i]->unit_type);
    }
}

//***************************
//task19 : get_attack_range()
//***************************

TEST(get_attack_range, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->get_attack_range(), test_21.players[0]->units[i]->attack_range);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->get_attack_range(), test_21.players[1]->units[i]->attack_range);
    }
}

//***************************
//task20 : get_movement_range()
//***************************

TEST(get_movement_range, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->get_movement_range(), test_21.players[0]->units[i]->movement_range);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->get_movement_range(), test_21.players[1]->units[i]->movement_range);
    }
}

//***************************
//task21 : get_position_row()
//***************************

TEST(get_position_row, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->get_position_row(), test_21.players[0]->units[i]->position_row);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->get_position_row(), test_21.players[1]->units[i]->position_row);
    }
}

//***************************
//task22 : get_position_col()
//***************************

TEST(get_position_col, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->get_position_col(), test_21.players[0]->units[i]->position_col);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->get_position_col(), test_21.players[1]->units[i]->position_col);
    }
}


//***************************
//task23 : is_ready()
//***************************

TEST(is_ready, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->is_ready(), test_21.players[0]->units[i]->ready_state);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->is_ready(), test_21.players[1]->units[i]->ready_state);
    }
}

//***************************
//task24 : is_alive()
//***************************

TEST(is_alive, test) {
    GameEngine test_21;
    load_test_map_player(test_21);
    
    for(int i=0;i<test_21.players[0]->num_units;++i){
        EXPECT_EQ(test_21.players[0]->units[i]->is_alive(), test_21.players[0]->units[i]->health!=0);
    }
    
    for(int i=0;i<test_21.players[1]->num_units;++i){
        EXPECT_EQ(test_21.players[1]->units[i]->is_alive(), test_21.players[1]->units[i]->health!=0);
    }
}
