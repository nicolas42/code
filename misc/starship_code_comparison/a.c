// Starship September 2019 Calculations
// from https://www.youtube.com/watch?v=5UUtNR6BhjE

#include <math.h>

struct rocket {
    double ship_dry_mass;
    double propellant_mass;
    double ascent_payload;
};

double calculate_initial_mass(struct rocket a){
    return a.ship_dry_mass + a.propellant_mass + a.ascent_payload; 
}

double calculate_final_mass(struct rocket a){
    return a.ship_dry_mass + a.ascent_payload;
}

double calculate_delta_v(struct rocket a){
    return 3.7 * log ( calculate_initial_mass(a) / calculate_final_mass(a) );
}

int main(int argc, char **argv){

    struct rocket starship;
    struct rocket superheavy;

    double dv[2];
    double orbital_velocity;


    starship.ship_dry_mass = 120;
    starship.propellant_mass = 1200;
    starship.ascent_payload = 150;

    superheavy.ascent_payload = calculate_initial_mass(starship),
    superheavy.propellant_mass = 2 * calculate_initial_mass(starship),
    superheavy.ship_dry_mass = superheavy.propellant_mass / 10;


    dv[0] = calculate_delta_v(superheavy);
    dv[1] = calculate_delta_v(starship);


    orbital_velocity =  sqrt(9.8 * 6371e3) / 1e3;
    
    printf("%f + %f = %f\n", dv[0], dv[1], dv[0]+dv[1]);
    printf("%f", orbital_velocity);

    return 0;
}



 
