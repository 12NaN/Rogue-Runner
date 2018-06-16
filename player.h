// Frank Orefice
// CS13 Honors Project
#ifndef PLAYER
#define PLAYER

#include "game.h"
#include <vector>
#include <ctime>
#include <cstdlib>

class Player
{
	public:
		int y = 1, x = 1;
		std::string dialog = "";
		//Inventory and dialog for game.
		std::vector<char>inventory;	
		void Move(int V, int H); // Player movement.   
	
	private:
		//Keys and portal for game. 
		bool got_key1 = false, got_key2 = false, got_key3 = false, got_key4 = false, thru_portal = false;
};

void Player::Move(int V, int H)
{
	Game play; // Game Class object.
	
	// Changes the player's coordinates.
	int y2 = y + V;
	int x2 = x + H;	
	
	// Seeding a random value for the treasure chest.
	srand(time(NULL));
	int chest = rand() % 2 + 1;
	
	// When the player obtains the sacred keys
	if(maze[y2][x2] == '%')
	{
		got_key1 = true;
		inventory.push_back('%'); // Adding the key to the player's inventory.
		dialog = "\aGot the Modulus key!\n"; // Changes dialog.
	}
	else if(maze[y2][x2] == '*')
	{
		got_key2 = true;
		inventory.push_back('*'); // Adding the key to the player's inventory.
		dialog = "\aGot the Asterisk key!\n"; // Changes dialog.
	}
	else if(maze[y2][x2] == '!')
	{
		got_key3 = true;
		inventory.push_back('!'); // Adding the key to the player's inventory.
		dialog = "\aGot the Exclamation point key!\n"; // Changes dialog.
	}
	else if(maze[y2][x2] == '+')
	{
		got_key4 = true;
		inventory.push_back('+'); // Adding the key to the player's inventory.
		dialog = "\aGot the Plus key!\n"; // Changes dialog.
	}
	else if((got_key1 == true && got_key2 == true && got_key3 == true && got_key4 == true) && thru_portal == false) // When the player obtains all of the keys.
	{
		dialog = "You may now enter the portal!\n"; // Changes dialog.
		if(maze[y2][x2] == 'O') {
			maze[y2][x2] = ' ';
			thru_portal = true;
		}
	}
	else if(thru_portal == true)
	{
		dialog = "Choose the right chest and achieve your prize. But if your choice is the wrong one, you'll die!"; // Changes dialog.
		if(maze[y2][x2] == '=')
		{
			maze[y2][x2] = ' '; // The chest disappears when it's touched.
			if(chest == 1) // When the chest equals one, the player wins. 
			{
				play.gameRunning = false; // gameRunning is made false, and the game ends.
				system("cls"); // Clears the screen.
				play.winner();  // Prints the winner's screen.
			}
			else
			{
				play.gameRunning = false; // gameRunning is made false, and the game ends.
				system("cls"); // Clears the screen.
				play.game_over(); // Prints out the game over screen.
			}
		}
	}
	else{
		dialog = "You need the 4 sacred keys to exit the maze and accept your prize!\n"; // Changes dialog when you have no keys.
		if((got_key1 == true && got_key2 == false && got_key3 == false && got_key4 == false) || (got_key1 == false && got_key2 == true && got_key3 == false && got_key4 == false)
		|| (got_key1 == false && got_key2 == false && got_key3 == true && got_key4 == false) || (got_key1 == false && got_key2 == false && got_key3 == false && got_key4 == true))
		{
			dialog = "Three keys remain!\n"; // Changes dialog when you have one key.
		}
		else if((got_key1 == true && got_key2 == true && got_key3 == false && got_key4 == false) || (got_key1 == false && got_key2 == true && got_key3 == true && got_key4 == false)
		|| (got_key1 == false && got_key2 == false && got_key3 == true && got_key4 == true) || (got_key1 == true && got_key2 == false && got_key3 == false && got_key4 == true) ||
		(got_key1 == true && got_key2 == false && got_key3 == true && got_key4 == false))
		 {
		 	dialog = "Two keys remain!\n"; // Changes dialog when you have two keys.
		 }
		 else if((got_key1 == true && got_key2 == true && got_key3 == true) || (got_key1 == true && got_key3 == true && got_key4 == true) || (got_key1 == true && got_key4 == true 
		 && got_key2 == true) ||  (got_key2 == true && got_key3 == true && got_key4 == true))
		 {
		 	dialog = "One key remains!\n"; // Changes dialog when you have three keys.
		 }
	}
 	
	if (maze[y][x2] == ' ' || maze[y][x2] == '%' || maze[y][x2] == '*' || 
	maze[y][x2] == '+' || maze[y][x2] == '!' || maze[y][x2] == '=') // Obtaining the items while moving on the x-axis.
	{
		maze[y][x] = ' '; // Creates an empty space when the item is touched.
		x += H; // Player moves up on the x-axis.
		maze[y][x] = '@'; // Player's coordinates change.
	}
	else if(maze[y][x2] == 's' || maze[y][x2] == '^') // When the player touches an enemy or trap while moving on the x-axis.
	{
		maze[y][x] = ' '; // Player disappears.
		std::cout << "\a"; // Alerts the player that they've been hit.
		y += V; // Player moves up on the y-axis.
		system("cls"); // Clears the screen.
		y = 1, x = 1; // y = 18, x = 29;  Player respawns at the starting position.
		maze[y][x] = '@'; // Player's coordinates change.
	}

	if (maze[y2][x] == ' ' || maze[y2][x] == '%' || maze[y2][x] == '*' ||
	maze[y2][x] == '+' || maze[y2][x] == '!' || maze[y2][x] == '=') // Obtaining the items while moving on the y-axis.
	{
		maze[y][x] = ' '; // Player disappears.
		y += V; //// Player moves up on the y-axis.
		maze[y][x] = '@'; // Player's coordinates change;
	}
	
	else if(maze[y2][x] == 's' || maze[y2][x] == '^') // When the player touches an enemy or trap while moving on the x-axis.
	{
		maze[y][x] = ' '; // Player disappears.
		std::cout << "\a"; // Alerts the player that they've been hit.
		y += V; // Player moves up on the y-axis.
		system("cls"); // Clears the screen.
		y = 1, x = 1; // y = 1, x = 1;  Player respawns at the starting position.
		maze[y][x] = '@'; // Player's coordinates change.
	}	
}

#endif
