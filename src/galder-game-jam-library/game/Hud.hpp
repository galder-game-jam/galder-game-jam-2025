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
            }
            void draw() override
            {
                if (!m_isVisible) return;

                m_hudTexture->Draw(m_portraitRect, m_portraitOffset);

                for (int i = 0; i < m_health; ++i)
                {
                    m_hudTexture->Draw(m_lifeRect, raylib::Vector2{m_portraitRect.width  + m_lifeRect.width * i + m_portraitOffset.x,6 + m_portraitOffset.y});
                }
                m_hudTexture->Draw(m_lifeEnd, raylib::Vector2{m_portraitRect.width + m_lifeRect.width * m_health + m_portraitOffset.x,2 + m_portraitOffset.y});

                m_hudTexture->Draw(m_coinRectLeft, m_coinOffset);
                m_hudTexture->Draw(m_coinRectMiddle, m_coinOffset + raylib::Vector2{TILE_UNIT * 2,0});
                m_hudTexture->Draw(m_coinRectRight, m_coinOffset + raylib::Vector2{TILE_UNIT * 4,0});
                m_hudTexture->Draw(m_coinRect, m_coinOffset + raylib::Vector2{TILE_UNIT * 1,4});
                DrawText(TextFormat("%i", static_cast<int>(m_coins)), m_coinOffset.x + TILE_UNIT * 3, m_coinOffset.y + 5, 15, BLACK);
            }

        private:
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

            float m_health{};
            raylib::Vector2 m_portraitOffset{};
            raylib::Rectangle m_portraitRect {TILE_UNIT * 0, TILE_UNIT * 0, TILE_UNIT * 5 + 4, TILE_UNIT * 4};
            raylib::Rectangle m_lifeRect = {TILE_UNIT * 9, TILE_UNIT * 0, 8, 16};
            raylib::Rectangle m_lifeEnd = {TILE_UNIT * 6, TILE_UNIT * 0, TILE_UNIT * 2, TILE_UNIT * 2};

            int m_coins{};
            raylib::Vector2 m_coinOffset{};
            raylib::Rectangle m_coinRect {TILE_UNIT * 7, TILE_UNIT * 6, TILE_UNIT * 1, TILE_UNIT * 1};
            raylib::Rectangle m_coinRectLeft {TILE_UNIT * 0, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
            raylib::Rectangle m_coinRectMiddle {TILE_UNIT * 2, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
            raylib::Rectangle m_coinRectRight {TILE_UNIT * 4, TILE_UNIT * 6, TILE_UNIT * 2, TILE_UNIT * 1 + 10};
    };

}
#endif //GALDER_GAME_JAM_2025_PROJECT_HUD_HPP