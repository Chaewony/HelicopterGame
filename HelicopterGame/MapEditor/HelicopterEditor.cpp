#include "HelicopterEditor.h"

void HelicopterEditor::update() {
    internalRemove();
    internalRender(Position::zeros, false);
    internalUpdate();
}