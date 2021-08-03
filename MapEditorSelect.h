#include "StateScreen.h"
#include "BeatMapEditor.h"
class MapEditorSelect : public StateScreen
{
private:
	Text text;
	Font font;
	BeatMapEditor*& mapEditor;
public:
	MapEditorSelect(BeatMapEditor*& mapEditor);
	~MapEditorSelect();

	// StateScreen functions
	//****************************************************
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(RenderWindow& window);
};

