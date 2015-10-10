//My Project
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

char *helpMessage = "Keys:\n-h or --help\t\t\tshow help\n-k or --key [keyfile]\t\tset keyfile for shared memory\n-i or --input [inputfile]\tset input file\n-g or --get [shmemory]\t\tread from shared memory\n-r or --remove [shmemory]\tremove shared memory\n-cheese\t\t\t\t...\n";
char *restrictMessage = "Do NOT delete SHMEM_INFO, it will be removed automatically when you clear shared memory with -r or --remove key\n";

struct FilesInfo
{
  char *keyFile;
  char *inputFile;
} workingFiles;

int Case2Args(char *args)
{
  if((strcmp(args, "-h") == 0) || (strcmp(args, "--help") == 0))
  {
    printf("%s", helpMessage);
    return 0;
  }

  if(strcmp(args, "cheese") == 0)
  {
    WhereIsMyCheese();
    return 0;
  }
  return 1;
}


int Case5Args(char **args)
{
  int i = 1;
  bool flag[2] = {false, false};
  while((i < 5) && (flag[0] == false))
  {
    if((strcmp(args[i], "-i") == 0) || (strcmp(args[i], "--input") == 0))
    {
      workingFiles.inputFile = args[i + 1];
      flag[0] = true;
    }
    i = i + 2;
  };
  i = 1;
  while((i < 5) && (flag[1] == false))
  {
    if((strcmp(args[i], "-k") == 0) || (strcmp(args[i], "--key") == 0))
    {
      workingFiles.keyFile = args[i + 1];
      flag[1] = true;
    }
    i = i + 2;
  };
  if((flag[0] == false) || flag[1] == false)
  {
    return 1;
  }
  printf("Key file is %s\n", workingFiles.keyFile);
  printf("Input file is %s\n", workingFiles.inputFile);
  int error = FileToShMem(workingFiles);
  switch (error)
  {
    case 2:
      return 2;
      break;

    case 3:
      return 3;
      break;

    case 4:
      return 4;
      break;

    default:
      return 0;
      break;
  }
}

int case3Args(char **args)
{
  int error;
  if((strcmp(args[1], "-g") == 0) || (strcmp(args[1], "--get") == 0))
  {
    error = ReadFromShMem(args[2]);
  }
  if((strcmp(args[1], "-r") == 0) || (strcmp(args[1], "--remove") == 0))
  {
    error = RemoveShMem(args[2]);
  }
  switch (error)
  {
    case 0:
      return 0;
      break;

    case 3:
      return 3;
      break;

    default:
      return 1;
      break;
  }
}

int FileToShMem(struct FilesInfo workingFiles)
{
  if(strcmp(workingFiles.keyFile, workingFiles.inputFile) == 0)
  {
    return 2;
  }
  int fileDesc = open(workingFiles.inputFile, O_RDONLY);
  if(fileDesc < 0)
  {
    return 3;
  }
	int sizeOfFile = 0, i;
	char dummy;
	while(read(fileDesc, &dummy, sizeof(char)) > 0)
  {
    sizeOfFile++;
  }
	char string[sizeOfFile];
  printf("Size of file is %d\n", sizeOfFile);
	lseek(fileDesc, 0, 0);

  FILE * aux_fileDesc = fopen("SHMEM_INFO", "wt");
  fprintf(aux_fileDesc, "%d\n", sizeOfFile);
  fclose(aux_fileDesc);
  printf("%s", restrictMessage);

  while(read(fileDesc, &string[i], sizeof(char)) > 0)
  {
    i++;
  }

  key_t key = ftok(workingFiles.keyFile, 0);
  printf("key = %d\n", key);
  (void)umask(0);
  int shmId = shmget(key, sizeOfFile, IPC_CREAT | 0777);

  if(key < 0)
  {
    return 4;
  }
  printf("shmId: %d\n", shmId);

  char *data = shmat(shmId, 0, 0);
  strcpy(data, string);
	close(fileDesc);
  return 0;
}

int ReadFromShMem(char *shMemFile)
{
  int sizeOfFile;
  FILE *aux_fileDesc = fopen("SHMEM_INFO", "rt");
  if(aux_fileDesc < 0)
  {
    printf("Shame you've deleted SHMEM_INFO...");
    exit(-1);
  }
  fscanf(aux_fileDesc, "%d", &sizeOfFile);
  fclose(aux_fileDesc);

  printf("Size of file is %d\n", sizeOfFile);

  key_t key = ftok(shMemFile, 0);
  printf("key = %d\n", key);
  (void)umask(0);
  int shmId = shmget(key, sizeOfFile, 0777);

  if(key < 0)
  {
    return 4;
  }
  printf("shmId: %d\n", shmId);

  char *data = shmat(shmId, 0, 0);
  char string[sizeOfFile];
  strcpy(string, data);
  printf("%s\n", string);
  return 0;
}

int RemoveShMem(char *shMemFile)
{
  int sizeOfFile;
  FILE *aux_fileDesc = fopen("SHMEM_INFO", "rt");
  if(aux_fileDesc < 0)
  {
    printf("Shame you've deleted SHMEM_INFO...");
    exit(-1);
  }
  fscanf(aux_fileDesc, "%d", &sizeOfFile);
  fclose(aux_fileDesc);
  key_t key = ftok(shMemFile, 0);
  printf("key = %d\n", key);
  (void)umask(0);
  int shmId = shmget(key, sizeOfFile, 0777);

  if(key < 0)
  {
    return 4;
  }
  printf("shmId: %d\n", shmId);
  shmctl(shmId, IPC_RMID, NULL);
  unlink("SHMEM_INFO");
  printf("Shared memory and SHMEM_INFO were successfully removed!\n");
  return 0;
}



void WhereIsMyCheese()
{
  printf("You might have some cheese now!\n");
  int cheese = open("cheese.txt", O_WRONLY | O_CREAT, 0777);
  write(cheese, "Some cheese", 12);
  close(cheese);
}
