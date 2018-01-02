//
// Created by Kuba on 02.01.2018.
//

#ifndef AAL_OPENGL_VISUALIZATION_FILEPARSER_H
#define AAL_OPENGL_VISUALIZATION_FILEPARSER_H


#include "CuboidContainer.h"
#include "Cuboid.h"

class FileParser {
public:
    static std::pair<CuboidContainer*, std::vector<std::vector<Cuboid* > >* > parseFile();
};


#endif //AAL_OPENGL_VISUALIZATION_FILEPARSER_H
