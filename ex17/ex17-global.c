#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100



struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

struct Connection *glob_conn;

void Database_close();

void die(const char *message)
{
  if(errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  Database_close();

  exit(1);
}

void Address_print(struct Address *addr)
{
  printf("%d %s %s\n",
          addr->id, addr->name, addr->email);
}

void Database_load()
{
  int rc = fread(glob_conn->db, sizeof(struct Database), 1, glob_conn->file);
  if(rc != 1) die("Failed to load database.");
}

void Database_open(const char *filename, char mode)
{
  glob_conn = malloc(sizeof(struct Connection));
  if(!glob_conn) die("Memory error");

  glob_conn->db = malloc(sizeof(struct Database));
  if(!glob_conn->db) die("Memory error");

  if(mode =='c') {
    glob_conn->file = fopen(filename, "w");
  } else {
    glob_conn->file = fopen(filename, "r+");

    if(glob_conn->file) {
      Database_load();
    }
  }

  if(!glob_conn->file) die("Failed to open the file");
}

void Database_close()
{
  if(glob_conn) {
    if(glob_conn->file) fclose(glob_conn->file);
    if(glob_conn->db) free(glob_conn->db);
    free(glob_conn);
  }
}

void Database_write()
{
  rewind(glob_conn->file);

  int rc = fwrite(glob_conn->db, sizeof(struct Database), 1, glob_conn->file);
  if(rc != 1) die("Failed to write database.");

  rc = fflush(glob_conn->file);
  if(rc == -1) die("Cannot flush database.");
}

void Database_create()
{
  int i = 0;

  for(i = 0; i < MAX_ROWS; i++) {
    struct Address addr = {.id = i, .set = 0};
    glob_conn->db->rows[i] = addr;
  }
}

void Database_set(int id, const char *name, const char *email)
{
  struct Address *addr = &glob_conn->db->rows[id];
  if(addr->set) die("Already set delete it first");

  addr->set = 1;
  char *res = strncpy(addr->name, name, MAX_DATA);
  res[MAX_DATA - 1] = '\0';
  if(!res) die("Name copy failed");

  res = strncpy(addr->email, email, MAX_DATA);
  res[MAX_DATA - 1] = '\0';
  if(!res) die("Email copy failed");
}

void Database_get(int id)
{
  struct Address *addr = &glob_conn->db->rows[id];

  if(addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set");
  }
}

void Database_delete(int id)
{
  struct Address addr = {.id = id, .set = 0};
  glob_conn->db->rows[id] = addr;
}

void Database_list()
{
  int i = 0;
  struct Database *db = glob_conn->db;

  for(i = 0; i < MAX_ROWS; i++) {
    struct Address *cur = &db->rows[i];

    if(cur->set) {
      Address_print(cur);
    }
  }
}

void Database_find(char *name)
{
  struct Database *db = glob_conn->db;

  for(int i = 0; i < MAX_ROWS; i++) {
    struct Address *dis_one = &db->rows[i];

    if(!strcmp(dis_one->name, name)) {
      Address_print(dis_one);
      return;
    }
  }
  die("Record with that name not found yo");
}

int main(int argc, char *argv[])
{
  if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

  char *filename = argv[1];
  char action = argv[2][0];
  Database_open(filename, action);
  char *name;
  int id;

  if(action == 'f') {
    name = argv[3];
  } else {
    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");
  }

  switch(action) {
    case 'c':
      Database_create();
      Database_write();
      break;

    case 'g':
      if(argc != 4) die("Need an id to get");

      Database_get(id);
      break;

    case 's':
      if(argc != 6) die("Need id, name, email to set");

      Database_set(id, argv[4], argv[5]);
      Database_write();
      break;

    case 'd':
      if(argc != 4) die("Need id to delete");

      Database_delete(id);
      Database_write();
      break;

    case 'l':
      Database_list();
      break;

    case 'f':
      if(argc != 4) die("Need name to find record");

      Database_find(name);
      break;

    default:
      die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
  }

  Database_close();

  return 0;
}
