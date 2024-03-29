#pragma once


// Singleton ��ũ��
#define SINGLE(type) public:\
					 static type* GetInst()\
					 {\
						static type mgr;\
						return &mgr;\
					 }\
					private:\
						type();\
						~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define CLONE(type)	type* Clone() {return new type(*this);}


#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f

#define TILE_SIZE 64




enum class GROUP_TYPE
{
	DEFAULT, // 0
	BEACHBACKGROUND1,
	BEACHBACKGROUND2,
	BEACHBACKGROUND3,
	SWAMPBACKGROUND,
	SWAMPBACKGROUND2,
	SWAMPBACKGROUND3,
	BOSSSTAGEBACKGROUND,
	BACKGROUNDANIM,
	BEACHFRONT,
	BROKENCONGAHOUSE,
	DESTROYEDBROKENSHIP,
	BROKENSHIP,
	CONGAHOUSE,
	SWAMP,
	SWAMPUNDER,
	WOODENSTOOL,
	SLUGTRANSPORT,
	SLUGTRANSPORTWAVE,
	SLUGTRANSPORTWAVE2,
	SHIP,
	SHIPDOOR,
	TILE,
	BOSSSTAGETILECOPY,
	BOSSSTAGETILE,
	CAPTIVE,
	MONSTER,
	SUPPLIES,
	R724,
	PLAYER,
	CAMERABOX,
	PROJ_PLAYER,
	GROUND,
	PROJ_MONSTER,
	TEST_ANIM,
	EVENT_OBJECT,
	UI,
	BULLETUI,

	END = 45,

};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	WHITE,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,

	END,
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	BUBBLE_FIRE,
	CLAWING,
	BITING,
	RUN,
	FLYING,
	KIDNAPPING,
	RUSH,
	BOUNCE,
	FIRING,
	APPEAR,
	DESTROYED,
	DEAD,
};


enum class MON_TYPE
{
	CHOWMEIN_CONGA,
	LOCUST,
	FLYING_KILLER,
	M3_ROCKET_LAUNCH_SUPPORT_VAN,
	M3_ROCKET_LAUNCH_SUPPORT_VAN_MISSILE,
	HUGE_HERMIT,
};

enum class FONT
{
	NONE = -1,
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	A,
	B,
	M,
	O,
	R,
	S,
};


enum class Digit
{
	NONE = -1,
	Bullet1,
	Bullet10,
	Bullet100,
	Grenade1,
	Grenade10,
};