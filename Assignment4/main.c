/*
* Programmer:   Jose R Hernandez
* Panther ID:   1398700
* Course:       Systems Programming - COP4338 U01 1211
* Instructor:   Kianoosh G. Boroojeni, Ph.D.
* Assignment:   4
*
* This program creates polygons and stores them into a list of polygons using the 'add' command.
* The program moves a selected polygon in a desired direction (up, down, left, right, up-right, up-left, down-right, down-left)
* a chosen number of spaces.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUM_OF_POLYGONS 1000
#define MAX_TOKEN_TOKEN_LENGTH 100

typedef enum {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8
}Direction;

typedef struct {
    int x, y;
}Vertex;

typedef struct {
    int numberOfVertices;
    Direction shiftDirection;
    Vertex* vertexList;
}Polygon;

static Polygon polygons[MAX_NUM_OF_POLYGONS]; //lists of polygons

Vertex makeVertices(int x, int y) {
    //this function makes a vertex
    Vertex temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

char getCommandWord(char command[], int maxLength) {
    char lastCharacter;
    int i;

    for (i = 0; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';

    return lastCharacter;
}

char getVertexToken(char command[], int maxLength) {

    char lastCharacter;
    int i;

    for (i = 0; i < maxLength - 1 && (command[i] = getchar()) != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';

    return lastCharacter;
}

void handleAdd() {
    char token[MAX_TOKEN_TOKEN_LENGTH];
    Vertex* vertexes = (Vertex*)malloc(sizeof(Vertex) * 100); //declaring a Vertex* list of Vertices for a polygon & allocating memory for it
    Polygon* p_polygon = (Polygon*)malloc(sizeof(Polygon)); //declaring a polygon* polygon pointer & allocating memory for it
    int x, y, i, j;

    if (getVertexToken(token, MAX_TOKEN_TOKEN_LENGTH) != '\n') {
        printf("\nTOO MANY ARGUMENTS FOR THE ADD COMMAND\n");
        while (getVertexToken(token, MAX_TOKEN_TOKEN_LENGTH) != '\n');
        return;
    }
    int numOfVert = 0;

    //making a vertex & adding it to the vertexes' list for the polygon
    i = -1;
    char* temp;
    int count = 0, k;
    while (token[++i]) {
        if (token[i] == ' ')//skipping white spaces
            continue;
        j = i;//recording the beginning index of a new number

        while (token[++i])//splitting over white space
            if (token[i] == ' ')
                break;
        temp = malloc(i - j + 1);//+1 for \0
        k = 0;
        while (k < i-j){
            temp[k] = token[j + k];
            k++;
        }
        temp[k] = '\0';
        count++;
        if(count%2)
            x = atoi(temp);
        else {
            y = atoi(temp);
            ++numOfVert;
            Vertex v = makeVertices(x, y);
            if (vertexes) {
                vertexes[count/2-1] = v;
            }
        }
        if (!token[i])
            break;
    }

    if (numOfVert == 0) {
        printf("\nNO POLYGON TO ADD\n");
        return;
    }

    //making a polygon - number of vertexes is the size of the token/2 since every two digits makes the x and the y
    if (p_polygon) {
        p_polygon->numberOfVertices = numOfVert;
        p_polygon->shiftDirection = NONE;
        p_polygon->vertexList = vertexes;
    }

    //debugging print statements
    printf("\nPOLYGON ADDED!");
    if (p_polygon) {
        printf("\n\tNUMBER OF VERTICES: %d", p_polygon->numberOfVertices);
    }
    printf("\n\tPOLYGON NOT CURRENTLY SET TO MOVE IN ANY DIRECTION\n");
    if (p_polygon) {
        for (i = 0; i < p_polygon->numberOfVertices; i++) {
            if (p_polygon) {
                x = p_polygon->vertexList[i].x;
                y = p_polygon->vertexList[i].y;
                printf("\tVERTEX #%d: (%d, %d)\n", i + 1, x, y);
            }
        }
    }

    //adding the polygon to the program's list of polygon
    for (i = 0; i < MAX_NUM_OF_POLYGONS; i++) {
        if (polygons[i].numberOfVertices == 0) {
            if(p_polygon){
                polygons[i] = *p_polygon;
            }
            break;
        }
    }
}

char* getDirectionStr(int direction) {

    char* str;
    str = malloc(11);

    switch (direction) {
    case NONE:
        str = "NONE";
        break;
    case UP:
        str = "UP";
        break;
    case DOWN:
        str = "DOWN";
        break;
    case LEFT:
        str = "LEFT";
        break;
    case RIGHT:
        str = "RIGHT";
        break;
    case UP | RIGHT:
        str = "UP-RIGHT";
        break;
    case DOWN | RIGHT:
        str = "DOWN-RIGHT";
        break;
    case UP | LEFT:
        str = "UP-LEFT";
        break;
    case DOWN | LEFT:
        str = "DOWN-LEFT";
        break;
    default:
        break;

    }
    return str;
}

void handleSummary() {

    int i, j;

    //making sure the list of polygons is not empty
    if (polygons[0].numberOfVertices == 0) {
        printf("\nTHE PROGRAM'S LIST OF POLYGONS IS EMPTY! PLEASE ADD SOME!\n");
        return;
    }

    //accessing & printing the list of polygons
    printf("\n****************ACCESSING THE PROGRAM'S LIST*************\n\n");
    for (i = 0; i < MAX_NUM_OF_POLYGONS && polygons[i].numberOfVertices != 0; i++) {

        int av_x = 0;
        int av_y = 0;
        int numberOfVertex = polygons[i].numberOfVertices;
        int directionStr = polygons[i].shiftDirection;

        printf("POLYGON %d: \n", i + 1);
        printf("\tNUMBER OF VERTICES: %d\n", numberOfVertex);
        printf("\tSHIFT DIRECTION SET TO: %s\n", getDirectionStr(directionStr));
        for (j = 0; j < polygons[i].numberOfVertices; j++) {
            printf("\tVERTEX #%d: (%d, %d)\n", j + 1, (polygons[i].vertexList[j].x), (polygons[i].vertexList[j].y));
        }

        for (j = 0; j < polygons[i].numberOfVertices; j++) {
            int x = polygons[i].vertexList[j].x;
            av_x += x;

            int y = polygons[i].vertexList[j].y;
            av_y += y;
        }
        //getting the average of the x-coordinates and the y-coordinates to find the Centroid of the polygon
        printf("\n\tCENTROID: (%.1f, %.1f)\n\n", (double)av_x / numberOfVertex, (double)av_y / numberOfVertex);
    }
    printf("\n****************END OF LIST******************************\n\n");
}

void handleTurn() {

    char token1[MAX_TOKEN_TOKEN_LENGTH];
    char token2[MAX_TOKEN_TOKEN_LENGTH];
    int polyIndex;  //variable to use as index for the desired polygon in the list
    char* dirMove; //string variable to store then shift direction set for the polygon
    dirMove = malloc(11);

    if (getCommandWord(token1, MAX_TOKEN_TOKEN_LENGTH) == '\n') {
        printf("\nTOO FEW ARGUMENTS FOR THE TURN COMMAND\n");
        return;
    }
    if (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n') {
        printf("\nTOO MANY ARGUMENTS FOR TURN COMMAND\n");
        while (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n');
        return;
    }

    polyIndex = atoi(token1) - 1;
    dirMove = token2;

    if (polyIndex < 0) {
        printf("\nERROR IN INPUT: ARGUMENT 1 MUST BE A NON-ZERO NUMBER\n");
        return;
    }

    //making sure the polygon at the polyIndex position is not empty
    if (polygons[polyIndex].numberOfVertices == 0) {
        printf("\nNO POLYGON FOUND\n");
        return;
    }
    //setting the polygon the new shift direction
    if (!strcmp(dirMove, "right")) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO RIGHT\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = RIGHT;
    }
    else if (!strcmp(dirMove, "left")) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO LEFT\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = LEFT;
    }
    else if (!strcmp(dirMove, "up")) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO UP\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = UP;
    }
    else if (!strcmp(dirMove, "down")) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO DOWN\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = DOWN;
    }
    else if ((!strcmp(dirMove, "right-up") || !strcmp(dirMove, "up-right"))) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO UP-RIGHT/RIGHT-UP\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = UP | RIGHT;
    }
    else if ((!strcmp(dirMove, "left-up") || !strcmp(dirMove, "up-left"))) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO LEFT-UP/UP-LEFT\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = LEFT | UP;
    }
    else if ((!strcmp(dirMove, "right-down") || !strcmp(dirMove, "down-right"))) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO RIGHT-DOWN/DOWN-RIGHT\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = RIGHT | DOWN;
    }
    else if ((!strcmp(dirMove, "left-down") || !strcmp(dirMove, "down-left"))) {
        printf("\nDIRECTION OF POLYGON %d CHANGED TO LEFT-DOWN/DOWN-LEFT\n", polyIndex + 1);
        polygons[polyIndex].shiftDirection = LEFT | DOWN;
    }
    else {
        printf("\nINCORRECT MOVE REQUEST!\n");
        printf("DIRECTION OF POLYGON REMAINS THE SAME\n");
    }
}

void handleShift() {

    char token1[MAX_TOKEN_TOKEN_LENGTH];
    char token2[MAX_TOKEN_TOKEN_LENGTH];
    int polyIndex, i, change = -1, changeDir;

    if (getCommandWord(token1, MAX_TOKEN_TOKEN_LENGTH) == '\n') {
        printf("\nTOO FEW ARGUMENTS FOR THE SHIFT COMMAND\n");
        return;
    }
    if (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n') {
        printf("\nTOO MANY ARGUMENTS FOR SHIFT COMMAND\n");
        while (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n');
        return;
    }

    polyIndex = atoi(token1) - 1;
    change = atoi(token2) - 1;

    //handling if the atoi() returns 0;
    if (change >= 0) {
        change++;
    }
    else {
        printf("\nERROR IN INPUT: ARGUMENT 2 MUST BE A NON-ZERO NUMBER\n");
        return;
    }

    //making sure we get the right index from input
    if (polyIndex < 0) {
        printf("\nERROR IN INPUT: ARGUMENT 1 MUST BE A NUMBER STARTING FROM 1\n");
        return;
    }
    //making sure there is a polygon at the polyIndex position
    if (polygons[polyIndex].numberOfVertices == 0) {
        printf("\nPOLYGON NOT FOUND\n");
        return;
    }
    //making sure the selected polygon has a shift direction already set
    if (polygons[polyIndex].shiftDirection == 0) {
        printf("\nPOLYGON REMAINS IN POSITION\n");
        return;
    }
    //getting the shift direction of the polygon
    changeDir = polygons[polyIndex].shiftDirection;

    //making the move of the polygon depending the direction and the amount of spaces from input
    switch (changeDir) {
    case UP:
        printf("\nPOLYGON %d HAS MOVED %d SPACES UP\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].y += change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    case DOWN:
        printf("\nPOLYGON %d HAS MOVED %d SPACES DOWN\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].y -= change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    case LEFT:
        printf("\nPOLYGON %d HAS MOVED %d SPACES LEFT\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].x -= change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    case RIGHT:
        printf("\nPOLYGON %d HAS MOVED %d SPACES RIGHT\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].x += change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    case UP | RIGHT:
        printf("\nPOLYGON %d HAS MOVED %d SPACES UP-RIGHT\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].x += change;
            polygons[polyIndex].vertexList[i].y += change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    case UP | LEFT:
        printf("\nPOLYGON %d HAS MOVED %d SPACES UP-LEFT\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].x -= change;
            polygons[polyIndex].vertexList[i].y += change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    case DOWN | RIGHT:
        printf("\nPOLYGON %d HAS MOVED %d SPACES DOWN-RIGHT\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].x += change;
            polygons[polyIndex].vertexList[i].y -= change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    case DOWN | LEFT:
        printf("\nPOLYGON %d HAS MOVED %d SPACES DOWN-LEFT\n", polyIndex + 1, change);
        for (i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
            polygons[polyIndex].vertexList[i].x -= change;
            polygons[polyIndex].vertexList[i].y -= change;
            polygons[polyIndex].shiftDirection = NONE;
        }
        break;
    default:
        printf("\nPOLYGON REMAINS UNMOVED\n");
        break;
    }
}

int main() {

    char command[MAX_TOKEN_TOKEN_LENGTH];
    char lastCharacter;

    printf("\nLIST OF COMMANDS:\n\n");
    printf("*****************************************************************************************************\n\n");
    printf("\t* add <x1 y1 x2 y2......xn yn>\t CREATES AND STORES POLYGON IN LIST\n\n");
    printf("\t* summary\t\t\t SHOWS THE LIST OF POLYGONS CREATED\n\n");
    printf("\t* turn <k> <DIRECTION>\t\t SETS THE SHIFT DIRECTION OF THE POLYGON k\n");
    printf("\t\t\t\t\t up, down, left, right, up-right/right-up,\n\t\t\t\t\t up-left/left-up, down-right/right-down, down-left/left-down\n\n");
    printf("\t* shift <k> <n>\t\t\t MOVES THE POLYGON k, n SPACES\n\n");
    printf("\t* quit\t\t\t\t TERMINATES THE PROGRAM\n\n");
    printf("*****************************************************************************************************\n\n\n");

    while (1) {
        printf("\nPlease enter a new command: ");
        lastCharacter = getCommandWord(command, MAX_TOKEN_TOKEN_LENGTH);

        if (!strcmp(command, "quit")) {
            printf("\nTERMINATING PROGRAM\n");
            break;
        }
        else if (!strcmp(command, "add")) {
            if (lastCharacter == '\n') {
                printf("\nERROR IN INPUT\n");
            }
            else {
                handleAdd();
            }
        }
        else if (!strcmp(command, "summary")) {
            if (lastCharacter != '\n') {
                printf("\nERROR IN INPUT\n");
            }
            else {
                handleSummary();
            }
        }
        else if (!strcmp(command, "turn")) {
            if (lastCharacter == '\n') {
                printf("\nERROR IN INPUT\n");
            }
            else {
                handleTurn();
            }
        }
        else if (!strcmp(command, "shift")) {
            if (lastCharacter == '\n') {
                printf("\nERROR IN INPUT");
            }
            else {
                handleShift();
            }
        }
        else {
            printf("\nInvalid Command!\n");
            while (lastCharacter != '\n')
                lastCharacter = getCommandWord(command, MAX_TOKEN_TOKEN_LENGTH);
        }
    }
}
