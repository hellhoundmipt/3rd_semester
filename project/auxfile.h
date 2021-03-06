#include <stdio.h>
#include <stdlib.h>

#define maxIncidentLocs 5
#define locsCount 5

struct Location
{
  char *name;
  int incidentLocs[maxIncidentLocs];
  int incidentLocsCount;
};

struct MainHero
{
  char name[20];
  int flag[8];
  int rifleShots;
  int grenades;
  int health;
};

/*
Some details:
  hero:
  hero.flag[0] - the hero knows about the house in the forest, Borzukhan alive or dead
  hero.flag[1] - the hero knows about the seceret enterace at the shore
  hero.flag[2] - hero has already been to the lawn
  hero.flag[3] - hero has a stunner
  hero.flag[4] - hero has already captured Borzukhan
  hero.flag[5] - hero demolished door near the beach
  hero.flag[6] - hero killed everybody at the enterance
  hero.flag[7] - hero killed everybody in the canteen
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
  printf("в лазерной винтовке, %d ", hero.grenades);
  switch (hero.grenades)
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
  if(hero.flag[0] == 2)
    printf("\t\tБорзухан взят живым.\n");
  if(hero.flag[0] == 3)
    printf("\t\tБорзухан мёртв.\n");
  if(hero.flag[1] == 1)
    printf("\t\tВы знаете про секретный вход в пещере у моря.\n");
  if(hero.flag[3] == 1)
    printf("\t\tУ вас есть станнер.\n");
}

/*Other---------------------------------------------------------------------------------------------------------------------------------------------------------*/

int TakeDecision()
{
  int decision = -1;
  char aux[1];
  scanf("%1s", aux);
  while (getchar() != '\n');
  sscanf(aux, "%d", &decision);
  return decision;
}

int ChangeLoc(struct Location *locations, int currLocation)
{
  int destination;
  while(1)
  {
    destination = TakeDecision();
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

int FireRifle(int avgShots, int neighbourhood)
{
  int res;
  long int seedval = time(NULL);
  struct drand48_data *buffer = calloc(1, sizeof(struct drand48_data));
  srand48_r(seedval, buffer);
  drand48_r(buffer, &res);
  res = res / (RAND_MAX / neighbourhood) + avgShots;
  return res;
}

void GameOver()
{
  sleep(1);
  int res = FireRifle(2, 5);      //здесь тож ранйдомайзер тащит
  switch (res)
  {
    case 0:
    printf("Печаль-беда\n");
    break;

    case 1:
      printf("Вот и сказки худой конец...\n");
    break;

    case 2:
      printf("Такие дела...\n");
    break;

    default:
      printf("Game over!\n");
    break;
  }
  exit(0);
}

/*Initialize----------------------------------------------------------------------------------------------------------------------------------------------------*/
struct MainHero InitHero(struct MainHero hero)
{
    int i = 0;
    for(i; i <= 7; i++)
    {
      hero.flag[i] = 0;
    }
    hero.rifleShots = 10;
    hero.grenades = 2;
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

  locations[4].name = (char *)calloc(13, sizeof(char));
  locations[4].name = "Домик в лесу";
  locations[4].incidentLocsCount = 1;
  locations[4].incidentLocs[0] = 0;
  return locations;
}
