#include "stdafx.h"
#include "Lights.h"

//
//							Konstruktory
//

TrafficLight::TrafficLight(ICOMPONENT * cpt)
	:cpt(cpt)
{
}

TrafficLightS1::TrafficLightS1(ICOMPONENT * cpt)
	: TrafficLight(cpt)
	, LS({HIZ, HIZ, HIZ})	//Inicjalizujemy strukture LS
{	
}

TrafficLightS5::TrafficLightS5(ICOMPONENT * cpt)
	:TrafficLight(cpt)
	, LS({ HIZ, HIZ })		//Inicjalizujemy strukture LS
{
}

//
//							Inicjalizacja pinów, wywo³ujemy w funkcji DSIMMODEL::setup
//

void TrafficLightS1::initPins(IINSTANCE * instance) {

	PinR = instance->getdsimpin((CHAR *)"R", true);
	PinY = instance->getdsimpin((CHAR *)"Y", true);
	PinG = instance->getdsimpin((CHAR *)"G", true);

}

void TrafficLightS5::initPins(IINSTANCE * instance) {

	PinR = instance->getdsimpin((CHAR *)"R", true);
	PinG = instance->getdsimpin((CHAR *)"G", true);

}

//
//							Rysowanie sygnalizatorów, wywo³ujemy w funkcji ACTIVEMODEL::plot
//

void TrafficLightS1::draw(bool tristate) {

	if (LS.Red == ON)
		cpt->setbrushcolour(RED_ON);
	else if ((LS.Red == OFF) || !tristate)
		cpt->setbrushcolour(RED_OFF);
	else
		cpt->setbrushcolour(-1);

	cpt->drawcircle(150, 750, 100);

	if (LS.Yellow == ON)
		cpt->setbrushcolour(YELLOW_ON);
	else if ((LS.Yellow == OFF) || !tristate)
		cpt->setbrushcolour(YELLOW_OFF);
	else
		cpt->setbrushcolour(-1);

	cpt->drawcircle(150, 450, 100);

	if (LS.Green == ON)
		cpt->setbrushcolour(GREEN_ON);
	else if ((LS.Green == OFF) || !tristate)
		cpt->setbrushcolour(GREEN_OFF);
	else
		cpt->setbrushcolour(-1);

	cpt->drawcircle(150, 150, 100);

}

void TrafficLightS5::draw(bool tristate) {

	if (LS.Red == ON)
		cpt->setbrushcolour(RED_ON);
	else if ((LS.Red == OFF) || !tristate)
		cpt->setbrushcolour(RED_OFF);
	else
		cpt->setbrushcolour(-1);

	cpt->drawcircle(350, 250, 100);

	if (LS.Green == ON)
		cpt->setbrushcolour(GREEN_ON);
	else if ((LS.Green == OFF) || !tristate)
		cpt->setbrushcolour(GREEN_OFF);
	else
		cpt->setbrushcolour(-1);

	cpt->drawcircle(350, -50, 100);

}

//
//							Sprawdzenie stanu pinów, i wys³anie do funkcji animate
//

void TrafficLightS1::sendState(ACTIVEDATA *data) {

	struct LS* pLS = new struct LS;

	//		( Kolor czerwony )
	if (ishigh(PinR->istate()))
		pLS->Red = ON;
	
	else if (islow(PinR->istate()))
		pLS->Red = OFF;
	
	else
		pLS->Red = HIZ;

	//		( Kolor ¿ó³ty )
	if (ishigh(PinY->istate()))
		pLS->Yellow = ON;

	else if (islow(PinY->istate()))
		pLS->Yellow = OFF;

	else
		pLS->Yellow = HIZ;

	//		( Kolor zielony )
	if (ishigh(PinG->istate()))
		pLS->Green = ON;

	else if (islow(PinG->istate()))
		pLS->Green = OFF;

	else
		pLS->Green = HIZ;

	data->type = ADT_USER;
	data->userinfo = pLS;

}

void TrafficLightS5::sendState(ACTIVEDATA *data) {

	struct LS* pLS = new struct LS;

	//		( Kolor czerwony )
	if (ishigh(PinR->istate()))
		pLS->Red = ON;

	else if (islow(PinR->istate()))
		pLS->Red = OFF;

	else
		pLS->Red = HIZ;

	//		( Kolor zielony )
	if (ishigh(PinG->istate()))
		pLS->Green = ON;

	else if (islow(PinG->istate()))
		pLS->Green = OFF;

	else
		pLS->Green = HIZ;

	data->type = ADT_USER;
	data->userinfo = pLS;

}

//
//							Pobranie stanu pinów w funkcji animate
//

void TrafficLightS1::receiveState(ACTIVEDATA *data) {

	if (data->type == ADT_USER) {
		
		struct LS* pLS;

		pLS = (struct LS*)data->userinfo;

		memcpy(&LS, pLS, sizeof(struct LS));	//Kopiujemy wartosc spod wskaznika do struktury
		delete pLS;		//Usuwamy niepotrzebna strukture z pamieci

	}

}

void TrafficLightS5::receiveState(ACTIVEDATA *data) {
	
	if (data->type == ADT_USER) {

		struct LS* pLS;

		pLS = (struct LS*)data->userinfo;

		memcpy(&LS, pLS, sizeof(struct LS));	//Kopiujemy wartosc spod wskaznika do struktury
		delete pLS;		//Usuwamy niepotrzebna strukture z pamieci

	}
}

