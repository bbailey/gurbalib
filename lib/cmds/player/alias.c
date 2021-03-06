inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: alias [-h] [ALIAS COMMAND]" });
   lines += ({ "" });
   lines += ({ "Allows you to create an alias for a command." });
   lines += ({ "If no alias is given show a list of your current aliases." });
   lines += ({ "If no command is given delete the specified alias." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-r\tRemove the specified ALIAS." });
   lines += ({ "Examples:" });
   lines += ({ "\talias ga get all" });
   lines += ({ "\talias da drop all" });
   lines += ({ "\talias da" });
   lines += ({ "See also:" });
   lines += ({ "\tansi, chfn, clear, describe, ignore, passwd" });

   if (query_admin(this_player())) {
      lines += ({ "\tcmdadm, coloradm, rehash" });
   }

   this_player()->more(lines);
}

void show_aliases(void) {
   mapping alias;
   string *aliases, *lines;
   int i;

   alias = this_player()->query_aliases();
   aliases = map_indices(alias);

   lines = ({ "You have defined these aliases: " });
   if (sizeof(aliases) == 0) {
      lines += ({ "   You have no personal aliases defined." });
      lines += ALIAS_D->show_alias("", "");
      this_player()->more(lines);
      return;
   }

   lines = ({ "You have defined these aliases: " });
   for (i = 0; i < sizeof(aliases); i++) {
      lines += ({ "  " + aliases[i] + "='" + alias[aliases[i]] + "'" });
   }

   lines += ALIAS_D->show_alias("", "");
   this_player()->more(lines);
}

static void main(string str) {
   string cmd, arg;

   if (empty_str(str)) {
      show_aliases();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else {
      if (sscanf(str, "%s %s", cmd, arg) != 2) {
         /* Remove an alias */
         if (this_player()->is_alias(str)) {
            write("Alias '" + str + "' (" + 
                  this_player()->query_alias(str) + ") removed.");
            this_player()->remove_alias(str);
            return;
         }

         usage();
         return;
      }

      /* Check for invalid input */
      if ((cmd == " ") || (arg == " ") || (cmd == "") || (arg == "")) {
         usage();
         return;
      }

      this_player()->add_alias(cmd, arg);
      write("Alias '" + cmd + "' (" + arg + ") added.");
   }
}
