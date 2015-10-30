#include <stdbool.h>
#include <stdio.h>
#include "auxfile.h"

#define maxIncidentLocs 5
#define locsCount 8


struct MainHero
{
  bool flag[2];
};

void GameLoop()
{
  struct Location locations[locsCount];
  InitLocations(locations);
  int currLocation = 0;
  int inSwitchCurrLoc = 0;
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
        printf("Where would you like to go?\n");
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 1:
        printf("You've landed on the lawn. Unfortunately, no signs of general.\n");
        ShowDestinations(locations, currLocation);
        printf("Where would you like to go?\n");
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 2:
        printf("Some soldiers at the enterance. Heavy weapons and armor, no reason to have some chat with them.\n");
        ShowDestinations(locations, currLocation);
        printf("Where would you like to go?\n");
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 3:
        printf("Calm sandy beach and calm sunny weather. What can be better now?.\n");
        ShowDestinations(locations, currLocation);
        printf("Where would you like to go?\n");
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 4:
        printf("I'm here 4\n");
        exit(0);
      break;

      case 5:
        printf("I'm here 5\n");
        exit(0);
      break;

      case 6:
        printf("I'm here 6\n");
        exit(0);
      break;

      case 7:
        printf("I'm here 7\n");
        exit(0);
      break;

      case 8:
        printf("I'm here 8\n");
        exit(0);
      break;
    }
    currLocation = inSwitchCurrLoc;
  }
}

int main()
{
  printf("Welcome, commader!\n");
  GameLoop();
  printf("Thanks for playing!\n");
}
