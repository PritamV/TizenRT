/****************************************************************************
 *
 * Copyright 2020 Samsung Electronics All Rights Reserved.
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
  * @file wifistate.h
  * @brief wifi state info.
  */

#ifndef _WIFISTATE_H__
#define _WIFISTATE_H__

#include <aienabler/network.h>
#include <aienabler/aienabler_log.h>
#include <tinyara/lwnl/lwnl.h>

#ifdef __cplusplus
extern "C"
{
#endif
	void  setwificonnectionstate(lwnl_cb_status);
	bool retWiFistate(void);
#ifdef __cplusplus
}
#endif

#endif _WIFISTATE_H__
