//
// Created by Андрей on 15.05.2023.
//

#ifndef GAME_2023_1_ECHPOCHMAKI_ECS_SYSTEMS_INC_CAMERASYSTEM_H_
#define GAME_2023_1_ECHPOCHMAKI_ECS_SYSTEMS_INC_CAMERASYSTEM_H_

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "../../inc/ECS.h"
#include "PositionComponent.h"
#include "PlayerSystem.h"

const int defaultCameraDelta = 50;

const int CameraSystemID = 5;
class  CameraSystem : public BaseSystem
{
 public:

	virtual void update(EntityManager* manager)
	{
		std::vector<Entity*> entities;
		manager->selectEntites<PlayerComponent,PositionComponent>(entities);
		for (Entity* e: entities)
		{
			auto position = e->getComponent<PositionComponent>().position;
			cameraView.setCenter(position.x + defaultCameraDelta,position.y + defaultCameraDelta);
		}
		window->setView(cameraView);
	}

	virtual bool added()
	{
		return true;
	}

	void setRenderWindow(RenderWindow *windowSrc) // We need to always set a rendew window
	{
		window = windowSrc;
		cameraView.reset(FloatRect(window->getViewport(window->getView())));
	}

	virtual int getSystemID() override
	{
		return CameraSystemID;
	}

	~CameraSystem() override = default;

 private:
	static int ID;
	View cameraView;
	RenderWindow *window;
};


#endif //GAME_2023_1_ECHPOCHMAKI_ECS_SYSTEMS_INC_CAMERASYSTEM_H_
