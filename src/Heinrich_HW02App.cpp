#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Square.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Heinrich_HW02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);

private:
	Square* list;

	static const int width = 360;
	static const int height = 360;

	static const Vec2f x;
	static const Vec2f y;
};

// you can define these under private: like with width and height.
// It would be less cluttered (this is a small block of text anyways) and faster to find, albeit marginally considering the size of the file
const Vec2f Heinrich_HW02App::x = Vec2f(0.7071f, -0.7071f);
const Vec2f Heinrich_HW02App::y = Vec2f(0.7071f, 0.7071f);

void Heinrich_HW02App::prepareSettings(Settings* settings){
	settings->setWindowSize(width,height);
	settings->setResizable(false);
}

void Heinrich_HW02App::setup()
{
	list = new Square();
	Vec2f trans = (width/2.0f)*x+(height/2.0f)*y;
	list->x = trans.x;
	list->y = trans.y+50;
	list->size = height/50.0f;
}

void Heinrich_HW02App::mouseDown( MouseEvent event )
{
	int x = event.getX();
	int y = event.getY();

	int red = (rand()%255);
	int green = (rand()%255);
	int blue = (rand()%255);

	int fall = rand()%2;
	bool falls = false;
	int speed = rand()%(9)+1;

	if(fall == 0)
		falls = true;

	Square* new_square = new Square();

	new_square->x = (float)x;
	new_square->y = (float)y;

	new_square->size=height/50.0f;

	// I find it interesting that you cast red, green, blue to uint8_t here, but they are floats in your .h file.
	// You should probably make sure you keep your variables constant type instead of casting to uint8_t, then to float, then int, and back to uint8_t.
	new_square->red = (uint8_t)red;
	new_square->green = (uint8_t)green;
	new_square->blue = (uint8_t)blue;

	new_square->falls = falls;
	new_square->speed = speed;

	insertAfter(new_square, list->prev);
}

void Heinrich_HW02App::update()
{
	Square* cur = list;

	if(cur != NULL){
		do{
			cur->update();
			cur = cur->next;
		}while(cur != list);
	}
}

void Heinrich_HW02App::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	Square* cur = list;

	if(cur != NULL){
		do{
			cur->draw();
			cur = cur->next;
		}while(cur != list);
	}
}


CINDER_APP_BASIC( Heinrich_HW02App, RendererGl )
