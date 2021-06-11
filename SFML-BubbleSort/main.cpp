
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>

using namespace std;
using namespace sf;

struct Rectangle
{
    int height = 0;
    int width = 1;
    
    int xPos = 0;
    int yPos = 0;
    
    Color color = Color(0, 0, 0);
    
    
};

void FillVector(Rectangle rect, vector<Rectangle> &rectHolder, Image img){
    
    int xOffset = 0;
    while (xOffset < img.getSize().x) {
        rect.height = rand() % img.getSize().y - 50;
        
        if(rect.height < 3){
            rect.height = 3;
        }
        
        rect.xPos = xOffset;
        rect.yPos = img.getSize().y - rect.height;
        
        rectHolder.push_back(rect);
        
        xOffset += 3;
        
    }
    
    cout << rectHolder.size() << endl;
    
}

void PaintVector(Image &image, vector<Rectangle> &rectHolder)
{

    for (int i = 0; i < rectHolder.size(); i++)
    {
        for (int x = 0; x < rectHolder[i].width; x++)
        {
            for (int y = 0; y < rectHolder[i].height; y++)
            {
                image.setPixel(rectHolder[i].xPos + x, rectHolder[i].yPos + y, Color(0,0,0));
            }
        }
    }
    
    cout << "Confirmed" << endl;
}
void BubbleSort(vector<Rectangle> &rectHolder, Image &image, RenderWindow &window, Texture texture, Sprite sprite){
    
    Rectangle tempRect;
    int tempXPos;
    for (int i = 0; i < rectHolder.size(); i++) {
        
        for (int j = 0; j < rectHolder.size()-1; j++) {
            
            if(rectHolder[j].height > rectHolder[j+1].height){
                window.clear();
                
                for (int x = 0; x < rectHolder[j].width; x++)
                    {
                        for (int y = 0; y < rectHolder[j].height; y++)
                        {
                            image.setPixel(rectHolder[j + 1].xPos + x, rectHolder[j].yPos + y, rectHolder[j].color);
                        }
                    }
                for (int x = 0; x < rectHolder[j].width; x++)
                    {
                        for (int y = 0; y < rectHolder[j].height; y++)
                        {
                            image.setPixel(rectHolder[j].xPos + x, rectHolder[j].yPos + y, Color(255, 255, 255));
                        }
                    }
                for (int x = 0; x < rectHolder[j+1].width; x++)
                    {
                        for (int y = 0; y < rectHolder[j+1].height; y++)
                        {
                            image.setPixel(rectHolder[j].xPos + x, rectHolder[j+1].yPos + y, rectHolder[j].color);
                        }
                    }
                
                tempXPos = rectHolder[j].xPos;
                rectHolder[j].xPos = rectHolder[j+1].xPos;
                rectHolder[j+1].xPos = tempXPos;
                
                tempRect = rectHolder[j];
                rectHolder[j] = rectHolder[j+1];
                rectHolder[j+1] = tempRect;
                texture.loadFromImage(image);
                sprite.setTexture(texture);
                
                window.draw(sprite);
                window.display();
            
            }
        }
    }
}

int main() {
    
    srand(time(NULL));
    
    int width = 1920;
    int height = 1080;
    bool isSpacePressed = false;

    RenderWindow window(VideoMode(width, height), "BubbleSort");
    Event ev;
    
    Image image;
    image.create(width, height);
    
    for (int i = 0;i <width; i++) {
        for (int j = 0; j < height; j++) {
            image.setPixel(i, j, Color(255, 255, 255));
        }
    }
    
    Texture texture;
    texture.loadFromImage(image);
    Sprite sprite;
    sprite.setTexture(texture);
    
    Rectangle rect;
    vector<Rectangle> rectVector;
    
    FillVector(rect, rectVector, image);
    PaintVector(image, rectVector);
    
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    
    cout << "test" << endl;
    
    while (window.isOpen()) {
        
        while (window.pollEvent(ev)) {
            if(ev.type == Event::Closed){
                window.close();
            }
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Space){
                    cout << "SpaceBar Pressed" << endl;
                    isSpacePressed = true;
                }
            }
        }
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        
        if(isSpacePressed){
            BubbleSort(rectVector, image, window, texture, sprite);
            isSpacePressed = false;
        }
        
        window.clear();
        
        window.draw(sprite);
        
        window.display();
        
        
    }
    
    return 0;
}
