/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:01:11 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/07 15:21:34 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define OK 0
# define KO 1

# define BOOL_YES 1
# define BOOL_NO 0

# define PRINTUSAGE "Usage: ./cub3d map.cub"

# define MALLOCFAIL "Malloc fail"

# define TEXTLOADFAIL "Could not load texture"
# define NOTSQUARE "XPM image not square shaped"

# define CANTOPEN "Error opening map file"
# define CANTCLOSE "Error closing map file"
# define BADSUFF "Program only accepts < *.cub > files as maps"
# define BADDOTCUB "The .cub file does not allow meaningful value extraction"
# define GNLFAIL "get_next_line returned no line"
# define NOCEILING "Missing RGB values for the ceiling"
# define NOFLOOR "Missing RGB values for the floor"
# define NOTXT "Missing textures. Specify 4."
# define EXTRAINFO "Found unexpected pieces of data in .cub, keep it (c)lean"

# define MAPTOOTINY "Map not spatious enough to render meaningfully"
# define ILLEGAL "Map file contains invalid symbols"

# define LEAKYMAP "Map not walled off"
# define AIRPOCKETS "Map contains unreachable areas"

# define NOPL "Player position and orientation not specified"
# define TOOMANYPL "Conflicting player positions and orientations"

#endif