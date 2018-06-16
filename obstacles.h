// Frank Orefice
// CS13 Honors Project
#ifndef OBSTACLES
#define OBSTACLES

#include "game.h"
#include "player.h"

class Obstacle // Class for enemies and traps.
{
	public:
		int trap_Init(int V, int H);
		int enemy_Init(int V, int H);
		
	private:
		void enemy_move(int V, int H);
		void trap_move(int V, int H);
		int Ex = 0; // Where the enemies and traps start on the x-axis.
		int Ey = 0; // Where the enemies and traps start on teh y-axis.
		char enemy_snake = 's';
		char trap_arrow = '^';
		bool player_caught = false;
		bool location = false;
		Game obstacle; // An object from the Game class.
		Player coordin; // An object from the Player class.
};

void Obstacle::enemy_move(int V, int H)
{	
	int Ey2 = Ey + V; // The enemies' coordinate increases as it moves
	int Ex2 = Ex + H;
	
	if(maze[Ey2][Ex2] == '@') // When the enemy touches the player, it will clear from the screen.
		system("cls"); // Clears the screen.
			
	else if(maze[Ey][Ex2] == ' ' || maze[Ey][Ex2] == '@') // Makes sure if there is an open space or the player is in the loaction, the enemy will move up.
	{
		maze[Ey][Ex] = ' '; // Will make an empty space.
		Ex += H; // Enemy will move up the x-axis.
		maze[Ey][Ex] = enemy_snake; // The enemy will appear.
	}
	else if(maze[Ey2][Ex] == ' ' || maze[Ey][Ex2] == '@')
	{
		maze[Ey][Ex] = ' '; // Will make an empty space.
		Ey += V; // Enemy will moveup the y-axis
		maze[Ey][Ex] = enemy_snake; // The enemy will appear.
	}
		
	else
		maze[Ey][Ex]; // Enemy placement doesn't change.
}

int Obstacle::enemy_Init(int V, int H) // Placement of the enemies.
{
	srand(time(NULL)); // Seeding a random value.
	int n = rand() % 5 + 1; // Random value from 1 to 5 to determine how the enemy will move.
	if (!location)
	{
		Ex = H; // Sets value to coordinates, so when they change, the enemy moves.
		Ey = V;
		maze[Ey][Ex] = enemy_snake;
		location = true;
	} 
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)) // When the player pressses a key, player_caught is true.
	{																													// This makes the enemies move when the player moves.
		player_caught = true;
	}
	while (player_caught == true && maze[Ey][Ex] != '#') // While player_caught is true and that the next space isn't a wall.
	{
	    if(n == 1)	
			Obstacle::enemy_move(1, 0); // Down
		else if(n == 2)
			Obstacle::enemy_move(-1, 0); // Up
	    else if(n == 3)
			Obstacle::enemy_move(0, 1); // Right
		else if(n == 4)
			Obstacle::enemy_move(0, -1); // Left
		else if(n == 5)
			Obstacle::enemy_move(0, 0); // Stationary
	
		return 0;
	}	
}

void Obstacle::trap_move(int V, int H)
{	
	// The traps'coordinate increases as it moves.
	int _x = Ex;
	int _y = Ey;
	int Ey2 = Ey + V;
	int Ex2 = Ex + H;
	
	if(maze[Ey2][Ex2] == '@')
	{
		system("cls"); // Clears the screen.
	}
	if((maze[Ey][Ex2] == ' ' || maze[Ey][Ex2] == '@') && maze[Ey][Ex2] != '#') // Movement on the y-axis if there is an empty space, the player, and not a wall.
	{
		maze[Ey][Ex] = ' '; // Creates an empty space.
		Ey += H; // Trap moves forward on the y-axis.
		maze[Ey][Ex] = trap_arrow; // Trap appears.
	}
	if((maze[Ey2][Ex] == ' ' || maze[Ey][Ex2] == '@') && maze[Ey][Ex2] != '#') // Movement on the x-axis if there is an empty space, the player, and not a wall.
	{
		maze[Ey][Ex] = ' '; // Creats an empty space.
		Ey += V; // Trap moves forward on the y-axis.
		maze[Ey][Ex] = trap_arrow; // Trap appears.
	}
	if(maze[Ey2][Ex2] == '#'){
		maze[coordin.y][coordin.x] == trap_arrow; // Trap returns to its original position when it hits a wall.
	}
	else{
		maze[Ey][Ex]; // Trap is stationary.
	}
}

int Obstacle::trap_Init(int V, int H)
{
	int j = rand() % 4 + 1; // Random value from 1 to 4 to determine how the trap will move.
	if (!location) // Sets value to coordinates, so when they change, the trap moves.
	{
		Ex = H;
		Ey = V;

		maze[Ey][Ex] = trap_arrow; // Trap will appear.
		location = true;
	}
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)) // When the player pressses a key, player_caught is true.
	{																													// This makes the traps move when the player moves.
		player_caught = true;
	}
	while (player_caught == true && maze[Ey][Ex] != '#'){ // While player_caught is true and that the next space isn't a wall.
		
	    if(j == 1)
			Obstacle::trap_move(1, 0); // Down
		else if(j == 2)
			Obstacle::trap_move(-1, 0); // Up
		else if(j == 3)
			Obstacle::trap_move(0, 1); // Right
		else if(j == 4)
			Obstacle::trap_move(0, -1); // Left
		
		return 0;
	}
}

#endif
