#include "GameOfLifeHeader.h"   
#include <iostream>      
#include <string>
#include <cmath> 
  
using namespace std;
  
int main (int argc, char** argv)
{
    GameOfLife myLife;
    myLife.basicSetup();
    myLife.runGameLoop();
}