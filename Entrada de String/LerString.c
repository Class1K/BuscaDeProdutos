void LerString(char s1[])
{
    fflush(stdin);
    fgets(s1, MAX, stdin);
    if (s1[strlen(s1)-1] == '\n')
        s1[strlen(s1)-1] = '\0';

}
