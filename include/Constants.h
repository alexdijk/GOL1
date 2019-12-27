#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

constexpr int SCREEN_W = 800;
constexpr int SCREEN_H = 600;
constexpr int TOTSIZE = SCREEN_W * SCREEN_H;

static const sf::Time UPDATE_STEP = sf::seconds(1.f / 60.f);