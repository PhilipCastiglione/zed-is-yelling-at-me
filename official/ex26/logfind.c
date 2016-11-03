#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

#include "dbg.h"

#define PATH_MAX 255

int main(int argc, char *argv[])
{
    // define terms pointer early so it is initialized in all cases
    char **terms = NULL;

    // validate input
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-o") == 0) || argc > 11) {
        printf("USAGE: logfind [-o] <words> <to> <find>\n");
        printf("       Note that default search is AND, -o uses OR\n");
        printf("       Max args to find is 10\n");
        sentinel("Bad cli usage.");
    }

    // initialize terms, terms_c and or
    const int or = (strcmp(argv[1], "-o") == 0) ? 1 : 0;
    const int start = or + 1;
    const int terms_c = argc - start;
    terms = malloc(sizeof(char*) * (argc - start));
    for (int i = 0; i < terms_c; i++)
    {
        terms[i] = argv[i + start];
    }

    // setup home_dir and filename of the logfile
    char *home_dir = getenv("HOME");
    if (home_dir == NULL)
    {
        home_dir = getpwuid(getuid())->pw_dir;
    }
    check(home_dir != NULL, "Failed reading home directory for current user.");
    char logfile_path[PATH_MAX];
    strncpy(logfile_path, home_dir, PATH_MAX - 10);
    strcat(logfile_path, "/.logfile");

    // read in ~/.logfile
    FILE *logfile = fopen(logfile_path, "r");
    check(logfile != NULL, "Couldn't open ~/.logfile.");

    // get the number of log_dirs
    int log_dir_c = 0;
    int line_length = 0;
    char ch;
    while (!feof(logfile) && !ferror(logfile))
    {
        ch = fgetc(logfile);
        line_length++;
        check(line_length < PATH_MAX,
              "Cannot use paths of more than %d characters", PATH_MAX);
        if (ch == '\n')
        {
            log_dir_c++;
        }
    }
    rewind(logfile);

    // read the log_dirs into memory
    char **log_dirs = malloc(sizeof(char *) * log_dir_c);
    int rc;
    for (int i = 0; i < log_dir_c; i++)
    {
        log_dirs[i] = malloc(sizeof(char) * PATH_MAX);
        rc = fscanf(logfile, "%s\n", log_dirs[i]);
        check(rc != 0, "Failed reading logfile line %d.\n", i);
        check(strcmp(log_dirs[i], "") != 0, "Logfile line %d is empty.\n", i);
    }

    for (int i = 0; i < log_dir_c; i++)
    {
        printf("%s\n", log_dirs[i]);
    }

    // TODO: permit glob

    // scan the files
    // output the filename being searched
    // FIRST PASS: check the file has the words with AND/OR
    // if false, keep going
    // as soon as true, bail on FIRST PASS and start...
    // SECOND PASS: output each line found, decorated
    // output summary for file (instances, lines)
    // output overall summary (instances, lines, files)

    // cleanup
    // TODO
    free(terms);

    return 0;

error:
    // cleanup
    // TODO
    if (terms)
    {
        free(terms);
    }

    return -1;
}
