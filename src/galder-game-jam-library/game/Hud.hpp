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
            Hud(IMapper &mapper, ggj::ITextureManager<TextureName, raylib::Texture> &textures) : m_mapper {mapper}, m_textures {textures}
            {
                m_isVisible = true;
            }

            void initialize()
            {
                m_color = raylib::Color::White();
                m_size = raylib::Vector2{200, 20};        // Example health bar size
                m_origin = raylib::Vector2{20, 20};       // HUD position
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
                m_health = GetRandomValue(1, 5);
            }
            void draw() override
            {
                if (!m_isVisible) return;


                DrawRectangle(100, 515, 400, 40, WHITE);
                DrawText(TextFormat("Se på meg nå! Du har %i i liv", m_health), 110, 525, 20, RED);
            }

        private:
            IMapper &m_mapper;
            ggj::ITextureManager<TextureName, raylib::Texture> &m_textures;

            raylib::Vector2 m_size {};
            raylib::Vector2 m_origin {};
            raylib::Color m_color {};
            UserData m_userData {};
            raylib::Vector2 m_velocity {};

            int m_health = 0;
    };

}
#endif //GALDER_GAME_JAM_2025_PROJECT_HUD_HPP