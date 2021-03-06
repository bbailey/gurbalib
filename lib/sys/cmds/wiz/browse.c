inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: browse [-h] [dir]" });
   lines += ({ " " });
   lines += ({ "An interactive way to look at files." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tbrowse void.c" });
   lines += ({ "\tbrowse " + DOMAINS_DIR + "/required/rooms" });
   lines += ({ "See also:" });
   lines += ({ "\tcat, cd, cp, diff, edit, indent, ls, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

static void main(string arg) {

   if (arg && sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   "/sys/obj/browser"->browse(arg);
}
