#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm\glm.hpp>
#include "Structs.h"
#include "Singleton.h"

// Data layout: Position.x, Position.y, Type, Order, Time (int sec
// Data format: .csv

class Parser : public Fluffy::Singleton<Parser>
{
public:
	static void ParseEnemyLayoutData(const std::string& inputFile, std::vector<EnemyEnteringData>& data)
	{
		std::ifstream file{ inputFile };
		if (!file)
			std::cout << "Cannot open " << inputFile << "!\n";

		while (!file.eof())
		{
			EnemyEnteringData enemy{};

			std::string line;
			std::getline(file, line);

			std::istringstream iLine{ line };
			std::string posX;
			std::getline(iLine, posX, ',');
			std::string posY;
			std::getline(iLine, posY, ',');
			std::string type;
			std::getline(iLine, type, ',');
			std::string order;
			std::getline(iLine, order, ',');
			std::string time;
			std::getline(iLine, time);

			if (!posX.empty())
			{
				bool isInt{ true };

				std::string::const_iterator it = posX.begin();

				while (it != posX.end())
				{
					if (!std::isdigit(*it))
					{
						isInt = false;
						break;
					}

					++it;
				}

				if (isInt)
				{
					enemy.position.x = float(std::stoi(posX));
				}
			}

			if (!posY.empty())
			{
				bool isInt{ true };

				std::string::const_iterator it = posY.begin();

				while (it != posY.end())
				{
					if (!std::isdigit(*it))
					{
						isInt = false;
						break;
					}

					++it;
				}

				if (isInt)
				{
					enemy.position.y = float(std::stoi(posY));
				}
			}

			if (type == "bee")
				enemy.type = EnemyType::Bee;
			else if (type == "butterfly")
				enemy.type = EnemyType::Butterfly;
			else if (type == "boss")
				enemy.type = EnemyType::Boss;

			enemy.order = std::stoi(order);
			enemy.time = float(std::stoi(time));

			data.push_back(enemy);
		}
	}

};