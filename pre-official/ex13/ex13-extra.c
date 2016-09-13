#include <stdio.h>

int main(int argc, char *argv[])
{
  if(argc == 0 || argc > 5) {
    printf("ERROR: you have provided no, or too many arguments.\n");
    return 1;
  }

  for(int i = 1; i < argc; i++) {
    printf("word is: %s\n", argv[i]);

    for(int j = 0; argv[i][j] != '\0'; j++) {
      char l = argv[i][j];
      if (l < 97) {
        l += 32;
      }
        
      switch(l) {
        case 'a':
          printf("vowel %c has val: %d\n", l, l);
          break;

        case 'e':
          printf("vowel %c has val: %d\n", l, l);
          break;

        case 'i':
          printf("vowel %c has val: %d\n", l, l);
          break;

        case 'o':
          printf("vowel %c has val: %d\n", l, l);
          break;

        case 'u':
          printf("vowel %c has val: %d\n", l, l);
          break;

          // happy as larry
        //case 'a': // fallthrough
        //case 'e': // fallthrough
        //case 'i': // fallthrough
        //case 'o': // fallthrough
        //case 'u':
          //printf("vowel %c has val: %d\n", l, l);
          //break;

        default:
          printf("non-vowel letter %c has val: %d\n", l, l);
      }

      //if(l == 'a') {
        //printf("vowel %c has val: %d\n", l, l);
      //} else if(l =='e') {
        //printf("vowel %c has val: %d\n", l, l);
      //} else if(l =='i') {
        //printf("vowel %c has val: %d\n", l, l);
      //} else if(l =='o') {
        //printf("vowel %c has val: %d\n", l, l);
      //} else if(l =='u') {
        //printf("vowel %c has val: %d\n", l, l);
      //} else {
        //printf("non-vowel letter %c has val: %d\n", l, l);
      //}
      //if(l == 'a' ||
         //l == 'e' ||
         //l == 'i' ||
         //l == 'o' ||
         //l == 'u') {
        //printf("vowel %c has val: %d\n", l, l);
      //} else {
        //printf("non-vowel letter %c has val: %d\n", l, l);
      //}
    }
  }
  
  return 0;
}
