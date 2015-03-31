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

result LoadWorldFromFile(modelBoard* model, char* name);
result SaveWorldToFile(modelBoard* model, char* name);

#endif /* SRC_SERVICES_WORLDSMANAGER_H_ */
