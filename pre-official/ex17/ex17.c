// stdio - standard lib - i/o input output library
#include <stdio.h>
// assert - standard lib - tests and responds with diagnostic information
// on failure. for development.
#include <assert.h>
// stdlib - standard lib - addition of "general functionality"
#include <stdlib.h>
// errno - standard lib - defines an integer variable for use by system
// calls and some lib functions for reporting error codes
#include <errno.h>
// string - standard lib - for manipulating arrays of chars
#include <string.h>

// setting constants with define is apparently a reliable approach
#define MAX_DATA 512
#define MAX_ROWS 100

// define a struct with some fixed size
struct Address {
  int id;
  int set;
  char name[MAX_DATA]; // non dynamic so not space efficient, but
  char email[MAX_DATA]; // simple for reads and writes
};

// containing struct, also of fixed size
struct Database {
  struct Address rows[MAX_ROWS];
};

// links the db with a FILE struct
struct Connection {
  // FILE is a C std lib struct for file i/o stuff
  FILE *file;
  struct Database *db;
};

// forward declaration pls
void Database_close(struct Connection *conn);

// log and exit error handling funcion
void die(const char *message, struct Connection *conn)
{
  if(errno) { // ie unless errno is 0 (has not been set)
    // prints a preset message determines by the value of errno,
    // after a custom message
    perror(message);
  } else {
    // so if errno wasn't set, we default here instead
    printf("ERROR: %s\n", message);
  }

  // CLOSE OUR SHIT
  // make sure you don't catch things with die in close, or we
  // get the old infinite call stack derpathon
  Database_close(conn);

  // exits and provides and error code (rather than 0, success code)
  // to the OS
  exit(1);
}

// custom print method for the address struct
void Address_print(struct Address *addr)
{
  printf("%d %s %s\n",
          // so remember this is just the syntax for accessing an
          // attribute of a struct
          addr->id, addr->name, addr->email);
}

// loads the db from the file into conn
void Database_load(struct Connection *conn)
{
  // 4 multifreading ur pogram
  // also, reads data from the given stream into the array pointed to in
  // the pointer that is the first arg
  // method signature: size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  // fread returns the number of read files (should be 1 here, and match nmemb generally)
  if(rc != 1) die("Failed to load database.", conn);
}

// "opens a connection" ie. allocates the memory required and returns
// the connection struct (with the db file name and mode)
struct Connection *Database_open(const char *filename, char mode)
{
  // get an empty struct of the right size
  struct Connection *conn = malloc(sizeof(struct Connection));
  if(!conn) die("Memory error", conn); // not sure how this would even happen

  // make the db attribute of conn be the right size (memory alloc)
  // for a Database struct
  conn->db = malloc(sizeof(struct Database));
  if(!conn->db) die("Memory error", conn); // maybe malloc can fail somehow?

  // have to split file opening method based on read/write,
  // mode c will 'create' ie write the file
  // otherwise we read+ (read & write) an existing file and load the contents
  if(mode =='c') {
    // fopen opens a file and returns a FILE struct
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if(conn->file) {
      Database_load(conn);
    }
  }

  if(!conn->file) die("Failed to open the file", conn);

  return conn;
}

// closes the file if open, frees up the memory in
// the various structs and their attrs
void Database_close(struct Connection *conn)
{
  if(conn) {
    if(conn->file) fclose(conn->file);
    if(conn->db) free(conn->db);
    free(conn);
  }
}

// writes the database to the file
void Database_write(struct Connection *conn)
{
  // takes the file position pointer to the beginning of the stream
  rewind(conn->file);

  // the inverse of fread, though the method sig is the same, takes
  // the contents of the array at the pointer addr and writes it to
  // the file stream
  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if(rc != 1) die("Failed to write database.", conn);

  // fflush "flushes the output buffer of a (file?) stream. I guess
  // this must be important to remove it from memory?
  // returns 0 on success
  rc = fflush(conn->file);
  if(rc == -1) die("Cannot flush database.", conn);
}

