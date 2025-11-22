//
// Created by soberga on 21.11.2025.
//

#ifndef GALDER_GAME_JAM_2025_PROJECT_HUD_HPP
#define GALDER_GAME_JAM_2025_PROJECT_HUD_HPP

#include "raylib-cpp.hpp"
#include "../../gamedev-base/GameDevBase.h"

namespace ggj
{
    class Hud : public IGameObject<raylib::Vector2>
    {
        public:
            Hud(IMapper &mapper, ggj::ITextureManager<TextureName, raylib::Texture> &textures, IInputManager<KeyboardKey> &inputManager) : m_mapper {mapper}, m_textures {textures}, m_inputManager {inputManager}
            {
                m_isVisible = true;
            }

            void initialize()
            {
                m_color = raylib::Color::White();
                m_size = raylib::Vector2{200, 20};
                m_origin = raylib::Vector2{20, 20};
                m_position = raylib::Vector2{ 5, 0 };

                m_portraitOffset = raylib::Vector2{ m_position.x + 0, m_position.y + 50 };
                m_coinOffset = raylib::Vector2{ m_position.x + 0, m_position.y + 120 };
                m_killsOffset = raylib::Vector2{ m_position.x + 0, m_position.y + 152 };
                m_playerPositionOffset = raylib::Vector2{ m_position.x + 570, m_position.y + 570 };
                m_questLogOffset = raylib::Vector2{ m_position.x + 0, m_position.y + 400 };

                m_hudTexture = m_textures.get(TextureName::HudRpgSubset);
            }

            void setPlayer(Player *player)
            {
                m_currentPlayer = player;
            }

            void setWorld(World *world)
            {
                m_currentWorld = world;
            }
            void setVisible(bool isVisible)
            {
                m_isVisible = isVisible;
            }

            void rotate(float degrees) override {}
            void scale(float scale) override {}
            void move(const raylib::Vector2 &toMove) override {}
            void destroy() override
            {
                IGameObject::destroy();
            }
            void update(float timeDelta) override
            {
                if(m_inputManager.keyPressed(KeyboardKey::F8))
                {
                    setVisible(!m_isVisible);
                }

                m_health = static_cast<float>(m_currentPlayer->getLives());
                m_mana = 2; // Implement mana and then: static_cast<float>(m_currentPlayer->getMana());
                m_energy = 3; // Implement energy and then: static_cast<float>(m_currentPlayer->getEnergy());
                m_coins = m_currentPlayer->getScore();
                m_kills = m_currentPlayer->getUserData()->enemiesKilled;
                m_playerPosition = raylib::Vector2 {m_currentPlayer->getPosition() };
            }

            void draw() override
            {
                if (!m_isVisible) return;

                drawPlayerPortrait();
                drawCoinBar(m_coinOffset);
                drawPlayerPositionBar(m_playerPositionOffset);
                drawKillsBar(m_killsOffset);

                drawQuestLog(m_questLogOffset, 3,1);

            }

        private:

            void drawQuestLog(raylib::Vector2 offset, int width, int height) const
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

