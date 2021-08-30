#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "display.h"

#define CHAR_MAX      1024
#define RAID_LVL      0
#define MASS_STORAGE  "sda1"

#define LCD_TTY_OUTPUT "/dev/tty1"

#ifdef DBG_TEST
#define TTY_OUTPUT  stdout
#else
#define TTY_OUTPUT  LCD_TTY_OUTPUT
#endif

//a text over 40 character will be cut to the next line
#define LCD_WIDTH     40

void test_display(void);

int main()
{
    FILE *pStdout;

    //the lcd output device
#ifdef DBG_TEST
    pStdout = stdout;
#else
    pStdout = fopen(TTY_OUTPUT,"w");
#endif


    print_time(pStdout);
    print_raid(pStdout);
    print_storage_state(pStdout);
    print_uptime(pStdout);


#ifndef DBG_TEST
    fclose(pStdout);
#endif
    return 0;
}

void test_display(void)
{
  FILE *pFile;
  //the lcd output device
  pFile = fopen(LCD_TTY_OUTPUT,"w");

  //test to be removed
  fprintf(pFile,"Hello world!\n");
  fclose(pFile);
  return;
}
