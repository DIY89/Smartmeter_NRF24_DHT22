#include <Arduino.h>
#include <printf.h>

int serial_putc(char c, FILE*){
	Serial.write(c);
	return c;
}

void printf_begin(void){
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)
    fdevopen(&serial_putc, 0);

#elif defined(__ARDUINO_X86__)
    // For redirect stdout to /dev/ttyGS0 (Serial Monitor port)
    stdout = freopen("/dev/ttyGS0", "w", stdout);
    delay(500);
    printf("Redirecting to Serial...");
#endif // defined(__ARDUINO_X86__)
}