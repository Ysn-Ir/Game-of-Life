#include "def.h"
using namespace def;
const int w = 800;
const int l = 600;
const float size = 10.f;

//creating grid class
class grid {
private:
	bool state;
	sf::RectangleShape box;
public:
	void setState() {
		if (this->state == 0)
			this->state = 1;
		else this->state = 0;
	}

	void setPos(sf::Vector2f pos) {
		this->box.setPosition(pos);
	}
	void setLife() {
		if (this->state == 0)
			this->box.setFillColor(sf::Color::White);
		else	
			this->box.setFillColor(sf::Color::Green);
	}
	bool getState() {
		return state;
	}
	sf::RectangleShape getBox() {
		return box;
	}
	grid() {
		state = 0;
		box = sf::RectangleShape(sf::Vector2f(size, size));
		box.setOutlineThickness(2.f);
		box.setOutlineColor(sf::Color::Black);
    }
};
//Global vector (easy access)
std::vector<std::vector<grid>> Grid(w/size, std::vector<grid>(l/size));
//update function
void updateLife() {
	std::vector<std::vector<bool>> nextState(w / size, std::vector<bool>(l / size));
	for (int i = 0; i < w / size; i++) {
		for (int j = 0; j < l / size; j++) {
			int count = 0;
			for (int k = -1; k < 2; k++) {
				for (int e = -1; e < 2; e++) {
					if (k == 0 && e == 0) continue; // Skip the current cell
					int ni = i + k, nj = j + e;
					// Check bounds
					if (ni >= 0 && ni < w / size && nj >= 0 && nj < l / size) {
						if (Grid[ni][nj].getState() == 1) {
							count++;
						}
					}
				}
			}
			if (Grid[i][j].getState() == 1) {
				
				nextState[i][j] = (count < 2 || count>3);

			}	
			else {
				nextState[i][j] = (count == 3);
			}
			
		}
	}
	// Update the grid states
	for (int i = 0; i < w / size; i++) {
		for (int j = 0; j < l / size; j++) {
			if (nextState[i][j]) {
				Grid[i][j].setState();
				Grid[i][j].setLife();
			}
		}
	}


}


int main() {

	sf::RenderWindow window(sf::VideoMode(w, l), "Game of Life", sf::Style::Default);
	
	// the grid vector
		//first crate instance of a grid then change it inside the loop
	grid Gbox;
	for (int i = 0; i < w / size; i++) {
		for (int j = 0; j < l / size; j++) {
			Gbox.setPos(sf::Vector2f(i *  size,j*size));
			Grid[i][j] = Gbox;
		}
	}



	//render loop
	while (window.isOpen()) {
		//poll events
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}
		//process
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			updateLife(); // Update on space key press
		}
		sf::Vector2i mpos = sf::Mouse::getPosition(window) / (int)size;
		std::cout << mpos.x << "    " << mpos.y << "\n";
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Grid[mpos.x][mpos.y].setState();
			Grid[mpos.x][mpos.y].setLife();
		}
		//render
		window.clear();
		for (int i = 0; i < w / size; i++) {
			for (int j = 0; j < l / size; j++) {
				window.draw(Grid[i][j].getBox());
			}
		}
		window.display();
	}
}