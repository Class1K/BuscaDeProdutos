#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255

void CriptografarString(char[], char[]);
void LerString(char[]);

int main()
{
    char s1[MAX] = {'\0'}, s2[MAX] = {'\0'};
    LerString(s1);
    CriptografarString(s1, s2);
    printf("%s", s2);


    return 0;
}


void LerString(char s1[])
{
    fflush(stdin);
    fgets(s1, MAX, stdin);
    if (s1[strlen(s1)-1] == '\n')
        s1[strlen(s1)-1] = '\0';

}

void CriptografarString(char s1[], char s2[])
{
    int i;
    for (i=0; i<strlen(s1); i++)
    {
        if (s1[i] != ' ')
        {
            if ( (s1[i]>=65 && s1[i]<88) || (s1[i]>=97 && s1[i]<120))
                s2[i] = s1[i]+ 3;
            else
                s2[i] = s1[i]-23;
        }
        else
            s2[i] = ' ';
    }

}

