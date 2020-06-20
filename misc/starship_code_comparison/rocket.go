package main

import "fmt"
import "math"

type Rocket struct {
    ship_dry_mass float64;
    propellant_mass float64;
    ascent_payload float64;
    exhaust_velocity float64;
};

func calculate_initial_mass(a Rocket) float64 {
    return a.ship_dry_mass + a.propellant_mass + a.ascent_payload; 
}

func calculate_final_mass(a Rocket) float64 {
    return a.ship_dry_mass + a.ascent_payload;
}

func calculate_delta_v(a Rocket) float64 {
    return a.exhaust_velocity * math.Log ( calculate_initial_mass(a) / calculate_final_mass(a) );
}

func main(){

	starship := Rocket{};
	superheavy := Rocket{};

    delta_vs := [2]float64{};
    var orbital_velocity float64;


    starship.ship_dry_mass = 120; // metric tonnes
    starship.propellant_mass = 1200;
    starship.ascent_payload = 150;
    starship.exhaust_velocity = 3.7; // km/s

    superheavy.ascent_payload = calculate_initial_mass(starship);
    superheavy.propellant_mass = 2 * calculate_initial_mass(starship);
    superheavy.ship_dry_mass = superheavy.propellant_mass / 10;
    superheavy.exhaust_velocity = 3.3;

    delta_vs[0] = calculate_delta_v(superheavy);
    delta_vs[1] = calculate_delta_v(starship);


    orbital_velocity =  math.Sqrt(9.81 * 6371e3) / 1e3;
    
    fmt.Printf("%f + %f = %f\n", delta_vs[0], delta_vs[1], delta_vs[0]+delta_vs[1]);
    fmt.Printf("%f", orbital_velocity);

}
