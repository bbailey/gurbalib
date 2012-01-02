#define COST 10

void usage() {
  write("Usage: cast cure [-h] TARGET\n");
  write("Casts cure light wounds on TARGET\n");
  write("This spell requires " + COST + " mana.\n");
  write("This spell heals 1-5 hit points on TARGET.\n");
  write("You need to have a certain skill level before " +
    "you can cast this spell on other players.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void cure(object thisp, object target) {
  int x;

  x = random(5) + 1;
  thisp->decrease_mana(COST);
  if (thisp == target) {
    write("You concentrate and heal yourself for " + x + " hp.\n");
    this_object()->targetted_action("A soft glow envlopes $N, " +
      "as they cure their wounds.\n");
  } else {
    write("You lay your hands on " + target->query_name() +
      " healing them for " + x + " hp.\n");
    this_object()->targetted_action("A soft glow envlopes " + 
      target->query_name() + "as $N cures their wounds.\n");
  }
  target->increase_hp(x);
}

void do_spell(object thisp, string target) {
  object tar;

  if (target == "-h") {
     usage();
     return;
  }
  if (!target || target == "") {
    tar = thisp;
  } else {
    tar = this_environment()->present(target);
  }
  if (tar) {
     if (tar == thisp) {
	cure(thisp,tar);
     } else if (thisp->query_skill("cure") > 50) {
	cure(thisp,tar);
     } else {
       write("You are not skilled enough at cure to cast it on others.\n");
     }
  } else {
     write("You want to cast cure on who?\n");
  }
}