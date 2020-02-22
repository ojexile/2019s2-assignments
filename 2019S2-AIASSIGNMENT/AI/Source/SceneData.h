#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "SingletonTemplate.h"

class SceneData : public Singleton<SceneData>
{
	friend Singleton<SceneData>;

private:
	SceneData();
	~SceneData();
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;
	int m_fishCount;
	int mineralCount;
	int harvesterCount;
	int harvestedMineral;
public:
	int getObjectCount();
	void setObjectCount(int input);
	int getNoGrid();
	void setNoGrid(int input);
	float getGridSize();
	void setGridSize(float input);
	float getGridOffset();
	int getFishCount();
	void setFishCount(int input);
	int getMineralCount();
	void setMineralCount(int input);
	int getHarvesterCount();
	void setHarvesterCount(int input);
	int getHarvestedMineral();
	void setHarvestedMineral(int input);
};

#endif // ! SCENEDATA_H
