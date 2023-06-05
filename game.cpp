/*
g++ -o run game.cpp
-L/home/talha/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
*/

#include <SFML/Graphics.hpp>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class Coin{

    int cax;
    int cay;
    bool check;
 
    public:
    Coin()
    {
        check=0;
        cax=cay=0;
    }
    Coin(int x,int y)
    {
        cax=x;
        cay=y;
    }
    int get_coinx()
    {
    return cax;
    }
      int get_coiny()
    {
    return cay;
    }

      int get_bool()
    {
    return check;
    }
    void setbool(bool c)
    {
        check = c;
    }
    void setvalue(int a,int b)
    {
    cax=a;
    cay=b;
    }
};


class Car{

    int dirx;
    int diry;
   

    public:
      Event action;
      Sprite car;
        Coin in_coin;
    Car()
    {
        dirx=diry=0;
    }
       Car(int x,int y)
    {
        dirx=x;
        diry=y;
    }
    void setvalues(int x,int y)
    {
        dirx=x;
        diry=y;
        
    }
    void set_event(Event& ev)
    {
        action.key.code=ev.key.code;
    }
    int getx()
    {
    return dirx;
    }
    int gety()
    {
        return diry;
    }
    void set_Movement(int x,int y)
    {
        int temp1=dirx;
        int temp2=diry;
     dirx+=x;
     diry+=y;  
     if( (dirx>560 || dirx<0) || (diry<0 || diry>580)  )
     {
        dirx=temp1;
        diry=temp2;
     }
  
    }

};




void* car_mv(void* arg)
{
int cax,cay=0;
Car* obj=(Car*) arg;
   


if (obj->action.key.code == Keyboard::Up) {
    cay = -40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::Down) {
    cay = 40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::Left) {
    cax = -40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::Right) {
    cax = 40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::W) {
    cay = -40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::S) {
    cay = 40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::A) {
    cax = -40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::D) {
    cax = 40;
    obj->set_Movement(cax, cay);
}
else if (obj->action.key.code == Keyboard::Escape || obj->action.key.code == Keyboard::Enter) {
    exit(1);
}
else {
    return (void*)arg;    
}
              
              
           //  obj->car.setPosition(obj->getx(),obj->gety());

         return (void*)arg;       
}


void* coin_collect(void* arg)
{
Car* obj=(Car*) arg;


if( (obj->getx()>= obj->in_coin.get_coinx() && obj->getx()<= obj->in_coin.get_coinx()+40) &&  (obj->gety()>= obj->in_coin.get_coiny() && obj->gety()<= obj->in_coin.get_coiny()+40) )
{
obj->in_coin.setvalue(999,999);
obj->in_coin.setbool(true);
}

return (void*)arg;
}

Text Showtext(Text& t,Font& f,string s,int x,int y)
{
    if (!f.loadFromFile("GA1.ttf"))
        return t;
        
        // text in the game
    Text text(s, f, 30);
    text.setStyle(Text::Bold);
     text.setPosition(x,y);
     text.setFillColor(Color::Red);
     return text;
}

void MENU()
{

    RenderWindow window(VideoMode(800, 600), "GAME PLAY");

        // Create a graphical text to display
    Font font;
    if (!font.loadFromFile("GA1.ttf"))
        return ;

  Texture texture;
    if (!texture.loadFromFile("menu.jpg"))
        return;
    // Create sprite with texture
    Sprite background(texture);
    // Scale background sprite to fill entire window
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                        window.getSize().y / background.getLocalBounds().height);
    // Create a view with the same size as the window
    View view(sf::FloatRect(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    // Set the view to the window
    window.setView(view);

     Text text=Showtext(text,font,"MAIN MENU",120,160);
      text.setFillColor(Color::Yellow);
     Text text2=Showtext(text,font,"COIN CATCHER",320,250);
     text2.setFillColor(Color::Green);
      Text text3=Showtext(text,font,"PRESS ENTER ",280,400);
     text3.setFillColor(Color::Blue);
    while (window.isOpen())
    {
        Event event;
        bool f=false;
        bool f1=false;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if(event.type == Event::KeyPressed)
            {
                 if(event.key.code==Keyboard::Enter){
                 window.close();
                 }
            }

        }
        window.draw(background);
          window.draw(text);
          window.draw(text2);
            window.draw(text3);
        window.display();
    }



}

