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
  * @file aienabler_log.h
  * @brief aienabler service logs.
  */

#ifndef _AIENABLER_LOG_H__
#define _AIENABLER_LOG_H__

#include <tinyara/config.h>

/**
 * Logging
 */
#define AIENABLER_TAG "[AIENABLER]"
#define CONFIG_AIENABLER_USE_PRINTF // TODO this needs to be defined at its proper place

#if defined(CONFIG_AIENABLER_USE_PRINTF)
#define AIENABLER_LOG_INFO printf
#define AIENABLER_LOG_DEBUG printf
#define AIENABLER_LOG_ERROR printf
#else
#define AIENABLER_LOG_VERBOSE nwdbg
#define AIENABLER_LOG_INFO nvdbg
#define AIENABLER_LOG_DEBUG ndbg
#define AIENABLER_LOG_ERROR ndbg
#endif

#define AIENABLER_ENTER AIENABLER_LOG_INFO(AIENABLER_TAG"T%d\t%s:%d\n", getpid(), __FUNCTION__, __LINE__);

#define AIENABLER_LEAVE													\
	do {														\
		AIENABLER_LOG_INFO(AIENABLER_TAG"<---%s:%d\n", __FILE__, __LINE__);	\
	} while (0)

#define AIENABLER_ERR												\
	do {													\
		AIENABLER_LOG_ERROR(AIENABLER_TAG"[ERR] %s: %d line err(%s)\n",	\
					 __FILE__, __LINE__, strerror(errno));	\
	} while (0)

#define MESSAGE_ERROR                                                        \
	do {                                                                     \
		AIENABLER_LOG_ERROR(AIENABLER_MSG_TAG_ERR"%s\t%s:%d\n", __FUNCTION__, __FILE__, __LINE__);	\	
	} while (0)

#endif // _AIENABLER_LOG_H__
