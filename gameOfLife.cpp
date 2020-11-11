/*
a.
Cristiano Firmani
Yiftach Nachman
b.
2272725 (Cristiano)
2270838	(Yiftach)
c.
firma103
nachm100
d.
CSPC-350 Section 2
e.
Assignment 2
*/

#include <iostream>
#include <fstream>
#include <cmath>  
#include <random>
#include <algorithm>
#include <unistd.h>
#include <string>
      
#include "GameOfLifeHeader.h"   //import the header file
using namespace std;
      
GameOfLife::GameOfLife()                //constructor 
{
	stable=true;
	
}
GameOfLife::~GameOfLife()           //destructor
{

	for (int i = 0; i < height; ++i)
    {
        delete [] gameBoard[i];
  		delete [] nextGen[i];
    }
    delete [] gameBoard;
    delete [] nextGen;
    outfile.close();
}
  
void GameOfLife::askQuestions()
{
/*
Method starts the game. First puts out the rules of the game.
Then asks user if he wants random or flatline
And asks for more information accordingly
*/
    cout<< "Welcome to the game of life!"<< endl;
    usleep(1000000);
    cout<<"The rules are: "<<endl;
    cout<< "1. A location that has one or fewer neighbors will be empty in the next generation. If a cell was in that location, it dies of loneliness."<<endl;
    usleep(1000000);
    cout<< "2. A location with two neighbors remains stable. If there was a cell, there’s still a cell. If it was empty, it’s still empty. "<< endl;
    usleep(1000000);
    cout<< "3. A location with three neighbors will contain a cell in the next generation. If it currently has a cell, the cell lives on. If it’s empty, a new cell is born." << endl;
    usleep(1000000);
    cout<< "4.A location with four or more neighbors will be empty in the next generation due to overcrowding." << endl;
    usleep(1000000);
    cout<< "Do you want to start with a random configuration, or provide a map for configuration?"<< endl;
    usleep(1000000);
    while (true)
    {
        cout<< "Enter 'r' for random and ‘f’  for a flatline and ’e’ to exit game" << endl;
        cin>> configAnswer;
        configAnswer = tolower(configAnswer);
        if (configAnswer == 'r')
        {
            cout<< "Choose the random configuration" << endl;   
            cout<< "Please input the height: " << endl;
            cin>> height;
            cout<< "Please input the width: " << endl;
            cin>> width;
            cout << "Please input a number between 0-1 for the population density: " << endl;
            cin>> popDens;
            break;
        } 
        else if(configAnswer=='f')
        {
            string line;
            int lineCount=0;
            cout<< "Please input the file name: " << endl;
            cin>> infileName;
               
            ifstream infile(infileName + ".txt");
            if(infile.is_open())
            {
				while (getline(infile,line))
				{   
					lineCount++;
					if(lineCount==1)
					{
						height=stoi(line);
					}
					else if(lineCount==2)
					{
						width=stoi(line);
					}
					else
						break;  
				}
				infile.close();
			}
			else
				cout<< "Unable to open file"<< endl;
            break;
        }
        else if(configAnswer =='e')
        {
            break;
        } 
        else
        {
            cout<< "Incorrect input \n Please try again" << endl; 
        }
    }
}
void GameOfLife::typeOfOutput()
{
/*
Method asks user if he wants to continue running the program 
or if want to print the method to a file
*/
	while(true)
	{
		
		cout << "Would you like the output to print to a file, print to the screen and pause before the next output, or wait for you to press the 'Return' key for the next output?. \n If you want to output the information into a file, type 'f'. \n If you want to output the information to the screen with a pause, type 'p'. \n If you want to output the information to the screen and wait for an enter, press 'e'. "<< endl;
		cin >> outputType;
		if (outputType == 'f')
		{	
			cout << "Please enter the fileName you want the file to use: " << endl;
			cin >> outFileName;
			outfile.open(outFileName);
			break;
		}
		else if(outputType== 'p')
		{
				
			break;
		}
		else if(outputType=='e')
		{
			
			break;
		}
		else
			cout<<"Incorrect input. Please try again."<<endl;
	}
}
void GameOfLife::setGameMode()
{
/*
Method asks user which mode he wants to play
1)Classic
2)Doughnut
3)Mirror
*/ 
    while (true)
    {
        cout << "There are three modes that you can play. \n Enter ‘c’ if you want to play in classic mode \n Enter ‘d’ if you want to play in doughnut mode \n Enter ‘m’ if you want to play in mirror mode" << endl;
        cin>> gameMode;
        gameMode= tolower(gameMode);
        if (gameMode =='c' || gameMode == 'd' || gameMode == 'm')
        {
            break;
        }
        else
            cout<< "Incorrect value! Please try again" << endl;
             
    }
}
  
