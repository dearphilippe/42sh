#include "libft.h"

int		ft_startwith(char *str, char *word)
{
    while (str && *str && word && *word && *str == *word)
    {
        str++;
        word++;
    }
    return (!ft_strlen(word) ? 1 : 0);
}