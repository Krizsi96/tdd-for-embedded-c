#ifndef M28W160ECT_H_
#define M28W160ECT_H_

typedef enum
{
    CommandRegister = 0x0,
    StatusRegister = 0x0
} Flash_Registers;

typedef enum
{
    ProgramCommand = 0x40,
    Reset = 0xFF
} Flash_Command;

typedef enum
{
    ReadyBit = 1 << 7,
    EraseSuspendBit = 1 << 6,
    EraseErrorBit = 1 << 5,
    ProgramErrorBit = 1 << 4,
    VppErrorBit = 1 << 3,
    ProgramSuspendBit = 1 << 2,
    BlockProtectionErrorBit = 1 << 1,
    ReservedBit = 1
} StatusRegisterBits;

#endif // M28W160ECT_H_