// A simple snake game
// version 1.0

#include <stdio.h> // allows for user input and output
#include <conio.h> // library to allow the program to detect key presses
#include <stdlib.h> // standard library
#include <unistd.h> // library to include the sleep function

// global variables
int height = 30, width = 30;
int i, j, gameover, score;
int x, y, egg_x, egg_y, flag;

// function to spawn eggs inside the boundary
void setup(){
	gameover = 0; // stores game scores
	
	// stores height and width
	x = height / 2;
	y = width / 2;
	
	label1:
		egg_x = rand() % 20;
		if (egg_x == 0){
			goto label1;
		}
	
	label2:
		egg_y = rand() % 20;
		if (egg_y == 0){
			goto label2;
		}
		score = 0;
}

// function to draw game boundary
void draw(){
	
	system("cls");
	
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			if (i == 0 || i == width - 1 
				|| j == 0 || j == height - 1){
				printf("x");
			}
			else {
				if (i == x && j == y){
					printf("O");
				}
				else if (i == egg_x && j == egg_y){
					printf("*");
				}
				else{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	
	// Print the score after the game ends
	printf("score = %d", score);
	printf("\n\n");
}

// Print the game instructions
void instructions(){
	printf("Instructions: \n");
	printf("Press 'W' to go up, Press 'S' to go down \n"); 
	printf("Press 'A' to go left, Press 'D' to go right \n");
	printf("Press 'X' to quit the game \n");
}

// function to take user input
void input(){
	if (kbhit()){
		switch (getch()){
			case 'a':
			case 'A':
				flag = 1;
				break;
			case 's':
			case 'S':
				flag = 2;
				break;
			case 'd':
			case 'D':
				flag = 3;
				break;
			case 'w':
			case 'W':
				flag = 4;
				break;
			case 'x':
			case 'X':
				gameover = 1;
				break;
		}
	}
}

// player movement function
void logic(){
	sleep(0.01);
	switch (flag){
		case 1:
			y--;
			break;
		case 2:
			x++;
			break;
		case 3:
			y++;
			break;
		case 4:
			x--;
			break;
		default:
			break;
	}
	
	// game over logic
	if (x < 0 || x > height || y < 0 || y > height){
		gameover = 1;
	}
	
	// scoring logic
	// if the snake eats the egg then update the score
	if (x == egg_x && y == egg_y){
		label3:
			egg_x = rand() % 20;
			if (egg_x == 0){
				goto label3;
			}
	
		// generate a new egg after the previous egg is eaten
		label4:
			egg_y = rand() % 20;
			if (egg_y == 0){
				goto label4;
			}
			score += 1;
	}
}

// Main driver code
void main(){
	
	int m, n;
	
	// initialize the game
	setup();
	
	// run until the user quits
	while (!gameover){
		
		// function calls
		draw();
		input();
		logic();
		instructions();
	}	
}
