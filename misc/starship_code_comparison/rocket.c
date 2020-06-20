//  tcc -IC:\Users\nick\Downloads\tcc\include rocket.c main.c -o rocket; ./rocket

#include "rocket.h"
#include <math.h>
#include <stdio.h>

double rocket_calculate_initial_mass(struct rocket_rocket a){
    return a.ship_dry_mass + a.propellant_mass + a.ascent_payload; 
}

double rocket_calculate_final_mass(struct rocket_rocket a){
    return a.ship_dry_mass + a.ascent_payload;
}

double rocket_calculate_delta_v(struct rocket_rocket a){
    return a.exhaust_velocity * log ( rocket_calculate_initial_mass(a) / rocket_calculate_final_mass(a) );
}

int rocket_main(int argc, char **argv){

    struct rocket_rocket starship;
    struct rocket_rocket superheavy;

    double delta_vs[2];
    double orbital_velocity;


    starship.ship_dry_mass = 120; // metric tonnes
    starship.propellant_mass = 1200;
    starship.ascent_payload = 150;
    starship.exhaust_velocity = 3.7; // km/s

    superheavy.ascent_payload = rocket_calculate_initial_mass(starship),
    superheavy.propellant_mass = 2 * rocket_calculate_initial_mass(starship),
    superheavy.ship_dry_mass = superheavy.propellant_mass / 10;
    superheavy.exhaust_velocity = 3.3;

    delta_vs[0] = rocket_calculate_delta_v(superheavy);
    delta_vs[1] = rocket_calculate_delta_v(starship);


    orbital_velocity =  sqrt(9.81 * 6371e3) / 1e3;
    
    printf("%f + %f = %f\n", delta_vs[0], delta_vs[1], delta_vs[0]+delta_vs[1]);
    printf("%f", orbital_velocity);

    return 0;
}
