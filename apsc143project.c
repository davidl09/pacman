#include <stdio.h>
#include <stdlib.h>

//#include <colours.h>

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
    char dirA = RIGHT;//randomDir(ghostA, pointerToMap, UP);
    char dirB = LEFT; //randomDir(ghostB, pointerToMap, DOWN);
    printf("Printing map\n");
    printMap(pointerToMap);
    printf("Printed Map\n");

    //the part after this needs to loop for the duration of the game.

    while(!winCheck(pointerToMap) && !loseCheck(pointerToMap)){
        char input = (char)getchar();
        if(input != UP && input != LEFT && input != RIGHT && input != DOWN){
            continue;
        }else{

            dirA = ghostAlgo(ghostA, pointerToMap, dirA);
            //dirB = ghostAlgo(ghostB, pointerToMap, dirB);
            printf("Direction of A is %c, direction of B is %c\n", dirA, dirB);

            ghostA = ghostMotion(ghostA, pointerToMap, dirA);
            //ghostB = ghostMotion(ghostB, pointerToMap, dirB);


            currentLocation = pacManLocation(currentLocation, pointerToMap, input);

            winCheck(pointerToMap), loseCheck(pointerToMap);

            printMap(pointerToMap);

            if (winCheck(pointerToMap) == 1) {
                printf("Congratulations! You win! Press any key to exit the game\n");
                break;
            }

            else if (loseCheck(pointerToMap) == 1) {
                printf("Sorry, you lose. Press any key to exit the game\n");
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
            printf("%c  ", *ptr[i][j]);
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

char randomDir(char* ghostLocation, char* ptr[rows][cols], char dir){
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
    if(!isWall(ptr[row][col+1])) {
        newDir = RIGHT;
    }else if(!isWall(ptr[row+1][col])){
        newDir = DOWN;
    }else if(!isWall(ptr[row][col-1])) {
        newDir = LEFT;
    }else newDir = UP;

    return newDir;
}

char ghostAlgo(char* ghostLocation, char* ptr[rows][cols], char dir) {
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

// The following block looks for pacman until it sees walls in all 4 directions. If it sees pacman it sets the direction accordingly.

    for(int i = 0; i < 10; i++){
        printf("Looking for pacman  ");

        if (i < row && *ptr[row-i][col] != WALL) {
            if (*ptr[row - i][col] == PACMAN) {
                printf("pacman is above\n");
                dir = UP;
                return dir;
            }
        }
        if(i < cols-col && *ptr[row][col+i] != WALL){
            if(i < cols - col && *ptr[row][col+i] == PACMAN){
                printf("pacman is to the right\n");
                dir = RIGHT;
                return dir;
            }
        }
        if (i < rows-row && *ptr[row+i][col] != WALL) {
            if (*ptr[row + i][col] == PACMAN) {
                printf("pacman is below");
                dir = DOWN;
                return dir;
            }
        }
        if(i < col && *ptr[row][col-i] != WALL){
            if(*ptr[row][col-i] == PACMAN){
                printf("pacman is to the left\n");
                dir = LEFT;
                return dir;
            }
        }
    }

    printf("Pacman not found, trying %c\n", dir);


    if(dir == UP && !isWall(ptr[row - 1][col])) {
        printf("Trying up\n");
        dir = UP;
        return dir;
    }
    else if(dir == DOWN && !isWall(ptr[row + 1][col])){
        printf("Trying down\n");
        dir = DOWN;
        return dir;
    }
    else if(dir == RIGHT && !isWall(ptr[row][col +1])) {
        printf("Trying right\n");
        dir = RIGHT;
        return dir;
    }
    else if(dir == LEFT && !isWall(ptr[row][col-1])) {
        printf("Trying left\n");
        dir = LEFT;
        return dir;
    }
    else{
        printf("Trying random\n");
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

    printf("Ghost is at %d, %d\n", row, col);

    if(dir == UP && !isWall(ptr[row-1][col])){
        if(*ptr[row-1][col] == DOT)
            *ptr[row][col] = DOT;
        else *ptr[row-1][col] = EMPTY;
        row--;
        *ptr[row][col] = GHOST;
    }else if(dir == DOWN && !isWall(ptr[row+1][col])) {
        if(*ptr[row+1][col] == DOT)
            *ptr[row][col] = DOT;
        else *ptr[row][col] = EMPTY;
        row++;
        *ptr[row][col] = GHOST;
    }else if(dir == LEFT && !isWall(ptr[row][col-1])) {
        if(*ptr[row][col-1] == DOT)
            *ptr[row][col] = DOT;
        else *ptr[row][col-1] = EMPTY;
        col--;
        *ptr[row][col] = GHOST;
    }else if(dir == RIGHT && !isWall(ptr[row][col+1])) {
        if(*ptr[row][col+1] == DOT)
            *ptr[row][col] = DOT;
        else *ptr[row][col] = EMPTY;
        col++;
        *ptr[row][col] = GHOST;
    }

    printf("Ghost moved to %d, %d\n", row, col);
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
    if(*ptr == WALL)
        return 1;
    else return 0;
}

int isGhost(char* ptr){
    if(*ptr == GHOST)
        return 1;
    else return 0;
}