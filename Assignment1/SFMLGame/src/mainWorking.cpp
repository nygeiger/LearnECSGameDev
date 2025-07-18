#include <iostream>
#include <cstddef>
#include <fstream>
#include <memory>

#include <SFML/Graphics.hpp> // Use with command line until fix
#include <SFML/System/Vector2.hpp>
// #include <../../../../../../../opt/homebrew/Cellar/sfml/3.0.0_1/include/SFML/Graphics.hpp> // Vscode compile temp fix

#include "utils.cpp"

// g++ -std=c++17 main.cpp -o CLmain -I/opt/homebrew/Cellar/sfml/3.0.0_1/include -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-window -lsfml-graphics -lsfml-system

// class AssignmentShape
// {

// public:
//     AssignmentShape(sf::Shape *drArt, float xSpd, float ySpd, sf::Text *textArt)
//     {
//         drawArtifact = drArt;
//         xSpeed = xSpd;
//         ySPeed = ySpd;
//         textArtifact = textArt;
//     }

//     // ~AssignmentShape() { // Is this needed? Is the pointer auto cleaned (is it on stack?)? It's probably already managed

//     //     if (drawArtifact != nullptr || drawArtifact != NULL) {
//     //         delete drawArtifact;
//     //     }
//     // }

//     void moveArtifacts()
//     {
//         const sf::Vector2f currentPosition = drawArtifact->getPosition();
//         const sf::Vector2f newPosition(xSpeed + currentPosition.x, ySPeed + currentPosition.y);
//         drawArtifact->setPosition(newPosition);

//         const sf::Vector2f currentTextPosition = textArtifact->getPosition();
//         const sf::Vector2f newTextPosition(xSpeed + currentTextPosition.x, ySPeed + currentTextPosition.y);
//         textArtifact->setPosition(newTextPosition);
//     }

//     void checkBounds(const sf::Vector2u windowSize)
//     {
//         const sf::Vector2f currentPosition = drawArtifact->getPosition();
//         if (currentPosition.x < 0 || currentPosition.x + drawArtifact->getLocalBounds().size.x > windowSize.x)
//         {
//             xSpeed *= -1;
//         }

//         if (currentPosition.y < 0 || currentPosition.y + drawArtifact->getLocalBounds().size.y > windowSize.y)
//         {
//             ySPeed *= -1;
//         }
//     }

