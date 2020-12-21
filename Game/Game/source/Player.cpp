
#include "ApplicationMain.h"
#include "Player.h"
#include "ModeGame.h"

Player* Player::_pInstance = NULL;

Player::Player()
{
	_pInstance = this;
	_mh = MV1LoadModel("res/model/���f�[�^/SDChar/SDChar.mv1");
	Initialize();
}

Player::~Player()
{

}

void Player::Initialize()
{
	_vPos = VGet(0.f, 0.f, -115.f);
	_vDir = VGet(0, 0, 1);

	_attachIndex = -1;
	_totalTime = 0;

	_playTime = 0.0f;
}

void Player::Process()
{
	// �L�[�̎擾
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;           // ���E�A�i���O�X�e�B�b�N�̍��W
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATE oldState = _state;

	// �J�����f�[�^�擾
	VECTOR camPos = Camera::GetInstance()->GetPos();
	VECTOR camTarg = Camera::GetInstance()->GetTarg();

	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// �ړ����������߂�
	VECTOR vec = { 0.f,0.f,0.f };
	float mvSpd = 0.3f;
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	if (length < analogMin) {
		// ���͂������������瓮���Ȃ��������Ƃɂ���
		length = 0.f;
	}
	else {
		length = mvSpd;
	}

	// vec��rad����]������
	vec.x = cos(rad + camRad) * length;
	vec.z = sin(rad + camRad) * length;

	// vec�̕��ړ�
	_vPos = VAdd(_vPos, vec);

	// �ړ��ʂ����̂܂܃L�����̌����ɂ���
	if (VSize(vec) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
		_vDir = vec;
		_state = STATE::WALK;
	}
	else {
		_state = STATE::WAIT;
	}

	// �X�e�[�^�X���ς���Ă��Ȃ����H
	if (oldState == _state) {
		// �Đ����Ԃ�i�߂�
		_playTime += 0.5f;
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		switch (_state) {
		case STATE::WAIT:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "idle"), -1, FALSE);
			break;
		case STATE::WALK:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "run"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);
		_playTime = 0.0f;
	}

	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}
	
}

void Player::Render()
{
	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(0.05f, 0.05f, 0.05f));
	{
		MV1SetPosition(_mh, _vPos);
		// ��������Y����]���Z�o
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);		// ���f�����W���łǂ���������Ă��邩�Ŏ����ς��(�����-z�������Ă���ꍇ)
		MV1SetRotationXYZ(_mh, vRot);
		MV1DrawModel(_mh);
	}
}

/* ���t�@�C������̕ϐ��l�������Ă�����@��
//VECTOR _cam = Camera::GetInstance()-GetPos();
	//ModeGame* modegame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	//printfDx("%f\n", _cam);

		// �V���O���g��������
	VECTOR camPos = Camera::GetInstance()->GetPos();
	DrawFormatString(0, 100, GetColor(255, 0, 0), "  camPos.x = %5.2f", camPos.x);
	DrawFormatString(0, 120, GetColor(255, 0, 0), "  camPos.y = %5.2f", camPos.y);
	DrawFormatString(0, 140, GetColor(255, 0, 0), "  camPos.z = %5.2f", camPos.z);
*/