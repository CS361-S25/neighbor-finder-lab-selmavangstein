#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/math.hpp"

emp::web::Document doc{"target"};

class NFAnimator : public emp::web::Animate {
    emp::web::Canvas canvas{500, 500, "canvas"};

    public: 
    int update;
    int square_size = 10;
    int y_squares = 10;
    int x_squares = 15;
     NFAnimator() {
        doc << canvas;
        doc << GetToggleButton("Toggle"); doc << GetStepButton("Step");
        //create a grid of 10x10 squares
        for (int i = 0; i < x_squares; ++i) {
            for (int j = 0; j < y_squares; ++j) {
                canvas.Rect(i * square_size, j * square_size, square_size, square_size, "white", "black");
            }
        }
        update = 0;
     }

     //method findNeighbors sets current cell to black and its neighbors to red
     void findNeighbors(int x, int y) {
        if (update>0){
            canvas.Rect(x * square_size, y * square_size, square_size, square_size, "black", "black");
        }
        if (emp::Mod(update, 2) == 1){
            //set neighbors to red. Use emp::Mod(x, y); to find wrapped neighbors as well
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) continue;
                    int nx = emp::Mod(x + i, x_squares);
                    int ny = emp::Mod(y + j, y_squares);
                    canvas.Rect(nx * square_size, ny * square_size, square_size, square_size, "red", "black");
                }
            }
        }
    }

    void DoFrame() override {
        canvas.Clear();
        for (int i = 0; i < x_squares; ++i) {
            for (int j = 0; j < y_squares; ++j) {
                canvas.Rect(i * square_size, j * square_size, square_size, square_size, "white", "black");
            }
        }
        findNeighbors(0,9);
        findNeighbors(4,2);

        update += 1;
    }
};

NFAnimator animator;

int main() {
    animator.Step();
}