#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>
#include <string>

class Cubemap
{
public:
    unsigned int ID;

    Cubemap(const std::vector<std::string>& faces);
    void Bind() const;

private:
    void LoadCubemap(const std::vector<std::string>& faces);
};

#endif
