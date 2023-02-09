#pragma once
#include "EnemyBase.h"

/// <summary>
/// 先回りする敵
/// </summary>
class PreemptiveEnemy : public EnemyBase
{
public:
	PreemptiveEnemy(int handle, int indexX, int indexY);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;
};

