#pragma once
#include "EnemyBase.h"

/// <summary>
/// 一貫性がない敵
/// </summary>
class InconsistentEnemy : public EnemyBase
{
public:
	InconsistentEnemy(int handle, int indexX, int indexY);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;
};

