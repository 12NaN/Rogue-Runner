// Frank Orefice
// CS13 Honors Project
#ifndef GAME
#define GAME

#include <Windows.h>
#include <string>
#include <fstream>

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Keeps the color on screen.
char maze[40][40] = { // The maze.
	
	"#######################################",
	"#@        ## ####                  ####",
	"####        s     ##### #s# #####    ##",
	"#### #######  ### #####      ##### % ##",
	"#### ############ ########## ##########",
	"####       ###### ###      #    #######",
	"#########  ###### ### #### ###  #######",
	"######     ##########  ### ##  ########",
	"###### ###           ^ ###    ^  ######",
	"###### ### #####################  #####",
	"###    ### ##################### s#####",
	"### *     ^        ##########       ###",
	"#################    #######  #####  ##",
	"#####   ##########   #######  ##### ###",
	"#####  s          ^ ##       ^#####  ##",
	"#####      ########### ############ ###",
	"#####  ##############     #########  ##",
	"####    ############# !   ######### ###",
	"#### +  ####################        ###",
	"############################      #####",
	"##############################O########",
	"                          #       #    ",
	"                          #       #    ",
	"                          #       #    ",
	"                          #       #    ",
	"                          #       #    ",
	"                          #       #    ",
	"                          #       #    ",
	"                          # =   = #    ",
	"                          #########    "
};

class Game
{
	public:
		bool gameRunning; // Shows if the game is running.
		int winner(); // Prints the winner screen.
		int game_over(); // Prints the game over screen.
		void logo(); // Prints logo.
		void credits(); // Shows intro credits.
		int choice; // Player's choice.
		int hall_of_fame(); // Opens the leaderboard.
		void legend(); // Shows legend.
		
	private:
		int load_HoF(); // Loads the Hall of Fame file.
		int add_to_HoF(); // Adds player to the HoF.		
		void Pos_xy(int, int); // Sets initial position for objects.
		bool the_winner = false; // Shows if the player won.
		std::string q = ""; // Gets a string.
		int Num_of_Winners;
		struct Win
		{
			std::string name;	
		};
		Win winners[100];
};


void Game::logo() // Prints out logo for game.
{
	SetConsoleTextAttribute(h, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY); // Sets the color to magenta.
	std::cout << "\t\t\t--------------------------------------\n";
	
	SetConsoleTextAttribute(h, FOREGROUND_BLUE| FOREGROUND_GREEN|FOREGROUND_INTENSITY); // Sets the color to cyan.
	std::cout << "\t\t\t    o>                        \n"
		 << "\t\t\t  </ \tTHE ROGUE-RUNNER CHALLENGE\n"
		 << "\t\t\t  />                               \n";
	
	SetConsoleTextAttribute(h, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY); // Sets the color to magenta.
	std::cout << "\t\t\t--------------------------------------\n\n";		
}
	
void Game::credits()
{
	logo(); // Prints logo.
	
	SetConsoleTextAttribute(h, FOREGROUND_BLUE| FOREGROUND_GREEN|FOREGROUND_INTENSITY); // Sets the text's color to magenta.
	std::cout << "\t\tSee if you're able to beat the time and secure the treasure!\n\t\tBut be warned, this is anything but an easy task,\n"
         << "\t\ttraverse snakes, pits, arrows, and more to reach the goal!\n\t\tBut fortune favors the bold, so go out, run for your life and your future!\n"
         << "\n\n\t\tPress any key to continue...\n";
    
    system("pause>nul"); // Pauses screen until a key press.
    system("cls");		// Clears the screen.
}

int Game::load_HoF() // Loads the Hall of Fame file.
{
	int i = 0;
	std::ifstream HoF("Hall_of_Fame.txt"); // Write to file.
	
	if (HoF.is_open()) // Checks if file is open.
	{
		HoF >> Num_of_Winners;
		
		if (Num_of_Winners > 0) // Checks if there are winners.
		{
			do
			{
				HoF >> winners[i].name;
				i++;
			}while(!HoF.eof()); // Runs until it reaches the end of the file.
			std::cout << "Hall of Fame loaded successfully...\n"; // Prints when the loading is successful.
		}
	}
	else
		std::cout << "File doesn't exist\n"; // Prints if the file doesn't exist.
}

int Game::hall_of_fame() // Player can view those who beat the maze.
{
	load_HoF(); // Loads file.
	
	system("cls"); // Clears the previous screen.
	std::cout << "\t\t\t===================\n" // Hall of Fame Logo.
	   		 << "\t\t\t=   Hall of Fame  =\n"
			 << "\t\t\t===================\n";
			 		
	if(Num_of_Winners > 0) // If there are winners it will run.
	{			
		for(int i = 0; i < Num_of_Winners; i++)
		{
			std::cout << (i+1) << ") " << winners[i].name << "\n";
		}
	}
	else
		std::cout << "No one has survived the challenge...\n"; // Prints if no one is in the Hall of Fame.
		
	system("pause"); // Pauses the screen until there a key is pressed.
}

