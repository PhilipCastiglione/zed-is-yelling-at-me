#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dbg.h"

int main(int argc, char *argv[])
{
    // define terms pointer early so it it initialized in all cases
    char **terms = NULL;

    // handle args (with -o)
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-o") == 0) || argc > 11) {
        printf("USAGE: logfind [-o] <words> <to> <find>\n");
        printf("       Note that default search is AND, -o uses OR\n");
        printf("       Max args to find is 10\n");
        sentinel("Bad cli usage.");
    }

    // initialize terms, terms_c and or
    int or = (strcmp(argv[1], "-o") == 0) ? 1 : 0;
    int start = or + 1;
    int terms_c = argc - start;
    terms = malloc(sizeof(char*) * (argc - start));
    for (int i = 0; i < terms_c; i++)
    {
        terms[i] = argv[i + start];
    }


    // read ~/.logfile for list
    // read the file, bail with an error if not there
    // read in the tokens, bail if empty

    // permit glob

    // scan the files
    // output the filename being searched
    // FIRST PASS: check the file has the words with AND/OR
    // if false, keep going
    // as soon as true, bail on FIRST PASS and start...
    // SECOND PASS: output each line found, decorated
    // output summary for file (instances, lines)
    // output overall summary (instances, lines, files)

    // cleanup
    free(terms);

    return 0;

error:
    // cleanup
    if (terms)
    {
        free(terms);
    }

    return -1;
}
