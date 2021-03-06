inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: eval [-h] STRING" });
   lines += ({ " " });
   lines += ({ "Evaluate the lpc code: STRING." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t.me  is shorthand for this_player()" });
   lines += ({ "\t.here  is shorthand for this_environment()" });
   lines += ({ "Examples:" });
   lines += ({ "\teval write(\"My hp: \" + this_player()->query_hp() + " +
      "\"\\n\");" });
   lines += ({ "\teval .here->tell_room(.me,\"Hi\\n\");" });
   lines += ({ "\teval return 5 + 5;" });
   lines += ({ "\teval write(\"Sirdude's HP: \" + \n" +
      "\t\tUSER_D->find_player(\"sirdude\")->query_hp() + \"\\n\");" });
   lines += ({ "See also" });

   if (query_admin(this_player())) {
      lines += ({ "\tcheck, checkmud, clean, clone, dest, graph, rebuild, " +
         "update, warmboot" });
   } else {
      lines += ({ "\tcheck, clean, clone, dest, graph, rebuild, " +
         "update" });
   }

   this_player()->more(lines);
}

static void main(string src) {
   object obj;
   string err;
   mixed result;
   int str_size;

   if (empty_str(src)) {
      usage();
      return;
   }

   if (src == "-h") {
      usage();
      return;
   }

   src = replace_string(src, ".me", "this_player()");
   src = replace_string(src, ".here", "this_environment()");
   str_size = strlen(src);
   if (str_size && (src[(str_size - 1)] != ';')) {
      src += ";";
   }
   rlimits(255;-1) {
      rlimits(255;2*MAX_TICKS) {
         err = catch(obj =
            compile_object("/wiz/" + this_player()->query_name() + "/obj/eval_ob",
	       "# include <float.h>\n# include <limits.h>\n" +
               "# include <status.h>\n# include <trace.h>\n" +
	       "# include <type.h>\n\n" +
	       "private mixed exec_fun(void) {\n" + "    mixed " +
	       "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;\n" +
	       src + "}\n" +
	       "mixed *exec(object player) {\n" +
	       "int ticks;\n" + "mixed returnval;\n" + 
	       "ticks = status()[ST_TICKS];\n" + "returnval = exec_fun();\n" +
	       "ticks = ticks - status()[ST_TICKS];\n" +
               "return ({ ticks, returnval });\n" + "}\n"), result =
            obj->exec(this_player()));
      }

      if (obj)
         destruct_object(obj);

      if (err) {
         write("Error: " + err + ".\n");
      } else {
         if (result[1] || intp(result[1])) {
	    write("Result: \n" + dump_value(result[1]) + "\n");
         } else {
	    write("Result: \n" + "<nil>" + "\n");
         }
         write("Ticks used: " + (string) result[0] + "\n");
      }
   }
}
