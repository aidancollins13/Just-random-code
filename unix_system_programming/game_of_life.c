#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void free_cells(char ** cells, int rows, int columns){ // This function clears the memory reserved for cells

    for(int i = 0; i< rows+2; i++){ //first clear all of the rows
        free(cells[i]);
    }
    free(cells);   //then we clear the columns 
    return;

}

char **  read_file(int rows, int columns, FILE * file) { //this function allocates a 2D array for the cells (leaving buffer rows)
    char** cells = (char**)malloc(sizeof(char*)*rows+2);
    for(int i = 0; i< rows+2; i++){
        cells[i] = (char*)malloc(sizeof(char*)*columns+2);
    }

    for(int i = 0; i< rows+2; i++){                         // then fills it with dead cells
        for(int j = 0; j < columns+2; j++)
            cells[i][j] = '-';
    }


    int fc;
    for(int i = 1; i < rows-1; i++){                      // It then fills the cells with what it reads from the file
        for(int j = 1; j < columns-1; j++){
            if((fc = fgetc(file)) == EOF){
                fprintf(stderr, "error reading rile\n");
                exit(1);
            }
            cells[i][j] = fc;
        }
    }
    fclose(file);
    return cells;       //It retruns a pointer to the array
 
}

void print_cells(char ** cells, int rows, int columns, FILE * fd){  //This prints the contents of the array char by char
    for(int i = 1; i< rows-1; i++){
        for(int j = 1; j < columns-1; j++)
            fprintf(fd, "%c", cells[i][j]);
       fprintf(fd, "\n");
    }
}


int num_of_neighbors(char ** cells, int row, int col){ // this checks all the possible positions for neighbors and returns the total number
    int neighbors = 0;
    if(cells[row][col-1] == '*') neighbors++;
    if(cells[row][col+1] == '*') neighbors++;
    if(cells[row-1][col] == '*') neighbors++;
    if(cells[row+1][col] == '*') neighbors++;
    if(cells[row-1][col-1] == '*') neighbors++;
    if(cells[row-1][col+1] == '*') neighbors++;
    if(cells[row+1][col-1] == '*') neighbors++;
    if(cells[row+1][col+1] == '*') neighbors++;

    return neighbors;
}

void advance_gen(char ** cells, int rows, int columns){ //this advances a single generation
    int r=1, c=1, num;

    char** new_cells = (char**)malloc(sizeof(char*)*rows+2); // it first creats a new array
        for(int i = 0; i< rows+2; i++){
            new_cells[i] = (char*)malloc(sizeof(char*)*columns+2);
        }
    for(int i = 0; i< rows+2; i++){                         // then fills it with dead cells
        for(int j = 0; j < columns+2; j++)
            new_cells[i][j] = '-';
    }


    for(; r < rows-1; r++) {                         // and checks the old array to see which cells should be alive or dead
        for(; c < columns-1; c++) {
            num = num_of_neighbors(cells, r, c);
            if(cells[r][c] == '*') {
                if(num == 2 || num == 3 )
                    new_cells[r][c] = '*';
            }
            else{
                if(num == 3)
                    new_cells[r][c] = '*';
                else
                    new_cells[r][c] = '-';
            }
        }
    }
    for(int i = 0; i <rows+2; i++){
        for(int j = 0; j<columns+2; j++){
            cells[i][j] = new_cells[i][j];
        }
    }
    free_cells(new_cells, rows, columns);            // and clears the old array

}


int main( int argc, char** argv) {
    FILE *  input = fopen("life.txt", "r");  //We start off by oppening the initial file
    if (input == 0) {
        fprintf(stderr, "failed to open input.txt\n");
        exit(1);
    }

    char * strtol_err;
    long generations = 10;
    char * out_name = "output.txt";
    long rows = 10;
    long columns = 10;
    FILE * outfile;
 
    if(argc > 3) {
        generations = strtol(argv[4], &strtol_err, 10);     //We then get the arguments
    }

    if(argc > 2) {
        out_name = argv[3];
    }

    if(argc > 1) {
        rows = strtol(argv[1], &strtol_err, 10);
        columns = strtol(argv[2], &strtol_err, 10);
    }

    char ** cells = read_file(rows, columns, input);        // we get the 2d array from the file

    char outbuf[100];           // apparently i have to do this because i cant pass in just a char * to fopen
    snprintf(outbuf, sizeof(outbuf), "%s", out_name);

    outfile = fopen(outbuf, "a+");
    if (outfile == NULL) {
        fprintf(stderr, "failed to open output file %s\n", out_name);
        exit(1);
    }


    for(int i = 0; i < generations; i++){                   // we itterate over the appropriate generations
        fprintf(outfile, "Generation %d\n", i);
        print_cells(cells, rows, columns, outfile);
        advance_gen(cells, rows, columns);

    }
    
    fclose(outfile);
    free_cells(cells, rows, columns);

}
