#include "my_filler.h"

void	find_size_map(char *str, t_fill *fill)
{
    char **tmp;
    int i;

    i = -1;
    tmp = ft_strsplit(str, ' ');
    fill->m_h = ft_atoi(tmp[0]);
    fill->m_w = ft_atoi(tmp[1]);
     while (tmp[++i] != NULL)
        free(tmp[i]);
     free(tmp);
}

void    find_size_elem(char *str, t_fill *fill)
{
    char **tmp;
    int i;

    i = -1;
    tmp = ft_strsplit(str, ' ');
    fill->e_h = ft_atoi(tmp[0]);
    fill->e_w = ft_atoi(tmp[1]);
    while (tmp[++i] != NULL)
       free(tmp[i]);
    free(tmp);
}

void	mem_for_map(t_fill *fill)
{
	int		i;

	i = -1;
	if (!(fill->map = (char**)malloc(sizeof(char*) * (fill->m_h))))
		return ;
	while (++i < fill->m_w)
		if (!(fill->map[i] = (char*)malloc(sizeof(char) * (fill->m_w))))
			return ;
}

void	mem_for_piece(t_fill *fill)
{
	int		i;

	if (!(fill->elem = (char**)malloc(sizeof(char*) * (fill->e_h + 1))))
		return ;
	fill->elem[fill->e_h] = 0;
	i = -1;
	while (++i < fill->e_h)
	{
		if (!(fill->elem[i] = (char*)malloc(sizeof(char) * (fill->e_w + 1))))
			return ;
		fill->elem[i][fill->e_w] = '\0';
	}
}

void	read_map(t_fill *fill, char *str)
{
	int		i;
	int		j;
    FILE    *logger;

    logger = fopen("filler.log", "a");
    fprintf(logger, "%s\n", str);
    fclose(logger);
	find_size_map(str,fill);
	free(str);
	mem_for_map(fill);
	i = -1;
	while (++i < fill->m_h)
	{
		get_next_line(0, &str);
        logger = fopen("filler.log", "a");
        fprintf(logger, "%s\n", str);
        fclose(logger);
        j = -1;
		while (++j < fill->m_w)
			fill->map[i][j] = str[j];
        fill->map[i][j] = '\0';
		free(str);
	}
}

void	read_piece(t_fill *fill, char *str)
{
	int		i;
    FILE *logger;

	find_size_elem(str, fill);
    logger = fopen("filler.log", "a");
    fprintf(logger, "%s\n", str);
    fclose(logger);
	free(str);
	mem_for_piece(fill);
	i = -1;
	while (++i < fill->e_h)
	{
		get_next_line(0, &str);
        logger = fopen("filler.log", "a");
        fprintf(logger, "%s\n", str);
        fclose(logger);;
		ft_strcpy(fill->elem[i], str);
		free(str);
	}
}

void	read_all(t_fill *fill)
{
    char    *str;

    (get_next_line(0, &str)) ? fill->my_symb = str[0] : 0;
    free(str);
    (get_next_line(0, &str) > 0) ? read_map(fill, str) : 0;
    (get_next_line(0, &str) > 0) ? read_piece(fill, str) : 0;
    // int i;

    // i = -1;
    // printf("my_symb = %c\n", fill->my_symb);
    // printf("MAP\n");
    // while (++i < fill->m_h)
    //     printf("%s\n", fill->map[i]);
    // i = -1;
    // printf("ELEM\n");
    // while (++i < fill->e_h)
    //     printf("%s\n", fill->elem[i]);

}
