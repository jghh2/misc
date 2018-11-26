/*
 * RingBuffer.cpp
 *
 *  Created on: 2018Äê11ÔÂ23ÈÕ
 *      Author: gjiang
 */

#include "RingBuffer.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define min(a,b) ((a) > (b) ? (b): (a))

RingBuffer::RingBuffer(int size) :
		_size(size) {

	_buf = new char[_size];
	_rIdx = _wIdx = 0;

}

RingBuffer::~RingBuffer() {
	delete[] _buf;
}

int RingBuffer::_read(void *buf, int len) {
	int Section = 0;

	if (_wIdx > _rIdx) {
		Section = min(_wIdx - _rIdx, len);
	} else if (_wIdx < _rIdx) {
		Section = min(_size - _rIdx, len);
	} else {
		assert(_rIdx != _size);
	}

	if (Section) {
		memcpy(buf, _buf + _rIdx, Section);
		_rIdx += Section;
		if (_rIdx >= _size)
			_rIdx = 0;
	}

	return Section;
}
int RingBuffer::_write(void * buf, int len) {

	int Section = 0;
	if (_wIdx > _rIdx) {
		Section = min(_size - _wIdx, len);
	} else if (_wIdx < _rIdx) {
		Section = min(_rIdx - _wIdx, len);
	} else {
		assert (_wIdx != _size);

		if (_wIdx < _size)
			Section = min(_size - _wIdx, len);
	}
	memcpy(_buf + _wIdx, buf, Section);
	_wIdx += Section;
	if (_wIdx >= _size)
		_wIdx = 0;
	return Section;
}
int RingBuffer::read(void *buf, int len) {

	int i;
	int ret;
	for (i = 0; i < len;) {
		ret = _read((char*) buf + i, len - i);
		if (ret == 0)
			break;
		i += ret;

	}
	return i;
}

int RingBuffer::write(void * buf, int len) {
	int i;
	int ret;
	for (i = 0; i < len;) {
		ret = _write((char*) buf + i, len - i);
		if (ret == 0)
			break;
		i += ret;

	}
	return i;
}
