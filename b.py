import pygame
import sys

# Initialize pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 800, 600
BUTTON_PADDING = 20
BUTTON_HEIGHT = 50
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 255, 0)

# Screen setup
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Gradient Display")

# Font setup
font = pygame.font.Font(None, 36)

def draw_button(text, x, y):
    text_surf = font.render(text, True, WHITE)
    text_width, text_height = text_surf.get_size()
    button_rect = pygame.Rect(x, y, text_width + 2 * BUTTON_PADDING, BUTTON_HEIGHT)
    pygame.draw.rect(screen, BLACK, button_rect)
    text_rect = text_surf.get_rect(center=button_rect.center)
    screen.blit(text_surf, text_rect)
    return button_rect

def draw_gradient_8bit():
    for i in range(10):
        color = (0, int((i / 9) * 128), 0)
        pygame.draw.rect(screen, color, (i * (WIDTH / 10), HEIGHT / 2 - 100, WIDTH / 10, 200))

def draw_gradient_10bit():
    for i in range(10):
        color = (0, int((i / 9) * 256), 0)
        pygame.draw.rect(screen, color, (i * (WIDTH / 10), HEIGHT / 2 - 100, WIDTH / 10, 200))

# Main loop
running = True
show_8bit = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:  # Left mouse button
                if bit_8_button.collidepoint(event.pos):
                    show_8bit = True
                elif bit_10_button.collidepoint(event.pos):
                    show_8bit = False

    # Drawing
    screen.fill(WHITE)
    
    bit_8_button = draw_button("8-bit Color", WIDTH / 4 - BUTTON_PADDING, HEIGHT - 100)
    bit_10_button = draw_button("10-bit Color", 3 * WIDTH / 4 - BUTTON_PADDING, HEIGHT - 100)

    if show_8bit:
        draw_gradient_8bit()
    else:
        draw_gradient_10bit()
    
    pygame.display.flip()

pygame.quit()
sys.exit()
