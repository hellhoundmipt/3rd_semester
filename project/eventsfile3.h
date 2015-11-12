#include <stdio.h>
#include <stdlib.h>
#define locsCountBase 5
/*At the mountains, shore and inside the base*/
/*First init locations inside the base------------------------------------------------------------------------------------------------------------------------*/
struct Location* InitLocationsInBase(struct Location *locations)
{
  locations[0].name = (char *)calloc(5, sizeof(char));
  locations[0].name = "Вход";
  locations[0].incidentLocsCount = 1;
  locations[0].incidentLocs[0] = 1;

  locations[1].name = (char *)calloc(9, sizeof(char));
  locations[1].name = "Корридор";
  locations[1].incidentLocsCount = 4;
  locations[1].incidentLocs[0] = 0;
  locations[1].incidentLocs[1] = 2;
  locations[1].incidentLocs[2] = 3;
  locations[1].incidentLocs[3] = 4;

  locations[2].name = (char *)calloc(5, sizeof(char));
  locations[2].name = "Столовая";
  locations[2].incidentLocsCount = 1;
  locations[2].incidentLocs[0] = 1;

  locations[3].name = (char *)calloc(10, sizeof(char));
  locations[3].name = "Комната 1";
  locations[3].incidentLocsCount = 1;
  locations[3].incidentLocs[0] = 1;

  locations[4].name = (char *)calloc(10, sizeof(char));
  locations[4].name = "Комната 2";
  locations[4].incidentLocsCount = 1;
  locations[4].incidentLocs[0] = 1;
  return locations;
}

/*Now for the action part!-----------------------------------------------------------------------------------------------------------------------------------------*/
void InTheBase(int startLoc, struct MainHero hero)
{
    struct Location *locations;
    locations = calloc(locsCountBase, sizeof(struct Location));
    locations = InitLocationsInBase(locations);
    int currLocation = startLoc;
    int inSwitchCurrLoc = startLoc;
    printf("I'm here!\n");
    /*while(1)
    {
      switch (currLocation)
      {
        case 0:
        break;

        case 1:
        break;

        case 2:
        break;

        case 3:
        break;

        case 4:
        break;
      }
    }*/
}

int EnterFromTheShore(struct MainHero hero)
{
  InTheBase(1, hero);
}

int EnterFromTheMounts(struct MainHero hero)
{
  InTheBase(0, hero);
}
