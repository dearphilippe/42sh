#include "helper.h"

char    *contain_term(char *str)
{
    char *dest;
    int     i;

    i = 0;
    if (str && *str && (*str == '|' || *str == ';' || (str[0] == '&' && str[1] && str[1] == '&')))
    {
        if (!(dest = ft_memalloc(sizeof(char) * 3)))
            return (NULL);
        if (*str == ';' || *str == '|' || *str == '&')
            dest[i++] = *str++;
        if (*str == '|' || *str == '&')
            dest[i++] = *str++;
        dest[i] = '\0';
        return (dest);
    }
    return (NULL);
}