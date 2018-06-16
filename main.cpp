// Frank Orefice
// CS13 Honors Project
#include <iostream>
#include <chrono> // Used for the timer.
#include "game.h" // Header files to access classes and functions being used.
#include "player.h"
#include "obstacles.h"
using namespace std;

// Class Instances.
Game start;
Obstacle obstacle, obstacle2, obstacle3, obstacle4, obstacle5, obstacle6, obstacle7, obstacle8, obstacle9, obstacle10, obstacle11;
Player player;
Game game;

int main()
{
	char cont; // Used to ask the user if they are sure they want to continue.
	chrono::steady_clock::time_point tend = chrono::steady_clock::now() + std::chrono::seconds(90); // Creates a timer for 90 seconds.
	start.credits(); // Prints credits and intro to game.
	
	do {
		start.logo(); // Prints logo

		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Sets the color of menu to cyan.
		cout << "\n\t\t\tCan you survive?!\n\n"
			<< "\t\t\tPress 1 to continue\n"
			<< "\t\t\tPress 2 to view the Hall of Fame\n"
			<< "\t\t\tPress 3 to leave before its too late!\n";
		SetConsoleTextAttribute(h, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY); // Sets the color of the bar to magenta.
		cout << "\t\t\t-------------------------------------\n";
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Sets the color of select to cyan.
		cout<< "\t\t\tSelect:                              \n";
		cin >> start.choice; // Accesses the choice variable from the Game class.
		
		if (start.choice == 1) // Starts the game.
		{
			cout << "\t\tI hope you won't regret it!";
			Sleep(3000); // Pauses for 3 seconds.
			system("cls"); // Clears the screen.
			system("mode con: cols=200 lines=75"); // Sets the screen to a certain size.
			cout << "\aYou have 1 minute and 30 seconds to obtain all four keys and reach the portal. Good luck, you're going to need it!\n" // Alerts the user of what to expect.
				 << "Press any key to continue...\n";
			system("pause>nul"); // Pauses and waits until the user presses a key.
			start.gameRunning = true; // Accesses the gameRunning variable from the Game class, which shows that the game is running.
			
			while(start.gameRunning == true && !(chrono::steady_clock::now() > tend)) // Loops while the game is running and the timer isn't going over 60 seconds.
			{
				system("cls"); // Clears screen.
				chrono::steady_clock::now(); // Timer starts.
				for (int i = 0; i < 40; i++) // This loop prints out each line of the map in its array.
				{
					SetConsoleTextAttribute(h, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY); // Sets cyan for the foreground and magenta for the background.
					cout << maze[i] << "\n"; // Prints out each line of the map.
				}
	
				for (int i = 0; i < 1; i++) // Keeps the prompt on the screen.
				{
					SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Sets a cyan color for the text
					cout << "Prompts: " << player.dialog; // Accesses the dialog variable from the Player class.
				}
	
				for (int i = 0; i < 1; i++) // Keeps the sacred keys on the screen.
				{
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN); // Sets a yellow color for the text.
					cout << "\nSacred Keys: ";
		
					for (unsigned int i = 0; i < player.inventory.size(); i++) // .size() is an unsigned integer type.
					{
						cout << player.inventory[i] << " "; // Prints out the inventory from the Player class.
					}
				}
				

				start.legend(); // Accesses the legend from the Game class.
				system("pause>nul"); // Pauses the screen until a key is pressed.
					
				// Enemy and trap placements
				obstacle.enemy_Init(2, 12);
				obstacle2.enemy_Init(2, 25);
				obstacle3.enemy_Init(10, 33);
				obstacle4.enemy_Init(14, 7);
		    	obstacle5.trap_Init(8, 21);
				obstacle6.trap_Init(8, 30);
				obstacle7.trap_Init(11, 10);
	    		obstacle8.trap_Init(14, 18);
		 		obstacle9.trap_Init(14, 29);				
			
				// Player controls
				if (GetAsyncKeyState(VK_UP))
					player.Move(-1, 0);
				if (GetAsyncKeyState(VK_DOWN))
					player.Move(1, 0);
				if (GetAsyncKeyState(VK_RIGHT)) 
					player.Move(0, 1);
				if (GetAsyncKeyState(VK_LEFT))
					player.Move(0, -1);			
			}
			return 0;
		}
		else if(start.choice == 2)
		{
			start.hall_of_fame(); // Accesses the Hall of Fame in the Game Class.
			system("cls");
			main(); // Returns to the main menu.
		}		
		else if(start.choice == 3)
		{
			do{
				cout << "\aAre you sure? (Y/N): "; // Asks the user if they're sure of their decision.
				cin >> cont;
				
				if(cont == 'y' || cont == 'Y') // "Yes" to exit.
					cout << "\a\t\tCoward!";
				
				else if(cont == 'n' || cont == 'N'){ // "No" to continue playing.
					cout << "\a\t\tWell aren't you brave.\n";
					Sleep(3000); // Pause for 3 seconds.
					system("cls"); // Clears the screen.
					main(); // Return to the starting screen.
				}
			
				else
					cout << "\aThat isn't an option.\n"; // Prints if the input is invalid.
					
			}while(cont != 'y' && cont != 'Y' && cont != 'n' && cont != 'N'); // Do until a valid choice is made.	
		}
		else{
			cout << "\aThat isn't an option!\n"; // Prints out if the user's input is anything other than 1 or 2.
			Sleep(2000); // Pause for 2 seconds.
			system("cls"); // Clear the screen.
			main(); // Return to the starting screen.
		}
		
	}while((cont != 'y' || cont != 'Y') && start.gameRunning != false && !(chrono::steady_clock::now() > tend)); // Loops until one of these cases becomes true.

  return 0; // Ends the program.
}

