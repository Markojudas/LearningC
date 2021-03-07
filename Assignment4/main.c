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

void handleAdd() {
    char token[MAX_TOKEN_TOKEN_LENGTH];
    Vertex* vertices = (Vertex*)malloc(sizeof(Vertex)*100); //declaring a Vertex* list of Vertices for a polygon & allocating memory for it
    Polygon *p_polygon = (Polygon*)malloc(sizeof(Polygon)); //declaring a polygon* polygon pointer & allocating memory for it
    int x, y;

    if (getCommandWord(token, MAX_TOKEN_TOKEN_LENGTH) != '\n') {
        printf("\nTOO MANY ARGUEMENTS FOR THE ADD COMMAND\n");
        while (getCommandWord(token, MAX_TOKEN_TOKEN_LENGTH) != '\n');
        return;
    }
    int size_of_token = 0;

    //getting the size of the input token
    for (int i = 0; i < MAX_TOKEN_TOKEN_LENGTH && token[i] != '\0'; i++) {
        ++size_of_token;
    }

    //making sure the input has enough to create the x's and y's (it has to be an even amount of character digits)
    if ((size_of_token % 2) != 0) {
        printf("'\nINVALID INPUT: IT HAS TO BE AN EVEN AMOUNT OF DIGITS\n");
        return;
    }

    //making a vertex & adding it to the vertices' list for the polygon
    for (int i = 0, j = 0; i < size_of_token; i += 2, j++) {
        x = token[i];
        y = token[i + 1];
        Vertex v = makeVertices(x, y);
        vertices[j] = v;
    }

    //making a polygon - number of vertices is the size of the token/2 since every two digits makes the x and the y
    p_polygon->numberOfVertices = size_of_token/2;
    p_polygon->shiftDirection = NONE;
    p_polygon->vertexList = vertices;

    //debugging print statements
    printf("\nPOLYGON ADDED!");
    printf("\n\tNUMBER OF VERTICES: %d", p_polygon->numberOfVertices);
    printf("\n\tDIRECTION: %d\n", p_polygon->shiftDirection);
    for (int i = 0; i < p_polygon->numberOfVertices; i++) {
        printf("\tVERTICES #%d: (%d, %d)\n", i + 1, (p_polygon->vertexList[i].x - '0'), (p_polygon->vertexList[i].y - '0'));
    }

    //adding the polygon to the program's list of polygon
    for (int i = 0; i < MAX_NUM_OF_POLYGONS; i++) {
        if (polygons[i].numberOfVertices == 0) {
            polygons[i] = *p_polygon;
            break;
        }
    }
}

void handleSummary() {

    int i = 0;
    int j = 0;

    //making sure the list of polygons is not empty
    if (polygons[0].numberOfVertices == 0) {
        printf("\nTHE PROGRAM'S LIST OF POLYGONS IS EMPTY! PLEASE ADD SOME!\n");
        return;
    }

    //accessing & printing the list of polygons
    printf("\nACCESSING THE PROGRAM'S LIST\n\n");
    for (i = 0; i < MAX_NUM_OF_POLYGONS && polygons[i].numberOfVertices != 0; i++) {

        int av_x = 0;
        int av_y = 0;
        int numberOfVertex = polygons[i].numberOfVertices;

        printf("POLYGON %d: \n", i + 1);
        printf("\tNUMBER OF VERTICES: %d\n", numberOfVertex);
        printf("\tDIRECTION: %d\n", polygons[i].shiftDirection);
        for (int j = 0; j < polygons[i].numberOfVertices; j++) {
            printf("\tVERTICES #%d: (%d, %d)\n", i + 1, (polygons[i].vertexList[j].x - '0'), (polygons[i].vertexList[j].y - '0'));
        }

        for (j = 0; j < polygons[i].numberOfVertices; j++) {
            int x = polygons[i].vertexList[j].x - '0';
            av_x += x;

            int y = polygons[i].vertexList[j].y - '0';
            av_y += y;
        }
        //getting the average of the x-coordinates and the y-coordinates to find the Centroid of the polygon
        printf("\n\tCENTROID: (%.1f, %.1f)\n\n", (double)av_x/numberOfVertex, (double)av_y/numberOfVertex);
    }
}

