#pragma once
#include <memory>
#include "../Geometry.h"
#include "../vec2.h"

// プロトタイプ宣言
class Player;
class Field;

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyBase
{
public:
	EnemyBase();

	// ポインタの設定
	void SetPlayer(std::shared_ptr<Player>player) { pPlayer_ = player; }
	void SetField(std::shared_ptr<Field>field) { pField_ = field; }

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	// 当たり判定
	bool Colision(int direction);

	// パワーエサを取得した場合の速度計算
	void SpeedCalculation();

	// インデックス座標を座標に変換
	void PosCalculation();

	// 敵が死んだときの初期化
	void SetInit();

	// 敵の座標の取得
	Vec2 GetSize()const { return size_; }
	Vec2 GetPos() const { return pos_; }

	bool GetIzike()const { return isIzike_; }

	// 敵の表示を消すか消さないかをセット
	void SetEnabled(bool isEnabled) { isEnabled_ = isEnabled; }

	// 敵が死んだ死んでないかをセット
	void SetDead(bool isDead) { isDead_ = isDead; }

	// 敵がイジケ状態かをセット
	void SetIzike(bool isIzike) { isIzike_ = isIzike; }

	void SetFlash(bool isFlash) { isFlash_ = isFlash; }

	/// <summary>
	/// 向いている方向によって値を返す
	/// </summary>
	/// <returns>画像のy座標</returns>
	virtual int DirectReturnNum();
protected:
	std::shared_ptr<Field> pField_ = nullptr;
	std::shared_ptr<Player> pPlayer_ = nullptr;

	// 画像サイズ
	Vec2 size_;

	// 座標
	Vec2 pos_;

	enum DIRECT
	{
		up = 1,
		down,
		left,
		right,
		direct_num
	};

	// 画像のハンドル
	int handle_;
	int izikeHandle_;

	// 表示する画像のインデックス
	int idX_;
	int idY_;

	// 動いている方向
	int moveDirection_;

	// インデックス座標
	int indexX_;
	int indexY_;

	// 仮の座標
	int kX_;
	int kY_;

	// 移動インターバル用タイマー
	int moveTimer_;

	// プレイヤーがどの方向に進みたいか
	int wantMoveDirection_;

	// プレイヤーの移動速度
	int moveInterval_;

	// パワーエサを取得した場合のスピード
	float speed_;

	// パワーエサを取得したかどうか
	bool isPowerFeed_;

	// パワーエサを取得した状態でどのくらい経ったか
	int powerFeedTimer_;

	// 表示するか
	bool isEnabled_;

	// フラッシュさせている場合の画像のインデックス
	int flashingImgY_;

	// 死んだか
	bool isDead_;

	// イジケ状態か
	bool isIzike_;

	// フラッシュさせるか
	bool isFlash_;
};
