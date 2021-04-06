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

 /****************************************************************************
  * Included Files
  ****************************************************************************/
#include <ai_messenger/ai_messenger.h>

#define AI_MESSENGER_TASH_PRI      100
#define AI_MESSENGER_TASH_STAKSIZE 10240
#define AI_MESSENGER_SCHED_POLICY  SCHED_RR

void network_event_notification(void)
{
	int listener = socket(AF_LWNL, SOCK_RAW, LWNL_ROUTE);
	if (listener < 0)
	{
		AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] Failed to create socket");
		AI_MESSENGER_ERR;
		return;
	}

	if (bind(listener, NULL, 0) < 0)
	{
		AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] bind error\n");
		AI_MESSENGER_ERR;
	}

	fd_set readfds, fds;
	FD_ZERO(&fds);
	FD_SET(listener, &fds);
	pthread_t thread_id_fetch_cloud_data;
	pthread_attr_t attr;
	struct sched_param sparam;	
	int status;

	bool flag = true;
	while (flag)
	{
		readfds = fds;
		// monitor readfds for readiness for reading
		if (select(listener + 1, &readfds, NULL, NULL, NULL) == -1)
		{
			AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] select error");
			AI_MESSENGER_ERR;
			flag = false;
		}

		if (FD_ISSET(listener, &readfds)) // fd is ready for reading
		{
			lwnl_cb_status network_status;
			uint32_t len;
			char type_buf[8] = { 0, };
			int nbytes = read(listener, (char*)type_buf, 8);
			if (nbytes < 0)
			{
				AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] - Failed to receive (nbytes=%d) from select read\n", nbytes);
				AI_MESSENGER_ERR;
				flag = false;
				break;
			}
			memcpy(&network_status, type_buf, sizeof(lwnl_cb_status));
			memcpy(&len, type_buf + sizeof(lwnl_cb_status), sizeof(uint32_t));
			AI_MESSENGER_LOG_INFO("[AI_MESSENGER] scan state(% d) length(% d)\n", network_status, len);

			if (network_status == LWNL_STA_CONNECTED)
			{
				sleep(5);
				/* Initialize the attribute variable */
				status = pthread_attr_init(&attr);
				if (status != 0) {
					AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] - pthread_attr_init failed, status=%d\n", status);
				}

				/* 1. set a priority */
				sparam.sched_priority = AI_MESSENGER_TASH_PRI;
				status = pthread_attr_setschedparam(&attr, &sparam);
				if (status != 0)
				{
					AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] - pthread_attr_setschedparam failed, status=%d\n", status);
				}

				/* 2. set a stacksize */
				status = pthread_attr_setstacksize(&attr, AI_MESSENGER_TASH_STAKSIZE);
				if (status != 0)
				{
					AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] - pthread_attr_setstacksize failed, status=%d\n", status);
				}

				/* 3. set a sched policy */
				status = pthread_attr_setschedpolicy(&attr, AI_MESSENGER_SCHED_POLICY);
				if (status != 0)
				{
					AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] - pthread_attr_setschedpolicy failed, status=%d\n", status);
				}

				/* Init CURL Lib */
				ai_messenger_curl_init();
				/* 4. create pthread with entry function */				
				status = pthread_create(&thread_id_fetch_cloud_data, &attr, fetch_data_fromd_cloud, NULL);
				if (status != 0)
				{
					AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] - pthread_create to fetch data from DA cloud got failed, status=%d\n", status);
					ai_messenger_curl_deinit();
				}
			}
			else // stop polling
			{
				if (pthread_cancel(thread_id_fetch_cloud_data) != 0)
				{
					AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] - polling thread (data fetching from DA cloud) cancellation failed\n");
				}
				else
				{
					ai_messenger_curl_deinit();
				}
			}
		}
	}
}

int ai_messenger_init(void)
{
	AI_MESSENGER_LOG_INFO("[AI_MESSENGER] Task creation for AI messenger \n");
	int tid = task_create("ai_messenger ", 100, 4096, (main_t)network_event_notification, NULL);
	if (tid < 0) 
	{		
		AI_MESSENGER_LOG_ERROR("[AI_MESSENGER]Task creation for AI messenger failed\n");
		AI_MESSENGER_ERR;
		return -1;
	}
	return 0;
}

