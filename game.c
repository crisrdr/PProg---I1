/** 
 * @brief It implements the game interface and all the associated calls
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_reader.h"

/**
   Private functions
*/
Id game_get_space_id_at(Game *game, int position);
STATUS game_set_player_location(Game *game, Id id);
STATUS game_set_object_location(Game *game, Id id);
Space *game_get_player_space(Game *game, Player *player);

void game_command_unknown(Game *game);
void game_command_exit(Game *game);
void game_command_next(Game *game); 
void game_command_back(Game *game);
void game_command_take(Game *game);
void game_command_drop(Game *game);
/**
   Game interface implementation
*/

STATUS game_create(Game *game)
{
  int i;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  game->player = NULL;
  game->object = NULL;
  game->last_cmd = NO_CMD;

  return OK;
}

STATUS game_create_from_file(Game *game, char *filename)
{

  if (game_create(game) == ERROR)
    return ERROR;

  if (game_reader_load_spaces(game, filename) == ERROR)
    return ERROR;

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

STATUS game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
  }

  player_destroy(game->player);
  object_destroy(game->object);

  return OK;
}

STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  if (space == NULL)
  {
    return ERROR;
  }

  while (i < MAX_SPACES && game->spaces[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{

  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

STATUS game_set_player_location(Game *game, Id id)
{

  if (id == NO_ID)
  {
    return ERROR;
  }
  if (!game)
  {
    return ERROR;
  }

  player_set_location(game->player,id);
  return OK;
}

STATUS game_set_object_location(Game *game, Id id)
{
  int i;

  if (id == NO_ID || !game)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (space_get_id(game->spaces[i]) == id)
    {
      return space_set_object(game->spaces[i], TRUE);
    }
  }

  return OK;
  }


/*
Respecto a la función game_set_object_location:
- Podría simplificarse usando game_get_space.
- No debería asignar/desasignar objetos al jugador (fallo repetido en otra pareja).
- No funciona correctamente por el tipo de dato utilizado en los espacios.
*/
Space *game_get_player_space(Game *game, Player *player)
{
  int i = 0;
  Id player_locat;
  Space *player_spc = NULL;
  if (!game || !player)
  {
    return NULL;
  }

  player_locat = game_get_player_location(game);

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (player_locat == space_get_id(game->spaces[i]))
    {
       player_spc= game->spaces[i];
    }
  }
  return player_spc;
}
Id game_get_player_location(Game *game)
{
  int i = 0;
  if (!game)
  {
    return NO_ID;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (space_get_object(game->spaces[i]) != FALSE)
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

Id game_get_object_location(Game *game)
{
  int i;
  
  if (!game) return NO_ID;

  for (i=0; i < MAX_SPACES && game->spaces[i]!=NULL; i++){
    if (space_get_object(game->spaces[i]) != FALSE){
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

STATUS game_update(Game *game, T_Command cmd)
{
  if (!game) return ERROR;

  game->last_cmd = cmd;
  
  switch (cmd)
  {
    case UNKNOWN:
      game_command_unknown(game);
      break;

    case EXIT:
      game_command_exit(game);
      break;

    case NEXT:
      game_command_next(game);
      break;

    case BACK:
      game_command_back(game);
      break;

    case TAKE:
    game_command_take(game);
    break;

    case DROP:
    game_command_drop(game);
    break;

    default:
      break;
  }

  return OK;
}

T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
}

void game_print_data(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %ld\n", game_get_object_location(game));
  printf("=> Player location: %ld\n", game_get_player_location(game));
}

BOOL game_is_over(Game *game)
{
  return FALSE;
}

/**
   Calls implementation for each action 
*/
void game_command_unknown(Game *game) {}

void game_command_exit(Game *game) {}

void game_command_next(Game *game)
{
  int i = 0;
  Id id_curr = NO_ID;
  Id id_spc = NO_ID;

  id_spc = game_get_player_location(game);
  if (id_spc == NO_ID)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    id_curr = space_get_id(game->spaces[i]);
    if (id_curr == id_spc)
    {
      id_curr = space_get_south(game->spaces[i]);
      if (id_curr != NO_ID)
      {
        game_set_player_location(game, id_curr);
      }
      return;
    }
  }
}

void game_command_back(Game *game)
{
  int i = 0;
  Id id_curr = NO_ID;
  Id id_spc = NO_ID;

  id_spc = game_get_player_location(game);

  if (NO_ID == id_spc)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    id_curr = space_get_id(game->spaces[i]);
    if (id_curr == id_spc)
    {
      id_curr = space_get_north(game->spaces[i]);
      if (id_curr != NO_ID)
      {
        game_set_player_location(game, id_curr);
      }
      return;
    }
  }
}

void game_command_take(Game *game){
  Space *player_space;

  /*Control errores*/
  if (!game || player_get_object_id(game->player) != NO_ID)
  {
    return;
  }

  player_space = game_get_player_space(game, game->player);

  /*Comprobar si en el espacio hay un objeto */
  if (space_get_object(player_space) == TRUE)
  {
    /*Asociar al jugador el id del objeto */
    player_set_object_id(game->player, object_get_id(game->object));
    /* Quitar el id al espacio */
    space_set_object(player_space, FALSE);
  }

  return;
}

void game_command_drop(Game* game){
  Space *player_space;

  /*Control errores*/
  if (!game || player_get_object_id(game->player) == NO_ID)
  {
    return;
  }

  player_space = game_get_player_space(game, game->player);

  /*Si no hay objeto en el espacio  */
  if (space_get_object(player_space) == FALSE)
  {
    /*Quitar al jugador el id del objeto */
    player_set_object_id(game->player, NO_ID);
    /* Asociar el id al espacio */
    game_set_object_location(game, space_get_id(player_space));
  }

  return;
}