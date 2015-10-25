#include <stdbool.h>
#include <auxfile.h>
#include <stdio.h>

const int maxIncidentLocs = 5;

struct Location
{
  char *name;
  int incidentLocs[maxIncidentLocs];
  int incidentLocsCount;
};

void GameLoop()
{
  while(1)
  {
    switch(currLocation)
    {
      case 0:
        printf("Where would you like to go?");
        int i = 0;
        for (i; i < locations[0].incidentLocsCount; i++)
        {
          printf("%d:\t%s\n", locations[0].incidentLocs[i], locations[i].name;);
        }
      break;
    }
  }
}

struct MainHero
{
  bool flag[2];
};

int main()
{
  GameLoop();
}
