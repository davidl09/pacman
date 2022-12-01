#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "colours.h"
#include <ctype.h>
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
const int rows = 11;
const int cols = 11;
FILE *map;
void printMap(char* ptr[rows][cols]);
int winCheck(char* ptr[rows][cols]);
int loseCheck(char* ptr[rows][cols]);
int isWall(char* ptr);
int isGhost(char* ptr);
char* pacManLocation(char* currentLocation, char*ptr[rows][cols], char input);
char* ghostMotion(char* ghostLocation, char* ptr[rows][cols], char dir);
char ghostAlgo(char* ghostLocation, char*ptr[rows][cols], char dir);
char randomDir(char* ghostLocation, char* ptr[rows][cols], char dir);


int main() {
    char* pointerToMap[rows][cols];
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            (pointerToMap[i][j]) = malloc(sizeof(char));
            if(pointerToMap[i][j] == NULL){
                printf("Memory allocation failed. Please try again");
            }
        }
    }

    map = fopen("C:\\Users\\dalae\\CLionProjects\\apsc143FinalAssign\\map.txt", "r");

    for(int i = 0; i<rows; i++){
        for(int j = 0; j< cols; j++){
            fscanf(map, "%s", pointerToMap[i][j]);
        }
    }

    char* currentLocation = pointerToMap[5][5];
    char* ghostA = pointerToMap[1][1];
    char* ghostB = pointerToMap[9][9];
    char dirA = RIGHT;
    char dirB = LEFT;
    printMap(pointerToMap);



    while(!winCheck(pointerToMap) && !loseCheck(pointerToMap)){ 
        char input = tolower((char)getch());
        if(input != UP && input != LEFT && input != RIGHT && input != DOWN){
            continue;
        }else{
            dirA = ghostAlgo(ghostA, pointerToMap, dirA);
            dirB = ghostAlgo(ghostB, pointerToMap, dirB);
            if(ghostA == ghostB){
                dirB = randomDir(ghostB, pointerToMap, dirB);
            }
            currentLocation = pacManLocation(currentLocation, pointerToMap, input);

            ghostA = ghostMotion(ghostA, pointerToMap, dirA);
            ghostB = ghostMotion(ghostB, pointerToMap, dirB);

            winCheck(pointerToMap), loseCheck(pointerToMap);
            system("cls");
            printMap(pointerToMap);

            if (winCheck(pointerToMap)) {
                colourChange(2);
                printf("\n\nCongratulations! You win! Press any key to exit the game\n");
                input = getch();
                if(input)
                    break;
            }

            else if (loseCheck(pointerToMap)) {
                colourChange(4);
                printf("\n\nSorry, you lose. Press any key to exit the game\n");
                input = getch();
                if(input)
                    break;
            }
        }
    }

    //end of game loop when winCheck() or loseCheck break the loop.
    for(int i = 0; i<rows; i++){
        for(int j = 0; j< cols; j++){
            free(pointerToMap[i][j]);
        }
    }
}

void printMap(char* ptr[rows][cols]){
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            if(*ptr[i][j] == GHOST)
                colourChange(PINK);
            else if(*ptr[i][j] == PACMAN)
                colourChange(YELLOW);
            else if(*ptr[i][j] == DOT)
                colourChange(WHITE);
            else colourChange(BLUE);
            printf("%c ", *ptr[i][j]);

        }printf("\n");
    }printf("\n\n\n");
}


