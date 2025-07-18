#include <iostream>
#include <cstddef>
#include <fstream>
#include <memory>

#include <SFML/Graphics.hpp> // Use with command line until fix
#include <SFML/System/Vector2.hpp>
// #include <../../../../../../../opt/homebrew/Cellar/sfml/3.0.0_1/include/SFML/Graphics.hpp> // Vscode compile temp fix

#include "utils.cpp"

// g++ -std=c++17 main.cpp -o CLmain -I/opt/homebrew/Cellar/sfml/3.0.0_1/include -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-window -lsfml-graphics -lsfml-system

class AssignmentShape
{
public:
    AssignmentShape(std::shared_ptr<sf::Shape> drArt, float xSpd, float ySpd, std::shared_ptr<sf::Text> textArt)
    {
        drawArtifact = drArt;
        xSpeed = xSpd;
        ySPeed = ySpd;
        textArtifact = textArt;
    }

    void moveArtifacts()
    {
        const sf::Vector2f currentPosition = drawArtifact->getPosition();
        const auto currentShapeBounds = drawArtifact->getLocalBounds();
        const sf::Vector2f newPosition(xSpeed + currentPosition.x, ySPeed + currentPosition.y);
        drawArtifact->setPosition(newPosition);

        const sf::Vector2f currentTextPosition = textArtifact->getPosition();
        const sf::Vector2f newTextPosition(xSpeed + currentTextPosition.x, ySPeed + currentTextPosition.y);
        textArtifact->setPosition(newTextPosition);
    }

    void checkBounds(const sf::Vector2u windowSize)
    {
        const sf::Vector2f currentPosition = drawArtifact->getPosition();
        if (currentPosition.x < 0 || currentPosition.x + drawArtifact->getLocalBounds().size.x > windowSize.x)
        {
            xSpeed *= -1;
        }

        if (currentPosition.y < 0 || currentPosition.y + drawArtifact->getLocalBounds().size.y > windowSize.y)
        {
            ySPeed *= -1;
        }
    }

    std::shared_ptr<sf::Shape> drawArtifact;
    std::shared_ptr<sf::Text> textArtifact;
    float xSpeed;
    float ySPeed;
};

