/*
 * Flashing_Manger.h
 *
 *  Created on: Aug 29, 2024
 *      Author: hp
 */

#ifndef FLASHING_MANAGER_FLASHING_MANGER_H_
#define FLASHING_MANAGER_FLASHING_MANGER_H_

#define VALID_APP_ADDRESS			((u8*) 0x00)
#define REQ_FROM_APP_ADDRESS	((u8*) 0x01)
#define APP_SECTION	0
#define BLD_SECTION	1
void flashingMngr_vidMainTask() ;
void flashingMngr_vidHandleReqFromApp(void);

#endif /* FLASHING_MANAGER_FLASHING_MANGER_H_ */
