#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // handle args (with -o)
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-o") == 0)) {
      printf("USAGE: logfind [-o] <words> <to> <find>\n");
      printf("       Note that default search is AND, -o uses OR\n");
    }

    // check ~/.logfile for list
    // permit glob

    // scan the files
    // output the filename being searched
    // FIRST PASS: check the file has the words with AND/OR
    // if false, keep going
    // as soon as true, bail on FIRST PASS and start...
    // SECOND PASS: output each line found, decorated
    // output summary for file (instances, lines)
    // output overall summary (instances, lines, files)
}
