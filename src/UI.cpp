#include <game/UI.hpp>

UI::UI() {
    GameEventSystem::on("ScoreIncrement", [=](GameEvent *ev){ 
        
    });
}

void UI::draw(RenderTarget& target, RenderStates states) const {

}