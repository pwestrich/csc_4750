
#ifndef PICTURE_H
#define PICTURE_H

#include <vector>

class BasicObject;

class Picture {

private:

	std::vector<BasicObject*> objects;

	//singletons everywhere
	Picture();

public:

	static Picture *getPicture();
	~Picture();

	//renders the picture
	void render();

};

#endif
