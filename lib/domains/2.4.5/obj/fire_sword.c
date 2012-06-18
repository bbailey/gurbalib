inherit WEAPON;

void setup(void) {
   set_id("sword");
   set_long("A red hot blade.  It glows with power");
   set_in_room_desc("Sword of fire");
   set_gettable(1);

   set_min_damage(5);
   set_max_damage(20);
   set_hit_bonus(5);

   set_weapon_skill("combat/sharp/large");

   set_wield_type("single");
   set_wield_message("$N $vwield $p $o.");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_action("slash");
   set_value(2000);
   set_size(20);
   // XXX set_weight(30);
}
