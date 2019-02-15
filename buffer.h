/*
 * buffer.h
 *
 *  Created on: 14.02.2019
 *      Author: Patrick Wagner
 *
 *      struct rb_item
 *      struct rb_frame
 *
 *      void rb_initEmpty(struct rb_frame *pBuffer)
 *      void rb_initData(struct rb_item *pData, unsigned short int data, char *pTime)
 *      void rb_setToWrite(struct rb_frame *pBuffer)
 *      void rb_setToRead(struct rb_frame *pBuffer)
 *      void rb_write(struct rb_frame *pBuffer, struct rb_item *pData)
 *      void rb_read(struct rb_frame *pBuffer, struct rb_item *pData)
 *      unsigned char rb_elements(struct rb_frame *pBuffer)
 *      void rb_print(struct rb_frame *pBuffer)
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#define BUFFER_SIZE 10

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
 * struct rb_item
 * @brief this is the data-field the buffer consists of
 * @param none
 * @return none
 */
struct rb_item {
	char timestamp[25];
	unsigned short int value;
	bool isRead, isWrite;
};

/*
 * struct rb_frame
 * @brief sets the frame for the buffer, creates an array of rb_items.
 * rb_write is the write index and rb_read is the read index
 * @param none
 * @return none
 */
struct rb_frame {
	struct rb_item buffer[BUFFER_SIZE];
	unsigned char rb_write, rb_read;
};

/*
 * void rb_initEmpty()
 * @brief initialises the transferred buffer with indexes set to 0 and prepares
 * each element for writing
 * @param struct rb_frame *pBuffer: a pointer to the buffer that the user wants to
 * initialize
 * @return none
 */
void rb_initEmpty(struct rb_frame *pBuffer) {
	pBuffer->rb_read = 0;
	pBuffer->rb_write = 0;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		pBuffer->buffer[i].isRead = true;
		pBuffer->buffer[i].isWrite = false;
	}
}

/*
 * void rb_initData()
 * @brief initializes a data field, used for testing
 * @param struct rb_item *pData: a pointer to the datafield that the user wants to
 * initialize
 * unsigned short int data: an arbitrary data value
 * char *pTime: a pointer to a string that contains the time, used as timestamp
 * @return none
 */
void rb_initData(struct rb_item *pData, unsigned short int data, char *pTime) {
	pData->value = data;
	strcpy(pData->timestamp, (const char*) pTime);
}

/*
 * void rb_setToWrite()
 * @brief sets the boolean r/w indices of the datafield of the transferred buffer
 * at the current read index to write access allowed and read access denied.
 * @param struct rb_fram *pBuffer: pointer to the ringbuffer
 * @return none
 */
void rb_setToWrite(struct rb_frame *pBuffer) {
	pBuffer->buffer[pBuffer->rb_read].isRead = true;
	pBuffer->buffer[pBuffer->rb_read].isWrite = false;
}

/*
 * void rb_setToRead()
 * @brief sets the boolean r/w indices of the datafield of the transferred buffer
 * at the current write index to write access denied and read acces allowed.
 * @param struct rb_frame *pBuffer: pointer to the ringbuffer
 * @return none
 */
void rb_setToRead(struct rb_frame *pBuffer) {
	pBuffer->buffer[pBuffer->rb_write].isRead = false;
	pBuffer->buffer[pBuffer->rb_write].isWrite = true;
}

/*
 * void rb_write()
 * @brief writes the transferred datafield into the transferred Buffer at the
 * position the write index currently is. Checks if the element is set to read
 * and prints error if not. Uses 'rb_setToRead()' after successfull writing and
 * increments the write index.
 * @param struct rb_fram *pBuffer: pointer the Buffer to write to
 * struct rb_item *pData: pointer the data field to write from
 * @return none
 */
void rb_write(struct rb_frame *pBuffer, struct rb_item *pData) {
	if (pBuffer->buffer[pBuffer->rb_write].isRead == false) {
		printf("Buffer overflow!\n");

	} else {
		pBuffer->buffer[pBuffer->rb_write] = *pData;
		rb_setToRead(pBuffer);
		pBuffer->rb_write++;
		if (pBuffer->rb_write == BUFFER_SIZE) {
			pBuffer->rb_write = 0;
		}
	}
}

/*
 * void rb_read()
 * @brief reads the datafield from the transferred buffer at the position the
 * read index currently is and writes it into the transferred datafiled. Checks
 * if the element is set to red and print error if not. Uses 'rb_setToWrite()'
 * after successfull reading and increments the read index.
 * @param struct rb_frame *pBuffer: pointer to the Buffer
 * struct rb_item *pData: pointer to the Datafield
 * @return none
 */
void rb_read(struct rb_frame *pBuffer, struct rb_item *pData) {
	if (pBuffer->buffer[pBuffer->rb_read].isWrite == false) {
		printf("No data to read!\n");
	} else {
		pData = &pBuffer->buffer[pBuffer->rb_read];
		rb_setToWrite(pBuffer);
		pBuffer->rb_read++;
		if (pBuffer->rb_read == BUFFER_SIZE) {
			pBuffer->rb_read = 0;
		}
	}
}

/*
 * unsigned char rb_elements()
 * @brief returns the current number of unread elements in the ringbuffer
 * @para struct rb_frame *pBuffer: pointer to the ringbuffer
 * @return unsigned char value: the number of elements
 */
unsigned char rb_elements(struct rb_frame *pBuffer) {
	unsigned char value = 0;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		if (pBuffer->buffer[i].isWrite) {
			value++;
		}
	}
	return value;
}

/*
 * void rb_print()
 * @brief prints the value and timestamp of the transferred buffer from the
 * position the write index was, before it got incremented
 * @param struct rb_frame *pBuffer: pointer to the Buffer
 * @return none
 */
void rb_print(struct rb_frame *pBuffer) {
	printf("element: %d || timestamp: %s",
			pBuffer->buffer[pBuffer->rb_write - 1].value,
			pBuffer->buffer[pBuffer->rb_write - 1].timestamp);

}

#endif /* BUFFER_H_ */
