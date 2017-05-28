

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>


using namespace sf;

class tloLight;
class Kolko
{
public:
	int x,y;
	Texture t1;

public:
	Sprite s1;
	Kolko(int xx=1000,int yy=1000);
	friend void OverwriteObjectKolko(Kolko &k,tloLight &tl);
};

class Krzyzyk
{
public:
	int x,y;
	Texture t1;

public:
	Sprite s1;
	Krzyzyk(int xx=1000,int yy=1000);
	friend void OverwriteObjectKrzyz(Krzyzyk &k,tloLight &tl);
};
class map
{
public:
	Texture t1;
	Sprite s1;
	map();
};

class tloLight
{
private:
	float poz_X,poz_Y;
public:
	Texture t1;
	Sprite s1;
	tloLight(float X=0,float Y=0);
	void changePoz(float xx,float yy);
	friend void OverwriteObjectKolko(Kolko &k,tloLight &tl);
	friend void OverwriteObjectKrzyz(Krzyzyk &k,tloLight &tl);
};

void OverwriteObjectKolko(Kolko &k,tloLight &tl);
void OverwriteObjectKrzyz(Krzyzyk &k,tloLight &tl);
bool logic(char tab[][3], int kPoziomy,int kPionowy,char znak);

int main()
{
    float licz_x=0,licz_y=0;
    int liczKolko=0,liczKrzyz=0;
	map mapa[3][3];
	char mapalogic[3][3]={' '};
    tloLight podswietlenie;
	Kolko k1[5];
	Krzyzyk krzyz[4];
	int player=0;
	char znakX='x';
	char znakO='o';

	 RenderWindow window(VideoMode(180,180),"KolkoKrzyzyk");

	 Event e;
	 while(window.isOpen())
	 {
         while(window.pollEvent(e))
         {
        	if(e.type == Event::Closed) window.close();
        	/*if(e.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
        		{
        		OverwriteObject(k1,podswietlenie);
        		window.draw(k1.s1);
        		}*/
        	if(e.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::P))
        	{
        		if(player%2==0)
        		{
        		OverwriteObjectKolko(k1[liczKolko],podswietlenie);liczKolko++;player++;
        		if(logic(mapalogic,(int)licz_y,(int)licz_x,znakO)) window.close();
        		}
        		else {OverwriteObjectKrzyz(krzyz[liczKrzyz],podswietlenie);liczKrzyz++;player++;
        		if(logic(mapalogic,(int)licz_y,(int)licz_x,znakX)) window.close();
        		}
        	}
        	if(e.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Right))
        	   {licz_x++;podswietlenie.changePoz(60*licz_x,60*licz_y);}
        	if(e.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Left))
        	   {licz_x--;podswietlenie.changePoz(60*licz_x,60*licz_y);}
            if(e.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up))
        	   {licz_y--;podswietlenie.changePoz(60*licz_x,60*licz_y); }
        	if(e.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down))
        	   {licz_y++;podswietlenie.changePoz(60*licz_x,60*licz_y);}


         }


         //draw maps
         for(int i=0;i<3;i++)
        	 for(int j=0;j<3;j++)
        	 {
        		 mapa[i][j].s1.setPosition(60*i,60*j);
        		 window.draw(mapa[i][j].s1);
        	 }
         window.draw(podswietlenie.s1);
         for(int i=0;i<liczKolko;i++)
         {
        	k1[i].s1.setPosition(k1[i].x,k1[i].y);
        	//std::cout<<"\n draw: "<<i<<" "<<k1[i].x <<" "<< k1[i].y;
            window.draw(k1[i].s1);
         }
         for(int i=0;i<liczKrzyz;i++)
                  {
                 	krzyz[i].s1.setPosition(krzyz[i].x,krzyz[i].y);
                 	//std::cout<<"\n draw: "<<i<<" "<<k1[i].x <<" "<< k1[i].y;
                     window.draw(krzyz[i].s1);
                  }
         window.display();
	 }

	 return 0;
}
Krzyzyk::Krzyzyk(int xx, int yy)
{
	x=xx;
	y=yy;
	t1.loadFromFile("images/krzyzyk.jpg");
	s1.setTexture(t1);

}

Kolko::Kolko(int xx, int yy)
{
	x=xx;
	y=yy;
	t1.loadFromFile("images/kolko.jpg");
	s1.setTexture(t1);

}

map::map()
{
  t1.loadFromFile("images/tlo.jpg");
  s1.setTexture(t1);
}

tloLight::tloLight(float X,float Y)
{
	poz_X=X;
	poz_Y=Y;
	t1.loadFromFile("images/tloLight.jpg");
	s1.setTexture(t1);
	s1.setPosition(X,Y);
}

void tloLight::changePoz(float xx,float yy)
{

	poz_X=xx;
	poz_Y=yy;
	s1.setPosition(poz_X,poz_Y);
}

void OverwriteObjectKolko(Kolko &k,tloLight &tl)
{
 k.x=(int)tl.poz_X;
 k.y=(int)tl.poz_Y;
}
void OverwriteObjectKrzyz(Krzyzyk &k,tloLight &tl)
{
 k.x=(int)tl.poz_X;
 k.y=(int)tl.poz_Y;
}
bool logic(char tab[][3], int kPoziomy,int kPionowy,char znak)
{
	tab[kPoziomy][kPionowy]=znak;

	if(tab[0][0]=='x' && tab[1][0]=='x' && tab[2][0]=='x') {return true;}
	if(tab[0][1]=='x' && tab[1][1]=='x' && tab[2][1]=='x') {return true;}
	if(tab[0][2]=='x' && tab[1][2]=='x' && tab[2][2]=='x') {return true;}
	if(tab[0][0]=='x' && tab[0][1]=='x' && tab[0][2]=='x') {return true;}
	if(tab[1][0]=='x' && tab[1][1]=='x' && tab[1][2]=='x') {return true;}
	if(tab[2][0]=='x' && tab[2][1]=='x' && tab[2][2]=='x') {return true;}
	if(tab[0][0]=='x' && tab[1][1]=='x' && tab[2][2]=='x') {return true;}             //skos
	if(tab[2][0]=='x' && tab[1][1]=='x' && tab[0][2]=='x') {return true;}             //skos

	if(tab[0][0]=='o' && tab[1][0]=='o' && tab[2][0]=='o') {return true;}
	if(tab[0][1]=='o' && tab[1][1]=='o' && tab[2][1]=='o') {return true;}
	if(tab[0][2]=='o' && tab[1][2]=='o' && tab[2][2]=='o') {return true;}
	if(tab[0][0]=='o' && tab[0][1]=='o' && tab[0][2]=='o') {return true;}
	if(tab[1][0]=='o' && tab[1][1]=='o' && tab[1][2]=='o') {return true;}
	if(tab[2][0]=='o' && tab[2][1]=='o' && tab[2][2]=='o') {return true;}
	if(tab[0][0]=='o' && tab[1][1]=='o' && tab[2][2]=='o') {return true;}             //skos
	if(tab[2][0]=='o' && tab[1][1]=='o' && tab[0][2]=='o') {return true;}             //skos

	for(int i=0;i<3;i++)
		{std::cout<<"\n";
		for(int j=0;j<3;j++)
			std::cout<<" "<<tab[i][j];
		}
	std::cout<<"\n";
return false;
}
