//
// Created by Kuba on 02.01.2018.
//
#ifndef SCENA_H
#define SCENA_H

#include <vector>
#include "CuboidContainer.h"
#include "Cuboid.h"

#define BOX_ALPHA 0.6
#define GLOBAL_SCALE 0.2
#define ZOOM_SPEED 1.0
#define VIEWING_DISTANCE_MIN  10.0

typedef struct Size
{
	int x;
	int y;
	int z;
} Size;

class Scene
{
public:
	static void start(int argc, char** argv, CuboidContainer* otherCuboidContainer, std::vector<std::vector<Cuboid*> >* emplacedCuboids);
	static void close();
	static float* getRandomColor();
protected:
private:
};

#endif // SCENA_H
