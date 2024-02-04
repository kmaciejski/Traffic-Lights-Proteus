#pragma once

#include "sdk/vsm.hpp"

//Kolory sygnalizatorów :

#define  RED_ON			MAKECOLOUR(0xFF,0x00,0x00)
#define  RED_OFF		MAKECOLOUR(0x20,0x00,0x00)

#define  GREEN_ON		MAKECOLOUR(0x00,0xFF,0x00)
#define  GREEN_OFF		MAKECOLOUR(0x00,0x20,0x00)

#define  YELLOW_ON		MAKECOLOUR(0xFF,0xFF,0x00)
#define  YELLOW_OFF		MAKECOLOUR(0x40,0x40,0x00)

//	Stany swiatel

enum LIGHTSTATE : BYTE
{
	OFF = 0x10,
	ON = 0x20,
	HIZ = 0x30
};

//	Klasa abstrakcyjna

class TrafficLight
{
public:

	virtual void initPins(IINSTANCE * instance) = 0;	//Metoda czysto wirtualna
	virtual void draw(bool tristate) = 0;
	virtual void sendState(ACTIVEDATA *data) = 0;
	virtual void receiveState(ACTIVEDATA *data) = 0;
	TrafficLight(ICOMPONENT * cpt);

protected:

	ICOMPONENT * cpt;

};

//Konkretne sygnalizatory :

class TrafficLightS1 : public TrafficLight{

public:

	virtual void initPins(IINSTANCE * instance);
	virtual void draw(bool tristate);
	virtual void sendState(ACTIVEDATA *data);
	virtual void receiveState(ACTIVEDATA *data);
	TrafficLightS1(ICOMPONENT * cpt);

private:

	struct LS {
		LIGHTSTATE Red;
		LIGHTSTATE Yellow;
		LIGHTSTATE Green;
	}LS;

	IDSIMPIN * PinR;
	IDSIMPIN * PinY;
	IDSIMPIN * PinG;

};

class TrafficLightS5 : public TrafficLight {

public:

	virtual void initPins(IINSTANCE * instance);
	virtual void draw(bool tristate);
	virtual void sendState(ACTIVEDATA *data);
	virtual void receiveState(ACTIVEDATA *data);
	TrafficLightS5(ICOMPONENT * cpt);

private:

	struct LS {
		LIGHTSTATE Red;
		LIGHTSTATE Green;
	}LS;

	IDSIMPIN * PinR;
	IDSIMPIN * PinG;

};

//Wskaznik do sygnalizatora

extern TrafficLight* pTL;