#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>
#include "../ViraBotState.hpp"

using namespace geode::prelude;

class ViraBotPopup : public geode::Popup<> {
protected:
    bool init() {
        if (!Popup::init(260.f, 220.f))
            return false;

        this->setTitle("ViraBot");

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        m_mainLayer->addChild(menu);

        float startY = 60.f;
        float spacing = 40.f;

        addToggle(menu, "Noclip", &ViraBotState::noclip, startY, 1);
        addToggle(menu, "Speedhack", &ViraBotState::speedhack, startY - spacing, 2);
        addToggle(menu, "Hitbox Show", &ViraBotState::hitboxShow, startY - spacing * 2, 3);
        addToggle(menu, "Auto Click", &ViraBotState::autoClick, startY - spacing * 3, 4);

        return true;
    }

    void addToggle(CCMenu* menu, char const* label, bool* state, float y, int tag) {
        auto labelNode = CCLabelBMFont::create(label, "bigFont.fnt");
        labelNode->setScale(0.45f);
        labelNode->setAnchorPoint({0.f, 0.5f});
        labelNode->setPosition({20.f, y});
        m_mainLayer->addChild(labelNode);

        auto toggler = CCMenuItemToggler::createWithStandardSprites(
            this, menu_selector(ViraBotPopup::onToggle), 0.6f
        );
        toggler->toggle(*state);
        toggler->setPosition({230.f, y});
        toggler->setTag(tag);
        menu->addChild(toggler);
    }

    void onToggle(CCObject* sender) {
        auto toggler = static_cast<CCMenuItemToggler*>(sender);
        bool newState = !toggler->isToggled();

        switch (toggler->getTag()) {
            case 1: ViraBotState::noclip = newState; break;
            case 2: ViraBotState::speedhack = newState; break;
            case 3: ViraBotState::hitboxShow = newState; break;
            case 4: ViraBotState::autoClick = newState; break;
        }

        toggler->toggle(newState);
    }

public:
    static ViraBotPopup* create() {
        auto ret = new ViraBotPopup();
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

class $modify(ViraBotMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        if (menu) {
            auto sprite = CCSprite::create("virabot-menu-btn.png"_spr);
            sprite->setScale(0.8f);

            auto btn = CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(ViraBotMenuLayer::onOpenViraBot)
            );
            btn->setID("virabot-button");

            menu->addChild(btn);
            menu->updateLayout();
        }

        return true;
    }

    void onOpenViraBot(CCObject*) {
        ViraBotPopup::create()->show();
    }
};
