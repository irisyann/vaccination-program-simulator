#pragma once
#ifndef USER_H
#define USER_H

class User
{
public:
	User();
	~User();
	void loadData();
	void enqueue(std::string name, int age, int status, std::string vaccineType);
	void dequeue(std::string& name, int& age, int& status, std::string& vaccineType);
	void searchUser(std::string& name);
	std::string getVaccineStatus(int& status) const;
	int getNumRegisteredUsers() const;
	bool isEmpty();
	void displayList();
	void clear();
	void updateDatabase();

private:
	struct Node
	{
		std::string name;
		std::string vaccineType;
		int age;
		int status;
		Node* next = nullptr; 
	};
	
	Node* head;
	Node* rear;
	int num_Registered_Users;
};

User::User()
{
	head = nullptr;
	rear = nullptr;
	num_Registered_Users = 0;
}

User::~User()
{
	clear();
}

void User::clear()
{
	std::string name;
	int age;
	int status;
	std::string vaccineType;

	while (!isEmpty())
	{
		dequeue(name, age, status, vaccineType);
	}
}

void User::loadData()
{
	std::ifstream dataFile("UserData.txt");

	std::string name;
	std::string vaccineType;
	int age;
	int status;
	char toSkip;
	
	// name,age,status,vaccineType
	while (std::getline(dataFile, name, ','))
	{
		dataFile >> age;
		dataFile >> toSkip;

		dataFile >> status;
		dataFile >> toSkip;

		std::getline(dataFile, vaccineType);
		enqueue(name, age, status, vaccineType);
	}
}

void User::enqueue(std::string name, int age, int status, std::string vaccineType)
{
	Node* ptr = nullptr;
	Node* newNode = new Node;
	newNode->name = name;
	newNode->age = age;
	newNode->status = status;
	newNode->vaccineType = vaccineType;
	newNode->next = nullptr;

	if (isEmpty())
	{
		head = newNode;
		rear = newNode;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}
	num_Registered_Users++;

}

void User::dequeue(std::string& name, int& age, int& status, std::string& vaccineType)
{
	Node* ptr = nullptr;

	if (isEmpty())
	{
		std::cout << "\n<!> There are no users in the database. <!>\n";
	}
	else
	{
		name = head->name;
		age = head->age;
		status = head->status;
		vaccineType = head->vaccineType;

		ptr = head;
		head = head->next;
		delete ptr;

		num_Registered_Users--;
	}
}

std::string User::getVaccineStatus(int& status) const
{
	if (status == 0)
		return "Pending 1st dose";
	else if (status == 1)
		return "Pending 2nd dose";
}

void User::searchUser(std::string& name)
{
	Node* ptr = nullptr;

	if (isEmpty())
	{
		std::cout << "\n<!> There are no users in the database. <!>\n";
	}
	else
	{
		ptr = head;
		bool isFound = false;

		while (ptr)
		{
			if (ptr->name == name)
			{
				isFound = true;

				std::cout << "===== User data match found! ====="
					<< "\nName: " << ptr->name
					<< "\nAge: " << ptr->age
					<< "\nVaccine type: " << ptr->vaccineType
					<< "\nStatus: " << getVaccineStatus(ptr->status) << "\n";

				break;
			}
			else
				ptr = ptr->next;
		}

		if (!isFound)
		{
			std::cout << "\n<!> User data not found. <!>\n";
		}
	}
}

int User::getNumRegisteredUsers() const
{
	return num_Registered_Users;
}

bool User::isEmpty()
{
	if (num_Registered_Users == 0)
		return true;
	else return false;

}

void User::displayList()
{
	Node* ptr = nullptr;

	if (isEmpty())
	{
		std::cout << "<!> There are no users in the database. <!>";
	}
	else
	{
		ptr = head;

		while (ptr)
		{
			std::cout << "Name: " << ptr->name
				<< "\nAge: " << ptr->age
				<< "\nVaccine type: " << ptr->vaccineType 
				<< "\nStatus: " << getVaccineStatus(ptr->status) << "\n\n";

			ptr = ptr->next;
		}
	}
}

void User::updateDatabase()
{
	std::ofstream dataFile("UserData.txt");
	Node* ptr = nullptr;

	ptr = head;

	while (ptr)
	{
		dataFile << ptr->name;
		dataFile << ",";
		dataFile << ptr->age;
		dataFile << ",";
		dataFile << ptr->status;
		dataFile << ",";
		dataFile << ptr->vaccineType;
		dataFile << "\n";

		ptr = ptr->next;
	}
	
}

#endif // !USER_H
