#include "libft.h"

char		*ft_str_append(char *str, char c)
{
    char	*out;
    int		i;

    i = 0;
    if (!(out = ft_strnew(ft_strlen(str) + 2)))
        return (NULL);
    while (str && *str)
        out[i++] = *str++;
    out[i++] = c;
    out[i] = '\0';
    if (!str)
        ft_strdel(&str);
    return (out);
}