int main()
{

    MENU();

    srand(time(0));
    /*
    ************************************************************************************
    Generated number will be 15 as last digit of my roll number is 0
    ************************************************************************************
    */
    const int gs = 40;
    int gridHeight = 600 / gs;
    int gridWidth = 800 / gs;

    int score1=0;
    int score2=0;

    RenderWindow window(VideoMode(800, 600), "GAME PLAY");

        // Create a graphical text to display
    Font font;
    if (!font.loadFromFile("GA1.ttf"))
        return EXIT_FAILURE;
        
        // text in the game
    Text text=Showtext(text,font,"COIN",650,0);
    Text text1=Showtext(text,font,"CATCHER",650,30);
    Text text2=Showtext(text,font,"GAME",650,60);
    
   
    
    
    // creating car 1
 
    Car obj;
     Texture car_tex;
    if (!car_tex.loadFromFile("car.png"))
        cerr<<"error"<<endl;
      Sprite car(car_tex);
        car.setPosition(obj.getx(),obj.gety());
      car.setScale(0.09,0.09);

          // creating car 2
 
    Car obj2(560,0);
     Texture car_tex2;
    if (!car_tex2.loadFromFile("car3.png"))
        cerr<<"error"<<endl;
      Sprite car2(car_tex2);
        car2.setPosition(obj2.getx(),obj2.gety());
      car2.setScale(0.09,0.09);

    int rx=700;
    int ry=500;
  
   

    Coin coin_obj(rx,ry);
    Texture coin_tex;
    if (!coin_tex.loadFromFile("coin.png"))
        cerr<<"error"<<endl;
      Sprite coin(coin_tex);
        coin.setPosition(coin_obj.get_coinx(),coin_obj.get_coiny());
     coin.setScale(0.09,0.09);

window.draw(coin);
  rx=rand()%560;
    ry=rand()%560;


    // Load texture of background image
    Texture texture;
    if (!texture.loadFromFile("carb.jpg"))
        return EXIT_FAILURE;
    // Create sprite with texture
    Sprite background(texture);
    // Scale background sprite to fill entire window
    background.setScale(window.getSize().x / background.getLocalBounds().width,
                        window.getSize().y / background.getLocalBounds().height);
    // Create a view with the same size as the window
    View view(sf::FloatRect(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    // Set the view to the window
    window.setView(view);



    RectangleShape grid[gridWidth][gridHeight];
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            grid[i][j].setSize(Vector2f(gs, gs));
            grid[i][j].setOutlineThickness(1);
            grid[i][j].setOutlineColor(Color::Black);
            grid[i][j].setPosition(j * gs, i * gs);
        grid[i][j].setFillColor(Color(255, 255, 255, 100)); 
        }
    }

// DISPLAYING THE MAIN GAME LOOP

    while (window.isOpen())
    {
        Event event;
        bool f=false;
        bool f1=false;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed)
            {
                

                   coin_obj.setvalue(ry,rx);

                obj.in_coin.setvalue(coin_obj.get_coinx(),coin_obj.get_coiny());
                 obj2.in_coin.setvalue(coin_obj.get_coinx(),coin_obj.get_coiny());
            
                void* coin_status;

                if(event.key.code== Keyboard::W || event.key.code== Keyboard::D || event.key.code== Keyboard::S || event.key.code== Keyboard::A )
               {
                void* status2;
                obj2.car=car2;
                obj2.set_event(event);
                pthread_attr_t attrib2;
                pthread_attr_init(&attrib2);
                pthread_attr_setdetachstate(&attrib2,PTHREAD_CREATE_JOINABLE);
                pthread_t id2;
                pthread_create(&id2,&attrib2,car_mv,(void*)&obj2);
                pthread_join(id2,&status2);

                Car* ret2=(Car*)status2;
                 car2.setPosition(ret2->getx(),ret2->gety());

                obj2.in_coin=coin_obj;
                 pthread_attr_t cattrib;
                pthread_attr_init(&cattrib);
                pthread_attr_setdetachstate(&cattrib,PTHREAD_CREATE_JOINABLE);
                 pthread_t cid;
                pthread_create(&cid,&cattrib,coin_collect,(void*)&obj2);
                pthread_join(cid,&coin_status);

                  Car* st=(Car*)coin_status;
               coin_obj.setvalue(st->in_coin.get_coinx(), st->in_coin.get_coiny());
               coin_obj.setbool(st->in_coin.get_bool());
                coin.setPosition(coin_obj.get_coinx(),coin_obj.get_coiny());
                f=coin_obj.get_bool();
               
                }
                else 
                {
                void* status;
                obj.car=car;
                obj.set_event(event);
                pthread_attr_t attrib;
                pthread_attr_init(&attrib);
                pthread_attr_setdetachstate(&attrib,PTHREAD_CREATE_JOINABLE);
                pthread_t id;
                pthread_create(&id,&attrib,car_mv,(void*)&obj);
                pthread_join(id,&status);
                Car* ret=(Car*)status;
                car.setPosition(ret->getx(),ret->gety());
                
                 obj.in_coin=coin_obj;
                pthread_attr_t cattrib;
                pthread_attr_init(&cattrib);
                pthread_attr_setdetachstate(&cattrib,PTHREAD_CREATE_JOINABLE);
                 pthread_t cid;
                pthread_create(&cid,&cattrib,coin_collect,(void*)&obj);
                pthread_join(cid,&coin_status);

                Car* st=(Car*)coin_status;
               coin_obj.setvalue(st->in_coin.get_coinx(), st->in_coin.get_coiny());
               coin_obj.setbool(st->in_coin.get_bool());
                coin.setPosition(coin_obj.get_coinx(),coin_obj.get_coiny());
                f1=coin_obj.get_bool();
                
                }
            }
        }

        //every time clear the window
        window.clear();
        // Draw sprite and grid line
        window.draw(background);
        // Draw grid lines
             for (int i = 0; i < gridWidth; i++)
             {
                 for (int j = 0; j < gridHeight; j++)
                 {
                     window.draw(grid[i][j]);
                 }
             }


  string s1,s2;
    if(f1==true)
    {
      
        score1+=10;
         
    }
    if(f==true)
    {
     
         score2+=10;
           
    }

    //DISPLAYING TEXT OF SCORE IN GAME

   s1="SCORE 1 : "+to_string(score1);
  s2="SCORE 2 : "+to_string(score2); 
 

    Text texts1=Showtext(texts1,font,s1,600,120);
     texts1.setFillColor(Color::Black);

   Text texts2=Showtext(texts2,font,s2,600,180);
     texts2.setFillColor(Color::Black);

    // Displaying the text in game

        window.draw(text);
        window.draw(text1);
        window.draw(text2);
         window.draw(texts1);
         window.draw(texts2);

    // Displaying the objexts in game

        window.draw(car);
       window.draw(car2);
       window.draw(coin);
      window.display();

        if(f || f1)
        {      
             rx=rand()%560;
             ry=rand()%560;
               
        }
        f=f1=false;    
          coin_obj.setbool(false);

    // DISPLAY THE WIN SCREEN WHEN THE PLAYER WIN

    if(score1>=100)
    {       

     Texture btex;
    if (!btex.loadFromFile("win.jpeg"))
        return 1;

    // Create sprite with texture
    Sprite winbg(btex);
    // Scale background sprite to fill entire window
    winbg.setScale(window.getSize().x / winbg.getLocalBounds().width,
                        window.getSize().y / winbg.getLocalBounds().height);
    // Create a view with the same size as the window
    View view(sf::FloatRect(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    // Set the view to the window
    window.setView(view);

     while(window.isOpen())
        {
            while (window.pollEvent(event))
            {
            if (event.type == Event::Closed)
                window.close();       
            }
            Text textw=Showtext(textw,font,"PLAYER 1 WINS",289,225);
         textw.setFillColor(Color::White);
        window.draw(winbg);
         window.draw(textw);
        window.display();
    
        }
}
    
    if(score2>=100)
    {
    Texture btex;
    if (!btex.loadFromFile("win.jpeg"))
        return 1;

    // Create sprite with texture
    Sprite winbg(btex);
    // Scale background sprite to fill entire window
    winbg.setScale(window.getSize().x / winbg.getLocalBounds().width,
                        window.getSize().y / winbg.getLocalBounds().height);
    // Create a view with the same size as the window
    View view(sf::FloatRect(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    // Set the view to the window
    window.setView(view);

     while(window.isOpen())
        {
            while (window.pollEvent(event))
            {
            if (event.type == Event::Closed)
                window.close();
               
            }
            Text textw=Showtext(textw,font,"PLAYER 2 WINS",289,225);
         textw.setFillColor(Color::White);
        window.draw(winbg);
         window.draw(textw);
        window.display();
        
        }
    }

    }

    return 0;
}
