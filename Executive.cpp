/**
* \Author: Chance Penner
* \Author: Markus Becerra
* \Author: Sarah Scott
* \Author: Thomas Gardner
* \Author: Haonan Hu
* \File:	 Executive.cpp
* \Date:   09/19/2019
* \Brief:  File is cpp file
* \copyright: Group "Big SegFault Energy" All rights reserved
*/


#include "Executive.h"
#include <limits>

int Executive::boatCheck() // will return numOfBoats when valid
{
	int numOfBoats = 0;
	std::string tempBoats = " ";

	std::cout << "How many ships would you like to play with? (Choose 1-5): ";

	try
	{
		std::getline(std::cin, tempBoats);
	}

	catch(std::out_of_range &ex)
	{
		std::cout << "No input was recieved, please enter a number 1-5: \n";
		return boatCheck();
	}

	if(tempBoats.length() < 1 || tempBoats.length() > 1)
	{
		std::cout << "Must be a one-digit number from 1-5!\n";
		return boatCheck();
	}

	else
	{
		numOfBoats = tempBoats.at(0) - '0';

		if(numOfBoats < 1 || numOfBoats > 5)
		{
			std::cout << "Must be an integer from 1-5!\n";
			return boatCheck();
		}

		else
		{
			return numOfBoats;
		}
	}

}

Executive::Executive()
{
	int numOfBoats = 0;

	try
	{
		numOfBoats = boatCheck();
	}

	catch(std::runtime_error &rte)
	{
		std::cout << rte.what();
	}

	player_1 = new Player(numOfBoats);
	player_2 = new Player(numOfBoats);
	gameOver = false;
	m_player_1Turn = 1;
	game();

	std::cout <<"\n\n\nPlayer 1 place your ships\n";
	player_1 -> getBoard() -> setupBoard();
	player_2 -> getBoard() -> setupBoard();

}

void Executive::mainMenu()
{

}

void Executive::game()
{
	std::string guess;
	int testTemp = 5;
	while(!gameOver && testTemp > 0)
	{
		try
		{
			if(m_player_1Turn % 2 == 1)
			{
				player_1->getBoard()->printShotBoard();
				player_1->getBoard()->printMyBoard();
				std::cout <<"Player 1: Where would you like to shoot? ";
			}
			else
			{
				player_2->getBoard()->printShotBoard();
				player_2->getBoard()->printMyBoard();
				std::cout <<"Player 2: Where would you like to shoot? ";
			}

//////below is the try catch block to make sure the guess is a string of length 2
			try
			{
				std::cin >> guess;

				while(guess.length() != 2)			//checking that string length is 2
				{
					std::cout << "Please enter a coordinate, such as A1,B5,H2: ";
					std::cin >> guess;
				}

				shoot(guess);

			}
			catch (std::string message)
			{
				//what do we add here??
			}
///////end try catch block for checking length of guess string

			if(m_player_1Turn % 2 == 1)
			{

				std::cout << "PLAYER 1 BOARDS\n";
				player_1->getBoard()->printShotBoard();
				player_1->getBoard()->printMyBoard();
				std::cin.ignore();
				std::cout <<"Player 1 please hit enter and let other player shoot at your ships in secret\n";
				std::cin.ignore();
				player_1->getBoard()->printIntermission();
			}
			else
			{
				std::cout << "PLAYER 2 BOARDS\n";
				player_2->getBoard()->printShotBoard();
				player_2->getBoard()->printMyBoard();
				std::cin.ignore();
				std::cout <<"Player 2 please hit enter and let other player shoot at your ships in secret\n";
				std::cin.ignore();
				player_2->getBoard()->printIntermission();
			}
			m_player_1Turn++;
			testTemp--;
		}
		catch(std::runtime_error &rte)
		{
			std::cout << rte.what();
		}
	}
}



void Executive::shoot(std::string location)
{
	bool hit = false;
	if(m_player_1Turn % 2 == 1)
	{
		hit = player_2->gettingShot(location);
		player_1->shooting(location,hit);

	}
	else
	{
		hit = player_1->gettingShot(location);
		player_2->shooting(location,hit);
	}

}
