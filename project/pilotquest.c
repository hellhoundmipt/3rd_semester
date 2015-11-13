//#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "auxfile.h"
#include "eventsfile.h"
#include "eventsfile2.h"
#include "eventsfile3.h"

#define maxIncidentLocs 5
#define locsCount 5


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
          printf("Вы приземлилсь на поляну у недавно потузшего костра. Оглядевшись, вы поняли, что делать здесь в общем-то нечего.\n");
          printf("Нужно решить, куда лететь дальше.\n");
          ShowDestinations(locations, currLocation);
          inSwitchCurrLoc = ChangeLoc(locations, currLocation);
        }
        else
        {
          hero.flag[2] = 1;
          hero = IncidentOnTheLawn(hero);
          if(hero.flag[0] == 1)
          {
            locations[0].incidentLocsCount++;
            locations[0].incidentLocs[3] = 4;
          }
          inSwitchCurrLoc = 0;
        }
      break;

      case 2:
        if(hero.flag[6] == 0)
        {
          printf("Прилетели ко входу, чё делать будем?\n");
          int desidion;
          int inFlag = 0;
          while(inFlag == 0)
          {
            printf(" Будете ли сейчас заходить? (0 do/1 do not)\n");
            scanf("%d", &desidion);
            if(desidion == 0)
            {
              hero = InTheBase(0, hero);
              inFlag = 1;
            }
            else
            {
              if(desidion == 1)
              {
                printf("Вы решили пока не входить в базу.\n");
                inFlag = 1;
              }
              else
                printf("Так не выйдет...\n");
            }
          };
        }
        else
        {
          hero = EnterFromTheMounts(hero);
        }
        ShowDestinations(locations, currLocation);\
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 3:
        if(hero.flag[1] == 0)
        {
          printf("Вы приземлились около песчаного пляжа, вышли из флаера и осмотрелись. Вдали виднеется грот, но,\n");
          printf("осмотрев его, вы так ничего и не заметили. Вы бы и дальше продолжали любоваться видами, но нужно возвращаться к выполнению задания.\n");
        }
        else
        {
          printf("Вы приземлились около песчаного пляжа, вышли из флаера и осмотрелись. Вдали виднеется грот, в котором,\n");
          printf("как вы знаете, находится вход на базу Борзухана.");
          int desidion;
          int inFlag = 0;
          while(inFlag == 0)
          {
            if(hero.flag[5] == 0)
              printf(" Будете ли искать вход сейчас? (0 do/1 do not)\n");
            else
              printf(" Будете ли заходить на базу сейчас? (0 do/1 do not)\n");
            scanf("%d", &desidion);
            if(desidion == 0)
            {
              if(hero.flag[5] == 0)
              {
                hero.flag[5]++;
                hero = EnterFromTheShore(hero);
              }
              else
                hero = InTheBase(1, hero);
              inFlag = 1;
            }
            else
            {
              if(desidion == 1)
              {
                printf("Вы решили пока не входить в грот.\n");
                inFlag = 1;
              }
              else
                printf("Так не выйдет...\n");
            }
          };
        }
        printf("Куда собираетесь выдвигаться?\n");
        ShowDestinations(locations, currLocation);
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      break;

      case 4:
      if(hero.flag[4] == 1)
      {
        printf("Вы приземлилсь у домика пеленега Борзухана. Оглядевшись, вы поняли, что делать здесь в общем-то нечего.\n");
        printf("Нужно решить, куда лететь дальше.\n");
        ShowDestinations(locations, currLocation);
        inSwitchCurrLoc = ChangeLoc(locations, currLocation);
      }
      else
      {
        hero = CaptureBorzukhan(hero);
        inSwitchCurrLoc = 0;
      }
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
  scanf("%29s", hero.name);
  while (getchar() != '\n');
  printf("Enjoy!\n");
  sleep(1);
  //Briefing(hero.name);
  GameLoop(hero);
  printf("Thanks for playing!\n");
  return 0;
}
