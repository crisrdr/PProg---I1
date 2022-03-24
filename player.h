/**
 * @brief It defines the player interface
 *
 * @file player.h
 * @author Cristina y Sofía
 * @version 2.0
 * @date 24-03-2022
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

Player *player_create(Id id);

STATUS player_destroy(Player *player);

Id player_get_id(Player *player);

STATUS player_set_id(Player *player, Id id);

char player_get_name(Player *player);

STATUS player_set_name(Player *player, char *name);

Id player_get_location(Player *player);

STATUS player_set_location(Player* player, Id location);

Id player_get_object(Player* player);

STATUS player_set_object(Player* player, Id id);

STATUS player_print(Player *player);


#endif