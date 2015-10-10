#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "functions.h"

char *helpMessage = "Keys:\n-h or --help\t\t\tshow help\n-k or --key [keyfile]\t\tset keyfile for shared memory\n-i or --input [inputfile]\tset input file\n-g or --get [shmemory]\t\tread from shared memory\n-r or --remove [shmemory]\tremove shared memory\n-cheese\t\t\t\t...\n";
char *restrictMessage = "Do NOT delete SHMEM_INFO, it will be removed automatically when you clear shared memory with -r or --remove key\n";

struct FilesInfo
{
  char *keyFile;
  char *inputFile;
};




int main (int argsCount, char **args)
{
  ParsArgs(int argsCount, char **args);
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
