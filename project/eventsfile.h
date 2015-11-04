#include <stdio.h>
#include <stdlib.h>

/*Events on the lawn----------------------------------------------------------------------------------------------------------------------------------------------------------*/
struct MainHero DealWithPelenegs(struct MainHero hero)
{
  int i = 0;
  for(i; i < 3; i++)
  {
    if((i == 0) || (i == 1))
    {
      if(i == 0)
      {
        printf("Вы незаметно посадили флаер в сторонке от костра, за большим валуном. Теперь вы видите, что вокруг костра\n");
        printf("собрались пятеро пеленгов весьма недружелюбного вида, которые оживленно что-то обсуждают. Рядом с ними неподвижно\n");
        printf("лежит человек. Он выглядит так, как будто его оглушили мощным разрядом из станнера.\n");
      }
      else
      {
        printf("Вы прислушались и попытались разобрать, о чем говорят пеленги у костра. Некоторые обрывки их разговора подтвердили ваши\n");
        printf("подозрения: компания у костра была отрядом пиратов Борзухана, вернувшихся 'с дела' и собирающихся доставить пленника на базу.\n");
      }
      ShowAmmo(hero);
      printf("0: Бросить гранату\n");
      printf("1: Расстрелять из лазерной винтовки\n");
      printf("2: Улететь\n");
      printf("3: Прислушаться к разговору\n");
      int inFlag = 0;
      while(inFlag != 1)
      {
        int decidion;
        scanf("%d", &decidion);
        switch (decidion)
        {
          case 3:
            inFlag = 1;
          break;

          case 1:
            printf("Высунувшись из-за камня, вы начали палить по пеленегам.\n");
            int shots = 5;
            if (hero.rifleShots - shots >= 0)
            {
              hero.rifleShots = hero.rifleShots - shots + 4;
              printf("Бедолаги в панике забегали по поляне, но благодаря удачной позиции вы были точны как никогда и потратили всего 5 зарядов.\n");
              printf("Когда со всеми было покончено, вы окинули взглядом поле боя.\n");
              printf("Вы подошли к неподвижно лежащему человеку и попробовали привести его в чувство. Поначалу вам ничего не удавалось,\n");
              printf("но наконец он зашевелился, открыл глаза и простонал:\n");
              printf("-Где я? Кто вы такой?\n");
              printf("-Я %s, я ищу базу пеленега Борзухана.\n", hero.name);
              printf("-Сп-пасибо в-вам, %s, за... то, что вы... с-спасли меня от этих мерз-завцев, - с трудом проговорил человек, - Я б-был простым...\n", hero.name);
              printf("торговцем... Они схватили меня прямо в космопорту... где же это было... извините, я не помню названия той планеты. Они потребовали\n");
              printf("выкуп, но я н-не мог заплатить той суммы, какую они от меня ›‹отели. Поэтому они... оглушили меня и перевезли сюда. Как-то я приходил в\n");
              printf("сознание и слышал, как они говорили что-то о каком-то Борзухане. Так это его вы ищете? Я слышал что-то про горы... а также про какой-то\n");
              printf("секретный ход на побережье... К сожалению, я не могу рассказать вам ничего более... подробного, поскольку, заметив, что я пришел в себя,\n");
              printf("они снова оглушили меня станнером... Пожалуйста, не могли бы вы доставить меня куда-то... где мне могли бы п-помочь выбраться из этой дыры?\n");
              printf("-Да, конечно! - ответили вы и помогли добраться незнакомцу до флаера, попутно захватив с собой станнер и 4 заряда для лазерной пушки.\n");
              sleep(1);
              printf("Долетев до лагеря, вы сдали раненного в медпалатку, а сами продлжили свои поиски.\n");
              hero.flag[1] = 1;
              hero.flag[3] = 1;
              return hero;
            }
            else
            {
              printf("В самый разгар стрельбы у вас кончились заряды. Выжившие пеленеги быстро сориентировались в сложившейся ситуации...\n");
              sleep(1);
              printf("На вас пысался град выстрелов, в конце концов один из пеленегов попал вам в голову, на чём ваши страдания закончились\n");
              printf("Game over!\n");
              exit (0);
            }
            break;

          case 0:
            if(hero.greandes > 0)
            {
              printf("Высунувшись из-за камня, вы достали гранату и кинули её в толпу сидящих у костра пеленегов.\n");
              hero.greandes--;
              printf("Ошмётки мяса разлетелись по всей поляне. Такая картина вызвала у вас приступ рвоты, и вы решили немедленно возвращаться\n");
              printf("в лагерь. В любом случае, пленник тоже не смог пережить взрыв гранаты и делать здесь точно больше нечего\n");
              return hero;
            }
            else
            {
              printf("Порывшись в своём поясе, вы не обнаружили ни одной гранаты. Нужно придумть что-то другое.\n");
            }
          break;

          case 2:
            printf("Вы решили не связыываться с подозрительными личностями, развернули флаер и отправились к лагерю\n");
            return hero;
          break;

          default:
            printf("Так не выйдет...\n");
          break;
        }
      }

    }
    if(i == 2)
    {
      printf("Вы продолжили прислушиваться к разговору пиратов и услышали, как кто-то из них с явным неудовольствием обсуждал привычку своего босса Борзухана\n");
      printf("отдыхать в одиночестве в домике, спрятанном в лесу на западе. Пират явно был уверен, что такая привычка не доведет до добра, и вы были\n");
      printf("с ним полностью согласны, учитывая, что этот кретин ухитрился выболтать несколько ориентиров, зная которые, найти лякушину\n");
      printf("хибарку будет совсем несложно!\n");
      hero.flag[0] = 1;

      ShowAmmo(hero);
      printf("0: Бросить гранату\n");
      printf("1: Расстрелять из лазерной винтовки\n");
      printf("2: Улететь\n");
      int inFlag = 0;
      while(inFlag != 1)
      {
        int decidion;
        scanf("%d", &decidion);
        switch (decidion)
        {
          case 2:
            printf("Вы решили не связыываться с подозрительными личностями, развернули флаер и отправились к лагерю\n");
            return hero;
          break;

          case 1:
            printf("Высунувшись из-за камня, вы начали палить по пеленегам.\n");
            int shots = 5;
            if (hero.rifleShots - shots >= 0)
            {
              hero.rifleShots = hero.rifleShots - shots + 4;
              printf("Бедолаги в панике забегали по поляне, но благодаря удачной позиции вы были точны как никогда и потратили всего 5 зарядов.\n");
              printf("Когда со всеми было покончено, вы окинули взглядом поле боя.\n");
              printf("Вы подошли к неподвижно лежащему человеку и попробовали привести его в чувство. Поначалу вам ничего не удавалось,\n");
              printf("но наконец он зашевелился, открыл глаза и простонал:\n");
              printf("-Где я? Кто вы такой?\n");
              printf("-Я %s, я ищу базу пеленега Борзухана.\n", hero.name);
              printf("-Сп-пасибо в-вам, %s, за... то, что вы... с-спасли меня от этих мерз-завцев, - с трудом проговорил человек, - Я б-был простым...\n", hero.name);
              printf("торговцем... Они схватили меня прямо в космопорту... где же это было... извините, я не помню названия той планеты. Они потребовали\n");
              printf("выкуп, но я н-не мог заплатить той суммы, какую они от меня xотели. Поэтому они... оглушили меня и перевезли сюда. Как-то я приходил в\n");
              printf("сознание и слышал, как они говорили что-то о каком-то Борзухане. Так это его вы ищете? Я слышал что-то про горы... а также про какой-то\n");
              printf("секретный ход на побережье... К сожалению, я не могу рассказать вам ничего более... подробного, поскольку, заметив, что я пришел в себя,\n");
              printf("они снова оглушили меня станнером... Пожалуйста, не могли бы вы доставить меня куда-то... где мне могли бы п-помочь выбраться из этой дыры?\n");
              printf("-Да, конечно! - ответили вы и помогли добраться незнакомцу до флаера, попутно захватив с собой станнер и 4 заряда для лазерной пушки.\n");
              sleep(1);
              printf("Долетев до лагеря, вы сдали раненного в медпалатку, а сами продлжили свои поиски.\n");
              hero.flag[1] = 1;
              hero.flag[3] = 1;
              return hero;
            }
            else
            {
              printf("В самый разгар стрельбы у вас кончились заряды. Выжившие пеленеги быстро сориентировались в сложившейся ситуации...\n");
              sleep(1);
              printf("На вас пысался град выстрелов, в конце концов один из пеленегов попал вам в голову, на чём ваши страдания закончились\n");
              printf("Game over!\n");
              exit (0);
            }
            break;

          case 0:
            if(hero.greandes > 0)
            {
              printf("Высунувшись из-за камня, вы достали гранату и кинули её в толпу сидящих у костра пеленегов.\n");
              hero.greandes--;
              printf("Ошмётки мяса разлетелись по всей поляне. Такая картина вызвала у вас приступ рвоты, и вы решили немедленно возвращаться\n");
              printf("в лагерь. В любом случае, пленник тоже не смог пережить взрыв гранаты и делать здесь точно больше нечего\n");
              return hero;
            }
            else
            {
              printf("Порывшись в своём поясе, вы не обнаружили ни одной гранаты. Нужно придумть что-то другое.\n");
            }
          break;

          default:
            printf("Так не выйдет...\n");
          break;
        }
      }
    }
  }
}


