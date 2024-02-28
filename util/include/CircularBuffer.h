#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

typedef struct CircularBufferStruct *CircularBuffer;

CircularBuffer CircularBuffer_Create(int capacity);
void CircularBuffer_Destroy(CircularBuffer);
int CircularBuffer_IsEmpty(CircularBuffer);
int Circularbuffer_IsFull(CircularBuffer);
int CircularBuffer_Put(CircularBuffer, int);
int CircularBuffer_Get(CircularBuffer);
int CircularBuffer_Capacity(CircularBuffer);
void CircularBuffer_Print(CircularBuffer);
int CircularBuffer_VerifyIntegrity(CircularBuffer);

#endif // CIRCULARBUFFER_H_