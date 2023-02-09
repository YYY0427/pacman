#pragma once
#include "EnemyBase.h"
#include "../vec2.h"
#include <memory>

class Field;
class Player;

/// <summary>
/// 粘着タイプ敵
/// </summary>
class ChasingEnemy : public EnemyBase
{
public:
	ChasingEnemy(int handle, int indexX, int indexY);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;
private:
};