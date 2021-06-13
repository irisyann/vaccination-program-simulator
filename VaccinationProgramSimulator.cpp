#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "User.h"
#include "VaccinationCenter.h"
// eh i think there might be some delay 
// hi jem // HIHIHI       // YOLO
// say hi in whastapp whenu see this
int main()
{
	VaccinationCenter vac;

	//User user;
	
	char identityChoice;
	char actionChoice;
	char continueChoice;

	do
	{
		system("CLS");

		vac.clearData();
		std::cout << "*******************************************"
			<< "\nWelcome to Vaccination Simulation Program!"
			<< "\n*******************************************\n"
			<< "\n=> Select your identity: "
			<< "\n[A] Regular user"
			<< "\n[B] Hospital staff\n";

		std::cin >> identityChoice;
		identityChoice = toupper(identityChoice);

		while (identityChoice != 'A' && identityChoice != 'B')
		{
			std::cout << "\nInvalid input. Please try again!";
			std::cout << "\n=> Select your identity: "
				<< "\n[A] Regular user"
				<< "\n[B] Hospital staff\n";

			std::cin >> identityChoice;
			identityChoice = toupper(identityChoice);
		}

		system("CLS");

		if (identityChoice == 'A')
		{
			std::cout << "\nBeginning vaccination registration process...\n";
			vac.registerUser();

		}
		else if (identityChoice == 'B')
		{
			
			std::cout << "\n=> Select an action: "
				<< "\n[A] Vaccinate a user"
				<< "\n[B] Search user details"
				<< "\n[C] View list of people in queue for vaccination\n";

			std::cin >> actionChoice;
			actionChoice = toupper(actionChoice);

			while (actionChoice != 'A' && actionChoice != 'B' && actionChoice != 'C')
			{
				std::cout << "\nInvalid input. Please try again!";
				std::cout << "\n=>Select an action: "
					<< "\n[A] Vaccinate a user"
					<< "\n[B] Search user details"
					<< "\n[C] View list of people in queue for vaccination\n";

				std::cin >> actionChoice;
				actionChoice = toupper(actionChoice);
			}

			system("CLS");

			if (actionChoice == 'A')
			{
				vac.vaccinate();
;			}
			else if (actionChoice == 'B')
			{
				std::string name;
				std::cin.ignore();

				std::cout << "\n=> Enter name to search database: ";
				std::getline(std::cin, name);

				vac.searchUser(name);
			}
			else if (actionChoice == 'C')
			{
				vac.getOverallData();
			} 
		}  
		system("CLS");
		std::cout << "\n\n=> Would you like to continue using this program?"
				<< "\n[Y] Yes"
				<< "\n[N] No\n";
		std::cin >> continueChoice;
		continueChoice = toupper(continueChoice);

		while (continueChoice != 'Y' && continueChoice != 'N')
		{
			std::cout << "\nInvalid input. Please try again!";
			std::cout << "\n=> Would you like to continue using this program?"
				<< "\n[Y] Yes"
				<< "\n[N] No\n";
			std::cin >> continueChoice;
			continueChoice = toupper(continueChoice);
		}
		std::cout << "\n\n";

	} while (continueChoice == 'Y');
	
	std::cout << "\n****************************************************"
		<< "\nThank you for using Vaccination Program Simulator!"
		<< "\n****************************************************\n\n";



	//std::string temp = "Noah Raymond";
	//User u;
	////u.registerUser();
	//u.loadData(); // load data from text file into a queue
	////u.displayList();
	//u.searchUser(temp);
}

// user register for vaccine
// can have status // 0- havent vac // 1- received first dose, waiting for 2nd
// vac center search user
// vac center give vaccine
// if 0, update 1 // if 1, dequeue
