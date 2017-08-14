#include "../include/my_filler.h"

void add(t_str *ptr, char* str)
{
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
