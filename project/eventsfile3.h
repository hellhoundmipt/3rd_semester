#include <stdio.h>
#include <stdlib.h>

#define locsCountBase 5
#define maxIncidentLocs 5
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
struct MainHero InTheBase(int startLoc, struct MainHero hero)
{
    struct Location *locationsInBase;
    locationsInBase = calloc(locsCountBase, sizeof(struct Location));
    locationsInBase = InitLocationsInBase(locationsInBase);
    int currLocation = startLoc;
    int inSwitchCurrLoc = startLoc;
    printf("I'm here!\n");
    ShowDestinations(locationsInBase, currLocation);
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
    return hero;
}

struct MainHero EnterFromTheShore(struct MainHero hero)
{
  printf("Вы вошли в грот и начали его внимательно осматривать. ...\n");
  printf("Как будете открывать дверь?\n");
  printf("0: Разрезать дверь с помощью винтовки\n");
  printf("1: Взорвать дверь гранатой\n");
  printf("2: Вернуться к пляжу\n");
  ShowAmmo(hero);
  int inFlag = 0;
  while(inFlag != 1)
  {
    int desidion;
    scanf("%d", &desidion);
    switch (desidion)
    {
      case 0:
        if(hero.rifleShots < 3)
        {
          printf("Вы вспомнили количество зарядов в своей винтовке и поняли, что вам скорее всего их не хватит на уничтожение двери.\n");
          printf("Нужно придумать что-то ещё.\n");
        }
        else
        {
          printf("Лазерной винтовкой вы проделали подохдящую для вас дыру, и вошли внутрь.\n");
          hero.rifleShots = hero.rifleShots - 3;
          hero = InTheBase(1, hero);
          inFlag++;
        };
      break;

      case 1:
        if(hero.grenades < 1)
        {
          printf("Вы порылись в поясе и поняли, что гранат у вас больше не осталось. Нужно придумать что-то ещё.\n");
        }
        else
        {
          hero.grenades--;
          printf("От взрыва дверь с грохотом упала на пол, и теперь проход перед вами стал открыт.\n");
          hero = InTheBase(1, hero);
          inFlag++;
        };
      break;

      case 2:
        printf("Вы решили пока вернуться назад к флаеру\n");
        inFlag++;
      break;

      default:
        printf("Ещё раз...\n");
      break;
    }
    return hero;
  }
}


struct MainHero  EnterFromTheMounts(struct MainHero hero)
{
  printf("Got here!\n");
  hero = InTheBase(0, hero);
}
