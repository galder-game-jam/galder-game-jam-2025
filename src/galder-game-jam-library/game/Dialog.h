//
// Created by soberga on 22.11.2025.
//

#ifndef GALDER_GAME_JAM_2025_PROJECT_DIALOG_H
#define GALDER_GAME_JAM_2025_PROJECT_DIALOG_H

#include "raylib-cpp.hpp"
#include "../../gamedev-base/GameDevBase.h"

namespace ggj
{
    class Dialog : public IGameObject<raylib::Vector2>
    {
        public:
            void rotate(float degrees) override;
            void scale(float scale) override;
            void move(const raylib::Vector2& toMove) override;
            void update(float timeDelta) override;
            void draw() override;
        private:

    };
}

#endif //GALDER_GAME_JAM_2025_PROJECT_DIALOG_H