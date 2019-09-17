/*
  This is a C program to encrypt and decrypt text files
  using Rail Fence cipher.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MSG_MAX 100  // max size for msg = 100 characters
#define KEY 3  // key = 3 (fixed)

void encrypt(char file[]);  // function to encrypt
void decrypt(char file[]);  // function to decrypt

FILE *f1, *f2;  // f1 and f2 are for input and output files respectively

int main(void)
{
  int ch;
  char filename[20];  // file given by user
  printf("\n1. Encrypt\n2. Decrypt\n3. Exit\n");
  do
  {
    printf("\nEnter your choice: ");
    scanf("%d", &ch);
    switch(ch)
    {
      case 1: printf("\nEnter the filename: ");
              scanf("%s", filename);  // input file
              encrypt(filename);
              printf("\nEncrypted.\n");
              break;

      case 2: printf("\nEnter the filename: ");
              scanf("%s", filename);  // input file
              decrypt(filename);
              printf("\nDecrypted.\n");
              break;

      case 3: printf("\nExiting...\n\n");
              exit(0);

      default: printf("\nInvalid choice. Try again.\n");
    }
  }
  while(ch != 3);
  printf("\n");
  return 0;
}

void encrypt(char file[]) // file[] stores filename
{
  int msgLen, m, n, k = -1, row = 0, col = 0;
  char msg[MSG_MAX], railMatrix[KEY][MSG_MAX];
  f1 = fopen(file, "r");
  if(f1 == NULL)
  {
    printf("\nFile could not be opened or does not exist. Try again.\nExiting...\n\n");
    exit(0);
  }
  f2 = fopen("encrypted.txt", "w");
  msgLen = strlen(fgets(msg, MSG_MAX, f1));
  for(m = 0; m < KEY; ++m)
      for(n = 0; n < msgLen; ++n)
        railMatrix[m][n] = '\n';

  for(m = 0; m < msgLen; ++m)
  {
    railMatrix[row][col++] = msg[m];

    if(row == 0 || row == KEY-1)
        k = k * (-1);

    row = row + k;
  }

  for(m = 0; m < KEY; ++m)
      for(n = 0; n < msgLen; ++n)
          if(railMatrix[m][n] != '\n')
              fprintf(f2, "%c", railMatrix[m][n]);
  fprintf(f2, "\n");
  fclose(f1);
  fclose(f2);
}

void decrypt(char file[]) // file[] stores filename
{
  int msgLen, m, n, k = -1, row = 0, col = 0, q = 0;
  char msg[MSG_MAX], railMatrix[KEY][MSG_MAX];
  f1 = fopen(file, "r");
  if(f1 == NULL)
  {
    printf("\nFile could not be opened or does not exist. Try again.\nExiting...\n\n");
    exit(0);
  }
  f2 = fopen("decrypted.txt", "w");
  msgLen = strlen(fgets(msg, MSG_MAX, f1));

  for(m = 0; m < KEY; ++m)
      for(n = 0; n < msgLen; ++n)
          railMatrix[m][n] = '\n';

  for(m = 0; m < msgLen; ++m)
  {
    railMatrix[row][col++] = '*';

    if(row == 0 || row == KEY-1)
        k = k * (-1);

    row = row + k;
  }

  for(m = 0; m < KEY; ++m)
      for(n = 0; n < msgLen; ++n)
          if(railMatrix[m][n] == '*')
            railMatrix[m][n] = msg[q++];


  row = col = 0;
  k = -1;

  for(m = 0; m < msgLen; ++m)
  {
    fprintf(f2, "%c", railMatrix[row][col++]);

    if(row == 0 || row == KEY-1)
        k = k * (-1);

    row = row + k;
  }
  fprintf(f2, "\n");
  fclose(f1);
  fclose(f2);
}
