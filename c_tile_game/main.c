// Block game "fitz" from university

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int debug = 0;

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


int load_tiles(char *tilefile, char *tiles){ // tiles[][25]){
  // load tiles
  // char tiles[100][25];
  int tiles_length = 0;
  int j = 0;
  while (1){
    make_tile(&tilefile[j], &tiles[25*tiles_length]);
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


void print_board(char *board, int width, int height){
    for (int i=0;i<height;i+=1){
      for (int j=0;j<width;j+=1){
	printf("%c",board[(i*width)+j]);
      }
      printf("\n");
    }
}


int place_tile(char *board, int width, int height, char* tile, int row, int column, int rotate, char playerchar){

  // return value is whether move completed ok.  0 = not okay.  everything else = ok.
  // tiles are 5x5 characters.  The center point of the tile is what is actually placed onto the board.
  // Lets just put a tile in the middle of the board for the time being.

  // lets put the tile at 2,2.
  // That means that we'll have to check all the points on the board from row 0..5 and col 0..5.

  char rotations[4][25];
  make_rotations(tile, rotations);
  int rotation_index = rotate / 90;
  char *rotated_tile = rotations[rotation_index];
  //  print_tile(rotated_tile);

  // do everything on a temporary board. if all of the char copies work then copy the results to the actual board.
  char *temporary_board = (char*)malloc(width*height*sizeof(char));
  for (int i=0;i<width*height;i+=1) { temporary_board[i] = board[i]; }
  
  int tileindex = 0;
  for (int i=(row-2);i<(row+3);i+=1){
    for (int j=(column-2);j<(column+3);j+=1){
      char tilechar = rotated_tile[tileindex];
      tileindex+=1;
      if (tilechar == '!'){
	// constraints on i and j are 0 < i < height  and 0 < j < width;
	// the board at this location must not have an existing tile. the board char must be '.'
	if (!((0 <= i) && (i < height) && (0 <= j) && (j < width))){
	  if (debug){ printf("out of bounds\n"); }
	  return 0;
	}
	else if (!(temporary_board[width*i+j] == '.')){
	  if (debug){ printf("Intersection error\n"); }
	  return 0;
	}
	else {
	  temporary_board[width*i+j] = playerchar;
	} 
      }
    }
  }
  for (int i=0;i<width*height;i+=1) { board[i] = temporary_board[i]; }

  free(temporary_board);
  return 1; // completed ok
}


int run_automatic_player_type_1(char *board, int width, int height, char* tile, char playerchar, int *r, int *c, int *rot){
  // automatic player type 1
  // r_start, c_start are the most recent legal play by either player or -2,-2 if no moves have been made yet.
  // let r = r_start, c = c_start
  // let rot = 0
  // loop, loop
  // if r,c,rot is a valid placement stop
  // add one to c
  // if c is larger than max column then set c to -2 and add 1 to r
  // if r is larger than maximum row + 2 then set r to -2
  // until r == r_start and c == c_start
  // rotation += 90
  // until rotation > 270

  
  // int r_start, c_start, r, c, rot, ok;
  // r_start = row; // set to -2 if not set yet.
  // c_start = column;
  // *r = r_start;
  // *c = c_start;
  // *rot = 0;

  int r_start = *r;
  int c_start = *c;
  int ok = 0;
  while (1) {
    while (1) {
      ok = place_tile(board, width, height, tile, *r, *c, *rot, playerchar);
      if (ok == 1){ return 1; }
      *c += 1;
      if (*c > (width+2)) { *c = -2; *r += 1; }
      if (*r > (height+2)) { *r = -2; }
      if (*r == r_start && *c == c_start) { break; }
    }
    *rot += 90;
    if ( *rot > 270 ) { break; }
  }
  return 0;
}  



int run_automatic_player_type_2(char *board, int width, int height, char* tile, char playerchar, int *r, int *c, int *rot, int player_index){

  // the most recent legal play by this player  
  int r_start = *r; 
  int c_start = *c;
  
  // starting location and search direction changes depending on which player this is.
  // if player_index = 0 then it's player 1
  // player_index = 1 means player 2
  // player one starts at (-2,-2) and searches left to right top to bottom.  Player two starts at bottom right (rows+2,cols+2) and searches right to left, bottom to top
  if (player_index == 0){
    *r = -2; 
    *c = -2;
  }
  else if (player_index == 1){
    *r = width+2; 
    *c = height+2;
  }

  int ok = 0;
  while (1) {
    *rot = 0;
    while (1) {
      ok = place_tile(board, width, height, tile, *r, *c, *rot, playerchar);
      if (ok == 1){ return 1; }
      *rot += 90;
      if (*rot > 270) { break; }
    }
    if (player_index == 0){
      *c += 1;
      if (*c > (width+2)){
	*c = -2;
	*r += 1;
      }
    }
    else if (player_index == 1){
      *c -= 1;
      if (*c < -2){
	*c = width+2;
	*r -= 1;
      }
    }

    if (*r==r_start && *c==c_start){ break; }
  }
  return 0;
}

int strlen(const char *a){
  int len = 0;
  for (int i=0; a[i] != '\0'; i+=1){
    len += 1;
  }
  return len;
}
    


int main(int argc, char *argv[]) {

    char *tilefile;
    char *p1type;
    char *p2type;
    int height = 5;
    int width  = 5;
    char *filename;
    
    if (debug) { for (int i = 0; i < argc; i++) { printf("'%s' ", argv[i]); }  printf("\n"); } 

    // load tiles
    tilefile = argv[1];
    char *tilestext = read_whole_file(tilefile);
    if (tilestext == 0) return -1;

    int tilestext_length = strlen(tilestext);
    int tiles_to_allocate = (tilestext_length + 1) / 31;
    char *tiles = (char*)malloc(tiles_to_allocate * 25 * sizeof(char));
    int tiles_length = load_tiles(tilestext, tiles); 
    

    if (argc == 2){
      // If only one argument is given, the contents of the tile file should be output to standard out as described below.
      for (int i=0;i<tiles_length;i+=1){
	print_rotations(&tiles[i]);
	printf("\n");
      }
      return 0;
    }
    
    if (argc == 4){
      p1type = argv[2];
      p2type = argv[3];
    }
    else if (argc == 6){
      p1type = argv[2];
      p2type = argv[3];
      width  = atoi(argv[4]);
      height = atoi(argv[5]);
    }
    else {
      printf("Usage: %s tilefile [p1type p2type [height width | filename]]\n", argv[0]);
      return 1;
    }
    

    // initialize board 
    char *board = (char*)malloc( height * width * sizeof(char) );
    for (int i=0;i<height;i+=1){
      for (int j=0;j<width;j+=1){
	board[width*i+j] = '.';
      }
    }      

    int row, column, rotate;
    row = -2;
    column = -2;
    rotate = 0;
    int tiles_index = 0;
    char player_chars[2] = {'*','#'};
    char player_types[2] = { p1type[0], p2type[0] };
    char ptype;
    char playerchar;
    int player_index = 0;
    char *tile;
    int ok = 0;
    while (1){
      print_board(board, width, height);
      print_tile(&tiles[25*tiles_index]);
      tile = &tiles[25*tiles_index];
      playerchar = player_chars[player_index];
      ptype = player_types[player_index];
      ok = 0;
      if (ptype == 'h'){
	while (ok == 0){
	  printf("Player %c] ", playerchar);
	  scanf("%d %d %d", &row, &column, &rotate);
	  ok = place_tile(board, width, height, tile, row, column, rotate, playerchar);
	}
      }
      else if (ptype == '1'){
	//if an automatic player returns 0 then there are no moves that it can play
	getchar();
	ok = run_automatic_player_type_1(board, width, height, tile, playerchar, &row, &column, &rotate);
	if (ok == 1) { printf("Player %c => %d %d rotated %d\n", playerchar, row, column, rotate); }
      }
      else if (ptype == '2'){
	//if an automatic player returns 0 then there are no moves that it can play
	getchar();
	ok = run_automatic_player_type_2(board, width, height, tile, playerchar, &row, &column, &rotate, player_index);
	if (ok == 1) { printf("Player %c => %d %d rotated %d\n", playerchar, row, column, rotate); }
      }
      
      if (ok == 0) { printf("Player %d (%c) loses\n", player_index+1, playerchar); break; }
      player_index = 1 - player_index; // toggles 0,1...
      tiles_index += 1;
      if (tiles_index == tiles_length){
	tiles_index = 0;
      }
      
    }


    free(tiles);
    return 0;
}

