#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

float xCamera = 0;
float yCamera = 0;
float xVelocitieCamera = 0;
float yVelocitieCamera = 0;
int squareSize = 32;
bool clicked = false;
sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
sf::RenderWindow window(desktop, "Random 1.0", sf::Style::Fullscreen);


sf::Color g_starColours[8] =
{
    sf::Color(255,255,255,255), sf::Color(255,51,51),sf::Color(255,34,102),sf::Color(153,255,255),
    sf::Color(255,128,0),sf::Color(102,204,0),sf::Color(0,128,205),sf::Color(204,0,204)
};


struct Planet
{
    double radius = 0.0;
    double distance = 0.0;
    double foliage = 0.0;
    double minerals = 0.0;
    double water = 0.0;
    double gases = 0.0;
    sf::CircleShape circle;
};



class cStarSystem
{
public:
    cStarSystem(uint32_t x_, uint32_t y_)
    {
        nLehmer = ((x_ -(uint32_t)xCamera) & 0xFFFF) << 16 | ((y_ - uint32_t(yCamera)) & 0XFFFF); 
        startExist = (rndInt(0, 10) == 1);
        if(!startExist) return;
        x = x_ + (squareSize - 1)*(uint32_t)xCamera;
        y = y_ + (squareSize - 1)*(uint32_t)yCamera;
        startRadius = rndDouble(3.0, 6.0);
        startColor = g_starColours[rndInt(0,8)];
        starXError = rndDouble(-3.5,3.5);
        starYError = rndDouble(-3,3);
        fillStar();
    }

    void draw(sf::RenderWindow& window)
    {
        if(mouseXPosition == x/squareSize && mouseYPosition == y/squareSize)
        {
            float outlineRadius = 20;
            sf::CircleShape outline(outlineRadius);
            outline.setPosition(x + starXError,y + starYError);
            outline.setOrigin(outlineRadius,outlineRadius);
            outline.setFillColor(sf::Color::Black);
            outline.setOutlineThickness(2);
            outline.setOutlineColor(sf::Color::Yellow);
            window.draw(outline);
            PlanetsToo();
        }

        for(auto circle : circles)
        {
            window.draw(circle);
        }

        

    }
    
public:
    bool startExist = false;
    double startRadius = 0.0f;
    sf::Color startColor = sf::Color::White; 
    int x = 0, y = 0;
    std::vector<Planet> planets;
    int numberPlanets = 0;

private:
    uint32_t nLehmer = 0;
    double starYError, starXError;    
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    int mouseXPosition = mouse.x/squareSize;
    int mouseYPosition = mouse.y/squareSize;
    std::vector<sf::CircleShape> circles;
    
    void PlanetsToo()
    {
        if(!clicked)return;
        std::cout<<"asd";
        numberPlanets = rndInt(0,10);
        createPlanets();
        sf::RenderWindow starWindow(sf::VideoMode(1000,400),"STAR SYSTEM");
        clicked = false;
        while(starWindow.isOpen())
        {
            drawStarWindow(starWindow);
            sf::Event event;
            while(starWindow.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    starWindow.close();
                }
                starWindow.clear(sf::Color::Black);
                starWindow.display();
            }
        }
    }

    void drawStarWindow(sf::RenderWindow &starWindow)
    {
        for(auto planet : planets)
        {
            //starWindow.draw(planet);
        }
    }

    uint32_t Lehmer32()
	//this function is used to create an random number based on an seed
    {
		nLehmer += 0xe120fc15;
		uint64_t tmp;
		tmp = (uint64_t)nLehmer * 0x4a39b70d;
		uint32_t m1 = (tmp >> 32) ^ tmp;
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	}

    int rndInt(int min, int max)
    {
        return Lehmer32() % (max - min) + min;
    }
    
    double rndDouble(double min, double max)
    {
        return ((double)Lehmer32() / (double)(0x7FFFFFFF) * (max - min) + min);
    }


    void fillStar()
    {
        int detail = 7;
        std::cout<<detail<<std::endl;
        for(int i = 0; i < detail; i++)
        {
            sf::CircleShape circle(startRadius/detail*i);
            startColor.a = (255 - 255/detail * i);
            circle.setFillColor(startColor);
            circle.setOrigin(startRadius/detail * i,startRadius/detail * i);
            circle.setPosition(x + starXError,y + starYError);
            circles.push_back(circle);
        }
    }

    void createPlanets()
    {
        for(int i = 0; i < numberPlanets; i++)
        {
            Planet newPlanet;
            newPlanet.radius = rndDouble(20.0, 50.0);
            newPlanet.distance = rndDouble(60.0, 100.0);
            newPlanet.foliage = rndDouble(0.0, 100.0);
            newPlanet.minerals = rndDouble(0.0, 100.0);
            newPlanet.water = rndDouble(0.0, 100.0);
            newPlanet.gases = rndDouble(0.0, 100.0);
            //newPlanet.circle(newPlanet.radius);
            
            planets.push_back(newPlanet);
        }
    }
};


void generateStars(std::vector<cStarSystem> &stars);
void generateStars(std::vector<cStarSystem> &stars)
{
    stars.clear();
    int nSectorsX = desktop.width/squareSize;
    int nSectorsY = desktop.height/squareSize; 
    for(int x = -xCamera ; x < nSectorsX - xCamera; x++)
    {
        for(int y = -yCamera ; y < nSectorsY - yCamera ; y++)
        {
            cStarSystem star(x * squareSize +squareSize/2 +(uint32_t)xCamera , y * squareSize +squareSize/2 +(uint32_t)yCamera );
            if(star.startExist)stars.push_back(star);
        }

    }
}



void keyEvent();
void keyEvent()
{
    bool HKey = sf::Keyboard::isKeyPressed(sf::Keyboard::H);
    bool WKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool AKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool SKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool DKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    if(AKey){xCamera+=1; }else if(DKey){xCamera -= 1;}
    if(WKey){yCamera += 1;}else if(SKey){yCamera -= 1;}
}


int main(){
    std::vector<cStarSystem> stars;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)window.close();
            if(event.type == sf::Event::KeyPressed)keyEvent();  
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    clicked = true;
                }
            } 
        }

        window.clear(sf::Color::Black);
        for(auto star : stars)
        {
            star.draw(window);
        }
        generateStars(stars);
     //   std::cout<<stars.size()<<std::endl;                   
        window.display();

    }

    return 0;
}
