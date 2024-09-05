/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:01:11 by mitadic           #+#    #+#             */
/*   Updated: 2024/09/05 14:01:13 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define OK 0
# define KO 1

# define PRINTUSAGE "Usage: ./cub3d map.cub"

# define MALLOCFAIL "Malloc fail"

# define CANTOPEN "Error opening map file"
# define CANTCLOSE "Error closing map file"
# define BADSUFF "Program only accepts < *.cub > files as maps"
# define BADMAP "The map does not allow meaningful rendering"

# define MAPTOOTINY "Map not spatious enough to render meaningfully"
# define ILLEGAL "Map file contains invalid symbols"

# define LEAKYMAP "Map not walled off"
# define AIRPOCKETS "Map contains unreachable areas"

# define NOPL "Player position and orientation not specified"
# define TOOMANYPL "Conflicting player positions and orientations"

#endif