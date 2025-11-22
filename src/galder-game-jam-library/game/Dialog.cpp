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

    m_dialogOffset = raylib::Vector2{m_position.x + 200, m_position.y + 380};
    m_dialogTexture = m_textures.get(TextureName::HudRpgSubset);
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
    drawDialogBox(m_dialogOffset, 15, 3);
}

void ggj::Dialog::drawDialogBox(raylib::Vector2 offset, int width, int height) const
{
    float grid = TILE_UNIT * 2;
    raylib::Vector2 shrinkflation = raylib::Vector2(4, 4);

    raylib::Rectangle backdrop = raylib::Rectangle(offset + shrinkflation, raylib::Vector2((width+2) * grid, (height+2) * grid) - shrinkflation * 2);
    DrawRectangle(backdrop.x, backdrop.y, backdrop.width, backdrop.height, raylib::Color(143, 86, 59, HUD_ALPHA));

    raylib::Rectangle tiles[3][3] =
    {
        { m_boxTopLeftRect,    m_boxTopMiddleRect,    m_boxTopRightRect    },
        { m_boxMiddleLeftRect, m_boxMiddleMiddleRect, m_boxMiddleRightRect },
        { m_boxBottomLeftRect, m_boxBottomMiddleRect, m_boxBottomRightRect }
    };

    for (int y = 0; y < height + 2; ++y)
    {
        for (int x = 0; x < width + 2; ++x)
        {
            int tx = (x == 0) ? 0 : (x == width + 1 ? 2 : 1);   // left/mid/right tile
            int ty = (y == 0) ? 0 : (y == height + 1 ? 2 : 1);  // top/mid/bottom tile

            const raylib::Rectangle& src = tiles[ty][tx];
            raylib::Vector2 pos = offset + raylib::Vector2{grid * x, grid * y};

            m_dialogTexture->Draw(src, pos);
        }
    }

    std::string name = "Galder";//m_currentWorld->getName();
    int enemies = 5;//m_currentWorld->getEnemies();
    int enemiesLeft = 0;//m_currentWorld->getNumberOfEnemiesLeft();

    int enemiesKilled = enemies - enemiesLeft;
    bool isOpen = enemiesKilled == enemies;

    m_font->DrawText(TextFormat("Hello %s!", name.c_str()), raylib::Vector2{offset.x + TILE_UNIT, offset.y + 7}, FONT_SIZE, 0, YELLOW);
    m_font->DrawText(TextFormat("Welcome to the world of Galdaria."), raylib::Vector2{offset.x + TILE_UNIT, offset.y + 27}, FONT_SIZE, 0, BLACK);
    m_font->DrawText(TextFormat("Your first task is to purge these lands of every creature in these woods!"), raylib::Vector2{offset.x + TILE_UNIT, offset.y + 47}, FONT_SIZE, 0, BLACK);
    m_font->DrawText(TextFormat("I am a bit too old to run around and kill, but I have scouted out the area for you."), raylib::Vector2{offset.x + TILE_UNIT, offset.y + 67}, FONT_SIZE, 0, BLACK);
    m_font->DrawText(TextFormat("Currently, %i creatures are running around. Happy little bastards...", enemies), raylib::Vector2{offset.x + TILE_UNIT, offset.y + 87}, FONT_SIZE, 0, BLACK);
    m_font->DrawText(TextFormat("Kill them for me, and I will grant you access to my torture chamber!"), raylib::Vector2{offset.x + TILE_UNIT, offset.y + 107}, FONT_SIZE, 0, BLACK);
    m_font->DrawText(TextFormat("When the deed is done, you will find a portal in a cave to the north."), raylib::Vector2{offset.x + TILE_UNIT, offset.y + 127}, FONT_SIZE, 0, BLACK);
}
