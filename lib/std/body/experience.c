int experience;
int level;

void create( void ) {
}

int ready_for_next_level() {
   int tmpexp;

   tmpexp = level * level * 2000;

   if (experience > tmpexp) {
      return 1;
   }
   return 0;
}

string query_level_title(int level) {
   switch (level) {
      case 1:
	 return "the uninitiated.\n";
         break;
      case 2:
	 return "the newbie.\n";
         break;
      case 3:
	 return "is getting the hang of things.\n";
         break;
      case 4:
	 return "the mediocher.\n";
         break;
      case 5:
	 return "the adverage.\n";
         break;
      case 6:
	 return "the level 6.\n";
         break;
      case 7:
	 return "the level 7.\n";
         break;
      case 8:
	 return "the level 8.\n";
         break;
      case 9:
	 return "the level 9.\n";
         break;
      case 10:
	 return "the level 10.\n";
         break;
      case 11:
	 return "the level 11.\n";
         break;
      case 12:
	 return "the level 12.\n";
         break;
      case 13:
	 return "the level 13.\n";
         break;
      case 14:
	 return "the level 14.\n";
         break;
      case 15:
	 return "the level 15.\n";
         break;
      case 16:
	 return "the level 16.\n";
         break;
      case 17:
	 return "the level 17.\n";
         break;
      case 18:
	 return "the level 18.\n";
         break;
      case 19:
	 return "the Mighty";
         break;
      default:
	 return "the Grand Wizard";
         break;
   }
}

void increase_level() {
   level += 1;
   write("Congragulations, you just achieved level: " + level + "\n");
   this_player()->set_title(query_level_title(level));
}

void increase_expr( int expr ) {
   if(expr < 0 ) {
      expr = expr * -1;
   }
   experience += expr;
   if( experience < 0 ) {
      experience = 0;
   }
   if (ready_for_next_level()) {
	increase_level();
	write("Congragulations, you just went up a level...\n");
	level += 1;
   }
}

void decrease_expr( int expr ) {
   if(expr > 0 ) {
      expr = expr * -1;
   }
   experience -= expr;
   if( experience < 0 ) {
      experience = 0;
   }
}

void set_expr( int expr ) {
   experience = expr;
   if( experience < 0 ) {
      experience = 0;
   }
}

int query_expr( void ) {
  return( experience );
}

int query_level(void) {
   if (level < 1) level = 1;
   return( level );
}

