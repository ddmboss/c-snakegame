// A simple snake game
// version 2.0

// Header Inclusions
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <process.h>

// Definitions
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// Global Variables
int bend_no;
int length = 5; // initial snake lenght
int len;
int life = 3; // number of extra lives
char key;

// Function Declarations
void gotoxy(int x, int y); // screen coordinates and positioning
void GoToXY(int x, int y); // screen coordinates and positioning
void load(); // load screen
void instructions(); // Instruction screen
void delay(long double);
void Food();
void scoreBoard(); // Records user's scores
int Score();
int scoreOnly();
void border(); // Game Border
void Bend();
void Move();
void Down();
void Left();
void Up();
void Right();
void record();
void GameOver();


struct coordinate {
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

// Int Main
int main(){

    char key;
    load();
    instructions();
    head.x = 25;
    head.y = 20;
    head.direction = RIGHT;
    border();
    Food(); // to generate food coordinates initially
    bend[0] = head;
    Move(); // initialing initial bend coordinate

    return 0;
}

// Movement Function
void Move(){
    int a, i;

    do{
		Food();
		
        fflush(stdin);

        len = 0;

        for(i=0; i<30; i++){
            body[i].x=0;
            body[i].y=0;

            if(i==length)
                break;
        }

        delay(length);

        border();

        if(head.direction==RIGHT)
            Right();
        else if(head.direction==LEFT)
            Left();
    	else if(head.direction==DOWN)
            Down();
        else if(head.direction==UP)
            Up();
            
        GameOver();
    }
    
    while(!kbhit());

    a = getch();

    if(a==27){
        system("cls");

        exit(0);
    }
    
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)
	||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)
	||(key==UP&&head.direction!=DOWN&&head.direction!=UP)
	||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
	{
        bend_no++;
        bend[bend_no]=head;
        head.direction=key;

        if(key==UP)
            head.y--;
        if(key==DOWN)
            head.y++;
        if(key==RIGHT)
            head.x++;
        if(key==LEFT)
            head.x--;

        Move();
    }
    else if(key==27){
    	
        system("cls");

        exit(0);
    }
	else {
        printf("\a");
        
        Move();
    }
}

// Screen Coordinates
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GoToXY(int x, int y){
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

// Load Screeen
void load(){
	system("cls");
    int row,col,r,c,q;
    gotoxy(10,5);
    printf(" ######  ##    ##    ###    ##    ## ########     ######      ###    ##     ## ######## ");
	gotoxy(10,6); 
	printf("##    ## ###   ##   ## ##   ##   ##  ##          ##    ##    ## ##   ###   ### ##       ");
	gotoxy(10,7);
	printf("##       ####  ##  ##   ##  ##  ##   ##          ##         ##   ##  #### #### ##       "); 
	gotoxy(10,8); 
	printf(" ######  ## ## ## ##     ## #####    ######      ##   #### ##     ## ## ### ## ######   ");
	gotoxy(10,9); 
	printf("      ## ##  #### ######### ##  ##   ##          ##    ##  ######### ##     ## ##       ");
	gotoxy(10,10); 
	printf("##    ## ##   ### ##     ## ##   ##  ##          ##    ##  ##     ## ##     ## ##       ");
	gotoxy(10,11);
	printf(" ######  ##    ## ##     ## ##    ## ########     ######   ##     ## ##     ## ######## ");
    gotoxy(47,18);
    printf("loading...");
    gotoxy(25,20);
    for(r = 1; r <= 50; r++){
        for(q = 0; q <= 10000000; q++); //to display the character slowly
        printf("%c",177);
    }
    gotoxy(37,22);
    printf("Press any key to continue...");
    getch();
}

// Instructions Function
void instructions(){
    system("cls");
	gotoxy(37,2);
    printf("Welcome to the Snake Game\n");
    gotoxy(4,6);
    printf("Game instructions:\n");
    gotoxy(6,8);
    printf("-> Use arrow keys to move the snake.\n");
    gotoxy(6,10);
	printf("-> You will be provided foods at the several coordinates of the screen which you have to eat.\n");
	gotoxy(7,11);
	printf("Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n");
	gotoxy(6,13);
	printf("-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n");
	gotoxy(6,15);
	printf("-> You can pause the game in its middle by pressing any key.\n");
	gotoxy(7,16);
	printf(" To continue the paused game press any other key once again\n");
	gotoxy(6,18);
	printf("-> If you want to exit press esc. \n");
	gotoxy(37,22);
	printf("Press any key to play game...");
    if(getch()==27)
        exit(0);
}

void Down(){
    int i;
    
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GoToXY(head.x,head.y-i);
		{
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}

void Left(){
    int i;
    
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GoToXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
}

void Right(){
    int i;
    
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GoToXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GoToXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Up(){
    int i;
    
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GoToXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}

void Bend(){
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--){
        if(bend[i].x==bend[i-1].x){
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++){
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GoToXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++){
                    /*GoToXY(bend[i].x,(bend[i].y-j));
                    printf("*");*/
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GoToXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GoToXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GoToXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GoToXY((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GoToXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}

// Game Over functionality
void GameOver(){
    int i, check = 0;
    
    for(i = 4; i < length; i++){ // it needs minimum 4 element to touch its own body
        if(body[0].x == body[i].x && body[0].y == body[i].y){
            check++; //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0){
        	break;
		}  
    }
    
    if(head.x<=10||head.x>=100||head.y<=5||head.y>=30||check!=0){
        life--;
        if(life >= 0){
            head.x = 25;
            head.y = 20;
            bend_no = 0;
            head.direction = RIGHT;
            Move();
        }
        else{
            system("cls");
            printf("All lives completed\n");
			printf("Better Luck Next Time!!!\n");
			printf("Press any key to quit the game\n");
            record();
            exit(0);
        }
    }
}

// past players record
void record(){
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);
    //************************
    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    //*****************************
    //sdfprintf(info,"\t\t\tPlayers List\n");
    fprintf(info,"Player Name :%s\n",nplname);
    //for date and time

    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    //**************************
    fprintf(info,"Score: %d\n",px=scoreOnly());//call score to display score
    //fprintf(info,"\nLevel:%d\n",10);//call level to display level
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}

// Food Function
void Food(){
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%100;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
    else if(food.x==0) // to create food for the first time coz global variable are initialized with 0
    {
        food.x=rand()%100;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=5)
            food.y+=11;
    }
}

// Delay Function
void delay(long double k){
    Score();
    long double i;
    for(i = 0; i <= (10000000); i++);
}

// scoring function
int Score(){
    int score;
    GoToXY(20,3);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GoToXY(70,3);
    printf("LIFE : %d", life);
    return score;
}

int scoreOnly(){
    int score=Score();
    system("cls");
    return score;
}

// Border Function
void border(){
	system("cls");
	
    int i;
    
    GoToXY(food.x,food.y);   // displaying food
    printf("*");
    
    for(i=10; i<101; i++){
        GoToXY(i,5);
        printf("x");
        GoToXY(i,30);
        printf("x");
    }
    for(i=5; i<31; i++){
        GoToXY(10,i);
        printf("x");
        GoToXY(100,i);
        printf("x");
    }
}