int Game::add_to_HoF() // Adds player to the hall of fame if they win.
{
	load_HoF(); // Calls the function that holds the file.
	std::fstream HoF("Hall_of_Fame.txt"); // Read and write to the file.
	std::cout << "Type name: ";
	std::cin >> winners[Num_of_Winners].name; // Adds the player's name to the HoF and increases the index.
	
	Num_of_Winners++;
	
	if(HoF.is_open()) // Makes sure that the file is open.
	{
		HoF << Num_of_Winners << std::endl; // Passes the player's name to the file.
		
		for(int i = 0; i < Num_of_Winners; i++)
		{
			HoF << winners[i].name << "\n";			
		}
		HoF.close(); // Closes the file.
	}
	else
		std::cout << "Error\n";
}

void Game::Pos_xy(int x, int y) // Positioning on screen.
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);	
}

void Game::legend() // Shows all of the items, obstacles, and controls of the game.
{
	Pos_xy(50, 0); // Sets the position of the legend on the screen.
	SetConsoleTextAttribute(h, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY); // Sets the color of the legend to magenta.
	std::cout << "Legend\n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\tYOU '@' \n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\tSacred Keys\n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\tAsterisk Key '*'\n"
		 << "\t\t\t\t\t\tModulus Key '%' \n"
		 << "\t\t\t\t\t\tPlus Key '+'\n"
		 << "\t\t\t\t\t\tExclamation Point Key '!'\n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\tEnemies/Obstacles\n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\tArrows '^'\n"
		 << "\t\t\t\t\t\tSerpents 's'\n"
		 << "\t\t\t\t\t\tTrench 'o'\n"
		 << "\t\t\t\t\t\tTreasure Chest '='\n"
		 << "\t\t\t\t\t\tPortal (Exit) 'O'\n"
		 << "\t\t\t\t\t\t-------------------\n"
		 << "\t\t\t\t\t\t-------------------\n"
	     << "\t\t\t\t\t\tControl Scheme\n"
		 << "\t\t\t\t\t\t--------------------\n"
		 << "\t\t\t\t\t\tLeft Arrow <- : Left\n"
		 << "\t\t\t\t\t\tRight Arrow ->: Right\n"
		 << "\t\t\t\t\t\tUp Arrow ^: Up\n"
		 << "\t\t\t\t\t\tDown Arrow v: Down\n"
		 << "\t\t\t\t\t\tPause: Shift key \n"
		 << "\t\t\t\t\t\t--------------------\n";	
}

int Game::game_over()
{
	gameRunning = false; // When the player loses, gameRunning is false and the loop for the game ends.
	SetConsoleTextAttribute(h, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY); // Sets the color to the game over screen to magenta.
	std::cout << "\t\t\t--------------------------------------\n"
		 << "\t\t\t                               \n"
		 << "\t\t\t           GAME OVER\n"
		 << "\t\t\t              ____             \n"
         << "\t\t\t            / /   \\        \n"
 		 << "\t\t\t           | | RIP |        \n"
         << "\t\t\t           | |     |       \n"
         << "\t\t\t            \\-------\\     \n"
         << "\t\t\t             \\_______\\    \n"
		 << "\t\t\t--------------------------------------\n\n";
		 
	std::cout << "\a\t\t\tRest in Pieces!\n"
		 << "\t\t\tPress any key to exit... \n";		 
	system("pause>nul"); // Waits for a key press.
	
	exit(0); // Terminates the program.
	
}
	
int Game::winner()
{
	do{
		the_winner = true;
		gameRunning = false; // When the player wins, the game will stop running.
		SetConsoleTextAttribute(h, FOREGROUND_BLUE |FOREGROUND_GREEN|FOREGROUND_INTENSITY); // Sets the color of the winner's screen to cyan.
		std::cout << "\t\t\t**************************************\n"
			 << "\t\t\t*             <o>  ________          *\n"
			 << "\t\t\t*	       |  _\\_____\\ \\         *\n"
			 << "\t\t\t*	       />|_____|___|         *\n"
			 << "\t\t\t*        ~ $ ~ WINNER! ~ $ ~         *\n" 
			 << "\t\t\t*                                    *\n"
			 << "\t\t\t**************************************\n\n";

		std::cout << "\a\t\t\tUnbelievable! You are the RogueRunner Champion!\n"
			 << "\t\t\tMake your mark in history by carving your name in the hall of fame!\n"
			 << "Press 1 to add your name to the hall of fame or 2 to exit...\n";
			 
		std::cin >> choice;
		
		if(choice == 1)
		{
			add_to_HoF();
			exit(0);
		}
		else if(choice == 2)
		{
			exit(0);
		}
		else
		{
			std::cout << "That isn't an option!\n";
		}
	}while(choice != 1);	   	
}

#endif
