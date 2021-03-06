#include <stdio.h>
#include <stdlib.h>

struct MainHero CaptureBorzukhan(struct MainHero hero)
{
  printf("Вспомнив подслушанный разговор пиратов у костра, вы решили разыскать домик, в котором любит отдыхать лякуша Борзухан. Поскольку вы\n");
  printf("знали все основные ориентиры, это оказалось несложной задачеи. Через несколько минут осторожнои ходьбы по лесу вы подошли к поляне,\n");
  printf("посреди которои деиствительно стоял деревянныи домик с застекленным окном. Похоже, даже в наше время и даже среди\n");
  printf("пиратов есть любители пожить на лоне природы!\n");
  int inFlag = 0;
  int choice;
  while(inFlag != 1)
  {
    ShowAmmo(hero);
    printf("0: Вернуться к флаеру\n");
    printf("1: Швырнуть гранату в окно\n");
    printf("2: Подкрасться к домику и осторожно заглянуть в окно\n");
    printf("3: Подойти к двери и вежливо постучать\n");
    printf("4: Вышибить дверь ногой и ворваться в домик с оружием наизготовку\n");
    int decision = TakeDecision();
    switch (decision)
    {
      case 0:
        printf("Вы решили пока не связываться с Борзуханом лично, поэтому развернулись и улетели к лагерю.\n");
        return hero;
      break;

      case 1:
        if(hero.grenades > 0)
        {
          hero.grenades--;
          hero.flag[4] = 1;
          hero.flag[0] = 3;
          printf("Вы подкрались к одну, достали гранату и заброслил её внутрь. Через бесконечно длинные 3 секунды внутри послышался гулкий хлопок.\n");
          printf("Вы решили заглянуть в хижину: внутри всё раскурочено, в дальнем углу лежит тело пеленега, в котором вы распознали Борзухана. Это\n");
          printf("означает, что часть вашей миссии выполнена, хоть и немного не так, как хотелось. С этими мыслями вы отправились в лагерь с докладом.\n");
          sleep(1);
          return hero;
        }
        else
        {
          printf("Порывшись в своём поясе, вы не обнаружили ни одной гранаты. Нужно придумть что-то другое.\n");
        }
      break;

      case 2:
        choice = 0;
        inFlag++;
      break;

      case 3:
        choice = 1;
        inFlag++;
      break;

      case 4:
        choice = 2;
        hero.flag[4] = 1;
        inFlag++;
      break;

      default:
        printf("Нужно придумать что-то другое...\n");
      break;
    }
  }
  if(choice == 0)
  {
    printf("Вы подкрались к окну и осторожно заглянули внутрь. В кресле, посреди богато убранной комнатки, сидит пеленг, в котором, присмотревшись,\n");
    printf("вы узнали лякушу Борзухана. Похоже, он вас не замечает.\n");
    printf("0: Расстрепять Борзухана из лазерной винтовки\n");
    printf("1: Выстрелить через окно из станнера\n");
    printf("2: Осторожно отойти от домика и вернуться в лагерь\n");
    while(1)
    {
      int decision = TakeDecision();
      switch (decision)
      {
        case 0:
          if(hero.rifleShots > 0)
          {
            hero.rifleShots--;
            printf("Вы достали лазерную винтовку, аккуратно прицелились и выстрелили. Не ожидавший нападения, лякуша Борзухан судорожно дернулся \n");
            printf("и обмяк. В груди у него зияла дыра. Что ж, с одной проблемой покончено, осталось разыскать и уничтожить базу..\n");
            sleep(1);
            hero.flag[0] = 3;
            hero.flag[4] = 1;
            printf("К счастью, выстрел был не совсем точным, и вы остались живы, хотя вас и задело. Ну что ж, с лякушей Борзуханом покончено. Теперь нужно искать его базу.\n");
            return hero;
          }
          else
          {
            printf("Не получится, придётся придумать что-нибудь другое.\n");
          }
        break;

        case 1:
          if(hero.flag[3] == 1)
          {
            hero.flag[3] = 0;
            hero.flag[0] = 2;
            hero.flag[4] = 1;
            printf("Вы аккуратно прицелились, выстрелили из станнера широким пучком энергии, и лякуша Борзухан свалился на пол. Однако\n");
            printf("станнер исчерпал свой анергозалас, и вы выбросили его за ненадобностью.\n");
            sleep(1);
            printf("Вы взвалили на себя оглушенного лякушу Борзухана и отволокли его на флаер. Следя за тем, чтобы он не пришел в сознание,\n");
            printf("вы отвезли его в лагерь. Встретивший вас Карл был очень рад вашему успеху. Однако вам еще предстоит разыскать и уничтожить базу Борзухана.\n");
            return hero;
          }
          else
          {
            printf("Не получится, придётся придумать что-нибудь другое.\n");
          }
        break;

        case 2:
          printf("Вы решили пока не связываться с Борзуханом лично, поэтому развернулись и улетели к лагерю.\n");
          return hero;
        break;
      }
    }
    return hero;
  }
  if(choice == 1)
  {
    printf("Вы подошли к двери и вежливо постучались. Вы услышали быстрые шаги, замершие у двери -должно быть, хозяин разглядывал вас через глазок.\n");
    printf("Затем послышался резкий голос:\n");
    printf("-Кто ты такой, и чего тебе здесь надо? Отвечай быстро и без фокусов!\n");
    printf("0: -Я ищу лякушу Борзухана!\n");
    printf("1: -Лесник я, хочу с вами поговорить\n");
    printf("2: -Да тут мимо проходил, дай, думаю, зайду!\n");
    int decision = TakeDecision();
    switch (decision)
    {
      case 0:
        printf("Деверь открылась, в проходе стоял грозный пеленег с бластером в руках.\n");
        printf("-Ты его нашёл. -ухмыльнулся он и выстрелил вам в голову.\n");
      break;

      case 1:
        printf("Деверь открылась, в проходе стоял грозный пеленег с бластером в руках.\n");
        printf("-Нет здесь таких. -сказал он и выстрелил вам в голову.\n");
      break;

      case 3:
        printf("Деверь открылась, в проходе стоял грозный пеленег с бластером в руках.\n");
        printf("-Гостей не ждали. -ухмыльнулся он и выстрелил вам в голову.\n");
      break;

      default:
        printf("Ваши раздумья преравла открывшаяся деверь. В проходе стоял грозный пеленег с бластером в руках.\n");
        printf("-Не люблю молчаливых. -ухмыльнулся он и выстрелил вам в голову.\n");
      break;
    }
    GameOver();
  }
  if(choice == 2)
  {
    printf("Вышибив ногой дверь, вы ворвались в домик. Сидящий в кресле лякуша Борзугхан резко вскочил и нервно огляделся в поисках своей лазерной винтовки, лежащей рядом.\n");
    ShowAmmo(hero);
    printf("0: Выстрелить из лазерной винтовки\n");
    if(hero.flag[3] == 1)
      printf("1: Оглушить лякугшу Борзухана выстрелом из станнера\n");

    int decision = TakeDecision();
    switch (decision)
    {
      case 0:
        if(hero.rifleShots > 0)
        {
          hero.rifleShots = hero.rifleShots - 2;
          hero.health--;
          printf("Вы выстрелили в лякушу Борзухана из лазерной винтовки, но он резко пригнулся, и ваш выстрел прошел мимо, а Борзухан метнулся к своей винтовке.\n");
          printf("Однако вы тщательно прицелились и выстрелили снова. Лякуша свалился замертво, но перед смертью успел все же выстрелить в вас...\n");
          sleep(1);
          hero.flag[0] = 3;
          hero.flag[4] = 1;
          printf("К счастью, выстрел был не совсем точным, и вы остались живы, хотя вас и задело. Ну что ж, с лякушей Борзуханом покончено. Теперь нужно искать его базу.\n");
        }
        else
        {
          printf("Пока вы пытались выстрелить из разряженной винтовки, Борзухан схватил свою и пристрелил вас.\n");
          GameOver();
        }
      break;

      case 1:
        if(hero.flag[3] == 1)
        {
          hero.flag[3] = 0;
          hero.flag[0] = 2;
          hero.flag[4] = 1;
          printf("Вы быстро выстрелили из станнера широким пучком энергии, и лякуша Борзухан свалился на пол. Однако\n");
          printf("станнер исчерпал свой анергозалас, и вы выбросили его за ненадобностью.\n");
          sleep(1);
          printf("Вы взвалили на себя оглушенного лякушу Борзухана и отволокли его на флаер. Следя за тем, чтобы он не пришел в сознание,\n");
          printf("вы отвезли его в лагерь. Встретивший вас Карл был очень рад вашему успеху. Однако вам еще предстоит разыскать и уничтожить базу Борзухана.\n");
        }
        else
        {
          printf("Пока вы стояли и раздумывали о смысле жизни, Борзухан схватил свою винтовку и пристрелил вас.\n");
          GameOver();
        }
      break;

      default:
        printf("Пока вы стояли и раздумывали о смысле жизни, Борзухан схватил свою винтовку и пристрелил вас.\n");
        GameOver();
      break;
    }
    return hero;
  }
}
