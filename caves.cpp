#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

//I tested these values
char panelGame[70][22];
char panelSide[29][22];
char panelBottom[98][6];//+2

char screen[100][30];

class Player{
	private:
		bool livedBefore = false;
	public:
     		int xPos, yPos;
  		int life;
		void respawn(int xSpwn, int ySpwn){
			//xPos = xSpwn;
			//yPos = ySpwn;	
			//this will give random items or something
			//and will create class room or something
			//but for now just spawning player.
			xPos = 0;
			yPos = 0;
		}
		
};

class Map{
	private:
		static const int xStart = 100, yStart = 100;
	public:
		std::vector<int> roomTile;
		std::vector<bool> isVis;
		
		int xSize, ySize, totalSize;	
		int xPos_spawn, yPos_spawn, iPos_spawn;
		int xPos_exit, yPos_exit, iPos_exit;
		void genMap(int diff){
			
			xSize = xStart * diff * ((std::rand()*diff%100)/50+0.90);
			ySize = yStart * diff * ((std::rand()*diff%100)/50+0.90);
			totalSize = xSize * ySize;

			xPos_exit = (xSize-10)+(std::rand()*diff%10);
			yPos_exit = (ySize-10)+(std::rand()*diff%10);
			iPos_exit = ((xSize*yPos_exit)+xPos_exit);
			
			roomTile.resize(totalSize);
			isVis.resize(totalSize);
			for(int i = 0; i < totalSize; i++){
				roomTile[i] = '.';
				isVis[i] = false;
			}
			int i = 0;
			int corners = 0;
			std::vector<int> xCor;
			std::vector<int> yCor;
			unsigned int xClose, yClose; //closest just shortened
			unsigned int sAmount = 0, lAmount = 0; //Small and big room count
			for(int y = 10; y < ySize-10; y++){
				for(int x = 10; x < xSize-10; x++){
					i++;
					xClose = xSize;
					yClose = ySize;
					int xDist, yDist;
					for(int c = 0; c < corners; c++){
						xDist = std::abs(xCor[c]-x);
						yDist = std::abs(yCor[c]-y);
						//this needs to be OR
						if(xDist < xClose || yDist < yClose){
							xClose = xDist;
							yClose = yDist;
						}
					}
					int xRad, yRad; //radious of room from center
					if((2*sAmount)<lAmount){
						xRad = std::rand()%4+1;//(*2+1) so 1 is 3
						yRad = std::rand()%4+1;
						sAmount++;
					}else{
						xRad = std::rand()%10+5;
						yRad = std::rand()%10+5;
						lAmount++;
					}
					
					//Make room NOTE > > is right!!!
					if(xClose > xRad && yClose > yRad){				
						// add the corners to the corner pool vector //
						xCor.push_back(x-xRad); yCor.push_back(y-yRad);
						xCor.push_back(x+xRad); yCor.push_back(y-yRad);
						xCor.push_back(x-xRad); yCor.push_back(y+yRad);
						xCor.push_back(x+xRad); yCor.push_back(y+yRad);
						corners =+ 4;//adding all 4 corners to the pool
						
						/*dbug*/ std::cout << "pokoj: " << std::endl;
						for(int yDraw = -(yRad); yDraw < yRad; yDraw++){
							for(int xDraw = -(xRad); xDraw < xRad; xDraw++){
								roomTile[(xSize*(y+yDraw))+(x+xDraw)] = '_';
								std::cout << "_";
								//basic xy to i
							}
							std::cout << std::endl;
						}

					}
				}//x end
			}//y end 
			//doing this to be sure
			sAmount = 0;
			lAmount = 0;
		}
};

class Bag{
	private:	
		std::vector<int> weapon;
		std::vector<int> armor;
		std::vector<int> item;
		//just add ID
		
	
	public:
		void add(std::string id){ //add item
			//
			//KIND.pushBack()
		}
		void use(){ //pop item and return perks // not for weapons

		}

};

//the most flexible way, is to make an array, and then render it, will allow to have things
//drawn on top of each other

int main(){
	Player player;
	Map map;
	Bag bag;
	char input;
	
	//VECTOR A MOZNA map.isVis[12][1] = true;

	int difficulty = 1; //CANT BE ZERO
	while(1){
		map.genMap(difficulty);
		player.respawn(map.xPos_spawn, map.yPos_spawn);
		while(1){
			std::cin >> input;
			if(player.xPos == map.xPos_exit && player.yPos == map.yPos_exit){
				system("clear");
				std::cout << std::endl << "Loading next level..." << std::endl;
				break;
			}
			
			//REFERENCE VALUES:
			//		Width *	Height
			//whole screen	100 X |	 30 Y |Frame
			//		----- |	------  X  Y
			//game screen	  69  |	  21   +1 +1
			//side		  29  |	  22   +1 +0
			//bottom	  98  |	   6   +2 +2
			
			//COMBINE SCREENS
			//IMPORTANT NOTE, If this works slowly,
			//just cout without passing to screen[][]
			//its prepared so that i dont need to change
			//a lot of code, just replace. Lets hope
			//this will work just fine. Screen[][]
			//addressess problem of blinking screen.
			
			//DECIDING IF CAMERA IS CENTERED OR OFFSET
			//this is for optimazation, but will be deleted eventually
			
			//reference values - padding
			
			//X// xPos < 34    xPos > xSize-34
			
			//Y// yPos < 10    yPos > ySize-10

			int xOff = 0, yOff = 0;
			//This is good, but not good enought
			if(player.xPos < 34){
			xOff = 34;
			}else
			if(player.xPos > map.xSize-34){
			xOff = -34;
			}
			
			if(player.yPos < 10){
			yOff = 10;
			}else
			if(player.yPos > map.ySize-10){
			yOff = -10;
			}
			
			//10 35
			
			//SAMPLE MAP TO SCREEN
			for(int y = 0; y <= 21; y++){
				for(int x = 0; x <= 69; x++){
					panelGame[x][y] = map.roomTile[map.xSize*(y-10+yOff)+(x-35+xOff)];
				}
			}
			
			//SCREENS TO MAIN SCREEN
				//OVERLAY PLAYER
			panelGame[25-xOff][11-yOff] = '@';
			for(int y = 0; y < 21; y++){
				for(int x = 0; x <= 69; x++){
					screen[x][y] = panelGame[x][y];
				}
				screen[70][y] = '|';
				for(int x = 0; x <= 22; x++){
					screen[x+71][y] = panelSide[x][y];
				}
			}
			screen[0][22] = '*';
			for(int x = 1; x < 100; x++){
				screen[x][22] = '=';	
			}

			for(int y = 0; y < 6; y++){
				screen[0][y] = '|';
				for(int x = 1; x <= 99; x++){
					screen[x][y] = panelBottom[x][y];
				}
				screen[100][y] = '|';
			}

			


			//ACTUALLY DRAW	
			std::system("clear");
			for(int y = 0; y < 30; y++){
				for(int x = 0; x < 100; x++){
					std::cout << screen[x][y];
				}
				std::cout << std::endl;
			}


			//TEST
			std::cout << "map size " << map.xSize << " by " << map.ySize << " so " << map.totalSize << std::endl;
			std::cout << "player position x y: " << player.xPos << " " << player.yPos << std::endl; 
			//map.genMap(1); working, good enought



		}//end of level
		difficulty++;
	}
}
