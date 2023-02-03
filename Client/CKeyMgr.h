#pragma once

// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ó��
// tap, hold, away 
// �� ������ ������ ����ó���� �Ǵ°� �ƴ϶� �ѹ��� 
// �۵��ϴ°�, �׸��� �� ������ �ִٰ� ���� �� �۵��ϴ� �� ���

enum class KEY_STATE
{
	NONE, // ������ �ʾҰ�, �������� ������ ���� ����
	TAP, // �� ���� ����
	HOLD, // ������ �ִ� 
	AWAY, // �� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	J,
	K,
	L,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE	eState;	// Ű�� ���°�
	bool		bPrevPush;	//  ���� �����ӿ��� ���ȴ��� ����
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;
	Vec2			 m_vCurMousePos;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMousePos() { return m_vCurMousePos; }
};
