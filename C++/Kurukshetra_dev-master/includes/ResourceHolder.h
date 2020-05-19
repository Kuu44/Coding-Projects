//
// Created by maverick on 16/2/19.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace Sounds
{
	enum ID {gunShot, soundNumber};
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
    Resource* resources;
public:
    ResourceHolder(Identifier id);
    void load(Identifier id, const char* filename, sf::IntRect area);
    void load(Identifier id, const char* filename);
    Resource& get(Identifier id);
    ~ResourceHolder();
};




