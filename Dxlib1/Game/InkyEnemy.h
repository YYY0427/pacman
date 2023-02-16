#pragma once
#include "EnemyBase.h"

/// <summary>
/// 気まぐれな敵
/// </summary>
class InkyEnemy : public EnemyBase
{
public:
	InkyEnemy(int handle, int indexX, int indexY);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;

	void MoveSwitch();
private:
};