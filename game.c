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

void game_command_unknown(Game *game);
void game_command_exit(Game *game);
void game_command_next(Game *game);
void game_command_back(Game *game);

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

  player_set_location(game->player,id);
  return OK;
}

STATUS game_set_object_location(Game *game, Id id)
{
  int i;

  if (id == NO_ID)
  {
    return ERROR;
  }

  for (i=0; i < MAX_SPACES && game->spaces[i]!=NULL; i++){
    if (space_get_id(game->spaces[i]) == id){
      if (space_get_object(game->spaces[i]) != NULL){
        space_set_object(game->spaces[i], NULL);
        player_set_object_id(game->player,object_get_id(game->object));
        return OK;
      } else {
        space_set_object(game->spaces[i], game->object);
        player_set_object_id(game->player,NO_ID);
        return OK;
      }
    }
  }

  return ERROR;
}

Id game_get_player_location(Game *game)
{
  if (!game) return NO_ID;

  return player_get_location(game->player);
}

Id game_get_object_location(Game *game)
{
  int i;
  
  if (!game) return NO_ID;

  for (i=0; i < MAX_SPACES && game->spaces[i]!=NULL; i++){
    if (space_get_object(game->spaces[i]) != NULL){
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

STATUS game_update(Game *game, T_Command cmd)
{
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

  object_print(game->object);
  player_print(game->player);

}

BOOL game_is_over(Game *game)
{
  return FALSE;
}

/**
   Calls implementation for each action 
*/
void game_command_unknown(Game *game)
{
}

void game_command_exit(Game *game)
{
  
}

void game_command_next(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_command_back(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}