//
// Created by Kuba on 02.01.2018.
//

#include "CuboidContainer.h"
#include <iostream>

CuboidContainer::CuboidContainer()
:   sizes({0.0, 0.0, 0.0})
{}

std::istream& operator>>(std::istream &str, CuboidContainer &data) {
    for(int i = 0; i < data.sizes.size(); ++i) {
        str >> data.sizes[i];
    }
    return str;
}

std::ostream& operator<<(std::ostream &str, CuboidContainer &data) {
    std::cout<<"Bin's sizes:"<<std::endl;
    std::cout<<"Length: "<<data.sizes[0]<<std::endl;
    std::cout<<"Height: "<<data.sizes[1]<<std::endl;
    std::cout<<"Depth:  "<<data.sizes[2]<<std::endl;
    return str;
}

std::vector<double> &CuboidContainer::getSizes() {
    return sizes;
}