void driver()
{

    // # CONSTANT VARIABLES
    const sf::Vector2u _DEFAULT_WINDOW_SIZE_VECTOR(650, 480);
    // # END CONSTANT VARIABLES

    // # create a new window of size width by height pixels
    // # top-left of the window is (0,0) and bottom-right is (w,h)
    int wWidth = 640;
    int wHeight = 480;
    // sf::Vector2u(wWidth, wHeight);
    sf::RenderWindow window(sf::VideoMode(_DEFAULT_WINDOW_SIZE_VECTOR), "SFML works!");
    window.setFramerateLimit(60); // # Set FPS to insure velocity consistency

    sf::Font myFont;

    // # Create Shapes to draw from file
    std::ifstream ass1File("../media/assignmentFile.txt");
    std::string currLine;
    std::vector<AssignmentShape> aShapes;


    // # Check if the file is successfully opened
    if (!ass1File.is_open())
    {
        std::cerr << "Error opening the assignment file!";
    }

    while (std::getline(ass1File, currLine))
    {
        const std::string firstWord = currLine.substr(0, currLine.find_first_of(" "));

        if (compareStrings(firstWord, "window"))
        {
            // # Paramters are formatted as the following:
            // # Window W H

            const size_t firstSpaceIndex = string_nth_occurrence(currLine, " ", 1);
            const size_t secondSpaceIndex = string_nth_occurrence(currLine, " ", 2);

            wWidth = stoi(currLine.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1));
            wHeight = stoi(currLine.substr(secondSpaceIndex + 1));

            sf::Vector2u newWindowSize(wWidth, wHeight);

            window.setSize(newWindowSize);
        }
        else if (compareStrings(firstWord, "font"))
        {
            // # Paramters are formatted as the following:
            // # Font F S R G B

            const size_t firstSpaceIndex = string_nth_occurrence(currLine, " ", 1);
            const size_t secondSpaceIndex = string_nth_occurrence(currLine, " ", 2);
            const size_t thirdsSpaceIndex = string_nth_occurrence(currLine, " ", 3);
            const size_t fourthSpaceIndex = string_nth_occurrence(currLine, " ", 4);
            const size_t fithSpaceIndex = string_nth_occurrence(currLine, " ", 5);

            const std::string fontLocation = currLine.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
            const int fontSize = std::stoi(currLine.substr(secondSpaceIndex + 1, thirdsSpaceIndex - secondSpaceIndex - 1));
            const std::uint8_t r = std::stoi(currLine.substr(thirdsSpaceIndex + 1, fourthSpaceIndex - thirdsSpaceIndex - 1));
            const std::uint8_t g = std::stoi(currLine.substr(fourthSpaceIndex + 1, fithSpaceIndex - fourthSpaceIndex - 1));
            const std::uint8_t b = std::stoi(currLine.substr(fithSpaceIndex + 1));

            const sf::Color textColor(r, g, b);

            // # attempt to load a font so we can display some text
            if (!myFont.openFromFile(fontLocation))
            {
                // # if we can;t load the font, print an error to the error console and exit
                std::cerr << "Could not load font!" << std::endl;
                exit(-1);
            }
            sf::Text text(myFont, "Sample Text", fontSize);
            text.setPosition({0, wHeight - (float)text.getCharacterSize() - fontSize});
            text.setFillColor(textColor);
        }
        else if (compareStrings(firstWord, "circle"))
        {
            // # Paramters are formatted as the following:
            // # Circle N X Y SX SY R G B R

            const size_t firstSpaceIndex = string_nth_occurrence(currLine, " ", 1);
            const size_t secondSpaceIndex = string_nth_occurrence(currLine, " ", 2);
            const size_t thirdsSpaceIndex = string_nth_occurrence(currLine, " ", 3);
            const size_t fourthSpaceIndex = string_nth_occurrence(currLine, " ", 4);
            const size_t fithSpaceIndex = string_nth_occurrence(currLine, " ", 5);
            const size_t sixthSpaceIndex = string_nth_occurrence(currLine, " ", 6);
            const size_t sevenSpaceIndex = string_nth_occurrence(currLine, " ", 7);
            const size_t eightSpaceIndex = string_nth_occurrence(currLine, " ", 8);
            const size_t nineSpaceIndex = string_nth_occurrence(currLine, " ", 9);

            const std::string circleName = currLine.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
            const int circleRadius = std::stoi(currLine.substr(nineSpaceIndex));
            const int circleXPos = std::stoi(currLine.substr(secondSpaceIndex + 1, thirdsSpaceIndex - secondSpaceIndex - 1));
            const int circleYPos = std::stoi(currLine.substr(thirdsSpaceIndex + 1, fourthSpaceIndex - thirdsSpaceIndex - 1));
            const float circleXSpeed = std::stof(currLine.substr(fourthSpaceIndex + 1, fithSpaceIndex - fourthSpaceIndex - 1));
            const float circleYSpeed = std::stof(currLine.substr(fithSpaceIndex + 1, sixthSpaceIndex - fithSpaceIndex - 1));
            const std::uint8_t r = std::stoi(currLine.substr(sixthSpaceIndex + 1, sevenSpaceIndex - sixthSpaceIndex - 1));
            const std::uint8_t g = std::stoi(currLine.substr(sevenSpaceIndex + 1, eightSpaceIndex - sevenSpaceIndex - 1));
            const std::uint8_t b = std::stoi(currLine.substr(eightSpaceIndex + 1, nineSpaceIndex - eightSpaceIndex - 1));

            // # let's make a shape that we will draw to the screen
            std::shared_ptr<sf::Shape> circle = std::make_shared<sf::CircleShape>(circleRadius);
            circle->setPosition(sf::Vector2f(circleXPos, circleYPos));
            circle->setFillColor(sf::Color(r, g, b));

            // sf::Text *circShapeText = new sf::Text(myFont, circleName, circleRadius / 4); // Should be a shared_ptr
            std::shared_ptr<sf::Text> circShapeText = std::make_shared<sf::Text>(myFont, circleName, circleRadius / 4);
            const sf::Vector2f circleCurrentPos = circle->getPosition();
            const float textWidth = circShapeText->getLocalBounds().size.x;
            const float textHeight = circShapeText->getLocalBounds().size.y;
            const float widthDifference = circleRadius * 2 - textWidth;
            const float heightDifference = circleRadius * 2 - textHeight;
            circShapeText->setPosition({circleCurrentPos.x + widthDifference / 2, circleCurrentPos.y + heightDifference / 2 - circShapeText->getCharacterSize()});

            aShapes.push_back(AssignmentShape(circle, circleXSpeed, circleYSpeed, circShapeText));
        }
        else if (compareStrings(firstWord, "rectangle"))
        {
            // # Paramters are formatted as the following:
            // # Rectangle N X Y SX SY R G B W H

            const std::vector<std::string> rectParams = splitString2(currLine, ' ');

            const std::string rectName = rectParams[1];
            const float rectXPos = std::stoi(rectParams[2]);
            const float rectYPos = std::stoi(rectParams[3]);
            const float rectXSpeed = std::stof(rectParams[4]);
            const float rectYSpeed = std::stof(rectParams[5]);
            const std::uint8_t r = std::stoi(rectParams[6]);
            const std::uint8_t g = std::stoi(rectParams[7]);
            const std::uint8_t b = std::stoi(rectParams[8]);
            const float rectWidth = std::stof(rectParams[9]);
            const float rectHeight = std::stof(rectParams[10]);

            std::shared_ptr<sf::Shape> rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectHeight, rectWidth));
            rect->setPosition({rectXPos, rectYPos});
            rect->setFillColor(sf::Color(r, g, b));

            std::shared_ptr<sf::Text> rectShapeText = std::make_shared<sf::Text>(myFont, rectName, rect->getLocalBounds().size.y / 4);
            const sf::Vector2f rectCurrentPos = rect->getPosition();
            const float rectTextWidth = rectShapeText->getLocalBounds().size.x;
            const float rectTextHeight = rectShapeText->getLocalBounds().size.y;
            const float rectBoundWidth = rect->getLocalBounds().size.x;
            const float rectBoundHeight = rect->getLocalBounds().size.y;
            const float rectWidthDifference = rectBoundWidth - rectTextWidth;
            const float rectHeightDifference = rectBoundHeight - rectTextHeight;
            rectShapeText->setPosition({rectCurrentPos.x + rectWidthDifference / 2, rectCurrentPos.y + rectHeightDifference / 2 - rectShapeText->getCharacterSize()});

            aShapes.push_back(AssignmentShape(rect, rectXSpeed, rectYSpeed, rectShapeText));
        }
    }

    const auto onClose = [&window](const sf::Event::Closed &)
    {
        window.close();
    };

    // # main loop - continues for each frame while window is open
    while (window.isOpen())
    {
        window.handleEvents(onClose); // # Accepts a list of event handlers
        window.clear(sf::Color::Black); // # clear the window of wnything previously drawn

        // for (AssignmentShape &currAShape : tempAShapes)
        // {
        //     window.draw(*currAShape.drawArtifact);
        //     window.draw(*currAShape.textArtifact);
        //     currAShape.moveArtifacts(); // Doing this after so thaht the initial position is drawn
        //     currAShape.checkBounds(window.getSize());
        // }
        for (AssignmentShape &currAShape : aShapes)
        {
            window.draw(*currAShape.drawArtifact);
            window.draw(*currAShape.textArtifact);
            currAShape.moveArtifacts(); // Doing this after so thaht the initial position is drawn
            currAShape.checkBounds(window.getSize());
        }
        window.display();
    }
}

int main(int argc, char *argv[])
{
    driver();
    return 0;
}