#include "../../main.h"
#include "../gui.h"
#include "../../game/game.h"
#include "../../net/netgame.h"
#include "../../net/localplayer.h"

extern UI* pUI;
extern CNetGame* pNetGame;
extern CGame *pGame;

bool bNeedEnterVehicle = false;

ButtonPanel::ButtonPanel()
	: Layout(Orientation::HORIZONTAL)
{
	m_bY = new Button("Y", UISettings::fontSize() / 2);
	m_bN = new Button("N", UISettings::fontSize() / 2);
	m_bH = new Button("H", UISettings::fontSize() / 2);
	m_bInv = new Button("INV", UISettings::fontSize() / 2);
	m_bPhone = new Button("TEL", UISettings::fontSize() / 2);
	m_bWheel = new Button("::", UISettings::fontSize() / 2);

	m_bY->setCallback([]() {
		if (pNetGame) {
			pNetGame->SendChatCommand("/cityhub");
		}
		LocalPlayerKeys.bKeys[ePadKeys::KEY_YES] = true;
	});

	m_bN->setCallback([]() {
		LocalPlayerKeys.bKeys[ePadKeys::KEY_NO] = true;
	});

	m_bH->setCallback([]() {
		LocalPlayerKeys.bKeys[ePadKeys::KEY_CTRL_BACK] = true;
	});

	m_bInv->setCallback([]() {
		if (pNetGame) {
			pNetGame->SendChatCommand("/inv");
		}
	});

	m_bPhone->setCallback([]() {
		if (pNetGame) {
			pNetGame->SendChatCommand("/phone");
		}
	});

	m_bWheel->setCallback([]() {
		if (pNetGame) {
			pNetGame->SendChatCommand("/cityhub");
		}
	});

	this->addChild(m_bY);
	this->addChild(m_bN);
	this->addChild(m_bH);
	this->addChild(m_bInv);
	this->addChild(m_bPhone);
	this->addChild(m_bWheel);
}