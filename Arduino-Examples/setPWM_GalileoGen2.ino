/*
setPWM_GalileoGen2.ino - Set PWM frequency and duty cycle on GalileoGen2

This example shows how to set the PWM frequency and duty cycle on GalileoGen2.

This example only works on Galileo Gen2.

This example code is in the public domain.

Revision History

----------------------------------------------------------
    Author		   Date		  Description
----------------------------------------------------------
Diego Villalobos	07-17-2015	Example created

*/

#include <interrupt.h>
#include <trace.h>

#define MY_TRACE_PREFIX "ServoX86Lib"
#define ERROR_FACTOR 1.1

static int  (*pointer_write)(  int  handle,  const void  *buffer,  unsigned int  nbyte  ) = write;

void setPWM(int pin, int frequency, int duty_cycle)
 {
     int freqInNanoSec = (1.0/frequency) * 1000000000 * ERROR_FACTOR;
     
     FILE *fp = NULL;
     int ret = 0;
     char export_value[16] = "";
     char fs_path[50] = LINUX_PWM_EXPORT;

     memset(fs_path, 0x00, sizeof(fs_path));
     snprintf(fs_path, sizeof(fs_path), LINUX_PWM_PERIOD_FMT);

     if (NULL == (fp = fopen(fs_path, "ab"))) {
         trace_error("can't open handle to %s", fs_path);
         return ;
     }
     rewind(fp);

     memset(export_value, 0x0, sizeof(export_value));
     snprintf(export_value, sizeof(export_value), "%u", freqInNanoSec);
     fwrite(&export_value, sizeof(char), sizeof(export_value), fp);

     fclose(fp);
     /////////////////////////////////////////////////////////////
     bool enable = 1;
     //set the mux and open the handles
     analogWrite(pin, 0);

     int handle_enable = pin2pwmhandle_enable(pin);

     lseek(handle_enable, 0, SEEK_SET);
     ret = pointer_write(handle_enable, (const void*)&enable, sizeof(enable));
     if (sizeof(enable) != ret) {
         trace_error("can't write to enable\n");
     }
     /////////////////////////////////////////////////////////////     
    int value_duty = (1.0/frequency) * 1000000000 / (100.0/duty_cycle);
    
    char value[16] = "";

    value_duty *= ERROR_FACTOR;

    int handle_duty = pin2pwmhandle_duty(pin);

    memset(value, 0x0, sizeof(value));
    snprintf(value, sizeof(value), "%u", (unsigned)value_duty);
    lseek(handle_duty, 0, SEEK_SET);
    ret = pointer_write(handle_duty, &value, sizeof(value));
    if (sizeof(value) != ret) {
         trace_error("can't write to duty_cycle\n");
    }    
}

void setup() {
  int pin = 9;          // PWM pin
  int frequency = 100;  // Hz
  int duty_cycle = 50;  // %
  
  setPWM(pin, frequency, duty_cycle);
}

void loop() {
  
}
