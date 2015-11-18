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

  locations[3].name = (char *)calloc(35, sizeof(char));
  locations[3].name = "Комната со знаком радиоактивности";
  locations[3].incidentLocsCount = 1;
  locations[3].incidentLocs[0] = 1;

  locations[4].name = (char *)calloc(14, sizeof(char));
  locations[4].name = "Комната охраны";
  locations[4].incidentLocsCount = 1;
  locations[4].incidentLocs[0] = 1;
  return locations;
}

/*Now for the action part!-----------------------------------------------------------------------------------------------------------------------------------------*/

struct MainHero RandomSecurityInBase(struct MainHero hero, int needRandom)
{
  if (needRandom == 1)
  {
    if(FireRifle(10,2) % 5 != 0)
      return hero;
    else
      printf("Внезапно вы увидели вооружённого пеленега, прохаживающегося по корридору.\n");
  }
  ShowAmmo(hero);
  printf("0: Попытаться одолеть его в рукопашном бою\n");
  printf("1: Выстрелить из винтовки\n");
  if(hero.flag[3] == 1)
    printf("2: Оглушить станнером\n");
  int decision = TakeDecision();
  switch (decision)
  {
    case 0:
      if(hero.health < 1)
      {
        printf("Вы попытались сразиться с пеленегом в рукопашную. К сожалению, на вы были уже порядком побиты, поэтому вам не хватило сил\n");
        printf("справиться с неприятелем. В конце концов пеленег повалил вас на пол и избил вас до потери сознания. А дальше вы и не очнулись...\n");
        GameOver();
      }
      else
      {
        hero.health--;
        printf("Вы набросились на недруга и начали его избивать. Через нескольких минут упорной возни с трудом вы смогли одалеть пеленега.\n");
      }
    break;

    case 1:
      if (hero.rifleShots < 1)
      {
        printf("Вы вскинули винтовку но в ней как назло не оказалось зарядов. Пеленег среагировал мгновенно, и луч лазерного автомата немедленно\n");
        printf("пронзил ваше тело.\n");
        GameOver();
      }
      else
      {
        printf("Вышей сноровки хватило, чтобы вскинуть оружие первым и выстрелить. Тело пеленега с грохотом упало на пол.\n");
        hero.rifleShots--;
      }
    break;

    case 2:
      if(hero.flag[3] == 1)
      {
        hero.flag[3]--;
        printf("Вы выхватили из пояса станнер и выстрелили в направлении нежданного гостя. Тело пеленега с грохотом упало на пол.\n");
      }
      else
      {
        printf("Реакция у пеленега оказалась куда лучше вашей. Два точных выстрела поразили ваше тело и задание для вас на этом закончилось...\n");
        GameOver();
      }
    break;

    default:
      printf("Реакция у пеленега оказалась куда лучше вашей. Два точных выстрела поразили ваше тело и задание для вас на этом закончилось...\n");
      GameOver();
    break;
  }
  return hero;
}


struct MainHero FinalScene(struct MainHero hero)
{
  printf("Вы вошли в комнату с примечательным занком, вашему взору предстал огромный плазмагенератор.\n");
  printf("-Лучшего места и не найти для диверсии, - подумали вы. Будете взрывать прямо сейчас? (0 да/1 нет)\n");
  int decision;
  int inFlag = 0;
  while(inFlag == 0)
  {
    decision = TakeDecision();
    switch (decision)
    {
      case 0:
        inFlag++;
      break;

      case 1:
        printf("Вы решили пока повременить с диверсией. Возможно, зря, так как каждая минута на счету.\n");
        return hero;
      break;

      default:
        printf("Так не выйдет...\n");
      break;
    }
  }
  printf("Вы принялись закладывать бомбу. Руки трясутся от волнения, но ошибаться ни в коем случае нельзя...\n");
  sleep(2);
  if(FireRifle(0, 10) == 0)
  {
    printf("Даже самые лучшие люди иногда ошибаются. Сегодня эта участь постигла вас. Бомба взорвалась прямо у вас в руках, стерев с лица земли\n");
    printf("пиратскую базу и вас вместе с ней, и вас. Задание, конечно, выполнено, но не той ценой, которой бы вам, пожалуй, хотелось...\n");
    printf("\nКстати, вероятность взрыва была всего 5 процентов, так что вы прямо-таки 'везунчик'.\n");
    GameOver();
  }
  printf("Наконец вы закончили с закладкой бомбы. Вытерев со лба пот, вы поставили таймер на 5 минут, и решили уже бежать прочь из этого места, как\n");
  printf("заметили входящего в комнату пеленега.\n");

