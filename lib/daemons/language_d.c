/* See /help/wiz/language_d for some explanations */
mapping dicts;

static void restore_me(void) {
   unguarded("restore_object", "/daemons/data/language_d.o");
}

static void save_me(void) {
   unguarded("save_object", "/daemons/data/language_d.o");
}

string make_word(int size) {
    int x, t;
    string word, letters;

    word = "";
    letters = "abcdefghijklmnopqurstuvwxyz";

    for(x=0; x<size; x++) {
       t = random(strlen(letters));
       word += letters[t];
    }
    return word;
}

string *query_languages(void) {
   string *langs, *files;
   string name;
   object obj;
   int i, x;

   files = get_dir(RACE_DIR + "/*.c")[0];
   langs = ( { } );

   for(i=sizeof(files) - 1; i>=0; i--) {
      x = strlen(files[i]) - 3;
      obj = find_object(RACE_DIR + "/" + files[i][0..x]);

      if (obj) {
         name = obj->query_language();
      } 

      if (!name || name == "") {
         name = "english";
      }

      if (member_array(name, langs) == -1) {
         langs += ({ name });
      }
   }
   return langs;
}

int valid_language(string str) {
   string *langs;
   object usr;

   langs = query_languages();

   if (member_array(str, langs) > -1) {
      return 1;
   }

   return 0;
}

void create(void) {
   string str, *langs;
   int i, x;

   langs = query_languages();
   dicts = ([]);
   x = sizeof(langs) - 1;

   for(i=x; i >= 0; i--) {
      str = make_word(5);
      dicts[langs[x]] = ([ "bingo" : str ]);
   }
   restore_me();
}

string random_word(string race) {
   int num_words;	/* Number of catfolk words in the 'english word' */
   int k;
   string words;	/*What's gonna be returned */

   if (race == "catfolk") {
      words = "";
      num_words = random(3) + 1;
      for (k = 0; k < num_words; k++) {
	 switch (random(15) + 1) {
	       /* Feel free to add more stuff here */
	    case 1:
	       words += "meow ";
	       break;
	    case 2:
	       words += "hiss ";
	       break;
	    case 3:
	       words += "purr ";
	       break;
	    case 4:
	       words += "weow ";
	       break;
	    case 5:
	       words += "s'fel ";
	       break;
	    case 6:
	       words += "m'naf ";
	       break;
	    case 7:
	       words += "myau ";
	       break;
	    case 8:
	       words += "myaw ";
	       break;
	    case 9:
	       words += "nyee ";
	       break;
	    case 10:
	       words += "rakas ";
	       break;
	    case 11:
	       words += "krss ";
	       break;
	    case 12:
	       words += "rrr";	/*I know these two lack spaces */
	       break;
	    case 13:
	       words += "ssss";	/*It's supposed to be that way */
	       break;
	    case 14:
	       words += "clsss ";
	       break;
	    case 15:
	       words += "mn ";
	       break;
	 }
      }

      words[strlen(words) - 1] = 0;	/*Strip the trailing space */
      return words;
   } else if (race == "dwarf") {
      /* Make code for returning a random Norwegian word here */
      return race;
   } else {
      return make_word(8);
   }
}

string add_racial(string language, string englishword) {
   string transword;

   englishword = lowercase(englishword);
   if (!(dicts[language][englishword])) {
      transword = random_word(language);
      dicts[language] += ([englishword:transword]);
      return transword;
   }
}

/* This here is the main function. It must be called for each word to be
  translated. If the word doesn't exist in the dictionary, then it will
  add it, then return the translation.
*/
string english_to_racial(string language, string arg) {
   string englishword;
   englishword = lowercase(arg);
   if (member_map(englishword, dicts[language])) {
	 return dicts[language][englishword];
   }
   return add_racial(language, englishword);
}

int language_has_dictionary(string language) {
	return mappingp(dicts) && mappingp(dicts[language]);
}
