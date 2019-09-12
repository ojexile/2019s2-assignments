#include "SceneData.h"

SceneData::SceneData()
{
	monsterCount = 0;
}

SceneData::~SceneData()
{
}

int SceneData::getObjectCount()
{
	return m_objectCount;
}

void SceneData::setObjectCount(int input)
{
	m_objectCount = input;
}

int SceneData::getNoGrid()
{
	return m_noGrid;
}

void SceneData::setNoGrid(int input)
{
	m_noGrid = input;
}

float SceneData::getGridSize()
{
	return m_gridSize;
}

void SceneData::setGridSize(float input)
{
	m_gridSize = input;
	m_gridOffset = m_gridSize / 2;
}

float SceneData::getGridOffset()
{
	return m_gridOffset;
}

int SceneData::getFishCount()
{
	return m_fishCount;
}

void SceneData::setFishCount(int input)
{
	m_fishCount = input;
}

int SceneData::getMineralCount()
{
	return mineralCount;
}

void SceneData::setMineralCount(int input)
{
	mineralCount = input;
}

int SceneData::getHarvesterCount()
{
	return harvesterCount;
}

void SceneData::setHarvesterCount(int input)
{
	harvesterCount = input;
}

int SceneData::getHarvestedMineral()
{
	return harvestedMineral;
}

void SceneData::setHarvestedMineral(int input)
{
	harvestedMineral = input;
}

int SceneData::getMonsterCount()
{
	return monsterCount;
}

void SceneData::setMonsterCount(int input)
{
	monsterCount = input;
}