//     sf::Shape *drawArtifact;
//     sf::Text *textArtifact;
//     float xSpeed;
//     float ySPeed;
// };

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

    // ~AssignmentShape() { // Is this needed? Is the pointer auto cleaned (is it on stack?)? It's probably already managed

    //     if (drawArtifact != nullptr || drawArtifact != NULL) {
    //         delete drawArtifact;
    //     }
    // }

    void moveArtifacts()
    {
        const sf::Vector2f currentPosition = drawArtifact->getPosition();
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

void readFile()
{
    std::ifstream ass1File("../media/assignmentFile.txt");
    std::string currLine;

    // # Check if the file is successfully opened
    if (!ass1File.is_open())
    {
        std::cerr << "Error opening the assignment file!";
    }

    std::vector<sf::Shape> shapes;

    while (std::getline(ass1File, currLine))
    {

        const std::string firstWord = currLine.substr(0, currLine.find_first_of(" "));
        std::cout << std::endl;
        std::cout << "Senctece ===> " << currLine << std::endl;
        std::cout << "First word ==> " << firstWord << std::endl;
    }
}

void tempFunc()
{
    const std::string tempStr = "hello word world world end";
    const std::string findMe = " ";

    std::cout << "********** " << string_nth_occurrence(tempStr, "afac", 0) << " *********" << std::endl;
}

// bool compareStrings(std::string str1, std::string str2)
// {
//     if (str1.length() != str2.length())
//         return false;

//     for (int i = 0; i < str1.length(); ++i)
//     {
//         if (tolower(str1[i]) != tolower(str2[i]))
//             return false;
//     }

//     return true;
// }

void driver1()
{
    std::cout << "Hello World \nWith Library Included" << std::endl;

    // # Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
                  << mode.size.x << "x" << mode.size.y << " - "
                  << mode.bitsPerPixel << " bpp" << std::endl;
    }

    // # create a new window of size width by height pixels
    // # top-left of the window is (0,0) and bottom-right is (w,h)
    const int wWidth = 640;
    const int wHeight = 480;
    // sf::Vector2u(wWidth, wHeight);
    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "SFML works!");
    window.setFramerateLimit(60); // # Set FPS to insure velocity consistency

    // # let's make a shape that we will draw to the screen
    sf::CircleShape circle(20);           // # create a circle shape with radius r
    circle.setFillColor(sf::Color::Cyan); // # set the circle color to cyan
    circle.setPosition({300, 300});       // # set the top-left position of the circle
    circle.setPointCount(100);
    float circleMoveSpeed = 0.5f; // # we will use this to move the circle later

    float rx = 300;
    float ry = 200;
    sf::Vector2f rsize(rx, ry);
    sf::RectangleShape rect(rsize);
    rect.setPosition({100, 5});
    rect.setFillColor(sf::Color(255, 255, 0));
    rect.setOutlineThickness(20);

    // # lets load a foant so we can display some text
    sf::Font myFont;

    // # attempt to load a font so we can display some text
    if (!myFont.openFromFile("../fonts/Bytesized/Bytesized-Regular.ttf"))
    {
        // # if we can;t load the font, print an error to the error console and exit
        std::cerr << "Could not load font!" << std::endl;
        exit(-1);
    }

    // # set up the text object that will be drawn to the screen
    sf::Text text(myFont, "Sample Text", 24);

    // # position the top-left corner of the text so that the text aligns on the bottom
    // # text character size is in pixels, so moev the text up from the bottom by it's height
    text.setPosition({0, wHeight - (float)text.getCharacterSize() - 30});
    text.setFillColor(sf::Color::Cyan);

    const auto onClose = [&window](const sf::Event::Closed &)
    {
        window.close();
    };

    // const auto onKeyPressed = [&window](const sf::Event::KeyPressed& keyPressed) {
    //     if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
    //         window.close();
    // };

    const auto onKeyPressedX = [&window, &circleMoveSpeed](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::X)
            circleMoveSpeed *= -1.0f;
    };

    const auto onKeyPressedP = [&window, &text](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::P)
            text.setFillColor({text.getFillColor() == sf::Color::Cyan ? sf::Color::Magenta : sf::Color::Cyan});
    };

    const auto onKeyPressed = [&window, &text, &circleMoveSpeed](const sf::Event::KeyPressed &keyPressed)
    {
        // should be case switch
        if (keyPressed.scancode == sf::Keyboard::Scancode::P)
            text.setFillColor({text.getFillColor() == sf::Color::Cyan ? sf::Color::Magenta : sf::Color::Cyan});
        if (keyPressed.scancode == sf::Keyboard::Scancode::X)
            circleMoveSpeed *= -1.0f;
    };

    const auto onMouseButtonPressed = [](const sf::Event::MouseButtonPressed &mouseButtonPressed)
    { std::cout << "Mouse Pressed" << std::endl; };

    // # main loop - continues for each frame while window is open
    while (window.isOpen())
    {
        // # event handling
        //  sf::Event event;
        window.handleEvents(onClose, onKeyPressed, onMouseButtonPressed); // # Accepts a list of event handlers

        // # basic animation - move the each frame if it's still in frame
        circle.setPosition({(circle.getPosition().x + circleMoveSpeed), circle.getPosition().y + circleMoveSpeed});

        rect.rotate(sf::degrees(-1));

        // # basic rendering function calls
        window.clear(sf::Color::White); // # clear the window of wnything previously drawn
        window.draw(circle);
        window.draw(text);
        window.draw(rect);
        window.display();
    }

    readFile();
}

