#include "minishell.h"

char *strnstr(char *s1, char *s2)
{
    int i;
    int j;
    int start;

    i = 0;
    j = 0;
    while(s1[i])
    {
        if(s1[i] == s2[j])
        {
            start = i;  
            while(s1[i] == s2[j] && s2[j])
            {
                i++;
                j++;
            }
            if(s2[j] == '\0') 
                return (s1 + i - 1); 
            j = 0;
            i = start; 
        }
        i++;
    }
    return (NULL);
}


int main()
{
    char *s1 = "Hello, World   !";
    char *s2 = "World!";
    char *result = strnstr(s1, s2);
    if(result)
        printf("%s\n", result);
}