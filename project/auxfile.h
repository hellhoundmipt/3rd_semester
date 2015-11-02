#include <stdio.h>
#include <stdlib.h>

#define maxIncidentLocs 5
#define locsCount 8

struct Location
{
  char *name;
  int incidentLocs[maxIncidentLocs];
  int incidentLocsCount;
};

struct MainHero
{
  char name[20];
  int flag[3];
  int rifleShots;
  int greandes;
  int health;
};

/*
Some details:
  hero:
  hero.flag[0] - the hero knows about the house in the forest
  hero.flag[1] - the hero knows about the seceret enterace at the shore
  hero.flag[2] - hero has already been to the lawn
*/

/*Messages------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ShowDestinations(struct Location *locations, int currLocation)
{
  printf("You can travel to these places (enter num to proceed):\n");
  int i = 0;
  for(i; i < locations[currLocation].incidentLocsCount; i++)
    printf("%d\t%s\n", i, locations[locations[currLocation].incidentLocs[i]].name);
}

/*Move rules----------------------------------------------------------------------------------------------------------------------------------------------------*/

int ChangeLoc(struct Location *locations, int currLocation)
{
  int destination;
  while(1)
  {
    scanf("%d", &destination);
    int i = 0;
    for(i; i < locations[currLocation].incidentLocsCount; i++)
    {
      if(destination == i)
        {
          printf("Travelling to %s.\n", locations[locations[currLocation].incidentLocs[i]].name);
          return locations[currLocation].incidentLocs[i];
        }
    }
  printf("Cannot travel there.\n");
  ShowDestinations(locations, currLocation);
  }
}

/*Events in locations-------------------------------------------------------------------------------------------------------------------------------------------*/

struct MainHero IncidentOnTheLawn(struct MainHero hero)
{
  hero.flag[0] = 0;
  hero.flag[1] = 0;
  hero.flag[2] = 0;
  hero.rifleShots = 10;
  hero.greandes = 2;
  hero.health = 3;
}

/*Initialize----------------------------------------------------------------------------------------------------------------------------------------------------*/
struct MainHero InitHero(struct MainHero hero)
{

}

struct Location *InitLocations(struct Location *locations)
{
  locations[0].name = (char *)calloc(5, sizeof(char));
  locations[0].name = "Base";
  locations[0].incidentLocsCount = 3;
  locations[0].incidentLocs[0] = 1;
  locations[0].incidentLocs[1] = 2;
  locations[0].incidentLocs[2] = 3;

  locations[1].name = (char *)calloc(6, sizeof(char));
  locations[1].name = "Lawn";
  locations[1].incidentLocsCount = 1;
  locations[1].incidentLocs[0] = 0;

  locations[2].name = (char *)calloc(10, sizeof(char));
  locations[2].name = "Enterance";
  locations[2].incidentLocsCount = 1;
  locations[2].incidentLocs[0] = 0;

  locations[3].name = (char *)calloc(6, sizeof(char));
  locations[3].name = "Shore";
  locations[3].incidentLocsCount = 1;
  locations[3].incidentLocs[0] = 0;

  locations[4].name = (char *)calloc(9, sizeof(char));
  locations[4].name = "Corridor";
  locations[4].incidentLocsCount = 3;
  locations[4].incidentLocs[0] = 5;
  locations[4].incidentLocs[1] = 6;
  locations[4].incidentLocs[2] = 7;

  locations[5].name = (char *)calloc(14, sizeof(char));
  locations[5].name = "Security room";
  locations[5].incidentLocsCount = 1;
  locations[5].incidentLocs[0] = 4;

  locations[6].name = (char *)calloc(10, sizeof(char));
  locations[6].name = "Canteen";
  locations[6].incidentLocsCount = 1;
  locations[6].incidentLocs[0] = 4;

  locations[7].name = (char *)calloc(12, sizeof(char));
  locations[7].name = "Engine room";
  locations[7].incidentLocsCount = 0;

  locations[8].name = (char *)calloc(20, sizeof(char));
  locations[8].name = "House in the forest";
  locations[8].incidentLocsCount = 1;
  locations[8].incidentLocs[0] = 0;
  return locations;
}
