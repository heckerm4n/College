import java.util.*;

public class CourseTable {

    // ANSI color codes
    public static final String RESET = "\u001B[0m";  // Resets the color
    public static final String BLUE = "\u001B[34m";  // Blue color

    // Function to print a formatted table for courses with alternating color
    public static void printCourseTable(String[][] courses) {
        // Print header in default color
        // Print course details
        System.out.printf("%-1s %-10s %-1s %-40s %-1s %-30s %-1s %-10s %-1s %-25s\n","|", "Code","|", "Course Name","|", "Class Type","|", "Credits","|", "Registration Type");
        System.out.println("--------------------------------------------------------------------------------------------------------------------------");

        // Print each row of the table, alternating colors for rows
        for (int i = 0; i < courses.length; i++) {
            String[] course = courses[i];

            // Apply blue color for even-indexed rows
            if (i % 2 == 0) {
                System.out.print(BLUE);
            }

            // Print course details
            System.out.printf("%-1s %-10s %-1s %-40s %-1s %-30s %-1s %-10s %-1s %-25s\n","|" ,course[0], "|",course[1],"|", course[2],"|", course[3],"|", course[4]);

            // Reset color for next line
            System.out.print(RESET);
        }
    }

    public static void main(String[] args) {
        // Define courses (Code, Name, Class Type, Credits, Registration Type)
        String[][] courses = {
            {"CSE201", "Advanced Programming", "Lecture-Tutorial-Lab", "4", "Mandatory (Core Elective)"},
            {"ECE215", "Circuit Theory and Devices", "Lecture-Tutorial-Lab", "4", "Mandatory (Core)"},
            {"ECE250", "Signals & Systems", "Lecture", "4", "Mandatory (Core)"}
        };

        // Call the function to print the table
        printCourseTable(courses);
    }
}


