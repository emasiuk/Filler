#ifndef _FILLER_H
# define _FILLER_H
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "libft/libft.h"
# define STDIN 0

typedef struct      s_fill
{
    int     m_h;
    int     m_w;
    int     e_h;
    int     e_w;
    char    my_symb;
    char  **elem;
    char   **map;
    int     count;
}                 t_fill;

void               read_all(t_fill *fill);

#endif
