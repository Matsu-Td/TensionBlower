
#include "Player.h"
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus() {

	_cgName = ResourceServer::LoadGraph("res/player_name.png");
	_cgFrame = ResourceServer::LoadGraph("res/player_status.png");
	_cgFrameBg = ResourceServer::LoadGraph("res/player_status_2.png");
	_cgBarHP = ResourceServer::LoadGraph("res/player_hp.png");
	_cgBarEnergy = ResourceServer::LoadGraph("res/player_energy.png");
	_cgRemainFrame = ResourceServer::LoadGraph("res/remain_frame.png");

	for (int i = 0; i < ALL_NUM; i++) {
		_cgRemainNum[i]= ResourceServer::LoadGraph(_numString[i]);
	}
}

PlayerStatus::~PlayerStatus() {

}

void PlayerStatus::Render() {

	int hitpoint = Player::GetInstance()->GetHitPoint();
	int energy = Player::GetInstance()->GetEnergy();
	int bulletNum = Player::GetInstance()->GetBulletNum();
	DrawGraph(30, 30, _cgFrameBg, TRUE);
	DrawExtendGraph(68, 45, 68 + (740 * hitpoint / 1000), 80, _cgBarHP, TRUE);
	DrawExtendGraph(59, 90, 59 + (738 * energy / 6000), 120, _cgBarEnergy, TRUE);
	DrawGraph(30, 30, _cgFrame, TRUE);
	DrawGraph(0, 130, _cgName, TRUE);

	DrawGraph(30, 900, _cgRemainFrame, TRUE);

	DrawGraph(45, 920,  _cgRemainNum[bulletNum / 100], TRUE);
	DrawGraph(100, 920, _cgRemainNum[bulletNum / 10 % 10], TRUE);
	DrawGraph(155, 920, _cgRemainNum[bulletNum % 10], TRUE);
}