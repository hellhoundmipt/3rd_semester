//#include <stdbool.h>
#include <stdio.h>
#include "auxfile.h"

#define maxIncidentLocs 5
#define locsCount 8


void GameLoop(struct MainHero hero)
{
  struct Location *locations;
  locations = calloc(locsCount, sizeof(struct Location));
  locations = InitLocations(locations);
  int currLocation = 0;
  int inSwitchCurrLoc = 0;

  int exitFlag = 0;
  printf("Currloc = %s\n", locations[currLocation].name);
  while(exitFlag != 1)
  {
    //printf("%d\t%d\t%d\n", hero.flag[0], hero.flag[1], hero.flag[2]);
    switch(currLocation)
    {
      case 0:
        printf("You are at the base, deciding where to go to and what to do.\n");
        ShowDestinations(locations, currLocation);
        printf("Where would you like to go?\n");
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 1:
        if(hero.flag[2] == 1)
        {
          printf("You've landed on the lawn, covered with blood of your victims. Unfortunately, there is nothing else to do here.\n");
          ShowDestinations(locations, currLocation);
          printf("Where would you like to go?\n");
          inSwitchCurrLoc = ChangeLoc(locations, currLocation);
        }
        else
        {
          printf("Got here\n");
          hero.flag[2] = 1;
          //hero = IncidentOnTheLawn(hero);
          inSwitchCurrLoc = 0;
        }
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
    printf("Newloc = %s\n", locations[currLocation].name);
  }
}

int main()
{
  struct MainHero hero = InitHero(hero);
  printf("Welcome, commader!\n");
  printf("Enter your name:\n");
  gets(hero.name);
  GameLoop(hero);
  printf("Thanks for playing!\n");
}
