#include "my_filler.h"
#include "libft/libft.h"
//
//void        find_near_enemy(t_fill *fill)
//{
//    int     i;
//    int     j;
//
//    i = -1;
//    j = -1;
//    while (++i < fill->m_h)
//    {
//        while (++j < fill->m_w)
//        {
//            if (fill->map[i][j] != fill->my_symb && fill->map[i][j] != '.')

//        }
//    }
//}

int         check_pos(t_fill *fill, int i, int j)
{
    for (int r = 0; r < fill->e_h; r++)
        for(int c = 0; c < fill->e_w; c++)
            if (fill->elem[r][c] == '*')
            {
                if (i + r < fill->m_h && j + c < fill->m_w)
                {
                    if (fill->map[i + r][j + c] != '.')
                        return (-1);
                }
                else
                    return (-1);
            }
    return (0);
}


int         check_touch(t_fill *fill, int i, int j)
{
    for (int r = 0; r < fill->e_h; r++)
        for (int c = 0; c < fill->e_w; c++)
            if (fill->elem[r][c] != '.')
            {
                if (i + r + 1 < fill->m_h && fill->map[i +r + 1][j + c] == fill->my_symb)
                    return (0);
                if (j + c +1 < fill->m_w && fill->map[i +r][j + c + 1] == fill->my_symb)
                    return (0);
                if (i + r - 1 >= 0 && fill->map[i +r - 1][j + c] == fill->my_symb)
                    return (0);
                if (j + c - 1 >= 0 && fill->map[i +r][j + c - 1] == fill->my_symb)
                    return (0);
            }
    return (-1);
}

void        tupik(t_fill *fill)
{
    FILE    *logger;
    int     i;
    int     j;

    i = 0;
    while (i < (fill->m_h))
    {
        j = 0;
        while (j < (fill->m_w))
        {
            if (!check_pos(fill, i, j) && !check_touch(fill, i, j))
            {
                logger = fopen("filler.log", "a");
                fprintf(logger, "%d %d\n", j, i);
                fclose(logger);
                dprintf(1, "%d %d", j, i);
                fill->status = READ;
                return ;
            }
            j++;
        }
        i++;
    }
    logger = fopen("filler.log", "a");
    fprintf(logger, "end tupik\n");
    fclose(logger);
}

void        free_struct(t_fill *fill)
{
    FILE *logger;
    logger = fopen("filler.log", "a");
    fprintf(logger, "free\n");
    fclose(logger);

    int     i;

    i  = -1;
    if (fill->map)
    {
      while (++i < fill->m_h)
            free(fill->map[i]);
        free(fill->map);
    }
    fill->map = NULL;
    i = -1;
    if (fill->elem[0])
    {
        while (++i < fill->e_h)
            free(fill->elem[i]);
        free(fill->elem);
    }
    free(fill->string->str);
    free(fill->string);
    fill->string = NULL;
    fill->elem = NULL;
    fill = (t_fill *)malloc(sizeof(t_fill));
//    logger = fopen("filler.log", "a");
//    fprintf(logger, "%s\n", fill->map[1]);
//    fclose(logger);

    //
    // if (fill->my_symb)
    //     fill->my_symb = NULL;
}

void        read_input1(t_fill *fill)
{
    fd_set rfds;
    fd_set wfds;
    int flags;
    FILE *logger;

    logger = fopen("filler.log", "w");
    fprintf(logger, "Start game\n");
    fclose(logger);

    flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, flags | O_NONBLOCK);
    while (42)
    {
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        if (fill->status == READ)
            FD_SET(0, &rfds);
        else
            FD_SET(1, &wfds);

        select(2, &rfds, &wfds, NULL, NULL);

        if (FD_ISSET(0, &rfds))
        {
            logger = fopen("filler.log", "a");
            fprintf(logger, "read\n");
            fclose(logger);
            read_all(fill);
            fill->status = WRITE;
            logger = fopen("filler.log", "a");
            fprintf(logger, "end read\n");
            fclose(logger);
        }

        if (FD_ISSET(1, &wfds))
        {
            logger = fopen("filler.log", "a");
            fprintf(logger, "write\n");
            fclose(logger);
            tupik(fill);
            logger = fopen("filler.log", "a");
            fprintf(logger, "end write\n");
            fclose(logger);
            free_struct(fill);
        }
    }
}

int         main()
{
	t_fill  *fill;

	fill = (t_fill *)malloc(sizeof(t_fill));
    fill->status = READ;
    read_input1(fill);
//    read_all(fill);
//    tupik(fill);
    //    find_near_enemy(fill);
    return (0);
}
