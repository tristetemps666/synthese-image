#include <corecrt_math.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

// float angle(glm::vec2 v1, glm::vec2 v2)
// {
//     return 1f;
// }

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};

    std::vector<p6::Center> list_rect_pos(100);
    std::vector<float>      list_mov_angle_dir(100);

    // set up randoms values
    for (unsigned int i = 0; i < 100; i++)
    {
        list_rect_pos[i]      = p6::Center{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1.)};
        list_mov_angle_dir[i] = p6::random::number(0.f, 360.f);
    }
    float speed = 1.f;

    ctx.maximize_window();

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        for (unsigned int i = 0; i < 100; i++)
        {
            //  update the position:
            list_rect_pos[i] = p6::Center{cos(list_mov_angle_dir[i]) * speed * ctx.delta_time() + list_rect_pos[i].value.x, sin(list_mov_angle_dir[i]) * speed * ctx.delta_time() + list_rect_pos[i].value.y};

            // update the direction
            // list_mov_angle_dir[i] =

            // draw the square
            ctx.square(
                p6::Center{list_rect_pos[i]},
                p6::Radius{0.2f}
            );
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}