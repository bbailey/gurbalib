#include <privileges.h>

#define AUTH_DATA_DIR "/sys/daemons/data/users"

string name;
string password;
int    priv;

static void secure() {
   if (previous_program(1) != USER_D && !require_priv("system")) {
      error("Access denied.");
   }
}

static void save_me() {
   if (name != "guest") {
      unguarded("save_object", AUTH_DATA_DIR + "/" + name + ".o");
   }
}

int load(string str) {
   string file;

   secure();

   file = AUTH_DATA_DIR + "/" + str + ".o";

   priv = 0;
   name = password = nil;

   return unguarded("restore_object", file);
}

int test(string user, string str) {
   secure();

   if (hash_string("SHA1", str, user) == password) return 1;
   return (hash_string("crypt", str, "gurba") == password);
}

void set_name(string str) {
   secure();

   name = str;
}

void set_pass(string user, string str) {
   secure();

   password = hash_string("SHA1", str, user);
   save_me();
}

void set_priv(int i) {
   secure();

   priv = i;
   save_me();
}

int query_priv() {
   return priv;
}
