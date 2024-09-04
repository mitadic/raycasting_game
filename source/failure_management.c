#include "../includes/cub3d.h"

/*
The idea behind the failure management design is to be able to print
the error as soon as encountered. To achieve that, the spectrum of different
protocols lends us control over when we're printing an error and returning
vs. printing an error, freeing and exiting, vs. just freeing and exiting.
*/

/* print err_msg and return the passthrough return_value. Space-saving */
int error(char* err_msg, int return_value)
{
    printf("Error:\n");
	printf("%s\n", err_msg);
	return (return_value);
}

/* purge(), then exit(); */
void    bail(t_data *data, int exit_status)
{
    purge(data);
    exit(exit_status);
}

/* print err_msg, then purge(), then exit(); */
void    error_and_bail(t_data *data, char *err_msg, int exit_status)
{
    printf("Error:\n");
    printf("%s\n", err_msg);
    purge(data);
    exit(exit_status);
}