void handleTurn() {

    char token1[MAX_TOKEN_TOKEN_LENGTH];
    char token2[MAX_TOKEN_TOKEN_LENGTH];
    int polyIndex;  //variable to use as index for the desired polygon in the list
    char dirMove[512]; //string variable to store then shift direction set for the polygon


    if (getCommandWord(token1, MAX_TOKEN_TOKEN_LENGTH) == '\n') {
        printf("\nTOO FEW ARGUEMENTS FOR THE TURN COMMAND\n");
        return;
    }
    if (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n') {
        printf("\nTOO MANY ARGUEMENTS FOR TURN COMMAND\n");
        while (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n');
        return;
    }

    polyIndex = atoi(token1) - 1;

    if (polyIndex < 0) {
        printf("\nNO SUCH POLYGON. PLEASE CHOOSE STARTING FROM 1\n");
        return;
    }
    //getting shift direction of the polygon and initializing the string variable
    for (int i = 0; i < (sizeof(token2) / sizeof(token2[0])); i++) {
        dirMove[i] = token2[i];
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
    int polyIndex;
    int change = 0;
    int changeDir;

    if (getCommandWord(token1, MAX_TOKEN_TOKEN_LENGTH) == '\n') {
        printf("\nTOO FEW ARGUEMENTS FOR THE SHIFT COMMAND\n");
        return;
    }
    if (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n') {
        printf("\nTOO MANY ARGUEMENTS FOR SHIFT COMMAND\n");
        while (getCommandWord(token2, MAX_TOKEN_TOKEN_LENGTH) != '\n');
        return;
    }

    polyIndex = atoi(token1) - 1;
    change = atoi(token2);

    //making sure we get the right index from input
    if (polyIndex < 0) {
        printf("\nNO SUCH POLYGON. PLEASE CHOOSE STARTING FROM 1\n");
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
        case 1:
            printf("\nPOLYGON %d HAS MOVED %d SPACES UP\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
                polygons[polyIndex].vertexList[i].y += change;
                polygons[polyIndex].shiftDirection = NONE;
            }
            break;
        case 2:
            printf("\nPOLYGON %d HAS MOVED %d SPACES DOWN\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
                polygons[polyIndex].vertexList[i].y -= change;
                polygons[polyIndex].shiftDirection = NONE;
            }
            break;
        case 4:
            printf("\nPOLYGON %d HAS MOVED %d SPACES LEFT\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
                polygons[polyIndex].vertexList[i].x -= change;
                polygons[polyIndex].shiftDirection = NONE;
            }
            break;
        case 8:
            printf("\nPOLYGON %d HAS MOVED %d SPACES RIGHT\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
                polygons[polyIndex].vertexList[i].x += change;
                polygons[polyIndex].shiftDirection = NONE;
            }
            break;
        case 9:
            printf("\nPOLYGON %d HAS MOVED %d SPACES UP-RIGHT\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
                polygons[polyIndex].vertexList[i].x += change;
                polygons[polyIndex].vertexList[i].y += change;
                polygons[polyIndex].shiftDirection = NONE;
            }
            break;
        case 5:
            printf("\nPOLYGON %d HAS MOVED %d SPACES UP-LEFT\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
                polygons[polyIndex].vertexList[i].x -= change;
                polygons[polyIndex].vertexList[i].y += change;
                polygons[polyIndex].shiftDirection = NONE;
            }
            break;
        case 10:
            printf("\nPOLYGON %d HAS MOVED %d SPACES DOWN-RIGHT\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
                polygons[polyIndex].vertexList[i].x += change;
                polygons[polyIndex].vertexList[i].y -= change;
                polygons[polyIndex].shiftDirection = NONE;
            }
            break;
        case 6:
            printf("\nPOLYGON %d HAS MOVED %d SPACES DOWN-LEFT\n", polyIndex + 1, change);
            for (int i = 0; i < polygons[polyIndex].numberOfVertices; i++) {
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
    printf("\t* add <x1y1x2y2......xnyn>\t CREATES AND STORES POLYGON IN LIST\n\n");
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
            printf("\nTERMINATING PROGRAM\n\n");
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
