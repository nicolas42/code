#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <vector>
#include "read_file.h"
#include "assert.h"

int DEBUG = 0;

struct tile { 
    char data[25]; 
};


struct board {
    char *data;
    int width;
    int height;
};

struct move { 
    int row;
    int column;
    int rotation;
};

struct player {
    char symbol;
    struct move last_move;
};


void parse_tiles( char *string, int string_length, struct tile** ret_tiles, int* ret_tiles_length )
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

// make move or return error -1 if the move is invalid
int is_move_valid( struct board board, struct tile tile_arg, int x, int y, int rotation_degrees) {
    
    if (!(rotation_degrees == 0 || rotation_degrees == 90 || rotation_degrees == 180 || rotation_degrees == 270 )) {
        // return error if the rotation value is invalid
        return 0;
    }

    struct tile tile;
    rotate_tile( tile_arg, rotation_degrees, &tile );
    // print_tile(tile);

    // x and y describe the middle character of the tile
    // so if we go from x-2,y-2 to x+2,y+2 on the board we cover the necessary space.
    
    int tile_index = 0;
    for(int board_y = y-2; board_y <= y+2; ++board_y) {
        for(int board_x = x-2; board_x <= x+2; ++board_x) {
            char board_data = board.data[board_y * board.width + board_x];

            if (DEBUG) printf("board_y, board_x, tile_index, board_data, tile.data[tile_index]: %d %d %d %c %c\n", board_y, board_x, tile_index, board_data, tile.data[tile_index]);

            if ( tile.data[tile_index] == '!' ) {
                if ( board_y < 0 || board_y > board.height-1 || board_x < 0 || board_x > board.width-1 ) {
                    if (DEBUG) printf("invalid move.  value out of bounds\n");
                    return 0;
                } else if ( board.data[board_y * board.width + board_x] != '.' ) { 
                    if (DEBUG) printf("invalid move.  collision\n");
                    return 0;
                }
            }
            tile_index++; 

        }
    }

    return 1;
}





// make move or return error -1 if the move is invalid
int make_move( struct board board, struct tile tile_arg, int x, int y, int rotation_degrees, struct player player) {

    struct tile tile;
    rotate_tile( tile_arg, rotation_degrees, &tile );
    // print_tile(tile);

    int tile_index = 0;
    for(int board_y = y-2; board_y <= y+2; ++board_y) {
        for(int board_x = x-2; board_x <= x+2; ++board_x) {
            if ( tile.data[tile_index] == ',' ) { 
            } else {
                board.data[board_y * board.width + board_x] = player.symbol;
            }
            tile_index++;
        }
    }
    return 0;
}