char* pacManLocation(char* currentLocation, char* ptr[rows][cols], char input){
    int row, col;

    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            if(currentLocation == ptr[i][j]){
                row = i;
                col = j;
                break;
            }
        }
    }

    if(input == LEFT){
        col--;
        if(!isWall(ptr[row][col]) && !isGhost(ptr[row][col])){
            *currentLocation = EMPTY;
            *ptr[row][col] = PACMAN;
            return ptr[row][col];
        }else if(isGhost(ptr[row][col])) {
            *currentLocation = EMPTY;
            *ptr[row][col] = GHOST;
            return currentLocation;
        }else return currentLocation;
    }else if(input == RIGHT){
        col++;
        if(!isWall(ptr[row][col]) && !isGhost(ptr[row][col])) {
            *currentLocation = EMPTY;
            *ptr[row][col] = PACMAN;
            return ptr[row][col];
        }else if(isGhost(ptr[row][col])){
            *currentLocation = EMPTY;
            *ptr[row][col] = GHOST;
            return currentLocation;
        }else return currentLocation;
    }else if(input == UP){
        row--;
        if(!isWall(ptr[row][col]) && !isGhost(ptr[row][col])){
            *currentLocation = EMPTY;
            *ptr[row][col] = PACMAN;
            return ptr[row][col];
        }else if(isGhost(ptr[row][col])) {
            *currentLocation = EMPTY;
            *ptr[row][col] = GHOST;
            return currentLocation;
        }else return currentLocation;
    }else if(input == DOWN){
        row++;
        if(!isWall(ptr[row][col]) && !isGhost(ptr[row][col])){
            *currentLocation = EMPTY;
            *ptr[row][col] = PACMAN;
            return ptr[row][col];
        }else if(isGhost(ptr[row][col])) {
            *currentLocation = EMPTY;
            *ptr[row][col] = GHOST;
            return currentLocation;
        }else return currentLocation;
    }
    else return currentLocation;
}

char randomDir(char* ghostLocation, char* ptr[rows][cols], char dir){ //returns a legal (non-wall) direction, preferrably not opposite the given direction.
    int row, col;
    for (int i = 0; i < rows; i++) { //find the location of the ghost in terms of rows and columns.
        for (int j = 0; j < cols; j++) {
            if (ptr[i][j] == ghostLocation) {
                row = i;
                col = j;
                break;
            }
        }
    }


    char newDir;
    if(!isWall(ptr[row][col+1]) && dir != LEFT) {
        newDir = RIGHT;
        //printf("Random dir is right\n");
    }else if(!isWall(ptr[row+1][col]) && dir != UP){
        newDir = DOWN;
        //printf("Random dir is down\n");
    }else if(!isWall(ptr[row][col-1]) && dir != RIGHT) {
        newDir = LEFT;
        //printf("Random dir is left\n");
    }else newDir = UP; //printf("Random dir is up\n");

    return newDir;
}

char ghostAlgo(char* ghostLocation, char* ptr[rows][cols], char dir) {
    int row, col;
    int dirUp = 1, dirDown = 1, dirLeft = 1, dirRight = 1;

    for (int i = 0; i < rows; i++) { //find the location of the ghost in terms of rows and columns.
        for (int j = 0; j < cols; j++) {
            if (ptr[i][j] == ghostLocation) {
                row = i;
                col = j;
                break;
            }
        }
    }
    //printf("Looking for pacman\n");
    // The following block looks for pacman until it sees walls in all 4 directions. If it sees pacman it sets the direction accordingly.
    for(int i = 1; dirUp == 1 || dirDown == 1 || dirLeft == 1 || dirRight == 1; i++){ // all 4 directions are marked as valid (1) until a wall is encountered (0).

        if(row-i > 0 && !isWall(ptr[row-i][col]) && dirUp == 1) {
            //printf("Looking up\n");
            dirUp = 1;
            if(*ptr[row-i][col] == PACMAN) {
                dir = UP;
                return dir;
            }
        }
        else dirUp = 0;

        if(row+i < 11 && !isWall(ptr[row+i][col]) && dirDown == 1) {
            //printf("Looking down\n");
            dirDown = 1;
            if(*ptr[row+i][col] == PACMAN) {
                dir = DOWN;
                return dir;
            }
        }
        else dirDown = 0;

        if(col-i > 0 && !isWall(ptr[row][col-i]) && dirLeft== 1) {
            //printf("Looking left\n");
            dirLeft = 1;
            if(*ptr[row][col-i] == PACMAN) {
                dir = LEFT;
                return dir;
            }
        }
        else dirLeft = 0;

        if(col+i < 11 &&!isWall(ptr[row][col+i]) && dirRight == 1) {
            //printf("Looking right\n");
            dirUp = 1;
            if(*ptr[row][col+i] == PACMAN) {
                dir = RIGHT;
                return dir;
            }
        }
        else dirRight = 0;
    }


    //printf("Pacman not found, trying %c\n", dir);


    if(dir == UP && !isWall(ptr[row - 1][col])) {
        //printf("Going up\n");
        dir = UP;
        return dir;
    }
    else if(dir == DOWN && !isWall(ptr[row + 1][col])){
        //printf("Going down\n");
        dir = DOWN;
        return dir;
    }
    else if(dir == RIGHT && !isWall(ptr[row][col +1])) {
        //printf("Going right\n");
        dir = RIGHT;
        return dir;
    }
    else if(dir == LEFT && !isWall(ptr[row][col-1])) {
        //printf("Going left\n");
        dir = LEFT;
        return dir;
    }
    else{
        //printf("Trying random\n");
        dir = randomDir(ghostLocation, ptr, dir);
        return dir;
    }

}


