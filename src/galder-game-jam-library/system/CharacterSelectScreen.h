//
// Created by robin on 23.11.2025.
//

#ifndef GALDER_GAME_JAM_2025_PROJECT_CHARACTERSELECTSCREEN_H
#define GALDER_GAME_JAM_2025_PROJECT_CHARACTERSELECTSCREEN_H

#include "raylib-cpp.hpp"
#include "../../gamedev-base/GameDevBase.h"
#include "../GalderGameJamLibrary.h"

namespace ggj
{
    class CharacterSelectScreen : public IGameObject<raylib::Vector2>
    {
        public:
            CharacterSelectScreen() = default;
            void initialize();
            void setFont(raylib::Font* font);
            void setPlayer(Player* player);
            void setWorld(World* world);
            void setVisible(bool isVisible);
            void rotate(float degrees) override;
            void scale(float scale) override;
            void move(const raylib::Vector2& toMove) override;
            void destroy() override;
            void update(float timeDelta) override;
            void draw() override;

        private:
            void lol();
    };
} // namespace ggj

#endif // GALDER_GAME_JAM_2025_PROJECT_CHARACTERSELECTSCREEN_H
