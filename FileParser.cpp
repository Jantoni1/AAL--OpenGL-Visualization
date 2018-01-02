//
// Created by Kuba on 02.01.2018.
//

#include "FileParser.h"
#include <sstream>

std::pair<CuboidContainer*, std::vector<std::vector<Cuboid *> >* > FileParser::parseFile() {
    std::stringstream stringStream;
    std::string line;
    auto* cuboidContainer = new CuboidContainer();
    std::getline(std::cin, line);
    stringStream .str(line);
    stringStream >> *cuboidContainer;
    stringStream.clear();
    auto cuboids = new std::vector<std::vector<Cuboid *> >();
    for(int i = 0; i < 3; ++i) {
        cuboids->emplace_back(std::vector<Cuboid*>());
        while(!std::cin.eof()) {
            std::getline(std::cin, line);
            if(!line.empty()) {
                stringStream.str(line);
                auto* cuboid = new Cuboid();
                stringStream >> *cuboid;
                cuboids->back().emplace_back(cuboid);
                stringStream.clear();
            }
            else {
                if((*cuboids)[i].size() == 1 && (*cuboids)[i].back()->isEmpty()) {
                    for(auto cuboid : (*cuboids)[i]) {
                        delete cuboid;
                    }
                    (*cuboids)[i].clear();
                }
                break;
            }
        }
        if((*cuboids).back().size() == 1 && (*cuboids).back().back()->isEmpty()) {
            for(auto cuboid : (*cuboids).back()) {
                delete cuboid;
            }
            (*cuboids).back().clear();
        }
    }
    return std::make_pair(cuboidContainer, cuboids);
}