  hero = RandomSecurityInBase(hero, 0);
  sleep(1);
  printf("Выбежав из комнаты, вы заметили, что дверь комнату охраны откыта, а в её конце виднеется вход в ангар. Недолго думая, вы ломанулись туда.\n");
  printf("Вы вскочили в первый попавшийся флаер и со свистом вылетев с базы понеслись по направлению к лагерю. Там вас уже ждал Карл и с радостью сообщил,\n");
  printf("что ваше задание выполнено успешно!");
  if(hero.flag[0] == 2)
    printf("Более того, вы сумели арестовать самого лякушу Борзухана, за что вас дополнительно вознаградили.\n");
  else
    printf("\n");
  sleep(1);
  printf("Игра пройдена, спасибо за уделённое время, %s!", hero.name);
  exit(1);
}


struct MainHero InTheBase(int startLoc, struct MainHero hero)
{
    struct Location *locationsInBase;
    locationsInBase = calloc(locsCountBase, sizeof(struct Location));
    locationsInBase = InitLocationsInBase(locationsInBase);
    int currLocation = startLoc;
    int inSwitchCurrLoc = startLoc;
    int shots, i;
    while(1)
    {
      switch (currLocation)
      {
        case 0:
          printf("Вы стоите у закрытого выхода из базы, остаётся пойти только в корридор.\n");
          ShowAmmo(hero);
          ShowKnowledge(hero);
          ShowDestinations(locationsInBase, currLocation);
          inSwitchCurrLoc = ChangeLoc(locationsInBase, currLocation);
        break;

        case 1:
          RandomSecurityInBase(hero, 1);
          printf("Вы стоите в корридоре базы Борзухана. Справа находится дверь в столовую, из которой доносится куча голосов.\n");
          printf("Судя по всему, у местных сейчас обед, поэтому действовать следует быстро. В дальнем конце виднеетс 2 двери, одна со знаком радиоктивной опасности,\n");
          printf("другая, судя по надписи, ведёт, в комнату охраны. Туда точно соваться не стоит... Другой конец корридора ведёт к выходу.\n");
          ShowAmmo(hero);
          ShowKnowledge(hero);
          ShowDestinations(locationsInBase, currLocation);
          inSwitchCurrLoc = ChangeLoc(locationsInBase, currLocation);
        break;

        case 2:
          if (hero.flag[7] == 0)
          {
            printf("Вы зашли в столовую. Обедавшие вояки застыли, уставившись на вас. Есть лишь мновение, чтобы принять решение...\n");
            ShowAmmo(hero);
            printf("0: Попытаться убежать.\n");
            printf("1: Расстрелять всех из винтовки.\n");
            printf("2: Поприветствовать присутствующих\n");
            printf("Цифра 7 валялалсь где-то...\n");
            int decision = TakeDecision();
            switch (decision)
            {
              case 0:
                printf("Вы выбежали из столовой и стремительно понеслись по корридору к выходу. Позади послышались выстрели, после чего вы почувствовали\n");
                printf("резкую боль в груди. Взвыв, вы свалились на пол. Однако ваши мучения кончились довольно быстро выстрелом в вашу голову...\n");
                GameOver();
              break;

              case 1:
                printf("Вы схватили винтовку и начали расстреливать сидящих за столом... \n");
                shots = FireRifle(9, 2);
                if ((shots > hero.rifleShots) || (hero.health < 3))
                {
                  if(shots > hero.rifleShots)
                    printf("Однако внезапно у вас кончились патроны, и спрятвшийся за колонной феянин точным выстрелом отправил вас в лучший мир...\n");
                  else
                    printf("В процессе перестрелки вас задело сначала в плечо, потом живот, и, в конце концов, в голову\n");
                  GameOver();
                }
                else
                {
                  hero.flag[7]++;
                  hero.health -= 2;
                  printf("Вас пару раз сильно ранили, отчего вам стало тяжело держать винтовку в руках. Тем не менее все бандиты были побеждены и\n");
                  printf("вы неспеша вышли из столовой\n");
                  inSwitchCurrLoc = 1;
                }
              break;

              case 2:
                printf("Вы улыбнулись и весело пожелали присутствующим приятного аппетита. Через несколько секунд один из доселе трапезничавших крикнул:\n");
                printf("-Да это не наш!\n");
                printf("Вам осталось так и стоять с идиотской улыбкой, так как стоящий рядом с вами малок уже крепко схватил вас за плечо.\n");
                printf("-Доставим шефу, он с ним разберётся, - сказал малок и повёл вас в комнату охраны. Ваша миссия была феерично провалена...\n");
                GameOver();
              break;

              case 7:
                i = 0;
                for(i; i < 8; i++)
                  printf("%d\t", i);
                printf("Привет, ты меня нашёл!\n");
                printf("Правда не выжил...\n");
                GameOver();
              break;

              default:
                printf("Пока вы стояли, и раздумывали, один из пеленегов вскочил из-за стола, схватил свой бластер и точным выстрелом в голову отправил вас на небеса...\n");
                GameOver();
              break;
            }
          }
          else
          {
            printf("Вы зашли в столовую, полную трупов. От воспоминаний о недавней перстрелке ваши раны предательки заныли, поэтому вы решили немедленно выйти в корридор.\n");
            inSwitchCurrLoc = 1;
          }
        break;

        case 3:
          hero = FinalScene(hero);
          inSwitchCurrLoc = 1;
        break;

        case 4:
          printf("Вы подошли к двери и поняли, что войти туда не получится, так как для этого требуется пароль. Ничего не поделаешь, поэтому вы решили отойти.\n");
          inSwitchCurrLoc = 1;
        break;
      }
      currLocation = inSwitchCurrLoc;
    }
    return hero;
}

