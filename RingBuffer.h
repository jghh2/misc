/*
 * RingBuffer.h
 *
 *  Created on: 2018Äê11ÔÂ23ÈÕ
 *      Author: gjiang
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

class RingBuffer {
public:
	RingBuffer(int size);
	int read(void *buf, int len);
	int write(void * buf, int len);
	virtual ~RingBuffer();
private:
	int _read(void *buf, int len);
	int _write(void * buf, int len);
	int _size;
	char* _buf;
	int _rIdx;
	int _wIdx;
};

#endif /* RINGBUFFER_H_ */