void GameOfLife::setBoard()
{
/*
Method creates two pointers to an array
1) gameBoard- the array that is constantly being changed
2) newGen- gameBoard is copied to this array so we can check if grid has become stable
*/
    gameBoard = new char*[height];
    for(int i = 0; i < height; ++i)
        gameBoard[i] = new char[width];
          
    for(int i=0; i<height; ++i)
    {
        for (int j=0; j<width;++j)
        {
            gameBoard[i][j]='0';
        }
    }
      
    nextGen = new char*[height];
    for(int i = 0; i < height; ++i)
        nextGen[i] = new char[width];
          
    for(int i=0; i<height; ++i)
    {
        for (int j=0; j<width;++j)
        {
            nextGen[i][j]='0';
        }
    }  
}
  
void GameOfLife::RandomDrawBoard()
/*
Draws a random board based on the user's input for height, width, and population density.
*/
{ 
    for (int i=0;i<height;++i)
    {
        for (int j=0;j<width;++j)
        {   
            double randomNum= ((double) rand() / (RAND_MAX));
            if(popDens>=randomNum)
                gameBoard[i][j]='X';
            else
                gameBoard[i][j]='-';        
        }
    }  
}
      
void GameOfLife::flatLineDrawBoard()
/*
Creates a game board based on a text file given to the program by the user.
*/
{
    char blah;
    ifstream infile(infileName + ".txt");
    infile >> height;
    infile >> width;
	for(int i=0; i<height;++i)
	{	
		for(int j=0; j<width;++j)
		{
			infile>> blah;
			blah= toupper(blah);
			gameBoard[i][j]=blah;
		}       
    }
    infile.close();
}
  
void GameOfLife::copyArr(char** before, char** after)
{
/*
Method copies the pervious grid to the new grid
*/
 for(int i=0; i<height;++i)
    {
        for(int j=0; j<width;++j)
        {
            after[i][j]=before[i][j];
        }
    }
}
void GameOfLife::checkIfEmpty(char** arr)
{
	bool empty=true;
    for(int i=0; i<height;++i)
    {
        for(int j=0; j<width;++j)
        {
            if(arr[i][j]!='-')
                empty=false;
        }
    }
    if(empty==true)
    {
    	stable=false;
    	cout<<"Every cell has died. Exiting Now."<<endl;
    }
}

void GameOfLife::checkIfStable(char** before, char** after)
{
/*
Method checks if the previous generation and the current generation are equal
If they are equal, we exit the program
*/
	bool same=true;
    for(int i=0; i<height;++i)
    {
        for(int j=0; j<width;++j)
        {
            if(before[i][j]!=after[i][j])
                same=false;
        }
    }
    if(same==true)
    {
    	stable=false;
    	cout<<"The board has stabilized. Exiting Now."<<endl;
    }
}
void GameOfLife::basicSetup()
{
/*
Method starts up the game
Checks if user wants to use random or file 
*/
    askQuestions();
    setBoard();
    setGameMode();
    typeOfOutput();
    if(configAnswer=='r')
        RandomDrawBoard();
    else if(configAnswer=='f')
        flatLineDrawBoard();
}
void GameOfLife::runGameLoop()
{
/*
Method checks for game mode and then calls to the preceding method to run the game
*/
    gameMode= tolower(gameMode);
    if(gameMode=='c')
    {
        cout<< "You choose to play the classic mode!"<< endl;
        classicMode();
           
    }
    else if(gameMode=='d')
    {
        cout<< "You choose to play the doughnut mode!" << endl;
        doughnutMode();
    }
    else
    {
        cout<< "You choose to play the mirror mode!" << endl;
        mirrorMode();
    } 
}
void GameOfLife::classicMode()
{
/*
Method runs the classic mode of the game
*/
    while(stable)
    {
        for(int i=0;i<height;++i)
        {
            for(int j=0;j<width;++j)
            {
            
               	int aliveCounter=0;
                if(i==0 && j==0)                //If statements for the corner indices
                {
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;             
                }   
                else if(i==(height-1) && j==0)
                {
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;     
                }
                else if(i==0 && j==(width-1))
                {
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++; 
                }
                else if(i==(height-1) && j==(width-1))
                {
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;                                 
                }
                else if(i==0)               //If statements for the edge indices
                {
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                }
                else if(i==(height-1))
                {
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                }
                else if(j==0)
                {
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;                 
                }
                else if(j==(width-1))
                {
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;                         
                }
                else                        //If statements for any of the middle indices
                {
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                }
                
                if(aliveCounter<=1)
                    nextGen[i][j]='-';
                else if(aliveCounter==2)
                    nextGen[i][j]=gameBoard[i][j];
                else if(aliveCounter==3)
                    nextGen[i][j]='X';
                else if(aliveCounter>=4)
                    nextGen[i][j]='-';
            }
        }
        cout<<endl;
        if(outputType=='p')
        {
            cout<<"Board:"<<endl;
        	printBoard(nextGen);
        	usleep(2000000);
        }
        else if(outputType=='e')
        {
            cout<<"Board:"<<endl;
        	printBoard(nextGen);
        	cout<< "Please press enter to continue" << endl;
       		cin.get();
       	}
       	else if(outputType=='f')
       	{
			for(int i=0;i<height; i++)
			{
				for(int j=0; j<width; j++)
				{
					outfile << nextGen[i][j];
				}
				outfile << endl; 

			}
			outfile << endl; 

       	}
        checkIfStable(nextGen, gameBoard);
        checkIfEmpty(nextGen);
        copyArr(nextGen, gameBoard); 
    }
}
  