/*Enter from the shore----------------------------------------------------------------------------------------------------------------------------------------*/

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
    int decision = TakeDecision();
    switch (decision)
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

/*Enter from the mounts------------------------------------------------------------------------------------------------------------------------------------------*/

struct MainHero DealWithSecurity(struct MainHero hero)
{
  hero.grenades--;
  printf("Вросили гранату в толпу, всех разнесло, но прибежало ещё 2, что делать будем?\n");
  ShowAmmo(hero);
  printf("0: Попробовать сбежать\n");
  printf("1: Стрелять из винтовки\n");
  printf("2: Бросить гранату\n");
  int inFlag = 0;
  while(inFlag == 0)
  {
    int decision = TakeDecision();
    switch (decision)
    {
      case 0:
        printf("Вы сбежали, но вас встретил Карл и заявил, что задание провалено, так как вы подняли кипиш и базу теперь наверняка перенесут.\n");
        GameOver();

      case 1:
        if((hero.rifleShots < 2) || (hero.health < 2))
        {
          if(hero.rifleShots < 2)
            printf("Вы остсреливались,но у вас кончились патроны и вас пристрелили...\n");
          else
            printf("пару точных выстрелов пронзили ваше бренное тело и вы умерли...\n");
        }
        else
        {
          hero.rifleShots--;
          hero.health--;
          printf("Вы прикончили агрессоров и спокойной вошли на базу\n");
          hero.flag[6]++;
          return hero;
        }
      break;

      case 2:
        if(hero.grenades < 1)
        {
          printf("Пока вы рылись в поясе в поисках гранаты, один из охранников вас заметил и пристрелил\n");
          GameOver();
        }
        else
        {
          hero.grenades--;
          printf("Вы прикончили агрессоров и спокойной вошли на базу\n");
          hero.flag[6]++;
          return hero;
        }
      break;
    }
  }
}

struct MainHero EnterFromTheMounts(struct MainHero hero)
{
  printf("Что делать с охраной? Их 6 и стоят они не не очень удобно, наверняка успеют ответить на агрессию.\n");
  printf("0: Расстерлять из винтовки\n");
  printf("1: Бросить гранату\n");
  printf("2: Уйти\n");
  int inFlag = 0;
  while(inFlag == 0)
  {
    int decision, shots;
    decision = TakeDecision();
    switch (decision)
    {
      case 0:
        shots = FireRifle(7, 1);
        if((shots > hero.rifleShots) || (hero.health < 2))
        {
          printf("Вы браво высунулись из-за камня, но... ");
          if(hero.health < 2)
            printf("пару точных выстрелов пронзили ваше бренное тело и вы умерли...\n");
          else
            printf("патроны кончились и вас пристрелили...\n");
          GameOver();
        }
        else
        {
          hero.rifleShots -= shots;
          hero.health -= FireRifle(1, 1);                     //рандомайзер здесь неплохо заходит, поэтому посчитаем, сколько убавилось жизней, этим методом
          printf("Вы браво высунулись из-за камня и расстреляли всех недоумков. К сожалению, один из них всё же успел вас поранить...\n");
          hero.flag[6]++;
          ShowAmmo(hero);
          return InTheBase(0, hero);
        }
      break;

      case 1:
        if(hero.grenades < 1)
          printf("Вы не нашли у себя гранат, нужно придумать что-то ещё.\n");
        else
        {
          hero = DealWithSecurity(hero);
          return InTheBase(0, hero);
        }
      break;

      case 2:
        printf("Вы решили пока с ними не связываться.\n");
        return hero;
      break;
    }
  }
}
