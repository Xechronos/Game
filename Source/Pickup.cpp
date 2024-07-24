#include "Pickup.h"
#include "Player.h"

void Pickup::OnCollision(Actor* actor)
{
	Player* player = dynamic_cast<Player*>(actor);
	if (player) {
		player->AddBulletCount(1);
		m_destroyed = true;
	}
}
