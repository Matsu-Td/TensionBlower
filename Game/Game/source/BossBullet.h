#pragma once
#include "appframe.h"

class BossBullet {
public:
	BossBullet();
	virtual ~BossBullet();

	void Initialize();
	void Shot();
	void EnterShot();
	void Process();
	void Render();
/*
	static BossBullet* GetInstance() { return _pInstance; }
	VECTOR GetPos() { return _vPos; }
	VECTOR GetScrnPos(){ return _scrnPos; }

	static BossBullet* _pInstance;
*/


	int _mh;
	int _cnt;
	int _pattern;
	float _angle;
	float _vAngle;
	float _bltSpd;
	VECTOR _vPos;   // 位置
	float _vx, _vz;
	VECTOR _vDir;   // 向き
	VECTOR _scrnPos;

	std::list<BossBullet> _lsBlt;

};

/*
void Enemy::Shot()
{
	//ショット開始時間になったらフラグを立てる
	if (shot_time == g_cnt)
		s_flag = true;

	//フラグが立ったら弾を登録する
	if (s_flag)
		Enter_shot();


	//フラグが立っている弾の数
	int s = 0;
	//フラグが立っている弾だけ移動計算
	for (std::list<shot_t>::iterator blItr = bullet.begin(); blItr != bullet.end();)
	{
		blItr->vx = float(cos(blItr->ang)) * blItr->speed;
		blItr->vy = float(sin(blItr->ang)) * blItr->speed;
		//実際に移動させる
		blItr->x += blItr->vx;
		blItr->y += blItr->vy;
		s++;
		shot_num++;

		//画面外でノードを削除
		if (blItr->x + blItr->sizeX < FIELD_X || FIELD_X_MAX + blItr->sizeX < blItr->x || blItr->y + blItr->sizeY < FIELD_Y || FIELD_Y_MAX + blItr->sizeY < blItr->y)
		{
			blItr = bullet.erase(blItr);
			s--;
			shot_num--;
			continue;
		}
		blItr++;
	}
	DrawFormatString(x + 40, y + 40, GetColor(255, 0, 0), "%d shot ", s);
	//キルフラグがたてばこのクラスを削除する
	if (killflag && s == 0)
	{
		//敵消滅フラグを立てる
		endflag = true;
	}

}

void Enemy::Enter_shot()
{
	++s_cnt;

	//プレイヤーとの角度を求める
	double px, py;
	Manager::Instance()->GetPlayerPos(&px, &py);
	ang = atan2(py - y, px - x);
	DrawFormatString(x + 50, y + 50, GetColor(255, 0, 0), "%f Rad", ang);

	//プッシュ用
	shot_t tmp;
	//最低限の初期化　バグ解消に2時間かけたとこ
	tmp.cnt = 0;
	tmp.sizeX = s_sizeX[0];
	tmp.sizeY = s_sizeY[0];

	//複数のパターンを作る
	switch (s_pattern)
	{
		//パターン0
	case 0:
	{
		//10カウントに1回、40カウントまで発射する
		if (s_cnt % 10 == 0 && s_cnt <= 60)
		{
			tmp.x = this->x;
			tmp.y = this->y;
			tmp.ang = PI / 2;
			bullet.push_front(tmp);
		}
		break;
	}

	//パターン1
	case 1:
	{
		int cnt_1 = 0;
		if (s_cnt % 4 == 0 && s_cnt <= 240)
		{
			for (int i = 0; i < 8; ++i)
			{
				cnt_1++;
				tmp.refflag = true;
				tmp.x = this->x;
				tmp.y = this->y;
				tmp.ang = (PI2 / 256 * cnt_1) + g_cnt * 5;
				tmp.speed = cnt_1 * 0.05 + 2;
				bullet.push_front(tmp);
			}
		}
		break;
	}

	//パターン2　自機狙い弾
	case 2:
	{
		//2フレームに一回、200フレーム間に
		if (s_cnt % 2 == 0 && s_cnt <= 180)
		{
			tmp.refflag = false;
			tmp.x = this->x;
			tmp.y = this->y;
			tmp.ang = this->ang;
			tmp.speed = this->speed;
			bullet.push_front(tmp);
		}
		break;
	}

	//パターン3　自機狙い全方位弾(360way)
	case 3:
	{
		if (s_cnt % 1 == 0 && s_cnt <= 180)
		{
			for (int i = 0; i < 360; i++)
			{
				tmp.refflag = false;
				tmp.x = this->x;
				tmp.y = this->y;
				tmp.ang = this->ang + (i * 1) * PI / 180;
				tmp.speed = this->speed;
				bullet.push_front(tmp);
			}
		}
	}
	}
}

void Enemy::Update()
{
	Move();
	Anim();
	Shot();
	++cnt;
}

void Enemy::Draw()
{
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//弾が前面
	for (std::list<shot_t>::iterator blItr = bullet.begin(); blItr != bullet.end();)
	{
		DrawRotaGraphF(blItr->x, blItr->y, 1.0f, 0.0f, shothandle[0], true, false);
		++blItr;
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	//キルフラグが立っていなければ描画
	if (!killflag)
	{
		DrawRotaGraphF(x, y, 1.0f, 0.0f, enemyhandle[num], true, false);
	}
}
*/