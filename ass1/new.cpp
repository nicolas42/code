#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char* read_whole_file(const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Seek to the end of the file to determine the file size
    fseek(file, 0, SEEK_END);
    int64_t filesize = ftell(file);
    rewind(file);  // Go back to the start of the file

    // Allocate memory for the entire content
    char *buffer = (char*)malloc((size_t)(filesize + 1));  // +1 for the null terminator
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    size_t read_size = fread(buffer, 1, (size_t)filesize, file);
    if (read_size != (size_t)filesize) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    // Null-terminate the string
    buffer[filesize] = '\0';

    // Close the file and return the buffer
    fclose(file);
    return buffer;
}

int read_and_display_tilefile() {
    const char *filename = "tilefile";
    char *content = read_whole_file(filename);
    if (content) {
        printf("File content:\n%s", content);
        free(content);  // Remember to free the memory allocated
    }
    
    return 0;
}


// Shape display
// For each tile in the file (in order), print the tile with its three rotations next to it (space separated). Put a blank line between each row of tiles.

void make_tile(const char *a, char *tile){
  // char tile[25];
  int j=0;
  for (int i=0; i<30;i+=1){
    if (a[i]!='\n') {
      tile[j] = a[i];
      j+=1;
    }
  }
}

void print_tile(const char *tile){

  // print tile
  printf("\n");
  for (int i=0;i<5;i+=1){
    for (int j=0;j<5;j+=1){
      printf("%c",tile[5*i+j]);
    }
    printf("\n");
  }
}    


void rotate_tile(const char *in, char *out){

  // the first row becomes the last column
  // out[(4-row)+5*col]
  int row,col;
  for (row=0;row<5;row+=1){
    for (col=0;col<5;col+=1){
      //      printf("%d,%d\n",row,col);
      out[(4-row)+(5*col)] = in[5*row+col];
    }
  }
}

void copy_tile(const char *a, char *b){

  for (int i=0;i<25;i+=1){
    b[i]=a[i];
  }
}

void make_rotations(const char *tile, char tiles[4][25]){
  //  printf("%lu\n", sizeof(tile));
  //  printf("%lu\n", sizeof(tiles));

  copy_tile(tile, tiles[0]); 
  for (int i=0; i<3; i+=1){
    rotate_tile(tiles[i], tiles[i+1]);
  }
}

void print_rotations(char *tile){
  // Note: in c an array element like this decays into a pointer.  Adding & actually introduces warnings.

  char tiles[4][25];
  make_rotations(tile, tiles);

  for(int row=0;row<5;row+=1){
    for(int i=0;i<4;i+=1){
      // print row of each rotation
      for(int j=0;j<5;j+=1){
	printf("%c",tiles[i][5*row+j]);
      }
      printf(" ");
    }
    printf("\n");
  }
}




int demo1(){
  // tilefile text a
  char *tilefile = read_whole_file("tilefile");
  if (!tilefile) return -1;
  // printf("%s",tilefile);

  // int i;
  // for(i=0;tilefile[i]!='\0';i+=1){}
  // printf("Length of tilefile: %d\n",i);

  // length of tile in buffer is 30.  They are separated by newlines.  So a tilefile with 3 tiles has a length of 30*3 + 2 = 92.
  // @todo Should be able to calculate the length of the tiles
  // len = 30n + n-1, len+1 = 30n+n = 31n, n = (len+1)/31

  // char *tiles = (char*)malloc(10*25*sizeof(char));
  char tiles[10][25];
  int tiles_length = 0;
  int j = 0;
  while (1){
    make_tile(&tilefile[j], tiles[tiles_length]);
    j += 30;
    tiles_length += 1;
    if (tilefile[j] == '\n') {
      j+=1;
    } else {
      break;
    }
  }

  // for(i=0;i<tiles_length;i+=1) print_tile((char*)&tiles[i]);

  char tile[25];
  copy_tile(tiles[0], tile);
  //  print_tile(tile);

  char rotated[25];
  rotate_tile(tile, rotated);
  // print_tile(rotated);

  print_rotations(tile);

  char rotations[4][25];
  make_rotations(tile, rotations);
  // for(i=0;i<4;i+=1){  print_tile(rotations[i]);  }

  free(tilefile);
  return 0;
}


int load_tiles(char *tilefile, char tiles[][25]){
  // load tiles
  // char tiles[100][25];
  int tiles_length = 0;
  int j = 0;
  while (1){
    make_tile(&tilefile[j], tiles[tiles_length]);
    j += 30;
    tiles_length += 1;
    if (tilefile[j] == '\n') {
      j+=1;
    } else {
      break;
    }
  }
  return tiles_length;
}


int demo2(){

  // read tilefile
  char *tilefile = read_whole_file("tilefile");
  if (!tilefile) return -1;
  // printf("Tilefile\n%s",tilefile);

  char tiles[100][25];
  load_tiles(tilefile,tiles); 

  
  char *tile = tiles[0];
  char rotations[4][25];
  make_rotations(tile, rotations);
  // for (auto r: rotations) {  print_tile(r); }
  // for (int i=0;i<4;i+=1){  print_tile(rotations[i]);  }

  printf("Print rotations of a tile\n");
  print_rotations(tile);

  free(tilefile);
  return 0;
}

void place_tile(){
}

int main(int argc, char *argv[]) {

    char *tilefile;
    char *p1type;
    char *p2type;
    int height;
    int width;
    char *filename;
    
    printf("Usage: %s tilefile [p1type p2type [height width | filename]]\n", argv[0]);
    // 1,3,5,or 4 arguments, not including the executable.

    // If only one argument is given, the contents of the tile file should be output to standard out as described below.    
    if (argc==2){

      tilefile = argv[1];
      char *tilestext = read_whole_file(tilefile);
      if (!tilestext) return -1;

      char tiles[100][25];
      int num_tiles = load_tiles(tilestext, tiles); 

      for (int i=0;i<num_tiles;i+=1){
	print_rotations(tiles[i]);
	printf("\n");
      }

    }

    return 0;
}

