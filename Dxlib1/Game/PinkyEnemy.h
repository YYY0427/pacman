#pragma once
#include "EnemyBase.h"

/// <summary>
/// 先回りする敵
/// </summary>
class PinkyEnemy : public EnemyBase
{
public:
	PinkyEnemy(int handle, int indexX, int indexY);

	virtual ~PinkyEnemy(){}
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;

	virtual void Draw()override;

	virtual void SetInit()override;
};