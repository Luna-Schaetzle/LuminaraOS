// kernel/serial.h
#ifndef SERIAL_H
#define SERIAL_H

void serial_init(void);
void serial_write(char c);
void serial_writestring(const char* str);

#endif

