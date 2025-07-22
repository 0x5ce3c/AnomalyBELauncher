#pragma once

struct func // структура дл€ функций, имеющих только включение/вылючение и гор€чие клавиши
{
	bool enabled;
    int active;
	//keycombo keys; кнопочки и тд в будущем
};

struct stsn
{		

	//lparams
	func dbg;

	Console con;
};
