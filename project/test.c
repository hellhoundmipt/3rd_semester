#include <stdlib.h>
#include <stdio.h>
#include <linux/input.h>
#include <memory.h>
#include <fcntl.h>

#include <sys/ioctl.h>


#define width 20
#define height 50
struct Player
{
    int x;
};

const int leftKey = 105;
const int rightKey = 106;

char keys[1024];
char testKey(int key)
{
    return keys[key / 8] & (1 << (key % 8));
}

int main ( int argc, char *argv[], char *env[] )
{
    int deviceFile = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY); //opening device file. ATTENTION: you have to have access to it. Easiest way is to "sudo ./a.out".
    if(deviceFile < 0)
    {
        printf("Device file not opened. Most likely you don't have access to it, try to run your program with sudo");
    }
    memset(keys, 0, sizeof(keys)); //just in case, not really necessary

    struct Player player;
    player.x = width / 2;

    while(1)
    {
        int x;
        int y;
        for(y = 0; y < height; y++)
        {
            printf("\n");
        }
        ioctl (deviceFile, EVIOCGKEY(sizeof keys), &keys); //update keyboard state


        if(testKey(leftKey) && player.x > 0) player.x--;
        if(testKey(rightKey) && player.x < width - 1) player.x++;

        for(x = 0; x < width; x++)
        {
            if(x == player.x)
            {
                printf("@");
            }
            else
            if(x > 0 || x < width - 1)
            {
                printf(".");
            }else
            {
                printf("#");
            }
        }
        printf("\n\n"); //to avoid screen tearing

        int w;
        for(w = 0; w < 10000000; w++);
    }
    return 0;
}
