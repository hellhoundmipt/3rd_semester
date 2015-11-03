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
  hero.flag[3] - hero has a stunner
*/

/*Messages------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ShowDestinations(struct Location *locations, int currLocation)
{
  int i = 0;
  for(i; i < locations[currLocation].incidentLocsCount; i++)
    printf("%d\t%s\n", i, locations[locations[currLocation].incidentLocs[i]].name);
}

void ShowAmmo(struct MainHero hero)
{
  printf("\n\t\tУ вас есть %d ", hero.rifleShots);
  if(hero.rifleShots == 1)
    printf("заряд ");
  else
    {
      if((hero.rifleShots >= 2) && (hero.rifleShots <= 4))
        printf("заряда ");
      else
        printf("зарядов ");
    }
  printf("в лазерной винтовке, %d ", hero.greandes);
  switch (hero.greandes)
  {
    case 2:
      printf("гранаты, ");
    break;

    case 1:
      printf("граната, ");
    break;

    case 0:
      printf("гранат, ");
    break;
  }
  switch (hero.health)
  {
    case 3:
      printf("вы полностью здоровы\n\n");
    break;

    case 2:
      printf("вы легко ранены\n\n");
    break;

    case 1:
      printf("вы тяжело ранены\n\n");
    break;
  }
}

void ShowKnowledge(struct MainHero hero)
{
  if(hero.flag[0] == 1)
    printf("\t\tВы знаете про домик Борзухана в лесу.\n");
  if(hero.flag[1] == 1)
    printf("\t\tВы знаете про секретный пароль в пещере у моря.\n");
  if(hero.flag[3] == 1)
    printf("\t\tУ вас есть станнер.\n");

}

/*Other---------------------------------------------------------------------------------------------------------------------------------------------------------*/

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
  printf("Туда нельзя.\n");
  ShowDestinations(locations, currLocation);
  }
}

int FireRifle(int avgDamage, int neighbourhood)
{
  int res;
  long int seedval = time(NULL);
  struct drand48_data *buffer = calloc(1, sizeof(struct drand48_data));
  srand48_r(seedval, buffer);
  drand48_r(buffer, &res);
  res = res / (RAND_MAX / neighbourhood) + avgDamage;
  return res;
}

/*Initialize----------------------------------------------------------------------------------------------------------------------------------------------------*/
struct MainHero InitHero(struct MainHero hero)
{
    hero.flag[0] = 0;
    hero.flag[1] = 0;
    hero.flag[2] = 0;
    hero.rifleShots = 10;
    hero.greandes = 2;
    hero.health = 3;
    return hero;
}

struct Location *InitLocations(struct Location *locations)
{
  locations[0].name = (char *)calloc(7, sizeof(char));
  locations[0].name = "Лагерь";
  locations[0].incidentLocsCount = 3;
  locations[0].incidentLocs[0] = 1;
  locations[0].incidentLocs[1] = 2;
  locations[0].incidentLocs[2] = 3;

  locations[1].name = (char *)calloc(7, sizeof(char));
  locations[1].name = "Поляна";
  locations[1].incidentLocsCount = 1;
  locations[1].incidentLocs[0] = 0;

  locations[2].name = (char *)calloc(5, sizeof(char));
  locations[2].name = "Горы";
  locations[2].incidentLocsCount = 1;
  locations[2].incidentLocs[0] = 0;

  locations[3].name = (char *)calloc(5, sizeof(char));
  locations[3].name = "Пляж";
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

  locations[8].name = (char *)calloc(13, sizeof(char));
  locations[8].name = "Домик в лесу";
  locations[8].incidentLocsCount = 1;
  locations[8].incidentLocs[0] = 0;
  return locations;
}
