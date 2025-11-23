//
// Created by soberga on 22.11.2025.
//

#ifndef GALDER_GAME_JAM_2025_PROJECT_DIALOG_H
#define GALDER_GAME_JAM_2025_PROJECT_DIALOG_H

#include "Player.h"
#include "raylib-cpp.hpp"
#include "../../gamedev-base/GameDevBase.h"
#include "../managers/DialogManager.h"
namespace ggj
{
    class World;

    class Dialog : public IGameObject<raylib::Vector2>
    {
        public:
            Dialog(IMapper &mapper, ggj::ITextureManager<TextureName, raylib::Texture> &textures, IInputManager<KeyboardKey> &inputManager) : m_mapper {mapper}, m_textures {textures}, m_inputManager {inputManager}
            {
                m_isVisible = true;
                m_dialogManager.addDialog(DialogItem{"initialGreeting",
                    "Hello Traveller!\n"
                    "Welcome to the world of Galdaria.\n"
                  "Your first task is to purge these lands of every creature in these woods!\n"
                  "I am a bit too old to run around and kill, but I have scouted out the area for you.\n"
                  "Currently, these pesky creatures are running around. Happy little bastards...\n"
                  "Kill them for me, and I will grant you access to my torture chamber!\n"
                  "When the deed is done, you will find a portal in a cave to the north.\n"
                  "Are you up for the task?",
                    {
                        DialogChoice{"Yes", "initialGreetingYes"},
                        DialogChoice{"No", "initialGreetingNo"},
                        DialogChoice{"Maybe", "initialGreetingMaybe"},
                    }
                });

                m_dialogManager.addDialog(DialogItem{"initialGreetingYes",
                    "Excellent choice!\n"
                    "I promise you won't regret it!\n"
                    "Talk to you later.",{}});

                m_dialogManager.addDialog(DialogItem{
                    "initialGreetingNo", "Uhm ok...\n"
                    "Listen. Here is the issue.\n"
                    "You can dwell on this as long as you want.\n"
                    "But as long as these creatures are still alive you will not be able to progress.\n"
                    "Up to you hippie! Peace & Love!\n"
                    "So will you help me?",
                    {
                        DialogChoice{"Yes", "initialGreetingYes"},
                    }
                });

                m_dialogManager.addDialog(DialogItem{"initialGreetingMaybe",
                    "Maybe!!??\n"
                    "How am I supposed to respond to that??\n"
                    "At least have the decency to make up a choice!\n"
                    "I presume you are capable of that! So spit it out.\n"
                    "Yes or No?",
                    {
                        DialogChoice{"Yes", "initialGreetingYes"},
                        DialogChoice{"No", "initialGreetingNo"},
                    }
                });
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
        void handleInputs(float timeDelta);
        void DrawBox(raylib::Vector2 offset, int width, int height) const;
        void drawDialogBox(raylib::Vector2 offset, int width, int height, const DialogItem &item) const;
        IMapper &m_mapper;
        ITextureManager<TextureName, raylib::Texture> &m_textures;
        IInputManager<KeyboardKey> &m_inputManager;
        raylib::Texture *m_dialogTexture;

        DialogManager m_dialogManager {};
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

        raylib::Vector2 m_dialogOffset{};
        raylib::Rectangle m_boxTopLeftRect {TILE_UNIT * 0, TILE_UNIT * 8, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxTopMiddleRect {TILE_UNIT * 2, TILE_UNIT * 8, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxTopRightRect {TILE_UNIT * 4, TILE_UNIT * 8, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxMiddleLeftRect {TILE_UNIT * 0, TILE_UNIT * 10, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxMiddleMiddleRect {TILE_UNIT * 2, TILE_UNIT * 10, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxMiddleRightRect {TILE_UNIT * 4, TILE_UNIT * 10, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxBottomLeftRect {TILE_UNIT * 0, TILE_UNIT * 12, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxBottomMiddleRect {TILE_UNIT * 2, TILE_UNIT * 12, TILE_UNIT * 2, TILE_UNIT * 2};
        raylib::Rectangle m_boxBottomRightRect {TILE_UNIT * 4, TILE_UNIT * 12, TILE_UNIT * 2, TILE_UNIT * 2};

        raylib::Rectangle m_dialogTabButtonRect {TILE_UNIT * 0, TILE_UNIT * 15, TILE_UNIT * 2, TILE_UNIT * 1};
        raylib::Rectangle m_dialogSpaceButtonRect {TILE_UNIT * 4, TILE_UNIT * 15, TILE_UNIT * 3, TILE_UNIT * 1};
        raylib::Rectangle m_dialogArrowRect {TILE_UNIT * 2, TILE_UNIT * 15, TILE_UNIT * 2, TILE_UNIT * 1};
        std::string m_dialogId{};
        bool m_draw {};
        int m_currentChoice {0};
    };
}

#endif //GALDER_GAME_JAM_2025_PROJECT_DIALOG_H