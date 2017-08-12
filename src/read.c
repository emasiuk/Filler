#include "my_filler.h"

void add(t_str *ptr, char* str) {
  int size = strlen(str);

  for(int i = 0; i < size; i++)
    ptr->str[ptr->size + i] = str[i];

  ptr->size += size;
  ptr->str[ptr->size] = 0;
}

t_str           *string_init()
{
    t_str       *s;
    s = (t_str*)malloc(sizeof(t_str));
    s->str = NULL;
    s->size = s->limit = 0;

    return s;
}

t_str           *string_create(char* str)
{
    t_str       *s;
    int         size;
    int         k;

    size = ft_strlen(str);
    k = size / BUFF_SIZE + 1;

    s = string_init();
    s->str = (char*) malloc (k * BUFF_SIZE * sizeof(char));

    strcpy(s->str, str);
    s->size = size;
    s->limit = k * BUFF_SIZE;

    return s;
}

void            string_append(t_str *ptr, char* str)
{
    int         size;

    if(!ptr)
        ptr = string_create(str);
    else {
        size = ft_strlen(str);

        if(ptr->size + size >= ptr->limit) {
            ptr->str = (char*) realloc (ptr->str, ptr->limit +  BUFF_SIZE);
            ptr->limit +=  BUFF_SIZE;
            ptr->str[ptr->size + size] = '\0';
        }
        add(ptr, str);
    }
}


int         find_size(char *dist, char *source, int start)
{
  int       end;

  end = start;
  while(source[end] != '\n')
    end++;

  strncpy(dist, source + start, end - start);
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

  memset(left, '\0', size);
  memset(right, '\0', size);

  for(i = 0; i < size && line[i] != ' '; i++);

  left = strncpy(left, line, i);
  right = strcpy(right, line + i + 1);
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
    FILE    *logger;

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
//    printf("pos = %d\n", pos);
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
    memset(str, '\0', 32);
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
    // int i = -1;
    FILE *logger;
    read_input(fill);

    if (read_is_fin(fill->string, fill))
        parse_all(fill->string->str, fill);
    else
    {
        logger = fopen("filler.log", "a");
        fprintf(logger, "not read\n");
        fclose(logger);
    }
    // while (++i < fill->m_h)
    // {
    // }
    // i = -1;
    // while (++i < fill->e_h)
    // {
    //     logger = fopen("filler.log", "a");
    //     fprintf(logger, "%s\n", fill->elem[i]);
    //     fclose(logger);
    // }
}
