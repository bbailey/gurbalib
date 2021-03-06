inherit M_COMMAND;

#include <status.h>

void usage(void) {
   string *lines;

   lines = ({ "Usage: title [-h] [string]" });
   lines += ({ " " });
   lines += ({ "Title allows you to set your title to string." });
   lines += ({ "You can use $N as a variable for your username." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Example:" });
   lines += ({ "\ttitle %N is the coolest kid on the block!" });
   lines += ({ "See also:" });
   lines += ({ "\tgender" });

   this_player()->more(lines);
}

static void main(string str) {

   if (empty_str(str)) {
      write("Your current title is: " + this_player()->query_title_string() +
	 "\n");
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   this_player()->set_title(str);
   out("New title: " + this_player()->query_title() + "\n");
}
