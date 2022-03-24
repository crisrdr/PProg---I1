/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Cristina y Sofía
 * @version 2.0
 * @date 24-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

struct _Player
{
    Id id;
    char name[WORD_SIZE + 1];
    Id location;
    Id object;
};

Player *player_create(Id id)
{
    Player *newPlayer = NULL;

    /* Error control */
    if (id == NO_ID)
        return NULL;

    newPlayer = (Player *)malloc(sizeof(Player));
    if (newPlayer == NULL)
    {
        return NULL;
    }

    /* Initialization of an empty space*/
    newPlayer->id = id;
    newPlayer->name[0] = '\0';
    newPlayer->location = NO_ID;
    newPlayer->object = FALSE;

    return newPlayer;
}

STATUS player_destroy(Player *player)
{
    if (!player)
    {
        return ERROR;
    }

    free(player);
    player = NULL;
    return OK;
}

Id player_get_id(Player *player)
{
    if (!player)
    {
        return NO_ID;
    }
    return player->id;
}

STATUS player_set_id(Player *player, Id id)
{
    if (!player || !id) return ERROR;

    player->id = id;

    return OK;
}

char player_get_name(Player *player)
{
     if (!player) {
    return NULL;
  }
  return player->name;
}

STATUS player_set_name(Player *player, char *name)
{
    if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

Id player_get_location(Player *player) {
    if (!player)
    {
        return NO_ID;
    }
    return player->location;
}

STATUS player_set_location(Player *player, Id location)
{
    if (!player || !location) return ERROR;

    player->location = location;

    return OK;
}

Id player_get_object_id(Player *player)
{
    if (!player) return NULL;

    return player->object;
}

STATUS player_set_object_id(Player *player, Id id)
{
    if (!player || !id) return ERROR;

    player->id = id;

    return OK;
}

STATUS player_print(Player *player)
{

  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s; Location: %ld; Object id: %ld)\n", player->id, player->name, player->location, player->object);
  return OK;
}