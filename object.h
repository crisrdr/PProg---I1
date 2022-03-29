/**
 * @brief It defines the space interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/**
 * @brief Object
 * 
 * This struct stores all the information of an object.
 * 
 */
typedef struct _Object Object;

/**
  * @brief It creates a new object, allocating memory and initializing its memebers
  * @author Profesores PPROG
  * 
  * @param id the identification number for the new object
  * @return a new object, initialized
  */
Object* object_create(Id id);

/**
  * @brief It destroys an object, freeing the allocated memory
  * @author Profesores PPROG
  * 
  * @param object a pointer to the object that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_destroy(Object* object);

/**
  * @brief It gets the id of an object
  * @author Profesores PPROG
  * 
  * @param object a pointer to the object  
  * @return the id of object
  */
Id object_get_id(Object* object);

/**
  * @brief It sets the id of the object
  * @author Profesores PPROG
  *
  * @param object a pointer to the object
  * @param id the id number of the object
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_id(Object* object, Id id);

/**
  * @brief It gets the name of an object
  * @author Sofía y Cristina
  * 
  * @param object a pointer to the object  
  * @return the name of the object
  */
const char * object_get_name(Object* object);

/**
  * @brief It sets the name of the object
  * @author Profesores PPROG
  *
  * @param object a pointer to the object
  * @param name the new name of the object
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS object_set_name(Object* object, char* name);

/**
  * @brief It prints the object information
  * @author Sofía y Cristina
  *
  * This function shows the object id and its name.
  * @param object a pointer to the object
  */
STATUS object_print(Object* object);

#endif