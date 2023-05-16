#ifndef GAME_RENDERINFOSYSTEM_H
#define GAME_RENDERINFOSYSTEM_H

#include "BaseSystem.h"
#include "../../ECS/inc/EntityManager.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "PositionComponent.h"

const int RenderInfoSystemID = 32523501;
class  RenderInfoSystem : public BaseSystem
{
public:

    RenderInfoSystem(RenderWindow *windowSrc, std::string& filepath) : window(windowSrc), font_filepath(filepath) {}

    virtual void update(EntityManager* manager)
    {
        std::cout << "Render info started" << std::endl;
        std::vector<Entity*> players;
        manager->selectEntites<PlayerComponent>(players);

        size_t kills = players.front()->getComponent<PlayerComponent>().kills;
        size_t health = players.front()->getComponent<HealthComponent>().health;

        sf::Font default_font;
        default_font.loadFromFile(font_filepath);
        sf::Text info;
        std::string msg = "POINTS: " + std::to_string(kills) + " " + "HEALTH: " + std::to_string(health);
        info.setString(msg);
        info.setFont(default_font);
        info.setCharacterSize(30);

        Vector2f position = players.front()->getComponent<PositionComponent>().position;
        info.setPosition(position.x + 110, position.y - 180);

        window->draw(info);
    }

    virtual bool added()
    {
        return true;
    }


    virtual int getSystemID() override
    {
        return RenderInfoSystemID;
    }

    ~RenderInfoSystem() override = default;

private:
    static int ID;
    RenderWindow *window;
    std::string font_filepath;
};


#endif //GAME_RENDERINFOSYSTEM_H
