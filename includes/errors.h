/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:01:11 by mitadic           #+#    #+#             */
/*   Updated: 2024/10/09 13:09:56 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define OK 0
# define KO 1

# define BOOL_YES 1
# define BOOL_NO 0

# define PRINTUSAGE "Usage: ./cub3d *.cub"

# define MALLOCFAIL "Malloc fail"

# define TEXTLOADFAIL "Could not load at least 1 texture"
# define BADTXTPATH "Bad filepath, loading up of texture failed"
# define NOTSQUARE "At least one XPM texture not square shaped"

# define CANTOPEN "Error opening *.cub file"
# define CANTCLOSE "Error closing *.cub file"
# define BADSUFF "Program requires < *.cub > files as arguments"
# define BADDOTCUB "The .cub file does not allow meaningful value extraction"
# define GNLFAIL "get_next_line returned no line"
# define NOCEILING "Missing RGB values for the ceiling"
# define NOFLOOR "Missing RGB values for the floor"
# define NOTXT "Missing textures. Specify 4."
# define EXTRAINFO "Found unexpected pieces of data in .cub, keep it (c)lean"
# define BADSPEC "Unexpected specification in *.cub file"
# define ALREADYSTORED "Too many instances of a single wall direction"
# define NOTTWOCOMMAS "Expected 2x ',' separating the RGB"
# define NOTTHREE_RGB "Bad number of values for [R,G,B]"
# define ALREADYINIT_RGB "Too many instances of F or C specification"
# define NONDIGIT "Non-digits found in one of [R,G,B]"
# define RGBTOOLONG "String suspiciously long for one of [R,G,B]"
# define MALLOCFAIL_GB "Malloc fail while extracting [G,B] of [R,G,B]"
# define MALLOCFAIL_R "Malloc fail while extracting [R] of [R,G,B]"
# define MALLOCFAIL_RGB "Malloc fail while extracting [R,G,B]"
# define GENERICBAD_RGB "Illegal specifications within [R,G,B]"

# define MAPTOOTINY "Map not spatious enough to render meaningfully"
# define ILLEGAL "Map file contains invalid symbols"

# define LEAKYMAP "Map not walled off"
# define AIRPOCKETS "Map contains unreachable areas"
# define UNRENDERABLE "Map contains unrenderable tiles, these don't work: \n" \
"11111  11111\n" \
"10 01  1000 \n" \
"11111  11111"
# define DIRTYBOTTOM "Artefacts found beyond map's southern end"

# define NOPL "Player position and orientation not specified"
# define TOOMANYPL "Conflicting player positions and orientations"

#endif