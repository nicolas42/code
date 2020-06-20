;// Starship September 2019 Calculations
;// from https://www.youtube.com/watch?v=5UUtNR6BhjE

rebol []

starship: context [
    ship_dry_mass: 120
    propellant_mass: 1200
    ascent_payload: 150
    initial_mass: ship_dry_mass + propellant_mass + ascent_payload
    final_mass: ship_dry_mass + ascent_payload
    delta_v: 3.7 * log-e ( initial_mass / final_mass )
]

comment {
    ;;// BOOSTER
    ;// for booster need to add starship's initial_mass
    "dv = v_e * log ( mass_fraction )"
    "3.5 = 3.3 * log ( ~3 )"
    mass_ratio: E^(3.5/3.3) ;// 2.88
    ;// So basically need a booster that is twice the size of the spaceship (not including dry_mass)
}

superheavy: context [
    propellant_mass:  2 * 1435;
    ship_dry_mass: propellant_mass / 10; ;// judging roughly by starship figures
    ascent_payload: 1435;
    initial_mass: ship_dry_mass + propellant_mass + ascent_payload;
    final_mass: ship_dry_mass + ascent_payload
    delta_v: 3.3 * log-e ( initial_mass / final_mass )
    ;// 3.23
]

orbital_velocity: square-root(9.8 * 6371e3) ;// 7901
delta_v: starship/delta_v + superheavy/delta_v
