// Nicolas De Toffoli (https://github.com/ndetoffoli)
// https://www.codingame.com/ide/puzzle/defibrillators

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <limits>

std::vector<std::string> splitString(const std::string & inputString, char delimiter = ';')
{
	std::vector<std::string> strings;
	std::istringstream stream(inputString);
	std::string s;
	while (std::getline(stream, s, delimiter))
	{
		strings.push_back(s);
	}
	return strings;
}

double parseDouble(std::string inputValue)
{
	std::replace(inputValue.begin(), inputValue.end(), ',', '.');
	return std::stod(inputValue);
}

class Coordinates
{
public:
	Coordinates():
		lon_(0.0), lat_(0.0) {}

	Coordinates(double lon, double lat):
		lon_(lon), lat_(lat) {}

	Coordinates(const std::string & lonString, const std::string & latString)
	{
		lon_ = parseDouble(lonString);
		lat_ = parseDouble(latString);
	}

	std::string toString() const
	{
		return std::to_string(lon_) + ";"
		+ std::to_string(lat_);
	}

	void debug() const
	{
		std::cerr << toString() << std::endl;
	}

public:
	double lon_, lat_;
};

class Defibrilator
{
public:
	Defibrilator():
		number_(0), name_(""), address_(""), phone_(""), coordinates_() {}

	Defibrilator(int number, std::string name, std::string address, std::string phone, double lon, double lat):
		number_(number), name_(name), address_(address), phone_(phone), coordinates_(lon, lat) {}

	Defibrilator(const std::string & defibString)
	{
		auto strings = splitString(defibString);
		number_ = std::stoi(strings[0]);
		name_ = strings[1];
		address_ = strings[2];
		phone_ = strings[3];
		coordinates_ = Coordinates(strings[4], strings[5]);
	}

	std::string toString() const
	{
		return std::to_string(number_) + ";"
		+ name_ + ";"
		+ address_ + ";"
		+ phone_ + ";"
		+ coordinates_.toString();
	}

	void debug() const
	{
		std::cerr << toString() << std::endl;
	}

public:
	int number_;
	std::string name_, address_, phone_;
	Coordinates coordinates_;
};

std::vector<Defibrilator> buildDefibrilatorList(int numberOfDefibrilators)
{
	std::vector<Defibrilator> defibrilatorList;
	for (int i = 0; i < numberOfDefibrilators; i++)
	{
		std::string temporaryString;
		std::getline(std::cin, temporaryString);
		defibrilatorList.emplace_back(temporaryString);
	}
	return defibrilatorList;
}

double computeDistanceBetweenTwoPoints(const Coordinates & point1, const Coordinates & point2)
{
	double x = (point2.lon_ - point1.lon_) * cos((point1.lat_ + point2.lat_) / 2);
	double y = point2.lat_ - point1.lat_;
	static constexpr int kEarthRadius = 6371;
	return sqrt(x * x + y * y) * kEarthRadius;
}

std::size_t getClosestDefribilatorIndex(const std::vector<Defibrilator> & defibrilators, const Coordinates & inputPoint)
{
	std::size_t closestDefibrilatorIndex = SIZE_MAX;
	double minimumDistanceToInputPoint = std::numeric_limits<double>::infinity();
	for (size_t index = 0; index < defibrilators.size(); index++)
	{
		const Defibrilator & defibrilator = defibrilators[index];

		double distanceToInputPoint = computeDistanceBetweenTwoPoints(inputPoint, defibrilator.coordinates_);

		if (distanceToInputPoint < minimumDistanceToInputPoint)
		{
			closestDefibrilatorIndex = index;
			minimumDistanceToInputPoint = distanceToInputPoint;
		}
	}
	return closestDefibrilatorIndex;
}

int main()
{
	// Read input parameters to create the inout point
	std::string longitudeString;
	std::cin >> longitudeString; std::cin.ignore();

	std::string latitudeString;
	std::cin >> latitudeString; std::cin.ignore();

	int numberOfDefibrilators;
	std::cin >> numberOfDefibrilators; std::cin.ignore();

	Coordinates inputPoint(longitudeString, latitudeString);

	// Build directory of defibs
	auto defibrilators = buildDefibrilatorList(numberOfDefibrilators);

	// Look for closest defibrilator
	std::size_t closestDefibrilatorIndex = getClosestDefribilatorIndex(defibrilators, inputPoint);

	// Send back answer
	std::cout << defibrilators[closestDefibrilatorIndex].name_ << std::endl;
}
