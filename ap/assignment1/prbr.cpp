#include <iostream>
#include <thread>

// ANSI escape codes for setting color (R, G, B values)
std::string color(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

void resetColor() {
    std::cout << "\033[0m"; // Reset color to default
}

void printProgressBar(int progress, int total) {
    int width = 50;  // Width of the progress bar
    int pos = (progress * width) / total;  // Position of the progress

    std::cout << "[";
    for (int i = 0; i < width; i++) {
        if (i < pos) {
            // Generate gradient color (tweaked for a smooth gradient effect)
            int red = static_cast<int>((1 - (i / static_cast<double>(width))) * 255);  // Red decreases
            int green = static_cast<int>((i / static_cast<double>(width)) * 255);  // Green increases
            std::cout << color(red, green, 0) << "=";
        } else {
            std::cout << " ";
        }
    }
    resetColor();
    std::cout << "] " << (progress * 100) / total << "%\r";
    std::cout.flush();  // Ensure the output is displayed in real time
}

int main() {
    int total = 100;

    for (int i = 0; i <= total; i++) {
        printProgressBar(i, total);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Delay to simulate progress
    }

    std::cout << std::endl; // Move to the next line after progress is complete
    return 0;
}