                        m_hudTexture->Draw(src, pos);
                    }
                }

                int enemies = 5;//m_currentWorld->getEnemies();
                int enemiesLeft = 0;//m_currentWorld->getNumberOfEnemiesLeft();

                int enemiesKilled = enemies - enemiesLeft;
                bool isOpen = enemiesKilled == enemies;

                DrawText(TextFormat("Quest Log"), offset.x + TILE_UNIT, offset.y + 7, FONT_SIZE, YELLOW);
                DrawText(TextFormat("Kill enemies %i/%i", enemiesKilled, enemies), offset.x + TILE_UNIT, offset.y + 27, FONT_SIZE, BLACK);
                DrawText(TextFormat("Portal is %s", isOpen ? "open": "closed"), offset.x + TILE_UNIT, offset.y + 67, FONT_SIZE, isOpen? GREEN : RED);
            }

            void DrawResourceBar(const float counter, raylib::Rectangle rectResource, raylib::Rectangle rectEnd, float barNo) const
            {
                float barTypeOffset = 20 * barNo;
                for (int i = 0; i < counter; ++i)
                {
                    m_hudTexture->Draw(rectResource, raylib::Vector2{m_portraitRect.width  + rectResource.width * i + m_portraitOffset.x,6 + barTypeOffset + m_portraitOffset.y});
                }
                m_hudTexture->Draw(rectEnd, raylib::Vector2{m_portraitRect.width + rectResource.width * counter + m_portraitOffset.x,2 + barTypeOffset + m_portraitOffset.y});
            }

            void drawPlayerPortrait() const
            {
                m_hudTexture->Draw(m_portraitRect, m_portraitOffset);

                DrawResourceBar(m_health, m_lifeRect, m_lifeEnd, 0);
                DrawResourceBar(m_mana, m_manaRect, m_manaEnd, 1);
                DrawResourceBar(m_energy, m_energyRect, m_energyEnd, 2);
            }

            void drawBar(raylib::Vector2 offset, int middleParts) const
            {
                m_hudTexture->Draw(m_barRectLeft, offset);
                for (int i = 0; i < middleParts; ++i)
                {
                    m_hudTexture->Draw(m_barRectMiddle, offset + raylib::Vector2{TILE_UNIT * 2 + TILE_UNIT * 2 * i,0});
                }

                m_hudTexture->Draw(m_barRectRight, offset + raylib::Vector2{TILE_UNIT * 2 + TILE_UNIT * 2 * middleParts,0});
            }

            void drawCoinBar(raylib::Vector2 offset) const
            {
                drawBar(offset, 1);
                m_hudTexture->Draw(m_coinRect, offset + raylib::Vector2{TILE_UNIT * 1,4});
                DrawText(TextFormat("%i", static_cast<int>(m_coins)), offset.x + TILE_UNIT * 3, offset.y + 5, FONT_SIZE, BLACK);
            }

            void drawKillsBar(raylib::Vector2 offset) const
            {
                drawBar(offset, 1);
                DrawText(TextFormat("Kills: %i", static_cast<int>(m_kills)), offset.x + TILE_UNIT * 1, offset.y + 5, FONT_SIZE, BLACK);
            }

            void drawPlayerPositionBar(raylib::Vector2 offset) const
            {
                drawBar(offset, 5);
                raylib::Text text {};
                text.text = TextFormat("Player position: (%i, %i)", static_cast<int>(m_playerPosition.x), static_cast<int>(m_playerPosition.y));
                text.SetFontSize(FONT_SIZE);
                text.color = HUD_FONT_COLOR;

                //text.Draw(offset.x + TILE_UNIT * 1, offset.y + 5);

                DrawText(TextFormat("Player position: (%i, %i)", static_cast<int>(m_playerPosition.x), static_cast<int>(m_playerPosition.y)), offset.x + TILE_UNIT * 1, offset.y + 5, FONT_SIZE, BLACK);
            }
            IMapper &m_mapper;
            ITextureManager<TextureName, raylib::Texture> &m_textures;
            IInputManager<KeyboardKey> &m_inputManager;
            raylib::Texture *m_hudTexture;

            Player *m_currentPlayer = nullptr;
            World *m_currentWorld = nullptr;

            raylib::Vector2 m_size {};
            raylib::Vector2 m_origin {};
            raylib::Color m_color {};
            UserData m_userData {};
            raylib::Vector2 m_velocity {};


            const float TILE_UNIT = 16.0f;
            const int FONT_SIZE = 15;
            const raylib::Color HUD_FONT_COLOR = BLACK;
            const int HUD_ALPHA = 180;

            float m_health{};
            float m_mana{};
            float m_energy{};

            raylib::Vector2 m_portraitOffset{};

            raylib::Rectangle m_portraitRect {TILE_UNIT * 0, TILE_UNIT * 0, TILE_UNIT * 5 + 4, TILE_UNIT * 4};

            raylib::Rectangle m_lifeRect = {TILE_UNIT * 9, TILE_UNIT * 0, 8, 16};
            raylib::Rectangle m_manaRect = {TILE_UNIT * 9, TILE_UNIT * 1, 8, 16};
            raylib::Rectangle m_energyRect = {TILE_UNIT * 9, TILE_UNIT * 2, 8, 16};

            raylib::Rectangle m_lifeEnd = {TILE_UNIT * 6, TILE_UNIT * 0, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_manaEnd = {TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_energyEnd = {TILE_UNIT * 6, TILE_UNIT * 4, TILE_UNIT * 2, TILE_UNIT * 2};

            int m_coins{};
            raylib::Vector2 m_coinOffset{};
            raylib::Rectangle m_coinRect {TILE_UNIT * 7, TILE_UNIT * 6, TILE_UNIT * 1, TILE_UNIT * 1};

            int m_kills {};
            raylib::Vector2 m_killsOffset{};

            raylib::Vector2 m_playerPosition{};
            raylib::Vector2 m_playerPositionOffset{};

            raylib::Rectangle m_barRectLeft {TILE_UNIT * 0, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
            raylib::Rectangle m_barRectMiddle {TILE_UNIT * 2, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
            raylib::Rectangle m_barRectRight {TILE_UNIT * 4, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};

            raylib::Vector2 m_questLogOffset{};
            raylib::Rectangle m_boxTopLeftRect {TILE_UNIT * 0, TILE_UNIT * 8, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxTopMiddleRect {TILE_UNIT * 2, TILE_UNIT * 8, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxTopRightRect {TILE_UNIT * 4, TILE_UNIT * 8, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxMiddleLeftRect {TILE_UNIT * 0, TILE_UNIT * 10, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxMiddleMiddleRect {TILE_UNIT * 2, TILE_UNIT * 10, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxMiddleRightRect {TILE_UNIT * 4, TILE_UNIT * 10, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxBottomLeftRect {TILE_UNIT * 0, TILE_UNIT * 12, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxBottomMiddleRect {TILE_UNIT * 2, TILE_UNIT * 12, TILE_UNIT * 2, TILE_UNIT * 2};
            raylib::Rectangle m_boxBottomRightRect {TILE_UNIT * 4, TILE_UNIT * 12, TILE_UNIT * 2, TILE_UNIT * 2};
    };

}
#endif //GALDER_GAME_JAM_2025_PROJECT_HUD_HPP