#include <stdbool.h>
#include "auxfile.h"
#include <stdio.h>


struct Location
{
  char *name;
  int incidentLocs[maxIncidentLocs];
  int incidentLocsCount;
};

struct MainHero
{
  bool flag[2];
};

void GameLoop()
{
  struct Location locations[locsCount];
  locations = InitLocations(locations);
  int currLocation = 0;
  struct MainHero hero;
  hero.flag[0] = false;
  hero.flag[1] = false;

  bool exitFlag = false;
  while(exitFlag != true)
  {
    switch(currLocation)
    {
      case 0:
        printf("You are at the base, deciding where to go to and what to do.\n");
        ShowDestinations(locations, currLocation);
        exit(0);
      break;

      case 1:
      break;

      case 2:
      break;

      case 3:
      break;

      case 4:
      break;

      case 5:
      break;

      case 6:
      break;

      case 7:
      break;

      case 8:
      break;
    }
  }
}

int main()
{
  printf("Welcome, commader!\n");
  GameLoop();
  printf("Thanks for playing!\n");
}