void driver2()
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
    std::vector<std::shared_ptr<sf::Shape>> shapes;
    std::vector<sf::Text> texts;
    std::vector<AssignmentShape> aShapes;

    // std::shared_ptr<sf::Shape> shape = std::make_shared<sf::CircleShape>(100);
    std::vector<sf::Drawable> drawables;

    // # Check if the file is successfully opened
    if (!ass1File.is_open())
    {
        std::cerr << "Error opening the assignment file!";
    }

    while (std::getline(ass1File, currLine))
    {

        const std::string firstWord = currLine.substr(0, currLine.find_first_of(" "));

        // const char* firstWord = copy( currLine.begin(), currLine.find_first_of(" ")) );
        std::cout << std::endl;
        std::cout << "Senctece ===> " << currLine << std::endl;
        std::cout << "First word ==> " << firstWord << std::endl;

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

            std::cout << " fLo --> " << fontLocation << " fSz --> " << fontSize << " r --> " << r << " g --> " << g << " b--> " << b << std::endl;

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

            std::cout << "Text Obj from File " << text.getCharacterSize() << std::endl;
            // drawables.push_back(text);
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
            // const std::string r = currLine.substr(sixthSpaceIndex + 1, sevenSpaceIndex - sixthSpaceIndex - 1);
            // const std::string g = currLine.substr(sevenSpaceIndex + 1, eightSpaceIndex - sevenSpaceIndex - 1);
            // const std::string b = currLine.substr(eightSpaceIndex + 1, nineSpaceIndex - eightSpaceIndex - 1);

            std::cout << "circleRadius => " << circleRadius << " circleXPos => " << circleXPos << " circleYPos => "
                      << circleYPos << " circleXSpeed => " << circleXSpeed << " circleYSpeed => " << circleYSpeed << " r=>"
                      << r << " g => " << g << " b => " << b << " circleName => " << circleName << std::endl;

            // # let's make a shape that we will draw to the screen
            sf::CircleShape circle(circleRadius); // # create a circle shape with radius r
            // std::shared_ptr<::CircleShape circle(circleRadius); // # create a circle shape with radius r
            circle.setPosition(sf::Vector2f(circleXPos, circleYPos));
            circle.setFillColor(sf::Color(r, g, b)); // # set the circle color to cyan

            std::shared_ptr<sf::Shape> circle2 = std::make_shared<sf::CircleShape>(circleRadius);
            circle2->setPosition(sf::Vector2f(circleXPos, circleYPos));

            sf::Text shapeText(myFont, circleName, circle.getRadius() / 4);
            const sf::Vector2f circleCurrentPos = circle.getPosition();
            const float textWidth = shapeText.getLocalBounds().size.x;
            const float textHeight = shapeText.getLocalBounds().size.y;
            const float widthDifference = circle.getRadius() * 2 - textWidth;
            const float heightDifference = circle.getRadius() * 2 - textHeight;
            shapeText.setPosition({circleCurrentPos.x + widthDifference / 2, circleCurrentPos.y + heightDifference / 2 - shapeText.getCharacterSize()});

            shapes.push_back(circle2);
            // aShapes.push_back(AssignmentShape(&circle, circleXSpeed, circleYSpeed, &shapeText));
            // aShapes.push_back(AssignmentShape(circle, circleXSpeed, circleYSpeed, shapeText));

            // std::shared_ptr<sf::Shape> circle = std::make_shared<sf::CircleShape>(100);
        }
        else if (compareStrings(firstWord, "rectangle"))
        {
            // # Paramters are formatted as the following:
            // # Rectangle N X Y SX SY R G B W H

            const std::vector<std::string> rectParams = splitString2(currLine, ' ');

            std::cout << " This should be the width and height of the rect: width  --> " << rectParams[rectParams.size() - 2] << " height _-__-> " << rectParams[rectParams.size() - 1] << std::endl;

            const std::string rectName = rectParams[1];
            const float rectXPos = std::stoi(rectParams[2]);
            const float rectYPos = std::stoi(rectParams[3]);
            const float rectXSpeed = std::stof(rectParams[4]);
            const float rectYSpeed = std::stof(rectParams[5]);
            const std::uint8_t r = std::stoi(rectParams[6]);
            const std::uint8_t g = std::stoi(rectParams[7]);
            const std::uint8_t b = std::stoi(rectParams[8]);
            const float rectWidth = std::stoi(rectParams[9]);
            const float rectHeight = std::stoi(rectParams[10]);

            sf::Vector2f rsize(rectHeight, rectWidth);
            sf::RectangleShape rect({rectHeight, rectWidth});
            rect.setPosition({rectXPos, rectYPos});
            rect.setFillColor(sf::Color(r, g, b));

            sf::Text text(myFont, "Sample Text", 24);

            // # position the top-left corner of the text so that the text aligns on the bottom
            // # text character size is in pixels, so moev the text up from the bottom by it's height
            text.setPosition({0, wHeight - (float)text.getCharacterSize() - 30});
            text.setFillColor(sf::Color::Cyan);

            sf::Text shapeText(myFont, rectName, rectHeight * rectWidth / 4);
            const sf::Vector2f currentRectPos = rect.getPosition();
            const float textWidth = shapeText.getLocalBounds().size.x;
            const float textHeight = shapeText.getLocalBounds().size.y;
            const float widthDifference = rectWidth - textWidth;
            const float heightDifference = rectHeight - textHeight;
            shapeText.setPosition({currentRectPos.x + widthDifference / 2, currentRectPos.y + heightDifference / 2 - shapeText.getCharacterSize()});

            // aShapes.push_back(AssignmentShape(&rect, rectXSpeed, rectYSpeed, &shapeText));
            // shapes.push_back();
        }
    }

    // // # let's make a shape that we will draw to the screen
    // sf::CircleShape circle(75);           // # create a circle shape with radius r
    // circle.setFillColor(sf::Color::Cyan); // # set the circle color to cyan
    // circle.setPosition({300, 300});       // # set the top-left position of the circle
    // circle.setPointCount(100);
    // float circleMoveSpeedX = 0.5f; // # we will use this to move the circle later
    // float circleMoveSpeedY = 0.5f; // # we will use this to move the circle later

    // sf::Text circleText(myFont, "Circle Text", circle.getRadius()/4);
    // const sf::Vector2f circlePos = circle.getPosition();
    // // circleText.setPosition({circlePos.x + circle.getRadius(), circlePos.y - circle.getRadius()});
    // const sf::Vector2f circleCurrentPos = circle.getPosition();
    // const float textWidth = circleText.getLocalBounds().size.x;
    // const float textHeight = circleText.getLocalBounds().size.y;
    // const float widthDifference = circle.getRadius() * 2 - textWidth;
    // const float heightDifference = circle.getRadius() * 2 - textHeight;
    // circleText.setPosition({circleCurrentPos.x + widthDifference/2, circleCurrentPos.y + heightDifference/2 - circleText.getCharacterSize()});

    // float rx = 300;
    // float ry = 200;
    // sf::Vector2f rsize(rx, ry);
    // sf::RectangleShape rect(rsize);
    // rect.setPosition({100, 5});
    // rect.setFillColor(sf::Color(255, 255, 0));
    // rect.setOutlineThickness(20);

    const auto onClose = [&window](const sf::Event::Closed &)
    {
        window.close();
    };

    // const auto onKeyPressed = [&window](const sf::Event::KeyPressed& keyPressed) {
    //     if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
    //         window.close();
    // };

    // const auto onKeyPressedX = [&window, &circleMoveSpeedX, &circleMoveSpeedY](const sf::Event::KeyPressed &keyPressed)
    // {
    //     if (keyPressed.scancode == sf::Keyboard::Scancode::X)
    //         circleMoveSpeedX *= -1.0f;
    //         circleMoveSpeedY *= -1.0f;
    // };

    // const auto onKeyPressedP = [&window, &text](const sf::Event::KeyPressed &keyPressed)
    // {
    //     if (keyPressed.scancode == sf::Keyboard::Scancode::P)
    //         text.setFillColor({text.getFillColor() == sf::Color::Cyan ? sf::Color::Magenta : sf::Color::Cyan});
    // };

    // const auto onKeyPressed = [&window, &text, &circleMoveSpeed](const sf::Event::KeyPressed &keyPressed)
    // {
    //     // should be case switch
    //     if (keyPressed.scancode == sf::Keyboard::Scancode::P)
    //         text.setFillColor({text.getFillColor() == sf::Color::Cyan ? sf::Color::Magenta : sf::Color::Cyan});
    //     if (keyPressed.scancode == sf::Keyboard::Scancode::X)
    //         circleMoveSpeed *= -1.0f;
    // };

    const auto onMouseButtonPressed = [](const sf::Event::MouseButtonPressed &mouseButtonPressed)
    { std::cout << "Mouse Pressed" << std::endl; };

    // # main loop - continues for each frame while window is open
    while (window.isOpen())
    {
        // # event handling
        //  sf::Event event;
        // window.handleEvents(onClose, onKeyPressedX, onMouseButtonPressed); // # Accepts a list of event handlers
        // window.handleEvents(onClose, onMouseButtonPressed); // # Accepts a list of event handlers

        // # basic animation - move the each frame if it's still in frame
        // circle.setPosition({(circle.getPosition().x + circleMoveSpeedX), circle.getPosition().y + circleMoveSpeedY});
        // circleText.setPosition({(circleText.getPosition().x + circleMoveSpeedX), circleText.getPosition().y + circleMoveSpeedY});

        // const sf::Vector2f circleCurrentPos = circle.getPosition();

        // if (circleCurrentPos.x < 0 || circleCurrentPos.x > window.getSize().x)
        // {
        //     circleMoveSpeedX *= -1;
        // }
        // if (circleCurrentPos.y < 0 || circleCurrentPos.y > window.getSize().y) {
        //     circleMoveSpeedY *= -1;
        // }

        // circleText.setPosition({circleCurrentPos.x, circleCurrentPos.y - (float)circleText.getCharacterSize() - 30});
        // const float lengthDifference = circle.getRadius()*2 - circleText;
        // const float textWidth = circleText.getLocalBounds().size.x;
        // const float textHeight = circleText.getLocalBounds().size.y;

        // const float widthDifference = circle.getRadius() * 2 - textWidth;
        // const float heightDifference = circle.getRadius() * 2 - textHeight;

        // circleText.setPosition({circleCurrentPos.x + widthDifference/2, circleCurrentPos.y + heightDifference/2 - circleText.getCharacterSize()});

        // rect.rotate(sf::degrees(-1));

        // # basic rendering function calls
        window.clear(sf::Color::Black); // # clear the window of wnything previously drawn
                                        // window.draw(circle);
                                        // window.draw(circleText);
                                        // window.draw(text);
                                        // window.draw(rect);

        // for (auto &aShape : aShapes)
        // {
        //     window.draw(*aShape.drawArtifact);
        //     window.draw(*aShape.textArtifact);
        //     aShape.moveArtifacts(); // Doing this after so thaht the initial position is drawn
        //     aShape.checkBounds(window.getSize());
        // }
        // window.display();

        window.draw(*aShapes[0].drawArtifact);
        window.draw(*aShapes[0].textArtifact);
        aShapes[0].moveArtifacts(); // Doing this after so thaht the initial position is drawn
        aShapes[0].checkBounds(window.getSize());

        window.display();
    }
}

