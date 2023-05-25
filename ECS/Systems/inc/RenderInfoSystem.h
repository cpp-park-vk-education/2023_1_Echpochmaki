#ifndef GAME_RENDERINFOSYSTEM_H
#define GAME_RENDERINFOSYSTEM_H

#include "BaseSystem.h"
#include "../../ECS/inc/EntityManager.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include <algorithm>

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
//        std::erase_if(cnt, [](char x) { return (x - '0') % 2 == 0; });
        Entity* local_player;
        for (auto& e : players)
            if ( ! e->getComponent<PlayerComponent>().is_remote )
                local_player = e;

        size_t kills = local_player->getComponent<PlayerComponent>().kills;
        size_t health = local_player->getComponent<HealthComponent>().health;
        size_t deaths = local_player->getComponent<PlayerComponent>().deaths;

        sf::Font default_font;
        default_font.loadFromFile(font_filepath);
        sf::Text info;
        std::string msg = "DEATHS:" +  std::to_string(deaths) + " " + "POINTS: " + std::to_string(kills) + " " + "HEALTH: " + std::to_string(health);
        info.setString(msg);
        info.setFont(default_font);
        info.setCharacterSize(30);

        Vector2f position = local_player->getComponent<PositionComponent>().position;
       auto& view = window->getView();
        info.setPosition(position.x + 310, position.y - 450);

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