struct MainHero IncidentOnTheLawn(struct MainHero hero)
{
  printf("Вы полетели к поляне и увидели группу существ, собрашихся у костра. ");
  printf("Издали вы не можете различить, кто именно перед вами, и чем они занимаются.\n");
  ShowAmmo(hero);
  printf("0: Подлететь поближе к костру и открыть огонь из лазерной винтовки\n");
  printf("1: Подлететь поближе и швырнуть гранату\n");
  printf("2: Развернуться и улететь\n");
  printf("3: Незаметно сесть поодаль от костра\n");
  printf("4: Посадить флаер у костра\n");
  int flag = 0;
  int decidion;
  while(flag != 1)
  {
    scanf("%d", &decidion);
    if((decidion == 0) || (decidion == 1) || (decidion == 2) || (decidion == 3) || (decidion == 4))
      flag = 1;
    else
      printf("Так не получится...\n");
  }
  switch (decidion)
  {
    case 0:
      printf("Подлетев поближе к костру, вы лихо высунулись из кабины и начали палить по существам, оказавшихся пеленегами.\n");
      int shots = FireRifle(6, 2);
      if (hero.rifleShots - shots >= 0)
      {
        hero.rifleShots = hero.rifleShots - shots;
        printf("Бедолаги в панике забегали по поляне, что затруднило стрельбу: вы потратили целых %d зарядов.\n", shots);
        printf("Когда со всеми было покончено, вы окинули взглядом поле боя. Движения на поляне не было, поэтому вы развернули флаер и направились к лагерю.\n");
        return hero;
      }
      else
      {
        printf("В самый разгар стрельбы у вас кончились заряды. Выжившие пеленеги быстро сориентировались в сложившейся ситуации...\n");
        sleep(1);
        printf("Ваш флаер с грохотом упал на землю, расстреленный из лазерных винтовок лякушей.\n");
        printf("Вы так и не смогли вылезти из горящего флаера. Один из пеленегов подошёл выстрелил вам в голову, на чём ваши страдания закончились\n");
        printf("Game over!\n");
        exit (0);
      }
    break;

    case 1:
      if(hero.greandes > 0)
      {
        printf("Подлетев поближе, вы достали гранату и кинули её в толпу сидящих у костра пеленегов.\n");
        hero.greandes--;
        printf("Ошмётки мяса разлетелись по всей поляне. Такая картина вызвала у вас приступ рвоты, и вы решили немедленно возвращаться\n");
        printf("в лагерь. В любом случае здесь делать больше нечего\n");
        return hero;
      }
      else
      {
        printf("Подлетев поближе к костру, вы попытались достать гранату, однако не обнаружили ни одной в своём поясе.\n");
        printf("Смачно выругавшись, вы повернули флаер и на форсаже полетели к лагерю\n");
        printf("К сожалению, ваш манёвр не был не замечен сидевшими у костра пеленегами, и удирали вы под жужжание лазерных винтовок.\n");
        printf("Один из выстрелов пришёлся вам в плечо. Было очень больно, но добраться до перевязочного пункта вы смогли и теперь готовы \n");
        printf("продолжать свои поиски\n");
        hero.health--;
      }
      return hero;
    break;

    case 2:
      printf("Вы решили не связыываться с подозрительными личностями, развернули флаер и отправились к лагерю\n");
      return hero;
    break;

    case 3:
      hero = DealWithPelenegs(hero);
      return hero;
    break;

    case 4:
      printf("Вы приземлили свой флаер около костра, вышли и направились к существам.");
      printf("Это были вооружёные до зубов пеленеги, которые до вашего прибытия активно обсуждали свою недавнюю вылазку.\n");
      printf("Едва завидев вас, они вскочили со своих мест и изрешетили вас из своих лазерных винтовок\n");
      sleep(1);
      printf("Game over!\n");
      exit(0);
    break;
  }
}

