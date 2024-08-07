import pygame
import sys

# Initialize pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 800, 600
BUTTON_WIDTH, BUTTON_HEIGHT = 200, 50
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 255, 0)

# Colors for the darkest 8 greens
darkest_greens = [
    (0, 0, 0), (0, 10, 0), (0, 20, 0), (0, 30, 0),
    (0, 40, 0), (0, 50, 0), (0, 60, 0), (0, 70, 0)
]

# Screen setup
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Gradient Display")

# Font setup
font = pygame.font.Font(None, 36)

def draw_button(text, x, y):
    text_surf = font.render(text, True, WHITE)
    text_width, text_height = text_surf.get_size()
    button_rect = pygame.Rect(x, y, text_width + 20, text_height + 10)
    pygame.draw.rect(screen, BLACK, button_rect)
    text_rect = text_surf.get_rect(center=button_rect.center)
    screen.blit(text_surf, text_rect)
    return button_rect

def draw_gradient_light_to_dark_green():
    for i in range(WIDTH):
        color = (0, int((i / WIDTH) * 255), 0)
        pygame.draw.rect(screen, color, (i, HEIGHT / 2 - 100, 1, 200))

def draw_gradient_darkest_8_colors():
    bar_width = WIDTH // 8
    for i, color in enumerate(darkest_greens):
        pygame.draw.rect(screen, color, (i * bar_width, HEIGHT / 2 - 100, bar_width, 200))

# Main loop
running = True
show_light_to_dark = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if light_to_dark_button.collidepoint(event.pos):
                show_light_to_dark = True
            elif darkest_8_button.collidepoint(event.pos):
                show_light_to_dark = False

    # Drawing
    screen.fill(WHITE)
    
    light_to_dark_button = draw_button("Light to Dark Green", WIDTH / 4 - BUTTON_WIDTH / 2, HEIGHT - 100)
    darkest_8_button = draw_button("Darkest 8 Greens", 3 * WIDTH / 4 - BUTTON_WIDTH / 2, HEIGHT - 100)

    if show_light_to_dark:
        draw_gradient_light_to_dark_green()
    else:
        draw_gradient_darkest_8_colors()
    
    pygame.display.flip()

pygame.quit()
sys.exit()




