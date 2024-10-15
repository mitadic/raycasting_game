/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:35 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/15 01:58:50 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
The idea behind the failure management design is to be able to print
the error as soon as encountered. To achieve that, the spectrum of different
protocols lends us control over when we're printing an error and returning
vs. printing an error, freeing and exiting, vs. just freeing and exiting.
*/

/* The void returnable */
void	put_err_msg(char *err_msg)
{
	ft_putstr_fd("Error:\n", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/* print err_msg and return the passthrough return_value. Space-saving */
int	error(char *err_msg, int return_value)
{
	put_err_msg(err_msg);
	return (return_value);
}

/* purge(), then exit(); */
void	bail(t_data *data, int exit_status)
{
	purge(data);
	exit(exit_status);
}

/* print err_msg, then purge(), then exit(); */
void	error_and_bail(t_data *data, char *err_msg, int exit_status)
{
	put_err_msg(err_msg);
	purge(data);
	exit(exit_status);
}
