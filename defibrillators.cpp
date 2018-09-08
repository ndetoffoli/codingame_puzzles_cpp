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

std::vector<std::string> splitString(const std::string & inputString,
	char delimiter = ';')
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

class Defibrilator
{
    public:
        Defibrilator():
            number_(0), name_(""), address_(""), phone_(""), lon_(0.0), lat_(0.0) {}

        Defibrilator(int number, std::string name, std::string address, std::string phone, double lon, double lat):
            number_(number), name_(name), address_(address), phone_(phone), lon_(lon), lat_(lat) {}

        Defibrilator(const std::string & defibString)
        {
            auto strings = splitString(defibString);
            number_ = std::stoi(strings[0]);
            name_ = strings[1];
            address_ = strings[2];
            phone_ = strings[3];
            lon_ = parseDouble(strings[4]);
            lat_ = parseDouble(strings[5]);
        }

        std::string toString() const
        {
            return std::to_string(number_) + ";"
                + name_ + ";"
                + address_ + ";"
                + phone_ + ";"
                + std::to_string(lon_) + ";"
                + std::to_string(lat_);
        }

        void debug() const
        {
            std::cerr << toString() << std::endl;
        }

    public:
        int number_;
        std::string name_, address_, phone_;
        double lon_, lat_;
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

double computeDistanceBetweenTwoDefibrilators(const Defibrilator & defibrilator1,
    const Defibrilator & defibrilator2)
{
    double x = (defibrilator2.lon_ - defibrilator1.lon_) * cos((defibrilator1.lat_ + defibrilator2.lat_) / 2);
    double y = defibrilator2.lat_ - defibrilator1.lat_;
    static constexpr int kEarthRadius = 6371;
    return sqrt(x * x + y * y) * kEarthRadius;
}


std::size_t getClosestDefribilatorIndex(const std::vector<Defibrilator> & defibrilators, const Defibrilator & inputPoint)
{
	std::size_t closestDefibrilatorIndex = SIZE_MAX;
	double minimumDistanceToInputPoint = std::numeric_limits<double>::infinity();
	for (size_t index = 0; index < defibrilators.size(); index++)
	{
		 const Defibrilator & defibrilator = defibrilators[index];

		 double distanceToInputPoint = computeDistanceBetweenTwoDefibrilators(inputPoint, defibrilator);

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
    // Read input parameters
    std::string longitude;
    std::cin >> longitude; std::cin.ignore();

    std::string latitude;
    std::cin >> latitude; std::cin.ignore();

    int numberOfDefibrilators;
    std::cin >> numberOfDefibrilators; std::cin.ignore();

    // Create a fake defib for input point
    Defibrilator inputPoint("0;;;;" + longitude + ";" + latitude);

    // Build directory of defibs
    auto defibrilators = buildDefibrilatorList(numberOfDefibrilators);

	 // Look for closest defibrilator
    std::size_t closestDefibrilatorIndex = getClosestDefribilatorIndex(defibrilators, inputPoint);

    // Send back answer
    std::cout << defibrilators[closestDefibrilatorIndex].name_ << std::endl;
}
