/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  arrayDinamic.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef ARRAYDINAMIC_HPP
# define ARRAYDINAMIC_HPP

# include <defines.hpp>

/*
Memory layout
uint64 capacity = number elements that can be held
uint64 length = number of elements currently contained
uint64 stride = size of each element in bytes
void* elements
*/

enum {
	DARRAY_CAPACITY,
	DARRAY_LENGTH,
	DARRAY_STRIDE,
	DARRAY_FIELD_LENGTH
};

DE_API void		*_ArrayDinCreate(uint64 length, uint64 stride);
DE_API void		_ArrayDinDestroy(void *array);

DE_API uint64	_ArrayDinFieldGet(void *array, uint64 field);
DE_API void		_ArrayDinFieldSet(void *array, uint64 field, uint64 value);

DE_API void		*_darray_resize(void *array);

DE_API void		*_ArrayDinPush(void *array, const void *valuePtr);
DE_API void		_ArrayDinPop(void *array, void *dest);

DE_API void		*_ArrayDinPopAt(void *array, uint64 index, void *dest);
DE_API void		*_ArrayDinInsertAt(void *array, uint64 index, void *valuePtr);

#define DE_ARRAY_DIN_DEFAULT_CAPACITY 1
#define DE_ARRAY_DIN_RESIZE_FACTOR 2

#define ArrayDinCreate(type) \
	_ArrayDinCreate(DE_ARRAY_DIN_DEFAULT_CAPACITY, sizeof(type))

#define ArrayDinReserve(type, capacity) \
	_ArrayDinCreate(capacity, sizeof(type))

#define ArrayDinDestroy(array) _ArrayDinDestroy(array);

#define ArrayDinPush(array, value)																\
	{																							\
		decltype(value) temp = value;															\
		array = static_cast<const char **>(_ArrayDinPush(static_cast<void *>(array), &temp));	\
	}

#define ArrayDinPushEvent(array, value)                                                           \
	{                                                                                             \
		decltype(value) temp = value;                                                             \
		array = static_cast<registeredEvent *>(_ArrayDinPush(static_cast<void *>(array), &temp)); \
	}
// NOTE: could use __auto_type for temp above, but intellisense
// for VSCode flags it as an unknown type. typeof() seems to
// work just fine, though. Both are GNU extensions.

#define ArrayDinPop(array, valuePtr) \
	_ArrayDinPop(array, valuePtr)

#define ArrayDinInsertAt(array, index, value)           \
	{                                                   \
		typeof(value) temp = value;                     \
		array = _ArrayDinInsertAt(array, index, &temp); \
	}

#define ArrayDinPopAt(array, index, valuePtr) \
	_ArrayDinPopAt(array, index, valuePtr)

#define ArrayDinClear(array) \
	_ArrayDinFieldSet(array, DARRAY_LENGTH, 0)

#define ArrayDinCapacity(array) \
	_ArrayDinFieldGet(array, DARRAY_CAPACITY)

#define ArrayDinLength(array) \
	_ArrayDinFieldGet(array, DARRAY_LENGTH)

#define ArrayDinStride(array) \
	_ArrayDinFieldGet(array, DARRAY_STRIDE)

#define ArrayDinLengthSet(array, value) \
	_ArrayDinFieldSet(array, DARRAY_LENGTH, value)

#endif
	