/*! @file
 *  @brief Entry point of the Demo Application
 *  @author Roman Golovanov
 *  @date 23 March 2016
 */

#include <iostream>
#include <filesystem>

#include <opencv2/highgui.hpp>

#include "idemo.hpp"

int main(int argc, char** argv)
{
    // Default directory with images relative to executable.
    std::filesystem::path resource_dir = "../image";
    if (argc > 1)
        resource_dir = argv[1];

    auto& reg = idemo::get_global_registry();

    std::cout << "Demo Application contains " << reg.size() << " demos:\n";
    unsigned int idx = 0;
    for (auto item : reg)
        std::cout << idx++ << ") " << item->to_string() << "\n";

    std::cout << "Please enter index of the demo to run: ";
    std::cin >> idx;

    auto demo = reg.at(idx);

    demo->prepare(resource_dir);

    std::cout << "Press Enter or Spacebar to apply parameters. Press Esc to exit...\n";
    do
    {
        demo->execute_opencv();
        demo->execute_openvx();
        demo->make_diff();
    } while (cv::waitKey(0) != 27);

    return 0;
}
