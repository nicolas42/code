# Import necessary libraries
import pygame
import sys

# Initialize Pygame
pygame.init()

# Screen settings
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Japanese Flashcards")

# Colors
black = (0, 0, 0)
white = (255, 255, 255)

# Font settings - load a custom font that supports Japanese characters
font_path = "NotoSansJP-Regular.ttf"
font_size = 60
font = pygame.font.Font(font_path, font_size)


# # Flashcards data: Japanese -> English
# flashcards = [
#     ("こんにちは", "Hello"),
#     ("本", "Book"),
#     ("猫", "Cat"),
#     ("犬", "Dog"),
#     ("ありがとう", "Thank you"),
#     ## ("きょうのてんきはどうですか？\n 
#     ("Kyou no tenki wa dou desu ka?","What is the weather like today?"),
    
# ]

# flashcards = [
#     ("天気", "Weather", "今日の天気はどうですか？", "What is the weather like today?"),
#     ("学校", "School", "私は学校に行きます。", "I am going to school."),
#     ("美味しい", "Delicious", "このケーキは美味しいです。", "This cake is delicious."),
#     ("早い", "Fast/Early", "彼はいつも早く来ます。", "He always comes early."),
#     ("遅い", "Slow/Late", "電車が遅れています。", "The train is late."),
# ]


def load_flashcards(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    flashcards = [tuple(line.strip().split(',')) for line in lines]
    return flashcards

# Load flashcards from text file
flashcards = load_flashcards("flashcards.txt")


# Flashcard index and state to show translation
index = 0
show_translation = False

# Function to draw text in the center of the screen
def draw_text(text, pos):
    text_surface = font.render(text, True, white)
    text_rect = text_surface.get_rect(center=pos)
    screen.blit(text_surface, text_rect)

# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                show_translation = not show_translation
            if event.key == pygame.K_RIGHT:
                index = (index + 1) % len(flashcards)
                show_translation = False
            if event.key == pygame.K_LEFT:
                index = (index - 1) % len(flashcards)
                show_translation = False

    # Fill the screen with black
    screen.fill(black)

    # Display Japanese text
    draw_text(flashcards[index][0], (width // 2, height // 2 - 50))
    # Display English translation if toggled
    if show_translation:
        draw_text(flashcards[index][1], (width // 2, height // 2 + 50))

    # Update the display
    pygame.display.flip()

# Quit Pygame and exit the script
pygame.quit()
sys.exit()



