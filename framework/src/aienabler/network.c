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

 /****************************************************************************
  * Included Files
  ****************************************************************************/

#include <aienabler/network.h>
#include <aienabler/wifistate.h>

#define AIENABLER_TASH_PRI      100
#define AIENABLER_TASH_STAKSIZE 10240
#define AIENABLER_SCHED_POLICY  SCHED_RR

void NetworkEventNotification(void)
{
	int listener = socket(AF_LWNL, SOCK_RAW, LWNL_ROUTE);
	if (listener < 0)
	{
		AIENABLER_LOG_ERROR("[AIENABLER] Failed to create socket");
		AIENABLER_ERR;
		return;
	}

	if (bind(listener, NULL, 0) < 0)
	{
		AIENABLER_LOG_ERROR("[AIENABLER] bind error\n");
		AIENABLER_ERR;
	}

	fd_set readfds, fds;
	FD_ZERO(&fds);
	FD_SET(listener, &fds);	
	pthread_t threadfetchCloudData;
	pthread_attr_t attr;
	struct sched_param sparam;
	struct input_arg args;
	int status;

	bool flag = true;
	while (flag)
	{
		readfds = fds;
		// monitor readfds for readiness for reading
		if (select(listener + 1, &readfds, NULL, NULL, NULL) == -1)
		{
			AIENABLER_LOG_ERROR("[AIENABLER] select error");
			AIENABLER_ERR;
			flag = false;
		}

		if (FD_ISSET(listener, &readfds)) // fd is ready for reading
		{
			lwnl_cb_status status;
			uint32_t len;
			char type_buf[8] = { 0, };
			int nbytes = read(fd, (char*)type_buf, 8);
			if (nbytes < 0)
			{
				AIENABLER_LOG_ERROR("[AIENABLER] - Failed to receive (nbytes=%d) from select read\n", nbytes);
				AIENABLER_ERR;
				flag = false;
				break;
			}
			memcpy(&status, type_buf, sizeof(lwnl_cb_status));
			memcpy(&len, type_buf + sizeof(lwnl_cb_status), sizeof(uint32_t));
			AIENABLER_LOG_INFO("[AIENABLER] scan state(% d) length(% d)\n", status, len);
			
			setwificonnectionstate(status);

			if(wificonnectionState)
			{
				sleep(5);
				AIENABLER_LOG_INFO("[AIENABLER] fetchDataFromCloud\n");				
				/* Initialize the attribute variable */
				status = pthread_attr_init(&attr);
				if (status != 0) {					
					AIENABLER_LOG_ERROR("[AIENABLER] - pthread_attr_init failed, status=%d\n", status);
				}

				/* 1. set a priority */
				sparam.sched_priority = AIENABLER_TASH_PRI;
				status = pthread_attr_setschedparam(&attr, &sparam);
				if (status != 0) 
				{					
					AIENABLER_LOG_ERROR("[AIENABLER] - pthread_attr_setschedparam failed, status=%d\n",status);
				}

				/* 2. set a stacksize */
				status = pthread_attr_setstacksize(&attr, AIENABLER_TASH_STAKSIZE);
				if (status != 0) 
				{					
					AIENABLER_LOG_ERROR("[AIENABLER] - pthread_attr_setstacksize failed, status=%d\n",status);
				}

				/* 3. set a sched policy */
				status = pthread_attr_setschedpolicy(&attr, CURL_SCHED_POLICY);
				if (status != 0) 
				{					
					AIENABLER_LOG_ERROR("[AIENABLER] - pthread_attr_setschedpolicy failed, status=%d\n", status);
				}

				/* 4. create pthread with entry function */
				status = pthread_create(&threadfetchCloudData, &attr, fetchdatafromdacloud, NULL);
				if (status != 0) 
				{					
					AIENABLER_LOG_ERROR("[AIENABLER] - pthread_create failed, status=%d\n", status);
				}								
			}
			else // stop polling
			{
				if (pthread_cancel(threadfetchCloudData) != 0)
				{
					AIENABLER_LOG_ERROR("[AIENABLER] - polling thread cancellation failed\n");										
				}
				else
				{
					AIENABLER_LOG_ERROR("[AIENABLER] - polling thread cancellation success & clean the resources\n");		
					if (hnd)
					{
						curl_easy_cleanup(hnd);
						hnd = NULL;
					}	
					if (slist1)
					{
						curl_slist_free_all(slist1);
						slist1 = NULL;
					}
				}
			}
		}
	}
}