// read a newline '\n' or null byte '\0' terminated line
void read_line(FILE* file, char **ret_line) 
{

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


// void parse_input_line(char *line)
// {
//     char* offsets[3];
//     int offsets_length = 0;
//     offsets[offsets_length++] = line;
//     for (int i=1; line[i] != '\0'; i+=1 ) {
//         if (line[i] == ' ') {
//             offsets[offsets_length++] = line+i;
//         }
//     }
//     int inputs[3];
//     int inputs_length = 0;
//     for (int i=0; i<3; i+=1) {
//         char *ptr;
//         inputs[i] = (int)strtol(offsets[i], &ptr, 10);    
//     }
//     for (int i=0; i<3; i+=1) {
//         printf("%d ", inputs[i]);
//     }
// }


// return 1 if valid move is found
int get_automatic_player_move_type_1(struct board board, struct tile tile, struct move last_move, struct move *ret_move)
{
    int rstart = last_move.row;
    int cstart = last_move.column;
    int theta = 0;

    int r = rstart;
    int c = cstart;
    for ( int theta = 0; theta < 360; theta += 90 ) {
        while (1) {
            if (DEBUG) printf("r,c,theta %d %d %d\n", r,c,theta);
            
            if (is_move_valid(board, tile, r, c, theta)){
                ret_move->row = r;
                ret_move->column = c;
                ret_move->rotation = theta;
                return 1;
            } 
            c += 1;
            if (c > board.width-1 + 2) {
                c = -2;
                r += 1;
            }
            if (r > board.height-1 + 2) {
                r = -2;
            }
            if ( r == rstart && c == cstart ) { break; }
        }
    } 

    return 0;
}




// // return 1 if valid move is found
// int get_automatic_player_move_type_2(struct board board, struct tile tile, struct move last_move_from_this_player, int player_number, struct move *ret_move)
// {

//     int rstart = last_move_from_this_player.row;
//     int cstart = last_move_from_this_player.column;
//     int theta = 0;

//     int r = rstart;
//     int c = cstart;
//     for ( int theta = 0; theta < 360; theta += 90 ) {
//         while (1) {
//             if (DEBUG) printf("r,c,theta %d %d %d\n", r,c,theta);
            
//             if (is_move_valid(board, tile, r, c, theta)){
//                 ret_move->row = r;
//                 ret_move->column = c;
//                 ret_move->rotation = theta;
//                 return 1;
//             } 
//             c += 1;
//             if (c > board.width-1 + 2) {
//                 c = -2;
//                 r += 1;
//             }
//             if (r > board.height-1 + 2) {
//                 r = -2;
//             }
//             if ( r == rstart && c == cstart ) { break; }
//         }
//     } 

//     return 0;
// }


int toggle(int a)
{
    if (a == 0){
        return 1;
    } else {
        return 0;
    }
}

int rotate(int a, int min, int max)
{
    a += 1;
    if ( a > max) {
        a = min;
    }
    return a;
}

int main(int argc, char **argv)
{

    // get command line arguments



    // load tiles
    struct tile *tiles = NULL;
    int tiles_length = 0;
    int tiles_index = 0;
    {
        char *file_string = NULL; 
        int string_length = -1;
        read_file( "tilefile", &file_string, &string_length );
        if (DEBUG) printf("%s", file_string);
        if (DEBUG) printf("%d\n", string_length);
        parse_tiles( file_string, string_length, &tiles, &tiles_length );
        free(file_string);
    }
    // for ( int i=0; i<tiles_length; i+=1 ) {
    //     print_tile(tiles[i]);
    // }

    // print_all_tiles_in_all_rotations(tiles, tiles_length);


    // initialize board
    struct board board;
    int width = 8;
    int height = 8;
    initialize_board( width, height, &board );
    // print_board( board );
    // printf("\n\n");


    // setup players
    // player 1 is at index 0.  player 2 is at index 1
    struct player players[2];
    int player_index = 0;
    players[0].symbol = '#';
    players[0].last_move.column = -2;
    players[0].last_move.row = -2;
    players[1].symbol = '*';
    players[1].last_move.column = -2;
    players[1].last_move.row = -2;




    // main loop
    while (1) {
        if (DEBUG) printf("tiles_index, tiles_length %d %d\n", tiles_index, tiles_length);

        print_board( board );
        printf("\n");
        print_tile(tiles[tiles_index]);



        while (1){
            // get move from automatic player type 1
            printf("> ");
            fgetc(stdin);
            struct move m;
            struct move last_move = players[toggle(player_index)].last_move;
            if (get_automatic_player_move_type_1(board, tiles[tiles_index], last_move, &m)){
                if (DEBUG) printf("move found - row column rotation: %d %d %d\n", m.row, m.column, m.rotation);
                make_move(board, tiles[tiles_index], m.row, m.column, m.rotation, players[player_index]);
                players[player_index].last_move = m;
                break;
            } else {
                printf("INVALID MOVE\n");
            }
        }


        // // get move from human
        // while (1) {
        //     struct move m;
        //     printf("> ");
        //     char *line = NULL;
        //     m.row = -1;
        //     m.column = -1;
        //     m.rotation = -1;
        //     read_line(stdin, &line);
        //     sscanf(line, "%d %d %d\n", &(m.row), &(m.column), &(m.rotation));
        //     free(line);
        //     printf("%d %d rotated %d\n", m.row, m.column, m.rotation);
            
        //     if (is_move_valid(board, tiles[tiles_index], m.row, m.column, m.rotation)){
        //         make_move(board, tiles[tiles_index], m.row, m.column, m.rotation, players[player_index]);
        //         players[player_index].last_move = m;
        //         break;
        //     } else {
        //         printf("INVALID MOVE\n");
        //     }
        // }

        
        tiles_index = rotate(tiles_index, 0, tiles_length-1);
        player_index = toggle(player_index);
    }


    free(tiles);
    free(board.data);
    return 0;
}

