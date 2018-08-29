#include "formation.h"
#include "timer.h"

void Formation::Create()
{
	//Left
	m_enterPaths[0] = { Vector2D(500.0f, -64.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f) };
	//Right
	m_enterPaths[1] = { Vector2D(300.0f, -64.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f) };
	//TopLeft
	m_enterPaths[2] = { Vector2D(-64.0f, 150.0f), Vector2D(100.0f, 350.0f), Vector2D(400.0f, 425.0f), Vector2D(650.0f, 350.0f) };
	//TopRight
	m_enterPaths[3] = { Vector2D(864.0f, 150.0f), Vector2D(700.0f, 350.0f), Vector2D(400.0f, 425.0f), Vector2D(250.0f, 350.0f) };
	//BottomLeft
	m_enterPaths[4] = { Vector2D(-64.0f, 500.0f), Vector2D(380.0f, 400.0f), Vector2D(200.0f, 300.0f), Vector2D(100.0f, 400.0f), Vector2D(200.0f, 500.0f), Vector2D(380.0f, 400.0f) };
	//BottomRight
	m_enterPaths[5] = { Vector2D(864.0f, 500.0f), Vector2D(420.0f, 400.0f), Vector2D(600.0f, 300.0f), Vector2D(700.0f, 400.0f), Vector2D(600.0f, 500.0f), Vector2D(420.0f, 400.0f) };

	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 450.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(200.0f, 300.0f), Vector2D(250.0f, 450.0f), Vector2D(400.0f, 600.0f), Vector2D(500.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(600.0f, 300.0f), Vector2D(500.0f, 450.0f), Vector2D(400.0f, 600.0f), Vector2D(350.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(100.0f, 300.0f), Vector2D(200.0f, 450.0f), Vector2D(300.0f, 600.0f), Vector2D(400.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(200.0f, 300.0f), Vector2D(100.0f, 400.0f), Vector2D(200.0f, 500.0f), Vector2D(100.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(600.0f, 300.0f), Vector2D(700.0f, 400.0f), Vector2D(600.0f, 500.0f), Vector2D(700.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(400.0f, 400.0f), Vector2D(400.0f, 500.0f), Vector2D(400.0f, 650.0f) });

	
	m_formation =
	{ {  { Enemy::BUG, Enemy::LEFT, 300.0f, Vector2D(260.0f, 80.0f),  this }, 0.0f,  false },
	{    { Enemy::BUG, Enemy::LEFT, 300.0f, Vector2D(260.0f, 120.0f), this }, 0.4f,  false },
		
	{	 { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(220.0f, 160.0f), this }, 0.75f, false },
	{    { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(260.0f, 160.0f), this }, 1.05f, false },
	{    { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(220.0f, 200.0f), this }, 1.4f,  false },
	{    { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(260.0f, 200.0f), this }, 1.75f, false },
	
	{	 { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(540.0f, 80.0f),  this }, 8.75f, false },
	{	 { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(540.0f, 120.0f), this }, 9.05f, false },

	{    { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(580.0f, 160.0f), this }, 9.4f,  false },
	{    { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(540.0f, 160.0f), this }, 9.75f, false },
	{    { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(580.0f, 200.0f), this }, 10.05f, false },
	{    { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(540.0f, 200.0f), this }, 10.4f,  false },

	{    { Enemy::BUG, Enemy::TOPLEFT, 300.0f, Vector2D(300.0f, 80.0f),  this }, 17.4f,  false },
	{    { Enemy::BUG, Enemy::TOPLEFT, 300.0f, Vector2D(340.0f, 80.0f),  this }, 17.75f, false },
	{    { Enemy::BUG, Enemy::TOPLEFT, 300.0f, Vector2D(300.0f, 120.0f), this }, 18.05f, false },
	{    { Enemy::BUG, Enemy::TOPLEFT, 300.0f, Vector2D(340.0f, 120.0f), this }, 18.4f,  false },

	{    { Enemy::BEE, Enemy::TOPLEFT, 300.0f, Vector2D(300.0f, 160.0f), this }, 18.75f, false },
	{	 { Enemy::BEE, Enemy::TOPLEFT, 300.0f, Vector2D(340.0f, 160.0f), this }, 19.05f, false },
	{    { Enemy::BEE, Enemy::TOPLEFT, 300.0f, Vector2D(300.0f, 200.0f), this }, 19.4f,  false },
	{    { Enemy::BEE, Enemy::TOPLEFT, 300.0f, Vector2D(340.0f, 200.0f), this }, 19.75f, false },

	{    { Enemy::BUG, Enemy::TOPRIGHT, 300.0f, Vector2D(500.0f, 80.0f),  this }, 26.75f, false },
	{    { Enemy::BUG, Enemy::TOPRIGHT, 300.0f, Vector2D(460.0f, 80.0f),  this }, 27.05f, false },
	{    { Enemy::BUG, Enemy::TOPRIGHT, 300.0f, Vector2D(500.0f, 120.0f), this }, 27.4f,  false },
	{    { Enemy::BUG, Enemy::TOPRIGHT, 300.0f, Vector2D(460.0f, 120.0f), this }, 27.75f, false },

	{    { Enemy::BEE, Enemy::TOPRIGHT, 300.0f, Vector2D(500.0f, 160.0f), this }, 28.05f, false },
	{    { Enemy::BEE, Enemy::TOPRIGHT, 300.0f, Vector2D(460.0f, 160.0f), this }, 28.4f,  false },
	{    { Enemy::BEE, Enemy::TOPRIGHT, 300.0f, Vector2D(500.0f, 200.0f), this }, 28.75f, false },
	{    { Enemy::BEE, Enemy::TOPRIGHT, 300.0f, Vector2D(460.0f, 200.0f), this }, 29.05f, false },

	{    { Enemy::BOSS, Enemy::BOTTOMLEFT, 300.0f, Vector2D(340.0f, 40.0f),  this }, 36.05f, false },
	{    { Enemy::BOSS, Enemy::BOTTOMLEFT, 300.0f, Vector2D(380.0f, 40.0f),  this }, 36.4f,  false },
	{    { Enemy::BUG,  Enemy::BOTTOMLEFT, 300.0f, Vector2D(380.0f, 80.0f),  this }, 36.75f, false },
	{    { Enemy::BUG,  Enemy::BOTTOMLEFT, 300.0f, Vector2D(380.0f, 120.0f), this }, 37.05f, false },
	{    { Enemy::BEE,  Enemy::BOTTOMLEFT, 300.0f, Vector2D(380.0f, 160.0f), this }, 37.4f,  false },
	{    { Enemy::BEE,  Enemy::BOTTOMLEFT, 300.0f, Vector2D(380.0f, 200.0f), this }, 37.75f, false },

	{    { Enemy::BOSS, Enemy::BOTTOMRIGHT, 300.0f, Vector2D(460.0f, 40.0f),  this }, 36.05f, false },
	{    { Enemy::BOSS, Enemy::BOTTOMRIGHT, 300.0f, Vector2D(420.0f, 40.0f),  this }, 36.4f,  false },
	{    { Enemy::BUG,  Enemy::BOTTOMRIGHT, 300.0f, Vector2D(420.0f, 80.0f),  this }, 36.75f, false },
	{    { Enemy::BUG,  Enemy::BOTTOMRIGHT, 300.0f, Vector2D(420.0f, 120.0f), this }, 37.05f, false },
	{    { Enemy::BEE,  Enemy::BOTTOMRIGHT, 300.0f, Vector2D(420.0f, 160.0f), this }, 37.4f,  false },
	{    { Enemy::BEE,  Enemy::BOTTOMRIGHT, 300.0f, Vector2D(420.0f, 200.0f), this }, 37.75f, false },
	};

	m_timer = 0.0f;
}

void Formation::Destroy()
{

}

void Formation::Update()
{
	m_timer += Timer::Instance()->DeltaTime();
	for (Info& info : m_formation)
	{
		if (info.isActive == false && m_timer > info.enterTime)
		{
			info.isActive = true;
			Enemy* enemy = m_scene->AddEntity<Enemy>();
			enemy->Create(info.enemyInfo);
		}
	}
}

const Formation::Path& Formation::GetRandomAttackPath()
{
	size_t index = rand() % m_attackPaths.size();
	return m_attackPaths[index];
}