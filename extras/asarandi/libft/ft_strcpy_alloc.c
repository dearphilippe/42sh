#include "libft.h"

char        *ft_strcpy_alloc(char *s, int n)
{
    char    *str;
    int     i;

    i = 0;
    if (!(str = (char *)ft_memalloc(sizeof(char) * n + 1)))
        return (NULL);
    while (s && *s && n--)
        str[i++] = *s++;
    str[i] ='\0';
    return (str);
}
