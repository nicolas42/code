void main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'H';  // Display 'H' on the screen
}
