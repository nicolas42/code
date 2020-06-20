// Starship September 2019 Calculations
// from https://www.youtube.com/watch?v=5UUtNR6BhjE

#ifndef ROCKET_H
#define ROCKET_H

struct rocket_rocket {
    double ship_dry_mass;
    double propellant_mass;
    double ascent_payload;
    double exhaust_velocity;
};

double rocket_calculate_initial_mass(struct rocket_rocket a);
double rocket_calculate_final_mass(struct rocket_rocket a);
double rocket_calculate_delta_v(struct rocket_rocket a);
int rocket_main(int argc, char **argv);
 
#endif