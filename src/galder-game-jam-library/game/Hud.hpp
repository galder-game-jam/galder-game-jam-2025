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

                m_hudTexture = m_textures.get(TextureName::HudRpg);
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

                m_health = GetRandomValue(1, 5);
            }
            void draw() override
            {
                if (!m_isVisible) return;

                raylib::Vector2 offset { 20, 50 };

                raylib::Rectangle rect = {448.f, 180.f, 83, 63};
                m_hudTexture->Draw(rect, raylib::Vector2{0 + offset.x,0 + offset.y});

                auto numberOfLives = m_currentPlayer->getLives();

                int lifeSize = 9;
                for (int i = 0; i < numberOfLives; ++i)
                {
                    raylib::Rectangle rect2 = {592.f, 186.f, 9, 12};
                    m_hudTexture->Draw(rect2, raylib::Vector2{83 + 1 + lifeSize * i + offset.x,6 + offset.y});
                }

                raylib::Rectangle rect3 = {551.f, 182.f, 31, 19};
                m_hudTexture->Draw(rect3, raylib::Vector2{83 + 1 + lifeSize * numberOfLives + offset.x,2 + offset.y});

                DrawRectangle(100, 515, 400, 40, WHITE);
                DrawText(TextFormat("Se på meg nå! Du har %i i liv", m_health), 110, 525, 20, RED);
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

            int m_health = 0;
    };

}
#endif //GALDER_GAME_JAM_2025_PROJECT_HUD_HPP