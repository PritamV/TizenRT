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
  * @file ai_messenger_log.h
  * @brief ai_messenger service logs.
  */

#ifndef _AI_MESSENGER_LOG_H__
#define _AI_MESSENGER_LOG_H__

#include <tinyara/config.h>

/**
 * Logging
 */
#define AI_MESSENGER_TAG "[AI_MESSENGER]"
#define CONFIG_AI_MESSENGER_USE_PRINTF // TODO this needs to be defined at its proper place

#if defined(CONFIG_AI_MESSENGER_USE_PRINTF)
#define AI_MESSENGER_VERBOSE(...)
#define AI_MESSENGER_LOG_INFO printf
#define AI_MESSENGER_LOG_DEBUG printf
#define AI_MESSENGER_LOG_ERROR printf
#else
#define AI_MESSENGER_LOG_VERBOSE nwdbg
#define AI_MESSENGER_LOG_INFO nvdbg
#define AI_MESSENGER_LOG_DEBUG ndbg
#define AI_MESSENGER_LOG_ERROR ndbg
#endif

#define AI_MESSENGER_ENTER AI_MESSENGER_LOG_INFO(AI_MESSENGER_TAG"T%d\t%s:%d\n", getpid(), __FUNCTION__, __LINE__);

#define AI_MESSENGER_LEAVE													\
	do {														\
		AI_MESSENGER_LOG_INFO(AI_MESSENGER_TAG"<---%s:%d\n", __FILE__, __LINE__);	\
	} while (0)

#define AI_MESSENGER_ERR												\
	do {													\
		AI_MESSENGER_LOG_ERROR(AI_MESSENGER_TAG"[ERR] %s: %d line err(%s)\n",	\
					 __FILE__, __LINE__, strerror(errno));	\
	} while (0)

#define MESSAGE_ERROR                                                        \
	do {                                                                     \
		AI_MESSENGER_LOG_ERROR(AI_MESSENGER_MSG_TAG_ERR"%s\t%s:%d\n", __FUNCTION__, __FILE__, __LINE__);	\	
	} while (0)

#endif // _AI_MESSENGER_LOG_H__

