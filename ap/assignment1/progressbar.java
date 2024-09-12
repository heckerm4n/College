public class GradientProgressBar {

    // ANSI escape codes for various colors (R,G,B values to simulate gradient)
    public static String color(int r, int g, int b) {
        return String.format("\u001B[38;2;%d;%d;%dm", r, g, b);
    }

    public static void resetColor() {
        System.out.print("\u001B[0m"); // Reset color to default
    }

    public static void printProgressBar(int progress, int total) {
        int width = 50;  // Width of the progress bar
        int pos = (int) ((progress / (double) total) * width);

        System.out.print("[");
        for (int i = 0; i < width; i++) {
            if (i < pos) {
                // Generate gradient color (You can tweak this formula to change the gradient)
                int red = (int) ((1 - (i / (double) width)) * 255);  // Red decreases
                int green = (int) ((i / (double) width) * 255);  // Green increases
                System.out.print(color(red, green, 0) + "=");
            } else {
                System.out.print(" ");
            }
        }
        resetColor();
        System.out.print("] " + (int) ((progress / (double) total) * 100) + "%\r");
    }

    public static void main(String[] args) throws InterruptedException {
        int total = 100;

        for (int i = 0; i <= total; i++) {
            printProgressBar(i, total);
            Thread.sleep(5);  // Delay to simulate progress
        }

        System.out.println(); // Move to the next line after progress is complete
    }
}

