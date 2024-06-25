import math

desired_velocity = 83333  # m/s
exhaust_velocity = 145000  # m/s

ln_term = desired_velocity / exhaust_velocity
mass_fraction = 1 - (1 / math.exp(ln_term))

print(mass_fraction)
