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

typedef struct _Object Object;

Object* object_create(Id id);

STATUS object_destroy(Object* object);

Id object_get_id(Object* object);

STATUS object_set_id(Object* object, Id id);

const char * object_get_name(Object* object);

STATUS object_set_name(Object* object, char* name);

STATUS object_print(Object* object);

#endif