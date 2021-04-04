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

#include <aienabler/wifistate.h>

void  setwificonnectionstate(lwnl_cb_status status )
{	
	if (status == LWNL_STA_CONNECTED)
	{				
		AIENABLER_LOG_INFO("[AIENABLER] IP is UP \n");
		wificonnectionState = true;		
	}
	//else if(status == LWNL_STA_DISCONNECTED)
	else
	{				
		AIENABLER_LOG_INFO("[AIENABLER] IP is DOWN \n");
		wificonnectionState = false;		
	}	
}
