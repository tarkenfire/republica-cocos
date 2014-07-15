/*
 * Modal Dialog.cpp
 * Michael Mancuso
 * July 9, 2014
 * Modal dialog class for Cocos2d-x using only cocos core.
*/

#ifndef __MODALDIALOG_H__
#define __MODALDIALOG_H__

#include "cocos2d.h"

class ModalDialog : public cocos2d::LayerColor
{
    
    public:
        enum class DialogType { CONFIRM, YESNO};
        
        
        virtual bool init();
        CREATE_FUNC(ModalDialog);
        void configDialog(DialogType dialogType, std::string title, std::string message);
        
        
        
};


#endif