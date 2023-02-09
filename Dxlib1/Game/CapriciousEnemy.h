#pragma once
#include "EnemyBase.h"

/// <summary>
/// 気まぐれな敵
/// </summary>
class CapriciousEnemy : public EnemyBase
{
public:
	CapriciousEnemy(int handle, int indexX, int indexY);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;

private:
};

