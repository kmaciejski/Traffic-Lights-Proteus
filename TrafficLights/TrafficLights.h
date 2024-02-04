#pragma once

#include "sdk/vsm.hpp"
#include "Lights.h"

//Model (wielokrotne dziedziczenie z 2 interfejsów)

class MODEL 
	: public IDSIMMODEL
	,public IACTIVEMODEL
{
public:

//Model cyfrowy :

	INT		isdigital(CHAR * pinname);
	VOID	setup(IINSTANCE * inst, IDSIMCKT * dsim);
	VOID	runctrl(RUNMODES mode);
	VOID	actuate(REALTIME time, ACTIVESTATE newstate);
	BOOL	indicate(REALTIME time, ACTIVEDATA * data);
	VOID	simulate(ABSTIME time, DSIMMODES mode);
	VOID	callback(ABSTIME time, EVENTID eventid);

//Model graficzny :

	VOID initialize(ICOMPONENT *cpt);
	ISPICEMODEL *getspicemodel(CHAR *primitive);
	IDSIMMODEL *getdsimmodel(CHAR *primitive);
	VOID plot(ACTIVESTATE state);
	VOID animate(INT element, ACTIVEDATA *newstate);
	BOOL actuate(WORD key, INT x, INT y, DWORD flags);

private:

	IINSTANCE*		inst;
	IDSIMCKT*		ckt;
	TrafficLight*	pTL;
	ICOMPONENT*		cpt;
	bool			triState;

};

