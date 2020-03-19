// Starship September 2019 Calculations
// from https://www.youtube.com/watch?v=5UUtNR6BhjE

calculate_initial_mass = function(a){
    return a.ship_dry_mass + a.propellant_mass + a.ascent_payload; 
}

calculate_final_mass = function(a){
    return a.ship_dry_mass + a.ascent_payload;
}

calculate_delta_v = function(a){
    return 3.7 * Math.log ( calculate_initial_mass(a) / calculate_final_mass(a) );
}

starship = {
    ship_dry_mass: 120,
    propellant_mass: 1200,
    ascent_payload: 150,
}


superheavy = {
    ascent_payload: calculate_initial_mass(starship),
    propellant_mass: 2 * calculate_initial_mass(starship),
    ship_dry_mass: undefined,
}
superheavy.ship_dry_mass = superheavy.propellant_mass / 10;

delta_vs = [
    calculate_delta_v(superheavy),
    calculate_delta_v(starship),
]

console.dir(delta_vs);

orbital_velocity =  Math.sqrt(9.8 * 6371e3) // 7901
 
