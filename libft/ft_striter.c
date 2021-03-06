/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:19:28 by emasiuk           #+#    #+#             */
/*   Updated: 2016/11/28 20:19:29 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char*))
{
	int i;

	if (s[0] == '\0' || !(f))
		return ;
	i = -1;
	while (s[++i])
		f(&s[i]);
}
