#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <vector>
#include "read_file.h"
#include "assert.h"

// void parse_tiles( char *string, int string_length, char*** ret_tiles, int* ret_tiles_length)
// {
// 	int allocated = 1000;
//     char **tiles = (char**)malloc(allocated);
// 	int tiles_length = 0;


//     tiles[0] = string;
//     tiles_length = 1;

//     for ( int i=0; ; i+=1 ) {
//         // expand output data if required
//         if ( allocated == tiles_length ) {
//             allocated *= 2;
//             tiles = (char**)realloc(tiles, allocated);
//         }

//         // end of file
//         if ( string[i] == '\n' && string[i+1] == '\0' ) {
//             string[i] = '\0';
//             break;
//         }
//         if ( string[i] != '\0' && string[i-1] == '\n' && string[i-2] == '\n' ) {
//             tiles[tiles_length] = string + i;
//             tiles_length += 1;
//             string[i-2] = '\0';
//         }
//     }

//     *ret_tiles = tiles;
//     *ret_tiles_length = tiles_length;
// }

// void parse_tiles2( char *string, int string_length, char*** ret_output, int* ret_output_length)
// {
//     char **output = (char**)malloc(1000);
// 	int output_allocated = 1000;
// 	int output_length = 0;

//     int string_pos = 0;
//     output[output_length] = string;
//     output_length += 1;

//     // the tiles file has the following format
//     // tile [30 bytes]
//     // newline [1 byte]
//     // ...
//     // tile [30 bytes]
//     // EOF null byte [1 byte]
//     // if there's a newline after the tile then assume there's another tile after it.  
//     // if there's an EOF null byte after a tile then assume there's nothing after it.

//     while (1) {

//         // expand output array if required
//         if ( output_allocated == output_length ) {
//             output_allocated *= 2;
//             output = (char**)realloc(output, output_allocated);
//         }
//         string_pos += 30;
//         if ( string[string_pos] == '\n' ) {
//             string[string_pos] = '\0';
//             string_pos += 1;
//             output[output_length] = string+string_pos;;
//             output_length += 1;
//         } 
//         if ( string[string_pos] == '\0' ) {
//             break;
//         }
//     }

//     *ret_output = output; 
//     *ret_output_length = output_length;
// }






struct tile { 
    char data[25]; 
};

void parse_tiles3( char *string, int string_length, struct tile** ret_tiles, int* ret_tiles_length )
{
    struct tile* tiles = (struct tile*)malloc(1000);
	int tiles_allocated = 1000;
	int tiles_length = 0;

    int string_position = 0;
    while (1) {

        // expand output array if required
        if ( tiles_allocated == tiles_length ) {
            tiles_allocated *= 2;
            tiles = (struct tile*)realloc(tiles, tiles_allocated);
        }

        for ( int i=0; i<5; i+=1 ) {
            for ( int j=0; j<5; j+=1 ) {
                tiles[tiles_length].data[5*i+j] = string[string_position++];
            }
            string_position++; // newline
        }
        tiles_length++;

        if ( string[string_position] == '\n' ) { 
            string_position++;
        }
        if ( string[string_position] == '\0' ) { 
            break;
        }
    }

    *ret_tiles = tiles;
    *ret_tiles_length = tiles_length;

}

void sprint_tile(struct tile tile, char cstr[31])
{
    int str_index = 0;
    for ( int i=0; i<5; i+=1 ) {
        for ( int j=0; j<5; j+=1 ) {
            cstr[str_index++] = tile.data[5*i+j];
        }
        cstr[str_index++] = '\n';
    }
    cstr[str_index++] = '\n';
    cstr[str_index++] = '\0';

}

void print_tile(struct tile tile)
{
    char tile_string[31];
    sprint_tile(tile, tile_string);
    printf("%s", tile_string);
}

void rotate_tile(struct tile tile, int rotation_degrees, struct tile *output_tile)
{
    assert(rotation_degrees == 0 || rotation_degrees == 90 || rotation_degrees == 180 || rotation_degrees == 270 );

    for ( int row=0; row<5; row+=1 ) {
        for ( int col=0; col<5; col+=1 ) {
            switch (rotation_degrees) {
            case 0:
                (*output_tile).data[ 5*row+col ] = tile.data[ 5*row+col ];
                break;
            case 90:
                (*output_tile).data[ 5*col + (4-row) ] = tile.data[ 5*row+col ];
                break;
            case 180:
                (*output_tile).data[ 5*(4-row) + (4-col) ] = tile.data[ 5*row+col ];
                break;
            case 270:
                (*output_tile).data[ 5*(4-col) + row ] = tile.data[ 5*row+col ];
                break;
            }
        }
    }

    // output_tile.rot0[row][col] = str[col];
    // output_tile.rot90[col][MAX_TILE - row] = str[col];
    // output_tile.rot180[MAX_TILE - row][MAX_TILE - col] = str[col];
    // output_tile.rot270[MAX_TILE - col][row] = str[col];

}

