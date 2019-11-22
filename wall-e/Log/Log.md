## Log

- 20191121

1) openocd
    (gdb) b 152
    Breakpoint 1 at 0x80006b0: file ../User/main.c, line 152.
    (gdb) r
    Don't know how to run.  Try "help target".

2) Jlink-rtt log 输出成功

    - jlink-v654
    - jlink/Samples/RTT/SEGGER_RTT_V654c/
    - SEGGER_RTT_Init();
    - enjoy
    - reference : https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/

- 20191122

1）rtt printf  默认不支持float类型输出

signed int RTT_printf(unsigned BufferIndex,const char * pFormat, ...){

    char pStr[50] = {'\0'};
    va_list ap;
    signed int result;

    // Forward call to vprintf
    va_start(ap, pFormat);
    result = vsprintf((char * )pStr, pFormat, ap);
    va_end(ap);

    SEGGER_RTT_WriteString(BufferIndex,(char * )pStr);

    return result;
}

int printf(const char * fmt,...) {

  char buffer[128];
  va_list args;
  va_start (args, fmt);
  int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
  SEGGER_RTT_Write(0, buffer, n);
  va_end(args);
  return n;
}
