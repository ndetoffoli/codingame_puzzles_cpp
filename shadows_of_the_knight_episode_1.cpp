// Nicolas De Toffoli (https://github.com/ndetoffoli)
// https://www.codingame.com/ide/puzzle/shadows-of-the-knight-episode-1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

// Constants for directons
static const std::string kUpString("U");
static const std::string kUpRightString("UR");
static const std::string kRightString("R");
static const std::string kDownRightString("DR");
static const std::string kDownString("D");
static const std::string kDownLeftString("DL");
static const std::string kLeftString("L");
static const std::string kUpLeftString("UL");

// Class to represent a direction of Batman in the building
class Direction
{
public:
    Direction(): value_("") {}

    Direction(const std::string & value): value_(value) {}

    bool operator ==(const Direction & otherDirection) const
    {
        return value_ == otherDirection.value_;
    }

    bool operator ==(const std::string & value) const
    {
        return value_ == value;
    }

    bool goesUp() const
    {
        return (value_ == kUpString)
            || (value_ == kUpLeftString)
            || (value_ == kUpRightString);
    }

    bool goesDown() const
    {
        return (value_ == kDownString)
            || (value_ == kDownLeftString)
            || (value_ == kDownRightString);
    }

    bool goesLeft() const
    {
        return (value_ == kLeftString)
            || (value_ == kUpLeftString)
            || (value_ == kDownLeftString);
    }

    bool goesRight() const
    {
        return (value_ == kRightString)
            || (value_ == kUpRightString)
            || (value_ == kDownRightString);
    }

    std::string value_;
};

// Class to represent a position of Batman
class Position
{
public:
    Position(): x_(0), y_(0) {}

    Position(int x, int y): x_(x), y_(y) {}

    Position(const Position & position):
        x_(position.x_), y_(position.y_) {}

    std::string toString() const
    {
        return std::to_string(x_) + " " + std::to_string(y_);
    }

    void debug() const
    {
        std::cerr << "Position = " << toString() << std::endl;
    }

    int x_, y_;
};

// Class to represent the area to explore in the building
class DiscoveryArea
{
public:
    DiscoveryArea(int x1, int y1, int x2, int y2):
        x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

    int getWidth() const
    {
        return x2_ - x1_;
    }

    int getHeight() const
    {
        return y2_ - y1_;
    }

    void update(const Position & position, const Direction & direction)
    {
        if (direction.goesUp())
        {
            y2_ = position.y_ - 1;
        }
        else if (direction.goesDown())
        {
            y1_ = position.y_ + 1;
        }

        if (direction.goesLeft())
        {
            x2_ = position.x_ - 1;
        }
        else if (direction.goesRight())
        {
            x1_ = position.x_ + 1;
        }
    }

    Position getCenter() const
    {
        return Position(x1_ + getWidth() / 2, y1_ + getHeight() / 2);
    }

    std::string toString() const
    {
        return "DiscoveryArea = (" + std::to_string(x1_)
            + ", " + std::to_string(y1_)
            + ")-(" + std::to_string(x2_) + ", "
            + std::to_string(y2_)
            + "), witdh = " + std::to_string(getWidth())
            + ", height = " + std::to_string(getHeight());
    }

    void debug() const
    {
        std::cerr << toString() << std::endl;
    }

    int x1_, y1_, x2_, y2_;
};

int main()
{
    // Read input parameters
    int buildingWidth;
    int buildingHeight;
    std::cin >> buildingWidth >> buildingHeight; std::cin.ignore();
    DiscoveryArea area(0, 0, buildingWidth - 1, buildingHeight - 1);

    int numberOfRemainingTurns;
    std::cin >> numberOfRemainingTurns; std::cin.ignore();

    int startX;
    int startY;
    std::cin >> startX >> startY; std::cin.ignore();
    Position position(startX, startY);

    // Game loop
    while (1)
    {
        // Read the direction of the bombs from current position
        std::string bombDirectionString;
        std::cin >> bombDirectionString; std::cin.ignore();
        Direction bombDirection(bombDirectionString);

        // Update the discovery area
        area.update(position, bombDirection);

        // Compute the new position: we target the center of the discovery area
        position = area.getCenter();
        std::cout << position.toString() << std::endl;
    }
}
