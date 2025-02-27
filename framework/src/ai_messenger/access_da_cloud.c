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

#include <ai_messenger/access_da_cloud.h>

static CURL* hnd = NULL;
static struct curl_slist* slist1 = NULL;
static CURLcode ret;

static char* argv[4] = { NULL,"http","get", "google.com" }; // TO do all above will be handle as per open third part APIs

#define POLLING_INTERVAL 15

void ai_messenger_curl_init(void)
{
	if (strcmp(argv[1], "http") == 0 || strcmp(argv[1], "https") == 0 || strcmp(argv[1], "http2") == 0)
	{
		if (strcmp(argv[2], "get") == 0)
		{
			hnd = curl_easy_init();
			curl_easy_setopt(hnd, CURLOPT_URL, argv[3]);
			curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.35.0");
			curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

			if (strcmp(argv[1], "https") == 0)
			{
				curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
				curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);
			}

			if (strcmp(argv[1], "http2") == 0)
			{
				curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2);
			}
		}
		else if (strcmp(argv[2], "post") == 0)
		{
			if (strcmp(argv[3], "json") == 0)
			{
				slist1 = NULL;
				slist1 = curl_slist_append(slist1, "Content-Type: application/json"); // Content Type Json
				hnd = curl_easy_init();
				curl_easy_setopt(hnd, CURLOPT_URL, argv[5]);
				curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
				curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, argv[4]);
				curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)35);
				curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.35.0");
				curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
				curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
				//curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
				curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

				if (strcmp(argv[1], "https") == 0)
				{
					curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);
				}

				if (strcmp(argv[1], "http2") == 0)
				{
					curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2);
				}
			}
			else
			{
				hnd = curl_easy_init();
				curl_easy_setopt(hnd, CURLOPT_URL, argv[4]);
				/* Default Content Type : application/x-www-form-urlencoded */
				curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, argv[3]);

				if (strcmp(argv[1], "https") == 0)
				{
					curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
					curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);
				}

				if (strcmp(argv[1], "http2") == 0)
					curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2);
			}
		}
	}
}

void fetch_data_fromd_cloud(void)
{
	while (true)
	{
		sleep(POLLING_INTERVAL);
		ret = curl_easy_perform(hnd);
		if (ret != CURLE_OK)
		{
			AI_MESSENGER_LOG_ERROR("[AI_MESSENGER] curl easy perform() failed\n");
			AI_MESSENGER_ERR;
		}
		AI_MESSENGER_LOG_INFO("[AI_MESSENGER] Result [%d]\n", ret);
	}
}

void ai_messenger_curl_deinit(void)
{
	if (strcmp(argv[2], "post") == 0)
	{
		if (strcmp(argv[3], "json") == 0)
		{
			curl_easy_cleanup(hnd);
			hnd = NULL;
			curl_slist_free_all(slist1);
			slist1 = NULL;
		}
	}
	else
	{
		curl_easy_cleanup(hnd);
		hnd = NULL;
	}
}
