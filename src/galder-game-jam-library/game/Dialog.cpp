//
// Created by soberga on 22.11.2025.
//

#include "Dialog.h"
#include "../GalderGameJamLibrary.h"

void ggj::Dialog::initialize()
{
    m_color = raylib::Color::White();
    m_size = raylib::Vector2{200, 20};
    m_origin = raylib::Vector2{20, 20};
    m_position = raylib::Vector2{ 5, 0 };

    m_hudTexture = m_textures.get(TextureName::HudRpgSubset);
}

void ggj::Dialog::setFont(raylib::Font *font)
{
    m_font = font;
}

void ggj::Dialog::setPlayer(Player *player)
{
    m_currentPlayer = player;
}

void ggj::Dialog::setWorld(World *world)
{
    m_currentWorld = world;
    int life = m_currentWorld->getEnemies();
}
void ggj::Dialog::setVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

void ggj::Dialog::rotate(float degrees)
{
}

void ggj::Dialog::scale(float scale)
{
}

void ggj::Dialog::move(const raylib::Vector2& toMove)
{
}

void ggj::Dialog::update(float timeDelta)
{
}

void ggj::Dialog::draw()
{
}
