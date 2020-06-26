#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
bool gameFinished;
int width = 18;
int length = 18;
int x, y , fruitX, fruitY; //coordinates.
int Score;
int TailX[100],TailY[100];      //segments of tail.
int nTail;
enum eDirection{ LEFT,RIGHT,UP,DOWN, STOP=0
};
eDirection Direct;
void setup(){
	gameFinished = false;
	Direct = STOP;
	x = width/2;         // centre from where
	y = length/2;       // the snake head starts.//
    fruitX= rand() %width;
	fruitY = rand() %length;   //place the fruit randomly only within the map.
	Score = 0;
}
void draw(){
	system("cls");          //to clear the output screen comletely.
	for (int i=0;i<width+2;i++){
		cout<<"^";
	}
	cout<<endl;
	
	for(int i=0; i<length;i++){
		for(int j=0; j<width ; j++){    //j is width.
			if(j==0)
			    cout<<"^^";
			if(i== x && j ==y)     //length and width = coordinates of the head of snake.
			    cout<<"0";
		    if(i== fruitX && j== fruitY)
			    cout<<"@";
			else{
				bool body = false;                 //to connect the head ad tail of the body together.
				for(int k = 0; k<nTail ; k++){
					if(TailX[k] == i && TailY[k] == j ){
					
					cout<<"o";
					body = true;
					}
				}
				if(!body){
					cout<<" ";
				}
			}
			    
			if(j==width-1)        //Right boundary(height)
			    cout<<"^^";
		}
		cout<<endl;
	}
	for (int i=0;i<width+2;i++){
		cout<<"^";
	}
	cout<<endl;
	cout<<"SCORE: "<<Score;
	
	
}
void controls(){
	if(_kbhit())
	{
		switch(_getch()){
			case '1':
				Direct = LEFT;
				break;
				case '3':
				Direct = RIGHT;
				break;
				case '2':
				Direct = DOWN;
				break;
				case '5':
				Direct = UP;
				break; 
		}
	}
	
}
void logic(){
	int PrevX = TailX[0];
	int PrevY = TailY[0];
	   int Prev2X, Prev2Y;
    TailX[0] = x;
    TailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        Prev2X = TailX[i];
        Prev2Y = TailY[i];
        TailX[i] = PrevX;
        TailY[i] = PrevY;
        PrevX = Prev2X;
        PrevY = Prev2Y;
    }
    
	switch(Direct){
		case LEFT:
		y--;
		break;
		case RIGHT:
		y++;
		break;
		case DOWN:
		x++;
		break;
		case UP:
		x--;
		break;
		default:
		break;
	}
	if (x > width || x < 0 || y > length || y < 0)
     gameFinished = true;
     if(x>= width) x= 0 ; else if(x<0)x=width-1;
     if(y>= width) x= 0 ; else if(y<0)x=width-1;
     for(int i = 0 ; i<nTail ; i++){
     	if (TailX[i]==x && TailY[i]==y){
     		gameFinished = true;
		 }
	 }
     if(x== fruitX && y== fruitY){
     	nTail++;                      //increase in tail as snake eats food.
     	Score = Score+10;
     	fruitX= rand() %width;
	    fruitY = rand() %length;
	 }
     
	
}
int main()
{
	setup();
	while(!gameFinished){
		draw();
		controls();
		logic();
		Sleep(400);
	}
	return 0;
}