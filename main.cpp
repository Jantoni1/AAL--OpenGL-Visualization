#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include "Scene.h"
#include "FileParser.h"

/**
 * Funkcja główna.
 */
int main(int argc, char** argv)
{
    auto parsedData = FileParser::parseFile();
	Scene::start(argc, argv, parsedData.first, parsedData.second);
	Scene::close();
	return 0;
}
