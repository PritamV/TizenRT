/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
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
 * examples/hello/hello_main.c
 *
 *   Copyright (C) 2008, 2011-2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <tinyara/lwnl/lwnl.h>
/*
 * it's test code so it doesn't strictly error handling.
 */
static void *event_listener(void *arg)
{
	int res = 0;
	int idx = *((int *)arg);
	printf("[%d] run event listener\n", idx);
	int fd = socket(AF_LWNL, SOCK_RAW, LWNL_ROUTE);
	if (fd < 0) {
		return NULL;
	}

	res = bind(fd, NULL, 0);
	if (res < 0) {
		printf("[%d] bind fail errno(%d)\n", idx, errno);
		return NULL;
	}

	fd_set rfds, ofds;
	FD_ZERO(&ofds);
	FD_SET(fd, &ofds);

	printf("[%d] run event loop\n", idx);
	for (;;) {
		rfds = ofds;
		res = select(fd + 1, &rfds, NULL, NULL, 0);
		if (res <= 0) {
			printf("[%d] select error res(%d) errno(%d))\n", idx, res, errno);
			return NULL;
		}

		if (FD_ISSET(fd, &rfds)) {
			char buf[8] = {0, };
			lwnl_cb_status status;
			uint32_t len;
			int nbytes = read(fd, (char *)buf, 8);
			if (nbytes < 0) {
				printf("[%d] read error bytes(%d) errno(%d))\n", idx, nbytes, errno);
				return NULL;
			}
			memcpy(&status, buf, sizeof(lwnl_cb_status));
			memcpy(&len, buf + sizeof(lwnl_cb_status), sizeof(uint32_t));
			printf("[%d] status (%d) len(%d)\n", idx, status, len);

			// flush the event queue
			if (len > 0) {
				char *tmp = (char *)malloc(len);
				read(fd, tmp, len);
				free(tmp);
			}
		}
	}
}

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int lwnl_sample_main(int argc, char *argv[])
#endif
{
	pthread_t pid[3];

	/*  run event listener thread */
	for (int i = 0; i < 3; i++) {
		pthread_create(&pid[i], NULL, event_listener, (void *)&i);
	}

	printf("Run wi-fi manager to generate events\n");
	/*  it's test program so it doesn't consider termination */

	return 0;
}