char* ghostMotion(char* ghostLocation, char* ptr[rows][cols], char dir){
    int row, col;
    for (int i = 0; i < rows; i++) { //find the location of the ghost in terms of rows and columns.
        for (int j = 0; j < cols; j++) {
            if (ptr[i][j] == ghostLocation) {
                row = i;
                col = j;
                break;
            }
        }
    }

    //printf("Ghost is at %d, %d\n", row, col);

    if(dir == UP && !isWall(ptr[row-1][col])){
        if(*ptr[row-1][col] == EMPTY || *ptr[row-1][col] == PACMAN || *ptr[row-1][col] == GHOST)
            *ptr[row][col] = EMPTY;
        else *ptr[row][col] = DOT;
        row--;
        *ptr[row][col] = GHOST;
    }else if(dir == DOWN && !isWall(ptr[row+1][col])) {
        if(*ptr[row+1][col] == EMPTY || *ptr[row+1][col] == PACMAN || *ptr[row+1][col] == GHOST)
            *ptr[row][col] = EMPTY;
        else *ptr[row][col] = DOT;
        row++;
        *ptr[row][col] = GHOST;
    }else if(dir == LEFT && !isWall(ptr[row][col-1])) {
        if(*ptr[row][col-1] == EMPTY || *ptr[row][col-1] == PACMAN || *ptr[row][col-1] == GHOST)
            *ptr[row][col] = EMPTY;
        else *ptr[row][col] = DOT;
        col--;
        *ptr[row][col] = GHOST;
    }else if(dir == RIGHT && !isWall(ptr[row][col+1])) {
        if(*ptr[row][col+1] == EMPTY || *ptr[row][col+1] == PACMAN || *ptr[row][col+1] == GHOST)
            *ptr[row][col] = EMPTY;
        else *ptr[row][col] = DOT;
        col++;
        *ptr[row][col] = GHOST;
    }else return ghostMotion(ghostLocation, ptr, randomDir(ghostLocation, ptr, dir));//printf("Direction passed to motion fx was not valid\n");

    //printf("Ghost moved to %d, %d\n", row, col);
    return ptr[row][col];
}

int winCheck(char* ptr[rows][cols]){
    int dots = 0;
    for(int i = 0; i< rows; i++){
        for(int j = 0; j< cols; j++){
            if (*ptr[i][j] == DOT)
                dots++;
        }
    }
    if(dots == 0)
        return 1;
    else return 0;
}

int loseCheck(char* ptr[rows][cols]){
    int pacman = 0;
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            if(*ptr[i][j] == PACMAN)
                pacman++;
        }
    }
    if(pacman == 0)
        return 1;
    else return 0;
}

int isWall(char* ptr){
    if(*ptr != WALL)
        return 0;
    else return 1;
}

int isGhost(char* ptr){
    if(*ptr == GHOST)
        return 1;
    else return 0;
}