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

void ChkNetwork(void)
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

	fd_set fds, readfds;
	FD_ZERO(&fds);
	FD_SET(listener, &fds);
	int fdmax = listener;
	bool flag = true;
	while (flag)
	{
		readfds = fds;
		// monitor readfds for readiness for reading
		if (select(fdmax + 1, &readfds, NULL, NULL, NULL) == -1)
		{
			AIENABLER_LOG_ERROR("[AIENABLER] select error");
			AIENABLER_ERR;
			flag = false;
		}
		
		for (int fd = 0; fd < (fdmax + 1); fd++)  
		{
			if (FD_ISSET(listener, &readfds)) // fd is ready for reading
			{
				if (fd == listener)
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
					if (wificonnectionstate(status))
					{						
						sleep(5);						
						AIENABLER_LOG_INFO("[AIENABLER] fetchDataFromCloud\n");					
						fetchdatafromdacloud();
					}					
				}				
			}			
		}
	}
}
