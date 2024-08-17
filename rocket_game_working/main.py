import pygame
import math
import os

# Vector addition
def vector_add(v1, v2):
    return [x + y for x, y in zip(v1, v2)]

# Vector subtraction
def vector_subtract(v1, v2):
    return [x - y for x, y in zip(v1, v2)]

# Scalar multiplication
def scalar_multiply(scalar, vector):
    return [scalar * x for x in vector]

# Initialize Pygame
pygame.init()

# Constants
SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600
FPS = 60
ROCKET_SCALE = 0.5  # Adjust scale factor to change size

# Set up the display
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Rocket Game")

# Load and scale rocket image
rocket_image = pygame.image.load('rocket-3432.png')  # Replace with the path to your rocket image
original_rect = rocket_image.get_rect()
scaled_dimensions = (int(original_rect.width * ROCKET_SCALE), int(original_rect.height * ROCKET_SCALE))
rocket_image = pygame.transform.scale(rocket_image, scaled_dimensions)
rocket_image = pygame.transform.rotate(rocket_image, -45) # (the rocket image is at 45 degrees in the image)
rocket_rect = rocket_image.get_rect(center=(SCREEN_WIDTH//2, SCREEN_HEIGHT//2))




# Rocket properties
rocket_pos = [SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2]
rocket_vel = [0,0]
rocket_angle = 0 # orientation of the rocket
rocket_acceleration = 0.1
rocket_acc = [0,0]
# max_speed = 5
rotation_speed = 5

# Clock
clock = pygame.time.Clock()

# Game loop
running = True
while running:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Key presses
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        rocket_angle += rotation_speed
    if keys[pygame.K_RIGHT]:
        rocket_angle -= rotation_speed
    if keys[pygame.K_UP]:
        rocket_acc[0] = rocket_acceleration * math.cos(math.radians(rocket_angle))
        rocket_acc[1] = rocket_acceleration * math.sin(math.radians(rocket_angle))
        rocket_vel[0] += rocket_acc[0]
        rocket_vel[1] += rocket_acc[1]
    if keys[pygame.K_DOWN]:
        rocket_acc[0] = rocket_acceleration * math.cos(math.radians(rocket_angle+180))
        rocket_acc[1] = rocket_acceleration * math.sin(math.radians(rocket_angle+180))
        rocket_vel[0] += rocket_acc[0]
        rocket_vel[1] += rocket_acc[1]

        

    # Update rocket position
    print(rocket_pos, rocket_angle, end='\r')
    rocket_pos[0] += rocket_vel[0]
    rocket_pos[1] -= rocket_vel[1]

    # Wrap around screen
    rocket_pos[0] %= SCREEN_WIDTH
    rocket_pos[1] %= SCREEN_HEIGHT

    # Drawing
    screen.fill((0, 0, 0))  # Clear screen with black
    rotated_rocket = pygame.transform.rotate(rocket_image, rocket_angle)
    new_rect = rotated_rocket.get_rect(center=rocket_rect.center)
    new_rect.center = rocket_pos
    screen.blit(rotated_rocket, new_rect.topleft)

    # Update display
    pygame.display.flip()

    # Maintain frame rate
    clock.tick(FPS)

pygame.quit()

