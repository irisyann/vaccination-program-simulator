#pragma once
#ifndef VACCINATION_CENTER_H
#define VACCINATION_CENTER_H
#include "User.h"

class VaccinationCenter
{
public:
	void vaccinate();
	void getOverallData();
	void searchUser(std::string name);
	void registerUser();
	void clearData();

private:
	User user;
};

void VaccinationCenter::clearData()
{
	user.clear();
}

void VaccinationCenter::vaccinate()
{
	std::cout << "\n\n===== ENTERING VACCINATION CENTER =====";

	user.loadData();

	if (user.getNumRegisteredUsers() == 0)
	{
		std::cout << "\n===== Everyone in the list has been fully vaccinated! ====="
			<< "\nWait for someone else to register for vaccination first.";
	}
	else
	{
		int newStatus = 0;
		std::string name;
		int age;
		int status;
		std::string vaccineType;

		user.dequeue(name, age, status, vaccineType);

		time_t timetoday;
		time(&timetoday);

		if (status == 0)
		{
			newStatus = 1;
			user.enqueue(name, age, newStatus, vaccineType);
			std::cout << "\n\n***** You have vaccinated one person for 1st dose at " << asctime(localtime(&timetoday))
				<< "\n***** This person is half vaccinated and will be back for 2nd dose of vaccine.";
			std::cout << "\n\n===== Person details ====="
				<< "\nName: " << name
				<< "\nAge: " << age
				<< "\nVaccine type: " << vaccineType
				<< "\nStatus: " << user.getVaccineStatus(newStatus);
		}
		else if (status == 1)
		{
			std::cout << "\n\n***** You have vaccinated one person for 2nd dose at " << asctime(localtime(&timetoday))
				<< "\n***** This person is FULLY vaccinated and will be removed from queue."
				<< "\n\n===== Person details ====="
				<< "\nName: " << name
				<< "\nAge: " << age
				<< "\nVaccine type: " << vaccineType;
		}

		std::cout << "\n\n";
		user.updateDatabase();
	}
	
	system("pause");

}

void VaccinationCenter::searchUser(std::string name)
{
	std::cout << "\n\n===== ENTERING VACCINATION DATABASE =====\n";

	user.loadData();

	user.searchUser(name);
	std::cout << "\n\n";

	system("pause");

}

void VaccinationCenter::getOverallData()
{
	std::cout << "\n\n===== ENTERING VACCINATION DATABASE =====\n";

	user.loadData();
	std::cout << "\n===== List of people waiting in queue for vaccination =====\n\n";
	user.displayList();

	std::cout << "\n\n";

	system("pause");

}

void VaccinationCenter::registerUser()
{
	std::cout << "\n\n===== ENTERING VACCINATION REGISTRATION =====\n";

	std::string name;
	int age;
	char char_vaccineType;
	std::string vaccineType;

	std::cin.ignore();
	std::cout << "=> Enter your name: ";
	std::getline(std::cin, name);

	std::cout << "=> Enter your age: ";
	std::cin >> age;

	if (age < 18)
	{
		std::cout << "\n<!> Sorry, you are not eligible for the vaccination program. <!>\n\n";
	}
	else
	{
		std::cout << "=> Choose type of vaccine: "
			<< "\n[A] Pfizer"
			<< "\n[B] AstraZeneca"
			<< "\n[C] Sinovac\n";
		std::cin >> char_vaccineType;

		char_vaccineType = toupper(char_vaccineType);

		while (char_vaccineType != 'A' && char_vaccineType != 'B' && char_vaccineType != 'C')
		{
			std::cout << "\nInvalid input! Please try again.";
			std::cout << "\n=> Choose type of vaccine: "
				<< "\n[A] Pfizer"
				<< "\n[B] AstraZeneca"
				<< "\n[C] Sinovac\n";
			std::cin >> char_vaccineType;

			char_vaccineType = toupper(char_vaccineType);
		}

		if (char_vaccineType == 'A')
			vaccineType = "Pfizer";
		else if (char_vaccineType == 'B')
			vaccineType = "AstraZeneca";
		else if (char_vaccineType == 'C')
			vaccineType = "Sinovac";

		std::fstream dataFile;
		dataFile.open("UserData.txt", std::ofstream::out | std::ofstream::app);

		dataFile << name;
		dataFile << ",";

		dataFile << age;
		dataFile << ",";

		dataFile << 0; // status - all newly registered user pending 1st dose so 0 by default
		dataFile << ",";

		dataFile << vaccineType;
		dataFile << "\n";

		time_t timetoday;
		time(&timetoday);
		std::cout << "\n===== You have been registered for vaccination successfully! =====";
		std::cout << "\nDate & time registered: " << asctime(localtime(&timetoday)) << "\n\n";

		user.loadData();
	}
	system("pause");


}

#endif // !VACCINATION_CENTER_H