void GameOfLife::doughnutMode()
{
/*
Method runs the doughnut mode of the game:
The grid is wrapped around itself horizontally and vertically, resulting
in a torus (doughnut) shape. In this mode, any reference off the right-hand-side is
wrapped around to the left-most column of the same row and vice-versa. Any reference
off the top wraps to the bottom in the same column. 
*/
    while(stable)
    {
        for(int i=0;i<height;++i)
        {
            for(int j=0;j<width;++j)
            {
                int aliveCounter=0;
                if(i==0 && j==0)                    //If statements for the corner indices
                {
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i+(height-1)][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+(height-1)][j+1]=='X')
                        aliveCounter++;
                }
                else if(i==0 && j==(width-1))
                {
                    if(gameBoard[i][width-2]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][width-2]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][width-1]=='X')
                        aliveCounter++;
                    if(gameBoard[height-1][width-2]=='X')
                        aliveCounter++;
                    if(gameBoard[height-2][width-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][0]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][0]=='X')
                        aliveCounter++;
                }
                else if(i==(height-1) && j==0)
                {
                    if(gameBoard[height-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[height-2][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[height-2][j]=='X')
                        aliveCounter++;
                    if(gameBoard[0][0]=='X')
                        aliveCounter++;
                    if(gameBoard[0][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[height-1][width-1]=='X')
                        aliveCounter++;
                    if(gameBoard[height-2][width-1]=='X')
                        aliveCounter++;             
                }
                else if(i==(height-1) && j==(width-1))
                {
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j-(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i-(height-1)][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-(height-1)][j-1]=='X')
                        aliveCounter++;
                        
                        
                }
                else if(i==0)                       //If statements for the edge indices
                {
                    if(gameBoard[i+(height-1)][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+(height-1)][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+(height-1)][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                }
                else if(i==(height-1))
                {
            
                    if(gameBoard[i-(height-1)][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-(height-1)][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-(height-1)][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                }
                else if(j==0)
                {
                    if(gameBoard[i-1][j+(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                }
                else if(j==(width-1))
                {
                    if(gameBoard[i-1][j-(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j-(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-(width-1)]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;             
                }
                  
                else                                //If statement for any of the middle indices
                {
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                }
                if(aliveCounter<=1)                      //Checks to see which live and which die
                    nextGen[i][j]='-';
                else if(aliveCounter==2)
                    nextGen[i][j]=gameBoard[i][j];
                else if(aliveCounter==3)
                    nextGen[i][j]='X';
                else if(aliveCounter>=4)
                    nextGen[i][j]='-';
            }
        }
		cout<<endl;
        if(outputType=='p')
        {
            cout<<"Board:"<<endl;
        	printBoard(nextGen);
        	usleep(2000000);
        }
        else if(outputType=='e')
        {
            cout<<"Board:"<<endl;
        	printBoard(nextGen);
        	cout<< "Please press enter to continue" << endl;
       		cin.get();
       	}
       	else if(outputType=='f')
       	{
			for(int i=0;i<height; i++)
			{
				for(int j=0; j<width; j++)
				{
					outfile << nextGen[i][j];
				}
				outfile << endl; 

			}
			outfile << endl; 

       	}
        checkIfStable(nextGen, gameBoard);
        checkIfEmpty(nextGen);
        copyArr(nextGen, gameBoard); 
    }    
}
void GameOfLife::mirrorMode()
{ 
/*
Method runs the mirror Mode of the game: 
References off the grid are bounced back as though the wall were a mirror.
This means the reflection of a cell could count as its own neighbor. 
*/
    while(stable)
    { 
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                int aliveCounter=0;
                if(i==0 && j==0)							//If statements for the corner indices
                {
                	if(gameBoard[i][j+1]== 'X')
                        aliveCounter+=3;
                    if(gameBoard[i+1][j]== 'X')         
                        aliveCounter+=2;
                    if(gameBoard[i+1][j+1]== 'X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]== 'X')
                        aliveCounter+=2;
                }
                else if(i==0 && j==(width-1))
                {
                	if(gameBoard[i][j]== 'X')
                        aliveCounter+=3;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter+=2;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter+=2;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                }
                else if(i==(height-1) && j==0)
                {
                	if(gameBoard[i][j]== 'X')
                        aliveCounter+=3;
                    if(gameBoard[i-1][j+1]== 'X')
                        aliveCounter++; 
                    if(gameBoard[i-1][j]== 'X')
                        aliveCounter+=2; 
                    if(gameBoard[i][j+1]== 'X')
                        aliveCounter+=2;
                }
                else if(i==(height-1) && j==(width-1))
                {
                	if(gameBoard[i][j]== 'X')
                        aliveCounter+=3;
                    if(gameBoard[i][j-1]== 'X')
                        aliveCounter+=2;
                    if(gameBoard[i-1][j-1]== 'X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]== 'X')
                        aliveCounter+=2;
                }
                else if(i==0)                           //if statements for sides of indices
                {
                	if(gameBoard[i][j]== 'X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')                     
                        aliveCounter+=2;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter+=2;
                }
                else if(j==0)                
                {
                	if(gameBoard[i][j]== 'X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')                          
                        aliveCounter+=2;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter+=2;  
                }
                else if(i==(height-1))                                  
                {
                	if(gameBoard[i][j]== 'X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')                    
                        aliveCounter+=2;
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter+=2;
                }
                else if(j==(width-1))
                {
                	if(gameBoard[i][j]== 'X')
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')                        
                        aliveCounter+=2;
                    if(gameBoard[i-1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter+=2;
                }
                else                                         //If statements for any of the middle indices
                {
                    if(gameBoard[i-1][j-1]=='X')                     
                        aliveCounter++;
                    if(gameBoard[i-1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i-1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j+1]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j]=='X')
                        aliveCounter++;
                    if(gameBoard[i+1][j-1]=='X')
                        aliveCounter++;
                    if(gameBoard[i][j-1]=='X')
                        aliveCounter++;
                }
                if(aliveCounter<=1)                      //Checks to see which live and which die
                    nextGen[i][j]='-';
                else if(aliveCounter==2)
                    nextGen[i][j]=gameBoard[i][j];
                else if(aliveCounter==3)
                    nextGen[i][j]='X';
                else if(aliveCounter>=4)
                    nextGen[i][j]='-';
            }
        }
		cout<<endl;
        if(outputType=='p')
        {
            cout<<"Board:"<<endl;
        	printBoard(nextGen);
        	usleep(2000000);
        }
        else if(outputType=='e')
        {
            cout<<"Board:"<<endl;
        	printBoard(nextGen);
        	cout<< "Please press enter to continue" << endl;
       		cin.get();
       	}
       	else if(outputType=='f')
       	{
			for(int i=0;i<height; i++)
			{
				for(int j=0; j<width; j++)
				{
					outfile << nextGen[i][j];
				}
				outfile << endl; 

			}
			outfile << endl; 

       	}
        checkIfStable(nextGen, gameBoard);
        checkIfEmpty(nextGen);
        copyArr(nextGen, gameBoard); 
    }
}

void GameOfLife::printBoard(char** arr)
{
/*
Method print out the gameBoard to the console
*/
    for(int i=0; i<height; i++)
    {
    	cout << string(width*4,'-')<< endl;
        for(int j=0; j<width; j++)
        {
        	cout<<" | ";
            cout<< arr[i][j];
        }
        cout<< endl;
    }
	cout << string(width*4,'-')<< endl;

}