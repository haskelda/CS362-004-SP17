#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TRACERS 0  // 1 = ON

char inputChar()
{ 
  int ascii = rand() % 94 + 32; // This creates an integer between 32-125 inclusive
  char c = ascii;
  #if (TRACERS == 1)
    printf("ASCII: %d\tchar c: %c\n", ascii, c);
  #endif
  return c;
}

char *inputString()
{
  char* stringArray[16] = {"on\0", "off\0", "switch\0", "status\0",
                         "min\0", "max\0", "median\0", "mean\0",
                         "ratio\0", "Reset\0", "RESET\0", "reset",
                          "on", "off", "\0", ""};
  int index = rand() % 16;
  char* s = stringArray[index];
  #if (TRACERS == 1)
    printf("index: %d\tstring s: %s\n", index, s);
  #endif
  return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c\t s = %s\t state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;

    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