void print_all_tiles_in_all_rotations( struct tile* tiles, int tiles_length )
{
    struct tile rotated_tile;

    for ( int i=0; i<tiles_length; i+=1 ) {
        printf("%d\n", i);
        print_tile(tiles[i]);
        rotate_tile(tiles[i], 90, &rotated_tile);
        print_tile(rotated_tile);
        rotate_tile(tiles[i], 180, &rotated_tile);
        print_tile(rotated_tile);
        rotate_tile(tiles[i], 270, &rotated_tile);
        print_tile(rotated_tile);
    }

}


// // tile
// typedef Tile[5][5];


// int main(int argc, char **argv)
// {
    
//     vector<Tile> Tiles; 
//     Tile tile;
//     tiles.push_back(tile);

// }

struct board {
    char *data;
    int width;
    int height;
};

// set all values of the board to '.'
void initialize_board(int width, int height, struct board *ret_board) {

    struct board board;
    board.data = malloc( width * height * sizeof(char) );
    board.width = width;
    board.height = height;
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            board.data[width * y + x] = '.';
        }
    }
    *ret_board = board;
}

void print_board( struct board board ) {
    
    for(int y = 0; y < board.height; ++y) {
        for(int x = 0; x < board.width; ++x) {
            printf("%c", board.data[y * board.width + x]);
        }
        printf("\n");
    }
}

void make_move( struct board board, struct tile tile, int x, int y, int rotation_degrees, int *is_valid ) {
    
    struct tile rotated_tile;
    rotate_tile( tile, rotation_degrees, &rotated_tile );
    print_tile(rotated_tile);

    // x and y describe the middle character of the tile
    // so if we go from x-2,y-2 to x+2,y+2 on the board we cover the necessary space.
    
    *is_valid = 1;
    int tile_index = 0;
    for(int board_y = y-2; board_y <= y+2; ++board_y) {
        for(int board_x = x-2; board_x < x+2; ++board_x) {
            if ( rotated_tile.data[tile_index++] == ',' ) { 
                continue;
            } 
            if ( board_y < 0 || board_y > board.height-1 || board_x < 0 || board_x > board.width-1 ) {
                *is_valid = 0;
                return;
            }
        }
    }

    tile_index = 0;
    for(int board_y = y-2; board_y < y+3; ++board_y) {
        for(int board_x = x-2; board_x < x+3; ++board_x) {
            if ( rotated_tile.data[tile_index] == ',' ) { 
                tile_index++;
            } else {
                board.data[board_y * board.width + board_x] = rotated_tile.data[tile_index++];
            }
        }
    }

}

// read a newline '\n' or null byte '\0' terminated line
void read_line(FILE* file, char **ret_line) {

    printf("> ");
    char *line = (char*)malloc(1000);
    int allocated = 1000;
    int length = 0;

    while (1) {
        
        if (length == allocated) {
            allocated *= 2;
            line = (char*)realloc(line, allocated);
        }
        
        int character = fgetc(file);
        if (character == '\0' || character == '\n') {
            line[length++] = '\0';
            break;
        } else {
            line[length++] = (char)character;
        }
    }
    *ret_line = line;
    // *ret_length = length;
}





int main(int argc, char **argv)
{

    struct tile *tiles = NULL;
    int tiles_length = 0;
    {
        char *file_string = NULL; 
        int string_length = -1;
        read_file( "tilefile", &file_string, &string_length );
        // printf("%s", file_string);
        // printf("%d\n", string_length);
        parse_tiles3( file_string, string_length, &tiles, &tiles_length );
        free(file_string);
    }

    // // print tiles
    // for ( int tiles_index=0; tiles_index<tiles_length; ++tiles_index) {
    //     char tile_string[31];
    //     sprint_tile(tiles[tiles_index], tile_string);
    //     printf("%d\n%s", tiles_index, tile_string);
    // }

    // print_all_tiles_in_all_rotations(tiles, tiles_length);

    struct board board;
    int width = 10;
    int height = 12;
    initialize_board( width, height, &board );
    print_board( board );
    printf("\n\n");


    int is_valid = 0;
    make_move(board, tiles[0], 2,2,90, &is_valid);
    if (is_valid != 1) {
        printf("INVALID MOVE\n");
    }
    print_board( board );


    while (1) {
        char *line = NULL;
        read_line(stdin, &line);
        printf("%s\n", line);
    }

    int row, column, rotate;
    sscanf(line, "%d %d %d\n", &row, &column, &rotate);
    printf("%d %d rotated %d\n", row, column, rotate);

    return 0;
}

