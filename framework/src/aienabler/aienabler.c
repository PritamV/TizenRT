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
#include <aienabler/aienabler.h>

static void aienabler_test(void)	
{				
	AIENABLER_LOG_INFO("[AIENABLER] ChkNetwork() \n");
	ChkNetwork();	
}

int aienabler_init(void)
{
	AIENABLER_LOG_INFO("[AIENABLER] after task create \n");
	int tid = task_create("aienabler ", 100, 4096, (main_t)aienabler_test, NULL);			
	if (tid < 0) 
	{		
		AIENABLER_LOG_ERROR("[AIENABLER] task create failed\n");
		//AIENABLER_ERR;
		return -1;
	}
	return 0;
}
