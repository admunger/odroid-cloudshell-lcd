#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define CHAR_MAX      1024
#define RAID_LVL      0
#define MASS_STORAGE  "sda1"

//a text over 40 character will be cut to the next line
#define LCD_WIDTH     40

void test_display(void);

int main()
{
  FILE *pStdout;
  //the lcd output device
  pStdout = fopen("/dev/tty1","w");

  //buffers for system commands
  FILE *pCmd;
  char cOutput[CHAR_MAX];

  //uses FIGLET to print in a bigger font
  //to get figlet's default directory location : figlet -I 2

  //get date in hh:mm format with figlet font
  pCmd = popen("figlet -f Basic $(date '+%H:%M')","r");

  //transfer pCmd output content to lcd FILE
  if(pCmd != NULL)
  {
    while(fgets(cOutput, CHAR_MAX, pCmd) != NULL)
      fprintf(pStdout, "%s", cOutput);
  }


  //hard-coded raid level
  fprintf(pStdout,"RAID mode : %d\n",RAID_LVL);


  //this chunk of code is too large to be printed correctly

//   //print usage of mass storage
//   char sCmd[CHAR_MAX];
//   sprintf(sCmd, "df -h | grep '\\(Filesystem\\|%s\\)'", MASS_STORAGE);
//   // system(sCmd);
//   pCmd = popen(sCmd,"r");
//   //transfer pCmd output content to lcd FILE
//   if(pCmd != NULL)
//   {
//     while(fgets(cOutput, CHAR_MAX, pCmd) != NULL)
//       fprintf(pStdout, "%s", cOutput);
//   }


  fclose(pStdout);
  return 0;
}

void test_display(void)
{
  FILE *pFile;
  //the lcd output device
  pFile = fopen("/dev/tty1","w");

  //test to be removed
  fprintf(pFile,"Hello world!\n");
  fclose(pFile);
  return;
}
