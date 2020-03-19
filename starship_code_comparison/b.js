// Starship September 2019 Calculations
// from https://www.youtube.com/watch?v=5UUtNR6BhjE

starship_ship_dry_mass = 120;
starship_propellant_mass = 1200;
starship_ascent_payload = 150;
starship_initial_mass = starship_ship_dry_mass + starship_propellant_mass + starship_ascent_payload; 
starship_final_mass = starship_ship_dry_mass + starship_ascent_payload;
starship_delta_v = 3.7 * Math.log ( starship_initial_mass / starship_final_mass );

/*
// BOOSTER
// for booster need to add starship's initial_mass
"dv = v_e * log ( mass_fraction )"
"3.5 = 3.3 * log ( ~3 )"
mass_ratio = E^(3.5/3.3) // 2.88
// So basically need a booster that is twice the size of the spaceship (not including dry_mass)
*/

superheavy_ascent_payload = starship_initial_mass;
superheavy_propellant_mass =  2.5 * starship_initial_mass
superheavy_ship_dry_mass = superheavy_propellant_mass / 10;

superheavy_initial_mass = superheavy_ship_dry_mass + superheavy_propellant_mass + superheavy_ascent_payload;
superheavy_final_mass = superheavy_ship_dry_mass + superheavy_ascent_payload
superheavy_delta_v = 3.3 * Math.log ( superheavy_initial_mass / superheavy_final_mass )
// 3.23

orbital_velocity = Math.sqrt(9.8 * 6371e3) // 7901
delta_v = starship_delta_v + superheavy_delta_v
