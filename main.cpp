#include <iostream>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>

// Barcode Drawing logic
sf::Vector2f drawLines(sf::RenderTexture &window, std::vector<float> lineWidths, sf::Vector2f position, float height, bool startsBlack) {
    sf::Vector2f curPosition = position;
    for (int i = 0; i < lineWidths.size(); i ++) {
        sf::Vector2f rectSize = {lineWidths[i], height};
        
        sf::RectangleShape rectangle;
        rectangle.setSize(rectSize);
        rectangle.setPosition(curPosition);
        if (startsBlack) {
            rectangle.setFillColor(sf::Color::Black);
        } else {
            rectangle.setFillColor(sf::Color::White);
        }
        startsBlack = !startsBlack;

        window.draw(rectangle);

        curPosition = {curPosition.x + lineWidths[i], curPosition.y};
    }
    return curPosition;
}

sf::Vector2f drawNumber(sf::RenderTexture &window, char num, sf::Vector2f position) {
    std::vector<float> lineWidths;
    bool startsBlack = true;
    switch(num) {
    case '0':
        lineWidths = {2, 2, 2, 6, 6, 2, 6, 2, 2, 2};
        startsBlack = true;
        break;
    case '1':
        lineWidths = {6, 2, 2, 6, 2, 2, 2, 2, 6, 2};
        startsBlack = true;
        break;
    case '2':
        lineWidths = {2, 2, 6, 6, 2, 2, 2, 2, 6, 2};
        startsBlack = true;
        break;
    case '3':
        lineWidths = {6, 2, 6, 6, 2, 2, 2, 2, 2, 2};
        startsBlack = true;
        break;
    case '4':
        lineWidths = {2, 2, 2, 6, 6, 2, 2, 2, 6, 2};
        startsBlack = true;
        break;
    case '5':
        lineWidths = {6, 2, 2, 6, 6, 2, 2, 2, 2, 2};
        startsBlack = true;
        break;
    case '6':
        lineWidths = {2, 2, 6, 6, 6, 2, 2, 2, 2, 2};
        startsBlack = true;
        break;
    case '7':
        lineWidths = {2, 2, 2, 6, 2, 2, 6, 2, 6, 2};
        startsBlack = true;
        break;
    case '8':
        lineWidths = {6, 2, 2, 6, 2, 2, 6, 2, 2, 2};
        startsBlack = true;
        break;
    case '9':
        lineWidths = {2, 2, 6, 6, 2, 2, 6, 2, 2, 2};
        startsBlack = true;
        break;
    case '*':
        lineWidths = {2, 6, 2, 2, 6, 2, 6, 2, 2, 2};
        startsBlack = true;
        break;
    }
    return drawLines(window, lineWidths, position, 200, startsBlack);
}

sf::Vector2f drawCode(sf::RenderTexture &window, sf::Vector2f position, std::string code){
    for (int i = 0; i < code.length(); i ++){
        position = drawNumber(window, code[i], position);
    }
    return position;
}

// Image Generation Logic
void createBarcode(std::string code) {
    std::string outputFilename = code + ".png";
    code = "*" + code + "*";
    unsigned int imgWidth = 32 * code.length();
    unsigned int imgHeight = 100;

    sf::RenderTexture renderTexture({imgWidth, imgHeight});
    sf::Vector2f rectPosition = {0.f, 0.f};

    drawCode(renderTexture, rectPosition, "*401669*");
    // renderTexture.display();
    
    const sf::Texture &texture = renderTexture.getTexture();
    sf::Image image = texture.copyToImage();

    if (image.saveToFile(outputFilename)) {
        std::cout << "Successfully saved image to " << outputFilename << std::endl;
    } else {
        std::cerr << "Error: Failed to save image to " << outputFilename << std::endl;
    }
}

int main()
{
    std::cout << "Tell me the file that contains the ids!" << std::endl;
    std::string idFilename;
    std::cin >> idFilename;

    std::ifstream fin(idFilename);
    if (fin.is_open()){
        std::string code;
        while(getline(fin, code)){
            if (code.length() > 0){
                createBarcode(code);
            }
        }
        fin.close();
    }

    return 0;
}