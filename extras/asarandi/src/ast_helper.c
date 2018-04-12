#include "parse.h"

char    *remove_start_space(char *str)
{
    char *dest;

    if (!str)
        return (NULL);
    while (str && *str && *str == ' ')
        str++;
    if (!(dest = ft_memalloc(ft_strlen(str) + 1)))
        return (NULL);
    return (ft_strcpy(dest, str));
}
