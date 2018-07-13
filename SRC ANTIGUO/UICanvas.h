#ifndef UICANVAS_H_
#define UICANVAS_H_

#include "Component.h"
#include "OgreOverlayContainer.h"

using namespace Ogre;

class UICanvas : public Component {
public:

	UICanvas(OverlayContainer* newContainer, Overlay* newOverlay) : Component()
	{
		ovContainer = newContainer;
		overlay = newOverlay;
	};

	virtual ~UICanvas()
	{
	}

	virtual void start() {
	
	};

	virtual void tick(double elapsed) {
		
	};

	void UICanvas::setNewUISize(float x, float y) {
		ovContainer->setDimensions(x, y);
	}

	float UICanvas::getUIWidth() {
		return ovContainer->getWidth();		
	}

	float UICanvas::getUIHeight() {
		return ovContainer->getHeight();
	}
	void UICanvas::updateUI() {
		overlay->show();
	}

protected:
	OverlayContainer* ovContainer;
	Overlay* overlay;
};

#endif