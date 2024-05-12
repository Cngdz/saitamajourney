//#include "graphics.h"
//#include "characters.h"
//#include "defs.h"
//
//
//using namespace std;
// vector<vector<int>> positions;
//    void update(int time) {
//        int now = SDL_GetTicks();
//        static int last = now;
//        if (now - last >= time) {
//            last = now;
//            positions.push_back({801, 395}); // Thêm một con slime mới tại vị trí (801, 395)
//        }
//
//        for (auto& position : positions) {
//            position[0] -= 10; // Di chuyển con slime sang trái
//        }
//
//        positions.erase(std::remove_if(positions.begin(), positions.end(), [](const vector<int>& position) {
//            return position[0] < -32; // Loại bỏ con slime nếu đã đi qua khỏi màn hình
//        }), positions.end());
//    }
//
//    void ve(Graphics& graphic , Threats& threat) {
//        for (const auto& position : positions) {
//            graphic.render3(position[0], position[1], threat); // Vẽ con slime lên màn hình
//        }
//    }
