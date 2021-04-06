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
  * @file access_da_cloud.h
  * @brief DA cloud Server access.
  */

#ifndef _ACCESS_DA_CLOUD_H__
#define _ACCESS_DA_CLOUD_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <ai_messenger/ai_messenger_log.h>


#ifdef __cplusplus
extern "C"
{
#endif
	void ai_messenger_curl_init(void);
	void fetch_data_fromd_cloud(void);	
	void ai_messenger_curl_deinit(void);	

#ifdef __cplusplus
}
#endif

#endif _ACCESS_DA_CLOUD_H__
