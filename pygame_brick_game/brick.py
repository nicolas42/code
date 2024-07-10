# crappygames.com

import pygame
import sys

# Initialize pygame and mixer
pygame.init()
pygame.mixer.init()

# Colors
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# Screen settings
SCREEN_WIDTH = 300
SCREEN_HEIGHT = 600
BLOCK_SIZE = 30

# Create the screen and clock objects
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Simple Tetris")
clock = pygame.time.Clock()


# Shape class
class Square:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def move_down(self):
        self.y += BLOCK_SIZE

    def move_left(self):
        self.x -= BLOCK_SIZE
        if self.x < 0: self.x = 0

    def move_right(self):
        self.x += BLOCK_SIZE
        if self.x >= 9*BLOCK_SIZE: self.x = 9*BLOCK_SIZE

    # This function doesn't change anything for a square, but it's here for consistency
    def rotate(self):
        pass

    def draw(self, screen):
        pygame.draw.rect(screen, RED, (self.x, self.y, BLOCK_SIZE, BLOCK_SIZE))


MOVE_DOWN_EVENT = pygame.USEREVENT + 1
pygame.time.set_timer(MOVE_DOWN_EVENT, 500)  # Trigger every 500 milliseconds


# Main game loop
def game_loop():

    left_key_pressed = False
    right_key_pressed = False
    left_key_time = 0
    right_key_time = 0
    initial_delay = 500  # initial half-second delay before repeating
    repeat_rate = 50  # rate at which to repeat movement after initial delay


    square = Square(SCREEN_WIDTH // 2, 0)

    # How to remove silence from songs with Audacity
    # Load a song.  Select all of song with ctrl+a. Go to effects > special > truncate silence . Export wav
    music_files = ['MUS2CD_truncated.wav','brick/MUS2E.WAV','brick/MUS2FA.WAV','brick/MUS2FB.WAV','brick/MUS2FC.WAV','brick/MUS2G.WAV','brick/MUS2RPT.WAV']
    music_files_index = 0

    while True:

        if not pygame.mixer.music.get_busy():
            pygame.mixer.music.load(music_files[music_files_index])
            pygame.mixer.music.play()
            music_files_index += 1
            if music_files_index >= len(music_files):
                music_files_index = 0


        screen.fill(WHITE)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.mixer.music.stop()  # Stop the music
                pygame.quit()
                sys.exit()

            elif event.type == MOVE_DOWN_EVENT:
                square.move_down()

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    left_key_pressed = True
                    left_key_time = pygame.time.get_ticks()  # Record the time when the key was pressed
                    square.move_left()  # Initial move
                elif event.key == pygame.K_RIGHT:
                    right_key_pressed = True
                    right_key_time = pygame.time.get_ticks()  # Record the time when the key was pressed
                    square.move_right()  # Initial move
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT:
                    left_key_pressed = False
                elif event.key == pygame.K_RIGHT:
                    right_key_pressed = False

        current_time = pygame.time.get_ticks()

        if left_key_pressed and current_time - left_key_time > initial_delay:
            if (current_time - left_key_time - initial_delay) % repeat_rate < clock.get_time():
                square.move_left()

        if right_key_pressed and current_time - right_key_time > initial_delay:
            if (current_time - right_key_time - initial_delay) % repeat_rate < clock.get_time():
                square.move_right()

        if square.y >= SCREEN_HEIGHT:
            square.y = 0

        # Draw the tile after processing inputs
        screen.fill(WHITE)
        square.draw(screen)
        pygame.display.flip()

        clock.tick(60) # Limit frame rate to 60 fps


game_loop()
