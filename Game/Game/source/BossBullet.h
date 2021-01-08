#pragma once
#include "appframe.h"
#include <list>

class BossBullet {
public:
	BossBullet();
	virtual ~BossBullet();

	void Initialize();
	void Process();
	void Render();
	void Shot();
	void ShotStart();
/*
	static BossBullet* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetScrnPos() const { return _scrnPos; }

	static BossBullet* _pInstance;
*/
private:
	int _mh;
	int _mhMap;
	int _mhPl;
	int _shotCnt;
	int _pattern;
//	float _angle;
	float _setAngle;
	float _bltSpd;
	float shotInterval;
//	VECTOR _capsulePos1, _capsulePos2; // �����蔻��p�J�v�Z��
//	VECTOR _vPos;   // �ʒu
//	float _vx, _vz;
	VECTOR _vDir;   // ����
//	VECTOR _scrnPos;
	MV1_COLL_RESULT_POLY_DIM _hitPolyDimStg;
	MV1_COLL_RESULT_POLY_DIM _hitPolyDimPl;
	//std::list<BossBullet> _lsBlt;

	typedef struct SHOT {
		VECTOR _capsulePos1, _capsulePos2; // �����蔻��p�J�v�Z��
		VECTOR _vPos;   // �ʒu
		float _vx, _vz;
		float _angle;
		VECTOR _scrnPos;
	}SHOT;

	std::list<SHOT> _lsBlt;

	SHOT _shot;
};

/*
void Enemy::Shot()
{
	//�V���b�g�J�n���ԂɂȂ�����t���O�𗧂Ă�
	if (shot_time == g_cnt)
		s_flag = true;

	//�t���O����������e��o�^����
	if (s_flag)
		Enter_shot();


	//�t���O�������Ă���e�̐�
	int s = 0;
	//�t���O�������Ă���e�����ړ��v�Z
	for (std::list<shot_t>::iterator blItr = bullet.begin(); blItr != bullet.end();)
	{
		blItr->vx = float(cos(blItr->ang)) * blItr->speed;
		blItr->vy = float(sin(blItr->ang)) * blItr->speed;
		//���ۂɈړ�������
		blItr->x += blItr->vx;
		blItr->y += blItr->vy;
		s++;
		shot_num++;

		//��ʊO�Ńm�[�h���폜
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
	//�L���t���O�����Ă΂��̃N���X���폜����
	if (killflag && s == 0)
	{
		//�G���Ńt���O�𗧂Ă�
		endflag = true;
	}

}

void Enemy::Enter_shot()
{
	++s_cnt;

	//�v���C���[�Ƃ̊p�x�����߂�
	double px, py;
	Manager::Instance()->GetPlayerPos(&px, &py);
	ang = atan2(py - y, px - x);
	DrawFormatString(x + 50, y + 50, GetColor(255, 0, 0), "%f Rad", ang);

	//�v�b�V���p
	shot_t tmp;
	//�Œ���̏������@�o�O������2���Ԃ������Ƃ�
	tmp.cnt = 0;
	tmp.sizeX = s_sizeX[0];
	tmp.sizeY = s_sizeY[0];

	//�����̃p�^�[�������
	switch (s_pattern)
	{
		//�p�^�[��0
	case 0:
	{
		//10�J�E���g��1��A40�J�E���g�܂Ŕ��˂���
		if (s_cnt % 10 == 0 && s_cnt <= 60)
		{
			tmp.x = this->x;
			tmp.y = this->y;
			tmp.ang = PI / 2;
			bullet.push_front(tmp);
		}
		break;
	}

	//�p�^�[��1
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

	//�p�^�[��2�@���@�_���e
	case 2:
	{
		//2�t���[���Ɉ��A200�t���[���Ԃ�
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

	//�p�^�[��3�@���@�_���S���ʒe(360way)
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
	//�e���O��
	for (std::list<shot_t>::iterator blItr = bullet.begin(); blItr != bullet.end();)
	{
		DrawRotaGraphF(blItr->x, blItr->y, 1.0f, 0.0f, shothandle[0], true, false);
		++blItr;
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	//�L���t���O�������Ă��Ȃ���Ε`��
	if (!killflag)
	{
		DrawRotaGraphF(x, y, 1.0f, 0.0f, enemyhandle[num], true, false);
	}
}
*/