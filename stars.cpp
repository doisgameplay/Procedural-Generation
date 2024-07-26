#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>


int main(){

    sf::RenderWindow window(sf::VideoMode(500,500), "stars");
    float radius = 10;
    int x = 250,y = 250;
    int detail  = 8;
    std::vector<sf::CircleShape> circles;
    for(int i = 0; i < detail; i++)
    {
        sf::CircleShape circle(radius/detail*i);
        circle.setFillColor(sf::Color(255,255,0,255 - 255/detail*i));
        circle.setOrigin(radius/detail * i,radius/detail * i);
        circle.setPosition(x,y);
        circles.push_back(circle);
    }
    sf::CircleShape starCentral(radius);
    starCentral.setFillColor(sf::Color(255,255,0));
    starCentral.setOrigin(radius,radius);
    starCentral.setPosition(x,y);
    std::vector<sf::RectangleShape> lines;
    for(int i = 0; i < 4; i++)
    {
        float rest;
        if(i % 2){rest = 1.5;}else{rest = 2;}
        sf::RectangleShape line(sf::Vector2f(radius/10,(3*radius)*(rest)));
        line.setFillColor(sf::Color::Yellow);
        line.setOrigin(radius/10,rest*(3*radius)/2);
        line.setPosition(x,y);
        line.setRotation(45 * i);
        lines.push_back(line);
    } 
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)window.close();
        }

        window.clear(sf::Color::Black);
        for(auto line : lines)
        {
            //window.draw(line);
        }
        for(auto circle : circles)
        {
          window.draw(circle);
        }
        //window.draw(starCentral);
        window.display();
    }





    return 0;
}