// Nicolas De Toffoli (https://github.com/ndetoffoli)
// https://www.codingame.com/ide/puzzle/shadows-of-the-knight-episode-1

#include <iostream>
#include <string>
#include <unordered_map>

// Class to represent a direction of Batman in the building
class Direction
{
private:
    enum class DirectionValue {UP,
        UP_LEFT,
        UP_RIGHT,
        DOWN,
        DOWN_LEFT,
        DOWN_RIGHT,
        LEFT,
        RIGHT,
        UNDEFINED};

public:
    Direction(const std::string & stringValue): value_(DirectionValue::UNDEFINED)
    {
        static std::unordered_map<std::string, DirectionValue> stringToDirectionMap = {
            {"U", DirectionValue::UP},
            {"UL", DirectionValue::UP_LEFT},
            {"UR", DirectionValue::UP_RIGHT},
            {"D", DirectionValue::DOWN},
            {"DL", DirectionValue::DOWN_LEFT},
            {"DR", DirectionValue::DOWN_RIGHT},
            {"L", DirectionValue::LEFT},
            {"R", DirectionValue::RIGHT}};

        if (stringToDirectionMap.find(stringValue) != stringToDirectionMap.end())
        {
            value_ = stringToDirectionMap[stringValue];
        }
    }

    bool goesUp() const
    {
        return (value_ == DirectionValue::UP)
            || (value_ == DirectionValue::UP_LEFT)
            || (value_ == DirectionValue::UP_RIGHT);
    }

    bool goesDown() const
    {
        return (value_ == DirectionValue::DOWN)
            || (value_ == DirectionValue::DOWN_LEFT)
            || (value_ == DirectionValue::DOWN_RIGHT);
    }

    bool goesLeft() const
    {
        return (value_ == DirectionValue::LEFT)
            || (value_ == DirectionValue::UP_LEFT)
            || (value_ == DirectionValue::DOWN_LEFT);
    }

    bool goesRight() const
    {
        return (value_ == DirectionValue::RIGHT)
            || (value_ == DirectionValue::UP_RIGHT)
            || (value_ == DirectionValue::DOWN_RIGHT);
    }

    DirectionValue value_;
};

// Class to represent a position of Batman
class Position
{
public:
    //Position(): x_(0), y_(0) {}

    Position(int x, int y): x_(x), y_(y) {}

    std::string toString() const
    {
        return std::to_string(x_) + " " + std::to_string(y_);
    }

    void debug() const
    {
        std::cerr << "Position = " << toString() << std::endl;
    }

    int x_;
    int y_;
};

// Class to represent the area to explore in the building
class ExplorationArea
{
public:
    ExplorationArea(int x1, int y1, int x2, int y2):
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
        return Position(x1_ + (getWidth()) / 2, y1_ + (getHeight()) / 2);
    }

    std::string toString() const
    {
        return "ExplorationArea = (" + std::to_string(x1_)
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

    int x1_;
    int y1_;
    int x2_;
    int y2_;
};

int main()
{
    // Read input parameters
    int buildingWidth;
    int buildingHeight;
    std::cin >> buildingWidth >> buildingHeight; std::cin.ignore();
    ExplorationArea area(0, 0, buildingWidth - 1, buildingHeight - 1);

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

        // Update the exploration area
        area.update(position, bombDirection);

        // Compute the new position: we target the center of the exploration area
        position = area.getCenter();
        std::cout << position.toString() << std::endl;
    }
}
