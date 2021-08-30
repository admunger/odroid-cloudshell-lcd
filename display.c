#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "display.h"

#define CHAR_MAX        1024
#define MASS_STORAGE    "sda1"
#define DBG_STORAGE     "nvme1" 

//a text over 40 character will be cut to the next line
#define LCD_WIDTH     40


// command output buffer
static char cOutput[CHAR_MAX];


//uses FIGLET to print in a bigger font
//to get figlet's default directory location : figlet -I 2
void print_time(FILE *fd)
{
    //buffers for system commands
    FILE *pCmd;
    //get date in hh:mm format with figlet font
    pCmd = popen("figlet -f Basic $(date '+%H:%M')","r");

    //transfer pCmd output content to lcd FILE
    if(pCmd != NULL)
    {
        while(fgets(cOutput, CHAR_MAX, pCmd) != NULL)
            fprintf(fd, "%s", cOutput);
    }
    pclose(pCmd);
}


// the RAID is set by 2 switches on the cloudshell
// as the cloudshell need to be disassembled to be changed,
// it's hard-coded for the moment as its current state
void print_raid(FILE *fd)
{
    //hard-coded raid level
    fprintf(fd,"RAID mode : %d\n",RAID_LVL);
}

// only prints the Mass Storage state for the moment
// TODO print usage of SSD, check if possible even if encrypted
void print_storage_state(FILE *fd)
{
    FILE *pCmd;
    char sCmd[CHAR_MAX];
    // print usage of mass storage

    sprintf(sCmd, "df -h --output=source,size,avail,pcent | grep '\\(Filesystem\\|%s\\|%s\\)'", MASS_STORAGE, DBG_STORAGE);
    pCmd = popen(sCmd,"r");
    // transfer pCmd output content to lcd FILE
    if(pCmd != NULL)
    {
        while(fgets(cOutput, CHAR_MAX, pCmd) != NULL)
            fprintf(fd, "%s", cOutput);
    }
    pclose(pCmd);
}

// print uptime, in days
void print_uptime(FILE *fd)
{
    //buffers for system commands
    FILE *pCmd;
    //get date in hh:mm format with figlet font
    pCmd = popen("uptime -p","r");

    //transfer pCmd output content to lcd FILE
    if(pCmd != NULL)
    {
        while(fgets(cOutput, CHAR_MAX, pCmd) != NULL)
            fprintf(fd, "%s", cOutput);
    }
    pclose(pCmd);
}
