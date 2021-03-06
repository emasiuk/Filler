#include "../include/my_filler.h"

int         find_size(char *dist, char *source, int start)
{
  int       end;

  end = start;
  while(source[end] != '\n')
    end++;

  ft_strncpy(dist, source + start, end - start);
  dist[end - start] = '\0';

  return end - 1;
}

void        parse_size(char *line, t_fill *fill, int flag)
{
    int       i;
    int       size;
    char      *left;
    char      *right;

    size = strlen(line);
    left = malloc(size);
    right = malloc(size);

    ft_memset(left, '\0', size);
    ft_memset(right, '\0', size);

    for(i = 0; i < size && line[i] != ' '; i++);

    left = ft_strncpy(left, line, i);
    right = ft_strcpy(right, line + i + 1);
    if (flag)
    {
        fill->e_h = ft_atoi(left);
        fill->e_w = ft_atoi(right);
    }
    else
    {
        fill->m_h = ft_atoi(left);
        fill->m_w = ft_atoi(right);
    }
    free(left);
    free(right);
}


int        read_is_fin(t_str *s,t_fill *fill)
{
    int     i;
    int     size;
    int     elem_pos;
    char    arr_elem_size[32];

    i = 0;
    elem_pos = -1;
    size = 1;

    while (i < s->size)
    {
        if (s->str[i] > '9' || s->str[i] < '0')
            i++;
        else if (size)
        {
            while (i <= s->size && s->str[i] != '\n')
                i++;
            i++;
            size = 0;
        }
        else
        {
            elem_pos = i;
            while (i <= s->size && s->str[i] != '\n' && s->str[i] != '\0')
                i++;
            if (s->str[i] != '\n')
                return (0);
            else
            {
                find_size(arr_elem_size, s->str, elem_pos);

                parse_size(arr_elem_size, fill, 1);
                if (s->size <= i + fill->e_h*(fill->e_w + 1))
                    return (0);
                else
                    return (1);
            }
        }
    }
    return (0);
}

void        read_input(t_fill *fill)
{
    char    str[BUFF_SIZE];
    int     r;
    FILE    *logger;

    r = 0;

    while (42)
    {
        memset(str, '\0', BUFF_SIZE);
        r = read(0, str, BUFF_SIZE - 1);

        if (!fill->string)
            fill->string = string_create(str);
        else
            string_append(fill->string, str);
        if (r <= 0)
        {
            if (fill->string->size < 200)
            {
                logger = fopen("filler.log", "a");
                fprintf(logger, "size = %d\n", fill->string->size);
                fprintf(logger, "string = %s\n", fill->string->str);
                fclose(logger);
            }
            break ;
        }
    }
}

void    mem_for_map(t_fill *fill)
{
    int     i;

    i = -1;
    if (!(fill->map = (char**)malloc(sizeof(char*) * (fill->m_h))))
        return ;
    while (++i < fill->m_w)
        if (!(fill->map[i] = (char*)malloc(sizeof(char) * (fill->m_w))))
            return ;
}

void    mem_for_elem(t_fill *fill)
{
    int     i;

    if (!(fill->elem = (char**)malloc(sizeof(char*) * (fill->e_h + 1))))
        return ;
    i = -1;
    while (++i < fill->e_h)
    {
        if (!(fill->elem[i] = (char*)malloc(sizeof(char) * (fill->e_w + 1))))
            return ;
        fill->elem[i][fill->e_w] = '\0';
    }
}

void        read_elem(t_fill *fill, char *string, int pos)
{
    FILE *logger;
    int     i;
    int     j;

    i = -1;
    mem_for_elem(fill);
    while (++i < fill->e_h)
    {
        j = -1;
        while (++j < fill->e_w)
        {
            fill->elem[i][j] = string[pos];
            pos++;
        }
        fill->elem[i][fill->e_w] = '\0';
        logger = fopen("filler.log", "a");
        fprintf(logger, "%s\n", fill->elem[i]);
        fclose(logger);
        pos++;
    }
}

void        read_map(t_fill *fill, char *string, int pos)
{
    FILE    *logger;
    int     i;
    int     j;

    mem_for_map(fill);
    i = -1;
    while (++i < fill->m_h)
    {
        j = -1;
        while (++j < fill->m_w)
            fill->map[i][j] = string[pos++];
        fill->map[i][fill->m_w] = '\0';
        logger = fopen("filler.log", "a");
        fprintf(logger, "%s\n", fill->map[i]);
        fclose(logger);
        pos++;
    }
}

void        parse_all(char *string, t_fill *fill)
{
    int pos;
    char str[32];

    pos = 2;
    fill->my_symb = string[0];
    ft_memset(str, '\0', 32);
    pos += find_size(str, string, pos);
    parse_size(str, fill, 0);
    read_map(fill, string, pos);

    pos += fill->m_h * (fill->m_w + 1);

    pos = find_size(str, string, pos) + 2;

    parse_size(str, fill, 1);
    read_elem(fill, string, pos);
}

void        read_all(t_fill *fill)
{
    read_input(fill);

    if (read_is_fin(fill->string, fill))
        parse_all(fill->string->str, fill);
    else
        read_all(fill);
}
