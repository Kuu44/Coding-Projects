//
// Created by maverick on 16/2/19.
//

#include <iostream>

#include "ResourceHolder.h"

template<typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder(Identifier id) {
    resources = new Resource[id];
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const char *filename, sf::IntRect area){
    if (!resources[id].loadFromFile(filename, area))
    {
        std::cerr<< "Couldn't load resource from "<<filename<<std::endl;
        exit(1);
    }
}
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const char *filename) {
    if (!resources[id].loadFromFile(filename))
    {
        std::cerr<< "Couldn't load resource from "<<filename<<std::endl;
        exit(1);
    }
}
template<typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) {
    return resources[id];
}
template<typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder() {
    delete[] resources;
}

