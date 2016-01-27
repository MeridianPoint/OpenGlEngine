#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "stdafx.h"

enum //Repeattype
{
	RT_CLAMP,
	RT_WRAP,
	RT_CYCLE,
	RT_QUANTITY
};

class Controller
{
public:
	Model *getModel() const;
	virtual ~Controller();

	virtual bool Update(float time)=0;
	
	 
	void ActiveRange();

	int RepeatType;
	float MinTime;
	float MaxTime;
	float phase;
	float Frequency;
	bool Active;
protected:
	Controller();

	friend class Model;
	friend class Spatial;
	virtual void SetModel(Model* pModel){ pModel = pModel; };
	void SetSpatial(Spatial *Spatial){ pSpatial = Spatial; };
	double GetControllTime(float time);
	Model* pModel;
	Spatial* pSpatial; //Spatial for 

	double lastTime;
	//virtual float getAjustedTime(float time);
};

#endif