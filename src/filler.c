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
    int     r;
    int     c;

    r = -1;
    while (++r < fill->e_h)
    {
        c = -1;
        while (++c < fill->e_w)
        {
            if (fill->elem[r][c] != '.' && fill->map[i + r][j + c] != '.')
                return (0);
        }
    }
    return (1);
}

int         check_touch(t_fill *fill, int i, int j)
{
    int     r;
    int     c;

    r = -1;
    while (fill->elem[++r])
    {
        c = -1;
        while (fill->elem[r][++c])
        {
            if (i == 0 && r == 0)
            {
                if (fill->elem[r][c] != '.' &&
               (fill->map[i + r][j + c] == fill->my_symb ||
                fill->map[i + r + 1][j + c] == fill->my_symb ||
                fill->map[i + r][j + c - 1] == fill->my_symb ||
                fill->map[i + r][j + c + 1] == fill->my_symb))
                return (1);
            }
            else if (j == 0 && c == 0)
            {
                if (fill->elem[r][c] != '.' &&
               (fill->map[i + r - 1][j + c] == fill->my_symb ||
                fill->map[i + r + 1][j + c] == fill->my_symb ||
                fill->map[i + r][j + c] == fill->my_symb ||
                fill->map[i + r][j + c + 1] == fill->my_symb))
                return (1);
            }

            else
            if (fill->elem[r][c] != '.' &&
               (fill->map[i + r - 1][j + c] == fill->my_symb ||
                fill->map[i + r + 1][j + c] == fill->my_symb ||
                fill->map[i + r][j + c - 1] == fill->my_symb ||
                fill->map[i + r][j + c + 1] == fill->my_symb))
                return (1);
        }
    }
    return (0);
}

void        tupik(t_fill *fill)
{

    int     i;
    int     j;

    i = -1;
    while (++i < (fill->m_h - fill->e_h))
    {
        j = -1;
        while (++j < (fill->m_w - fill->e_w))
        {
            if (check_pos(fill, i, j) && check_touch(fill, i, j))
            {
                dprintf(1, "%d %d ", i, j);
                fill->status = READ;
                return ;
            }
        }
    }
}

void        free_struct(t_fill *fill)
{
    int     i;

    i  = -1;
    if (fill->map)
        while (++i < fill->m_h)
            free(fill->map[i]);
        free(fill->map);

    i = -1;
    if (fill->elem)
        while (++i < fill->e_h)
            free(fill->elem[i]);
        free(fill->elem);
    //
    // if (fill->my_symb)
    //     fill->my_symb = NULL;
}

void        read_input(t_fill *fill)
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
            read_all(fill);
            fill->status = WRITE;
        }

        if (FD_ISSET(1, &wfds))
        {
            tupik(fill);
            free_struct(fill);
        }
    }
}

int         main()
{
	t_fill  *fill;

	fill = (t_fill *)malloc(sizeof(t_fill));
    fill->status = READ;
    read_input(fill);
//    read_all(fill);
//    tupik(fill);
    //    find_near_enemy(fill);
    return (0);
}
