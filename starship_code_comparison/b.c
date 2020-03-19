// Starship September 2019 Calculations
// from https://www.youtube.com/watch?v=5UUtNR6BhjE

#include <math.h>

int main(int argc, char **argv){


    double starship_ship_dry_mass = 120;
    double starship_propellant_mass = 1200;
    double starship_ascent_payload = 150;
    double starship_initial_mass = starship_ship_dry_mass + starship_propellant_mass + starship_ascent_payload; 
    double starship_final_mass = starship_ship_dry_mass + starship_ascent_payload;
    double starship_delta_v = 3.7 * log ( starship_initial_mass / starship_final_mass );

    /*
    // BOOSTER
    // for booster need to add starship's initial_mass
    "dv = v_e * log ( mass_fraction )"
    "3.5 = 3.3 * log ( ~3 )"
    mass_ratio = E^(3.5/3.3) // 2.88
    // So basically need a booster that is twice the size of the spaceship (not including dry_mass)
    */

    double superheavy_ascent_payload = starship_initial_mass;
    double superheavy_propellant_mass =  2.5 * starship_initial_mass;
    double superheavy_ship_dry_mass = superheavy_propellant_mass / 10;
    double superheavy_initial_mass = superheavy_ship_dry_mass + superheavy_propellant_mass + superheavy_ascent_payload;
    double superheavy_final_mass = superheavy_ship_dry_mass + superheavy_ascent_payload;
    double superheavy_delta_v = 3.3 * log ( superheavy_initial_mass / superheavy_final_mass );

    double orbital_velocity = sqrt(9.8 * 6371e3);
    double delta_v = starship_delta_v + superheavy_delta_v;

    return 0;
}