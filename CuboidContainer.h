//
// Created by Kuba on 02.01.2018.
//

#ifndef AAL_OPENGL_VISUALIZATION_CUBOIDCONTAINER_H
#define AAL_OPENGL_VISUALIZATION_CUBOIDCONTAINER_H


#include <vector>
#include <istream>

class CuboidContainer {
public:
    CuboidContainer();
    ~CuboidContainer() = delete;
    friend std::istream& operator>>(std::istream& str, CuboidContainer& data);
    friend std::ostream& operator<<(std::ostream &str, CuboidContainer& data);
    std::vector<double>& getSizes();
private:
    std::vector<double> sizes;
};


#endif //AAL_OPENGL_VISUALIZATION_CUBOIDCONTAINER_H
