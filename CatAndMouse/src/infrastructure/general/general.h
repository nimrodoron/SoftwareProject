/*
 * general.h
 *
 *  Created on: Mar 29, 2015
 *      Author: parallels
 */

#ifndef SRC_MAIN_GENERAL_H_
#define SRC_MAIN_GENERAL_H_

typedef enum resultCode {
	SUCCESS,
	ERROR
}resultCode;

typedef struct result {
	resultCode code;
	char message[30];
}result;

#endif /* SRC_MAIN_GENERAL_H_ */