/*Briefing-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Briefing(char *yourName)
{
  printf("В лагере вас встретил правительственный агент\n");
  printf("-Уважаемый %s, я рад приветствовать вас здесь. Меня зовут Карл. Как вам, наверное, уже рассказали, вашей задачей\n", yourName);
  printf("здесь будет обнаружение и ликвидация базы пеленега, известного как лякуша Борзухан. Главное - уничтожить базу\n");
  printf("При этом вам скорее всего придётся столкнуться с сопротивлением самого Борзухана. В таком случае ориентируйтесь\n");
  printf("по ситуации, но учтите, что лучше всего будет захватить его живым. Если у вас есть какие-то вопросы, задавайте\n");
  printf("их сейчас, я постараюсь рассказать вам всё, что знаю сам\n");
  int flag = 0;
  while(flag != 1)
  {
    printf("0: Я готов!\n");
    printf("1: Как мне найти базу Борзухана?\n");
    printf("2: Почему вы не обнаружили базу сами?\n");
    printf("3: Каким образом я смогу уничтожить базу?\n");
    int decidion;
    scanf("%d", &decidion);
    switch (decidion)
    {
      case 0:
        printf("Отлично! Но перед тем как вы уйдете, вы должны получить ваше снаряжение. Ведь не собираетесь же вы идти бороться\n");
        printf("с Борзуханом с голыми руками? Значит так: вы получите заряд взрывчатки для уничтожения базы, лазерную винтовку и\n");
        printf("несколько гранат. К сожалению, запасы оружия у нас небольшие, так как пилот транспорта, который должен был недавно\n");
        printf("доставить нам снаряжение, оказался любителем пеленгских галлюциногенов и ухитрился врезаться в пять астероидов\n");
        printf("подряд. Надеюсь, вы такими вещами не балуетесь?\n");
        printf("Ходить пешком тут будет далековато, так что вы полетите на легком флаере. Он достаточно невелик и неплохо акранирован,\n");
        printf("поэтому вас вряд ли засекут, если вы сами себя не обнаружите. Мы покажем вам фотографию лякуши Борзухана, чтобы\n");
        printf("вы могли его узнать. Это все. Будьте осторожны и внимательны, и удачи вам в обнаружении и ликвидации базы!\n");
        flag = 1;
      break;

      case 1:
        printf("-Это действительно может оказаться сложной задачей, поскольку планета достаточно велика. Однако я могу дать\n");
        printf("вам совет по поводу тех мест, где, по нашим данным с наибольшей вероятностью может быть расположена база.\n");
        printf("С нашей точки зрения, база может находиться в горах на севере от нашего лагеря, в лесу на юго-западе или\n");
        printf("в подземных пещерах, в которые можно попасть через грот на востоке у моря\n");
        printf("Но всё равно будьте внимательны, мы можем много не знать, поэтому лучше не полагайтесь только на эту информацию.\n");
      break;

      case 2:
        printf("Конечно, мы могли заранее послать своих людей на поиски базы, но у нас нет достаточно опытных агентов, которым\n");
        printf("мы могли бы доверить эту работу. Мы опасаемся, что неопытный разведчик может неосторожными деиствиями вспугнуть\n");
        printf("Борзухана. Еспи он поимет, что мы знаем местонахождение его базы, то, скорее всего, он перенесет ее в другое место,\n");
        printf("возможно, даже на другую планету, и нам придется искать его снова. Надеюсь, вы понимаете, насколько важна ваша миссия.\n");
        printf("Кстати, у нас есть некоторые данные по поводу возможного расположения базы пякуши Борзухана. Я отмечу их на вашеи карте.\n");
      break;

      case 3:
        printf("Конечно, мы не пошлем вас уничтожкать базу безоружным. Вы получите лазерную винтовку и несколько гранат на случай\n");
        printf("столкновения с вооруженной охраной. Кроме того, мы дадим вам специальное взрывное устройство с дистанционным детонатором.\n");
        printf("Вам предстоит выяснить, какое место на базе является наиболее уязвимым, и установить взрывчатку там. Но не забывайте,\n");
        printf("что не менее важной задачей является поимка самого лякуши Борзухана.\n");
        printf("Как я уже говорил, желательно захватить его живым, за это вы получите дополнительное вознаграждение, но если вам\n");
        printf("это не удастся, то можете его убить. Однако ни в коем случае не дайте ему уйти!\n");
      break;

      default:
        printf("Ещё раз...\n");
      break;
    }
  }
}
