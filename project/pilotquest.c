//#include <stdbool.h>
#include <stdio.h>
#include "auxfile.h"
#include "eventsfile.h"

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
        printf("Вы сидите в лёгком флаере и думаете, куда полететь.\n");
        ShowAmmo(hero);
        ShowKnowledge(hero);
        ShowDestinations(locations, currLocation);
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 1:
        if(hero.flag[2] == 1)
        {
          printf("Вы приземлилсь на поляну у недавно погашенного костра. Оглядевшись, вы поняли, что сделать здесь в общем-то нечего.\n");
          printf("Нужно решить, куда лететь дальше.\n");
          ShowDestinations(locations, currLocation);
          inSwitchCurrLoc = ChangeLoc(locations, currLocation);
        }
        else
        {
          hero.flag[2] = 1;
          hero = IncidentOnTheLawn(hero);
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
  printf("Enjoy!\n");
  sleep(1);
  Briefing(hero.name);
  GameLoop(hero);
  printf("Thanks for playing!\n");
}
