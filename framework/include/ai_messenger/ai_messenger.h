/****************************************************************************
 *
 * Copyright 2021 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

/**
 * @file ai_messenger.h
 * @brief ai_messenger service functions.
 */

#ifndef __AI_MESSENGER_H
#define __AI_MESSENGER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tinyara/config.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <debug.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <net/if.h>
#include <wifi_manager/wifi_manager.h>
#include <tinyara/wifi/wifi_manager.h>
#include <tinyara/lwnl/lwnl.h>
#include <ai_messenger/access_da_cloud.h>

#ifdef __cplusplus
extern "C" 
{
#endif
	int ai_messenger_init(void);
	void network_event_notification(void);
#ifdef __cplusplus
}
#endif
#endif //__AI_MESSENGER_H
