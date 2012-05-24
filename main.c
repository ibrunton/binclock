/*
 *        Project:  binclock
 *       Filename:  main.c
 *
 *    Description:  simple text-only binary clock
 *
 *        Version:  1.0
 *        Created:  2012-05-23 16:51
 *       Compiler:  gcc
 *
 *         Author:  Ian D Brunton (ib), iandbrunton@gmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char bc0;
char bc1;

void byte_to_binary (char*, int);
void print_version ();
void print_usage ();

int
main (int argc, char *argv[])
{
	bc0 = '0'; /* character to represent value "0" */
	bc1 = '1'; /* character to represent value "1" */
	char separator = ':'; /* separator character */

	int once = 0;

	time_t time_raw;
	struct tm *time_struct;

	char seconds [7];
	char minutes [7];
	char hours [7];

	/* get command-line options */
	int i;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == '0') {
			bc0 = argv[++i][0];
		} else if (argv[i][0] == '-' && argv[i][1] == '1') {
			bc1 = argv[++i][0];
		} else if (argv[i][0] == '-' && argv[i][1] == 's') {
			separator = argv[++i][0];
		} else if (argv[i][0] == '-' && argv[i][1] == 'o') {
			once = 1;
		} else if (argv[i][0] == '-' && argv[i][1] == 'v') {
			print_version ();
			return EXIT_SUCCESS;
		} else if (argv[i][0] == '-' && argv[i][1] == '?') {
			print_usage ();
			return EXIT_FAILURE;
		}
	}

	int count = 0;
	while (count < 1) {
		time (&time_raw);
		time_struct = localtime (&time_raw);

		byte_to_binary (seconds, time_struct->tm_sec);
		byte_to_binary (minutes, time_struct->tm_min);
		byte_to_binary (hours, time_struct->tm_hour);

		printf ("%s", hours);
		printf ("%c", separator);
		printf ("%s", minutes);
		printf ("%c", separator);
		printf ("%s", seconds);
		printf ("\n");

		count += once;
		if (count == 0) {
			sleep (1);
		}
	}

	return EXIT_SUCCESS;
}

/* This function modified from
http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
*/
void
byte_to_binary (char *b, int x)
{
	b[0] = '\0';

	int z;
	char *p = b;

	for (z = 64; z > 0; z >>= 1) {
		*p++ = (x & z) ? bc1 : bc0;
	}
}

void
print_version ()
{
	printf ("%s %s - a binary clock\n", APPNAME, VERSION);
}

void
print_usage ()
{
	printf ("%s [-0 char] [-1 char] [-s char] [-o]\n", APPNAME);
}
