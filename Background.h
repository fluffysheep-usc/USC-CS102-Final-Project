#ifndef BACKGROUND
#define BACKGROUND
#include <QGraphicsPixmapItem>
#include "GameObject.h"

#include <iostream>

using namespace std;

class Background : public GameObject {
	
public:
	Background(int nx, int ny, int nz, QPixmap* pixmap);
	~Background();
	void Update();
	
public slots:

private:
};

#endif 
