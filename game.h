/** 
 * @brief It defines the game interface
 * 
 * @file game.h
 * @author Sofía y Cristinas
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"

/**
 * @brief Game
 * 
 * This struct stores all the information of a game.
 * 
 */
typedef struct _Game
{
  Id player_location;
  Id object_location;
  Space *spaces[MAX_SPACES];
  T_Command last_cmd;
} Game;

/**
 * @brief Add a new space to the game
 * @author Sofía and Cristina
 * 
 * @param game pointer to the game
 * @param space pointer to the space to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_space(Game *game, Space *space);

/**
  * @brief It creates a new game, allocating memory and initializing its memebers
  * @author Sofía y Cristina
  *
  * @param game pointer to the game that is being created
  * @return a new game, initialized
  */
STATUS game_create(Game *game);

/**
 * @brief It creates a game from a file
 * @author Sofía and Cristina
 * 
 * @param game pointer to the game to be created
 * @param filename pointer to the name of the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_create_from_file(Game *game, char *filename);

/**
 * @brief It update the last command recieved
 * @author Sofía and Cristina
 * 
 * @param game pointer to the game
 * @param cmd the new command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_update(Game *game, T_Command cmd);

/**
  * @brief It destroys a game, freeing the allocated memory
  * @author Sofia y Cristina
  * 
  * @param game a pointer to the game that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_destroy(Game *game);

/**
  * @brief It gets whether the game is over or not
  * @author Sofia y Cristina
  * 
  * @param game a pointer to the game 
  * @return TRUE, if the game is over or FALSE if not.
  */
BOOL game_is_over(Game *game);

/**
  * @brief It prints the game information
  * @author Sofía y Cristina
  *
  * This function shows the player location, the object location and each of the spaces.
  * @param game a pointer to the game
  */
void game_print_data(Game *game);

/**
  * @brief It gets the space of a game
  * @author Sofía y Cristina
  * 
  * @param game a pointer to the game  
  * @param id id of the space
  * @return the space
  */
Space *game_get_space(Game *game, Id id);

/**
  * @brief It gets the location of the player
  * @author Sofía y Cristina
  * 
  * @param game a pointer to the game
  * @return id of the player location
  */
Id game_get_player_location(Game *game);

/**
 * @brief It gets the location of the object
 * @author Sofía y Cristina
 *
 * @param game a pointer to the game
 * @return id of the object location
 */
Id game_get_object_location(Game *game);

/**
 * @brief It gets the last command of the game
 * @author Sofía y Cristina
 * 
 * @param game pointer to the game
 * @return the last command recieved
 */
T_Command game_get_last_command(Game *game);

#endif