void driver3()
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

    // sf::Shape *tempCircleShape = new sf::CircleShape(100);
    // sf::Shape *tempCircleShape2 = new sf::CircleShape(50);
    std::shared_ptr<sf::Shape> tempCircleShape = std::make_shared<sf::CircleShape>(100);
    std::shared_ptr<sf::Shape> tempCircleShape2 = std::make_shared<sf::CircleShape>(50);

    // # Check if the file is successfully opened
    if (!ass1File.is_open())
    {
        std::cerr << "Error opening the assignment file!";
    }

    while (std::getline(ass1File, currLine))
    {

        const std::string firstWord = currLine.substr(0, currLine.find_first_of(" "));

        // const char* firstWord = copy( currLine.begin(), currLine.find_first_of(" ")) );
        std::cout << std::endl;
        std::cout << "Senctece ===> " << currLine << std::endl;
        std::cout << "First word ==> " << firstWord << std::endl;

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

            std::cout << " fLo --> " << fontLocation << " fSz --> " << fontSize << " r --> " << r << " g --> " << g << " b--> " << b << std::endl;

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

            std::cout << "Text Obj from File " << text.getCharacterSize() << std::endl;
            // drawables.push_back(text);
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

            std::cout << "circleRadius => " << circleRadius << " circleXPos => " << circleXPos << " circleYPos => "
                      << circleYPos << " circleXSpeed => " << circleXSpeed << " circleYSpeed => " << circleYSpeed << " r=>"
                      << r << " g => " << g << " b => " << b << " circleName => " << circleName << std::endl;

            // # let's make a shape that we will draw to the screen
            // sf::CircleShape circle(circleRadius); // # create a circle shape with radius r
            // sf::Shape *circle = new sf::CircleShape(circleRadius); // # create a circle shape with radius r. !! Should be a shared_ptr
            std::shared_ptr<sf::Shape> circle = std::make_shared<sf::CircleShape>(circleRadius);
            circle->setPosition(sf::Vector2f(circleXPos, circleYPos));
            circle->setFillColor(sf::Color(r, g, b)); // # set the circle color to cyan

            std::shared_ptr<sf::Shape> circle2 = std::make_shared<sf::CircleShape>(circleRadius);
            circle2->setPosition(sf::Vector2f(circleXPos, circleYPos));

            // sf::Text *circShapeText = new sf::Text(myFont, circleName, circleRadius / 4); // Should be a shared_ptr
            std::shared_ptr<sf::Text> circShapeText = std::make_shared<sf::Text>(myFont, circleName, circleRadius / 4);
            const sf::Vector2f circleCurrentPos = circle->getPosition();
            const float textWidth = circShapeText->getLocalBounds().size.x;
            const float textHeight = circShapeText->getLocalBounds().size.y;
            const float widthDifference = circleRadius * 2 - textWidth;
            const float heightDifference = circleRadius * 2 - textHeight;
            circShapeText->setPosition({circleCurrentPos.x + widthDifference / 2, circleCurrentPos.y + heightDifference / 2 - circShapeText->getCharacterSize()});

            // aShapes.push_back(AssignmentShape(&circle, circleXSpeed, circleYSpeed, &shapeText));
            aShapes.push_back(AssignmentShape(circle, circleXSpeed, circleYSpeed, circShapeText));

            tempCircleShape->setPosition(sf::Vector2f(circleXPos, circleYPos));
            tempCircleShape->setFillColor(sf::Color(r, g, b));

            // std::shared_ptr<sf::Shape> circle = std::make_shared<sf::CircleShape>(100);
        }
        else if (compareStrings(firstWord, "rectangle"))
        {
            // # Paramters are formatted as the following:
            // # Rectangle N X Y SX SY R G B W H

            const std::vector<std::string> rectParams = splitString2(currLine, ' ');

            std::cout << " This should be the width and height of the rect: width  --> " << rectParams[rectParams.size() - 2] << " height _-__-> " << rectParams[rectParams.size() - 1] << std::endl;

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

            // sf::Shape *rect = new sf::RectangleShape({rectHeight, rectWidth}); // Should be a shared_ptr
            std::shared_ptr<sf::Shape> rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectHeight, rectWidth));
            rect->setPosition({rectXPos, rectYPos});
            rect->setFillColor(sf::Color(r, g, b));

            std::shared_ptr<sf::Text> tempSharedText = std::make_shared<sf::Text>(myFont, "Circle Text Shared", 25);
            // sf::Text *rectShapeText = new sf::Text(myFont, rectName, rect->getLocalBounds().size.y / 4); // Should be a shared_ptr
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

    std::shared_ptr<sf::Shape> tempSharedCirc = std::make_shared<sf::CircleShape>(100);
    std::shared_ptr<sf::Text> tempSharedText = std::make_shared<sf::Text>(myFont, "Circle Text Shared", 25);
    AssignmentShape tempAShapeShared(tempSharedCirc, 0.2f, 0.4f, tempSharedText);

    std::shared_ptr<sf::Text> tempCircText = std::make_shared<sf::Text>(myFont, "Circle Text", 25);
    // AssignmentShape tempAShape(tempCircleShape, 0.2f, 0.4f, &tempCircText);

    tempCircleShape2->setFillColor(sf::Color::Green);
    sf::Text tempCircText2(myFont, "Circle 2 Text", 50 / 4);
    const sf::Vector2f circleCurrentPos = tempCircleShape2->getPosition();
    const float textWidth = tempCircText2.getLocalBounds().size.x;
    const float textHeight = tempCircText2.getLocalBounds().size.y;
    const float widthDifference = 50 * 2 - textWidth;
    const float heightDifference = 50 * 2 - textHeight;
    tempCircText2.setPosition({circleCurrentPos.x + widthDifference / 2, circleCurrentPos.y + heightDifference / 2 - tempCircText2.getCharacterSize()});
    // AssignmentShape tempAShape2(tempCircleShape2, 0.2f, 1.0f, &tempCircText2);

    // sf::Shape *tempRectShape = new sf::RectangleShape({100, 50});
    std::shared_ptr<sf::Shape> tempRectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(100, 50));
    tempRectShape->setFillColor(sf::Color::Red);
    sf::Text tempRectText(myFont, "Rect Text", tempRectShape->getLocalBounds().size.y / 4);
    const sf::Vector2f rectCurrentPos = tempRectShape->getPosition();
    const float rectTextWidth = tempRectText.getLocalBounds().size.x;
    const float rectTextHeight = tempRectText.getLocalBounds().size.y;
    const float rectWidth = tempRectShape->getLocalBounds().size.x;
    const float rectHeight = tempRectShape->getLocalBounds().size.y;
    const float rectWidthDifference = rectWidth - rectTextWidth;
    const float rectHeightDifference = rectHeight - rectTextHeight;
    tempRectText.setPosition({rectCurrentPos.x + rectWidthDifference / 2, rectCurrentPos.y + rectHeightDifference / 2 - tempCircText2.getCharacterSize()});
    // AssignmentShape tempARect(tempRectShape, 0.6f, 0.75f, &tempRectText);

    // std::vector<AssignmentShape> tempAShapes;
    // tempAShapes.push_back(tempAShape);
    // tempAShapes.push_back(tempAShape2);
    // tempAShapes.push_back(tempARect);

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
    driver3();
    return 0;
}