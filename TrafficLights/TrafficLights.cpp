//
//						 TrafficLights.cpp: Określa eksportowane funkcje dla aplikacji DLL.
//

#include "stdafx.h"
#include "TrafficLights.h"

using namespace std;

//Tworzenie IACTIVEMODEL

extern "C" IACTIVEMODEL __declspec(dllexport) *createactivemodel(CHAR* device, ILICENCESERVER* ils)
{
	return new MODEL;
}

//Usuwanie IACTIVEMODEL

extern "C" VOID __declspec(dllexport) deleteactivemodel(IACTIVEMODEL* model)
{
	delete (MODEL *)model;
}

//Tworzenie IDSIMMODEL

extern "C" IDSIMMODEL __declspec(dllexport) *createdsimmodel(CHAR* device, ILICENCESERVER* ils)
{
	return new MODEL;
}

//Usuwanie IDSIMMODEL

extern "C" VOID __declspec(dllexport) deletedsimmodel(IDSIMMODEL* model)
{
	delete (MODEL *)model;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//												Metody IACTIVEMODEL :
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//					Inicjalizacja modelu

VOID MODEL::initialize(ICOMPONENT * cpt) 
{
	
	this->cpt = cpt;

	PCHAR prop = cpt->getprop((PCHAR)"TriState");

	if (prop && (strcmp(prop, "OFF") == 0))
		triState = false;
	else
		triState = true;




}

//					Zwraca model SPICE

ISPICEMODEL* MODEL::getspicemodel(CHAR *primitive)
{
	return NULL;
}

//					Zwraca model DSIM

IDSIMMODEL*	MODEL::getdsimmodel(CHAR *primitive)
{

	string s = primitive;

	if ( s.find("S-1") != string::npos )
		pTL = new TrafficLightS1(cpt);
	
	else if (s.find("S-5") != string::npos)
		pTL = new TrafficLightS5(cpt);


	return this;

}

//					Renderowanie modelu graficznego

VOID MODEL::plot(ACTIVESTATE state)
{

	cpt->drawsymbol(-1);
	pTL->draw(triState);

}

//					Reakcja na zdarzenia generowane przez model elektryczny (DSIM)

VOID MODEL::animate(INT element, ACTIVEDATA *data)
{

	pTL->receiveState(data);
	plot(NULL);

}


//					Reakcja na klikanie itp.

BOOL MODEL::actuate(WORD key, INT x, INT y, DWORD flags)
{
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//												Metody IDSIMMODEL :
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

INT MODEL::isdigital(CHAR * pinname)
{
	return 1;
}

VOID MODEL::setup(IINSTANCE * instance, IDSIMCKT * dsimckt)
{
	inst = instance;
	ckt = dsimckt;

	//Pobieramy uchwyty do pinów
	pTL->initPins(instance);

}

VOID MODEL::runctrl(RUNMODES mode)
{
}

VOID MODEL::actuate(REALTIME time, ACTIVESTATE newstate)
{
}

//			Komunikacja z modelem graficznym i odczyt pinów

BOOL MODEL::indicate(REALTIME time, ACTIVEDATA * data)
{

	pTL->sendState(data);
	
	return TRUE;
}

//			Reakcja na zmiane stanów pinów

VOID MODEL::simulate(ABSTIME time, DSIMMODES mode)
{
}

VOID MODEL::callback(ABSTIME time, EVENTID eventid)
{
}

