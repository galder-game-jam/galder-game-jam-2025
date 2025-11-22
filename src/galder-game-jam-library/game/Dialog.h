//
// Created by soberga on 22.11.2025.
//

#ifndef GALDER_GAME_JAM_2025_PROJECT_DIALOG_H
#define GALDER_GAME_JAM_2025_PROJECT_DIALOG_H

#include "Player.h"
#include "raylib-cpp.hpp"
#include "../../gamedev-base/GameDevBase.h"

namespace ggj
{
    class World;

    class Dialog : public IGameObject<raylib::Vector2>
    {
        public:
        Dialog(IMapper &mapper, ggj::ITextureManager<TextureName, raylib::Texture> &textures, IInputManager<KeyboardKey> &inputManager) : m_mapper {mapper}, m_textures {textures}, m_inputManager {inputManager}
        {
            m_isVisible = true;
        }
            void initialize();
            void setFont(raylib::Font* font);
            void setPlayer(Player* player);
            void setWorld(World* world);
            void setVisible(bool isVisible);
            void rotate(float degrees) override;

            void scale(float scale) override;
            void move(const raylib::Vector2& toMove) override;
            void update(float timeDelta) override;
            void draw() override;
        private:
        IMapper &m_mapper;
        ITextureManager<TextureName, raylib::Texture> &m_textures;
        IInputManager<KeyboardKey> &m_inputManager;
        raylib::Texture *m_hudTexture;

        raylib::Font *m_font = nullptr;

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
    };
}

#endif //GALDER_GAME_JAM_2025_PROJECT_DIALOG_H