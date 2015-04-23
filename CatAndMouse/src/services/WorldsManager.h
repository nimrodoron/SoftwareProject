/*
 * WorldsManager.h
 *
 *  Created on: Mar 29, 2015
 *      Author: parallels
 */

#ifndef SRC_SERVICES_WORLDSMANAGER_H_
#define SRC_SERVICES_WORLDSMANAGER_H_

#include "../models/ModelBoard.h"
#include "../infrastructure/general/general.h"

#define CAT_START "cat\0"
#define MOUSE_START "mouse\0"
#define WALL_CELL 'W'
#define CAT_CELL 'C'
#define MOUSE_CELL 'M'
#define CHEESE_CELL 'P'

#define FILE_NUM_OF_ROWS 9

result LoadWorldFromFile(modelBoard* model, char* name);
result SaveWorldToFile(modelBoard* model, char* name);

#endif /* SRC_SERVICES_WORLDSMANAGER_H_ */
