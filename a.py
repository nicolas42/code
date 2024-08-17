import pygame
import math

# Initialize Pygame
pygame.init()

# Set up the display
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("2D Rocket Game")

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# Rocket properties
rocket_img = pygame.Surface((20, 40))
rocket_img.fill(WHITE)
rocket_rect = rocket_img.get_rect(center=(width // 2, height // 2))
rocket_angle = 0
rocket_speed = 0
rocket_acceleration = 0.1
engine_on = False

# Game loop
clock = pygame.time.Clock()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                engine_on = not engine_on

    # Handle continuous key presses
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        rocket_angle += 3
    if keys[pygame.K_RIGHT]:
        rocket_angle -= 3

    # Update rocket position and speed
    if engine_on:
        rocket_speed += rocket_acceleration
        rocket_rect.x += rocket_speed * math.sin(math.radians(rocket_angle))
        rocket_rect.y -= rocket_speed * math.cos(math.radians(rocket_angle))
    else:
        rocket_speed = max(0, rocket_speed - rocket_acceleration / 2)

    # Wrap around screen edges
    rocket_rect.x %= width
    rocket_rect.y %= height

    # Clear the screen
    screen.fill(BLACK)

    # Draw the rocket
    rotated_rocket = pygame.transform.rotate(rocket_img, rocket_angle)
    rotated_rect = rotated_rocket.get_rect(center=rocket_rect.center)
    screen.blit(rotated_rocket, rotated_rect)

    # Draw engine flame when on
    if engine_on:
        flame_length = 20
        flame_width = 10
        flame_offset = rotated_rect.height // 2
        flame_start = (
            rotated_rect.centerx + flame_offset * math.sin(math.radians(rocket_angle)),
            rotated_rect.centery + flame_offset * math.cos(math.radians(rocket_angle))
        )
        flame_end = (
            flame_start[0] + flame_length * math.sin(math.radians(rocket_angle)),
            flame_start[1] + flame_length * math.cos(math.radians(rocket_angle))
        )
        pygame.draw.line(screen, RED, flame_start, flame_end, flame_width)

    # Update the display
    pygame.display.flip()

    # Control the frame rate
    clock.tick(60)

# Quit the game
pygame.quit()
