#ifndef FORMATOUTPUTSPYTEST_H_
#define FORMATOUTPUTSPYTEST_H_

void FormatOutputSpy_Create(int size);
void FormatOutputSpy_Destroy(void);
int FormatOutputSpy(const char *format, ...);
const char *FormatOutputSpy_GetOutput(void);

#endif // FORMATOUTPUTSPYTEST_H_