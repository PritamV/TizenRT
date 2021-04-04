/****************************************************************************
*
* Copyright 2019 Samsung Electronics All Rights Reserved.
*
*Licensed under the Apache License, Version 2.0 (the "License");
*you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
*Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
* either express or implied.See the License for the specifica
* language governing permissionsand limitations under the License.
*
**************************************************************************** /

/**
 * @file network.h
 * @brief network connection service functions.
 */

#ifndef __NETWORK_H
#define __NETWORK_H

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
#include <aienabler/aienabler_log.h>
#include <aienabler/accessdacloud.h>

#ifdef __cplusplus
extern "C"
{
#endif
	void NetworkEventNotification(void);
#ifdef __cplusplus
}
#endif
#endif // __NETWORK_H

