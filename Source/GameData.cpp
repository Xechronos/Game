#include "GameData.h"
namespace GameData {
	const std::vector<Vector2>ShipPoints{
		{ 5, 0 },
		{-5,-5},
		{-3,-3},
		{-5,-2},
		{-4,0},
		{-8,-2},
		{-8,2},
		{-4,0},
		{-5,2},
		{-3,3},
		{-5,5},
		{5,0}
	};

	const std::vector<Vector2>EnemyPoints{
		{ 5, 0 },
		{-5,-5},
		{-4,0},
		{-8,-2},
		{-8,2},
		{-4,0},
		{-5,5},
		{5,0}
	};

	const std::vector<Vector2>BulletPoints{
		{ 5, 0 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 0 }
	};

	const std::vector<Vector2>PickupPoints{
		{ 5, 0 },
		{1,1},
		{0,5},
		{-1,1},
		{-5,0},
		{-1,-1},
		{0,-5},
		{1,-1},
		{5,0}
	};
}