// fills the conn's db's rows with Addresses that have content equal
// to the id, but only all 0s apart from that in each attr
// this will create a bunch of placeholder structs basically
// I guess it's easier to do this and then when you go to write or
// whatever you can rely on an initialized (in memory) struct with
// the right attrs and everything already being there, rather than
// having to check if it exists and try and create if it doesn't,
// or just update etc etc
void Database_create(struct Connection *conn)
{
  int i = 0;

  for(i = 0; i < MAX_ROWS; i++) {
    // make a prototype to initialize it
    struct Address addr = {.id = i, .set = 0};
    // then just assign it
    conn->db->rows[i] = addr;
  }
}

// writes an address, though note this is not an update, if the address is written
// already then it fails. takes the connection struct we are passing around and
// the id of the addr, with the name and email to set
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  // pointer to the addr in the row we want
  struct Address *addr = &conn->db->rows[id];
  if(addr->set) die("Already set delete it first", conn);

  // the addr is now considered "set" right.. this is a C bool basically?
  addr->set = 1;
  //ZED WARNING: bug, read the "How To Break It" and fix this
  // looks like this will attempt to copy the name arg into addr->name
  // better check what is wrong with strncpy that makes this risky
  // OK so looks like it copies up to MAX_DATA here, (3 arg) BUT what
  // if the name is longer, then we don't end the string with that '\0'
  // nul byte business, which we need to indicate the end of the char ary
  // HMM so to make this safe, what do we do? append a nul byte on the end?
  // or just make the last char a nul byte and maybe lose some data?
  // AH yes this last idea is Zed's recommendation
  char *res = strncpy(addr->name, name, MAX_DATA);
  res[MAX_DATA - 1] = '\0'; // this is my line to make the strncpy safe for >512 bytes
  //ZED demonstrate the strncpy bug
  if(!res) die("Name copy failed", conn);

  res = strncpy(addr->email, email, MAX_DATA);
  res[MAX_DATA - 1] = '\0'; // this is my line to make the strncpy safe for >512 bytes
  if(!res) die("Email copy failed", conn);
}

// read the contents of the addr in the specified row by id
// if set, otherwise die
void Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if(addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set", conn);
  }
}

//  just overwrite (reassign over the top of the memory) into
//  the specified id with the blank placeholder addr
void Database_delete(struct Connection *conn, int id)
{
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

// goes through every row in the db and prints addrs that are
// set
void Database_list(struct Connection *conn)
{
  int i = 0;
  struct Database *db = conn->db;

  for(i = 0; i < MAX_ROWS; i++) {
    struct Address *cur = &db->rows[i];

    if(cur->set) {
      Address_print(cur);
    }
  }
}

void Database_find(struct Connection *conn, char *name)
{
  struct Database *db = conn->db;

  for(int i = 0; i < MAX_ROWS; i++) {
    struct Address *dis_one = &db->rows[i];

    if(!strcmp(dis_one->name, name)) {
      Address_print(dis_one);
      return;
    }
  }
  die("Record with that name not found yo", conn);
}

// fork from the number of args and the case to either fail or
// attempt the db command
int main(int argc, char *argv[])
{
  if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

  // initializes from cli args specifying the db file, action, params
  char *filename = argv[1];
  char action = argv[2][0];
  // this pointer for conn will be passed around containing reference
  // to everything, pretty magical c pointer stuff, this
  struct Connection *conn = Database_open(filename, action);
  char *name;
  int id;

  // atoi is string to int - not quite sure why a? a for alpha maybe?
  // anyhow this is just .to_i
  // TRY CHECKING what typecasting with (int) would do?
  // answer: bad things
  if(action == 'f') {
    name = argv[3];
  } else {
    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.", conn);
  }

  // wat u wan bb?
  switch(action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 'g':
      if(argc != 4) die("Need an id to get", conn);

      Database_get(conn, id);
      break;

    case 's':
      if(argc != 6) die("Need id, name, email to set", conn);

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'd':
      if(argc != 4) die("Need id to delete", conn);

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;

    case 'f':
      if(argc != 4) die("Need name to find record", conn);

      Database_find(conn, name);
      break;

    default:
      die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
  }

  Database_close(conn);

  return 0;
}
