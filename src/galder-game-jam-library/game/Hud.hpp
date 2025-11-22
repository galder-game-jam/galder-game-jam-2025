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
                m_playerPositionOffset = raylib::Vector2{ m_position.x + 570, m_position.y + 570 };

                m_hudTexture = m_textures.get(TextureName::HudRpgSubset);
            }

            void setPlayer(Player *player)
            {
                m_currentPlayer = player;
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
                m_coins = m_currentPlayer->getScore();
                m_playerPosition = raylib::Vector2 {m_currentPlayer->getPosition() };
            }

            void draw() override
            {
                if (!m_isVisible) return;

                drawPlayerPortrait();
                drawCoinBar(m_coinOffset);
                drawPlayerPositionBar(m_playerPositionOffset);
            }

        private:
            void drawPlayerPortrait() const
            {
                m_hudTexture->Draw(m_portraitRect, m_portraitOffset);

                for (int i = 0; i < m_health; ++i)
                {
                    m_hudTexture->Draw(m_lifeRect, raylib::Vector2{m_portraitRect.width  + m_lifeRect.width * i + m_portraitOffset.x,6 + m_portraitOffset.y});
                }
                m_hudTexture->Draw(m_lifeEnd, raylib::Vector2{m_portraitRect.width + m_lifeRect.width * m_health + m_portraitOffset.x,2 + m_portraitOffset.y});
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

            raylib::Vector2 m_size {};
            raylib::Vector2 m_origin {};
            raylib::Color m_color {};
            UserData m_userData {};
            raylib::Vector2 m_velocity {};


            const float TILE_UNIT = 16.0f;
            const int FONT_SIZE = 15;
            const raylib::Color HUD_FONT_COLOR = BLACK;

            float m_health{};
            raylib::Vector2 m_portraitOffset{};
            raylib::Rectangle m_portraitRect {TILE_UNIT * 0, TILE_UNIT * 0, TILE_UNIT * 5 + 4, TILE_UNIT * 4};
            raylib::Rectangle m_lifeRect = {TILE_UNIT * 9, TILE_UNIT * 0, 8, 16};
            raylib::Rectangle m_lifeEnd = {TILE_UNIT * 6, TILE_UNIT * 0, TILE_UNIT * 2, TILE_UNIT * 2};

            int m_coins{};
            raylib::Vector2 m_coinOffset{};
            raylib::Rectangle m_coinRect {TILE_UNIT * 7, TILE_UNIT * 6, TILE_UNIT * 1, TILE_UNIT * 1};

            raylib::Vector2 m_playerPosition{};
            raylib::Vector2 m_playerPositionOffset{};

            raylib::Rectangle m_barRectLeft {TILE_UNIT * 0, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
            raylib::Rectangle m_barRectMiddle {TILE_UNIT * 2, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
            raylib::Rectangle m_barRectRight {TILE_UNIT * 4, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
    };

}
#endif //GALDER_GAME_JAM_2025_PROJECT_HUD_HPP