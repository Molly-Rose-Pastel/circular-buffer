/*
 * main.c
 *
 *  Created on: 14.02.2019
 *      Author: Patrick Wagner
 *
 *      test program for the circular buffer:
 *
 *     first declare a buffer, a read-datafield and a write-datafield.
 *     then initialize the buffer as empty.
 *     the for-loop creates a datafield with different values and timestamps
 *     on each iteration.
 */

#include "buffer.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int main() {

	struct rb_frame buffer;
	struct rb_item w_data;
	struct rb_item r_data;

	rb_initEmpty(&buffer);

	for (int i = 0; i < BUFFER_SIZE; i++) {
		time_t timer = time(NULL);
		rb_initData(&w_data, i, ctime(&timer));
		rb_write(&buffer, &w_data);
//		rb_read(&buffer, &r_data);
		rb_print(&buffer);
		Sleep(250);		// as the computation is so fast, we use this to create
						// different timestamps
	}
//	rb_write(&buffer, &w_data);
	printf("Number of written elements: %i\n", rb_elements(&buffer));
	return 0;
}
