# ideas for 1st assignment

- colors
- loading bar
- like installation script(possible to call a python file)
- print table for grades -|:
- after doing al the task return to main menue

## Java Code Example for colors and table:

```java
import java.util.*;

public class CourseTable {

    // ANSI color codes
    public static final String RESET = "\u001B[0m";  // Resets the color
    public static final String BLUE = "\u001B[34m";  // Blue color

    // Function to print a formatted table for courses with alternating color
    public static void printCourseTable(String[][] courses) {
        // Print header in default color
        System.out.printf("%-10s %-40s %-30s %-10s %-25s\n", "Code", "Course Name", "Class Type", "Credits", "Registration Type");
        System.out.println("--------------------------------------------------------------------------------------------------------------");

        // Print each row of the table, alternating colors for rows
        for (int i = 0; i < courses.length; i++) {
            String[] course = courses[i];

            // Apply blue color for even-indexed rows
            if (i % 2 == 0) {
                System.out.print(BLUE);
            }

            // Print course details
            System.out.printf("%-10s %-40s %-30s %-10s %-25s\n", course[0], course[1], course[2], course[3], course[4]);

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



```

### Output:

```
Code       Course Name                             Class Type                     Credits    Registration Type      
---------------------------------------------------------------------------------------------------------
CSE201     Advanced Programming                    Lecture-Tutorial-Lab            4          Mandatory (Core Elective)
ECE215     Circuit Theory and Devices              Lecture-Tutorial-Lab            4          Mandatory (Core)        
ECE250     Signals & Systems                       Lecture                         4          Mandatory (Core)        
```

--- Explanation:
- The `printCourseTable` method prints each course's details in a formatted table.
- **`%-10s`**: Reserves 10 spaces for the course code, left-aligned.
- **`%-40s`**: Reserves 40 spaces for the course name.
- **`%-30s`**: Reserves 30 spaces for the class type.
- **`%-10s`**: Reserves 10 spaces for the credits.
- **`%-20s`**: Reserves 20 spaces for the registration type.

## example with main menue


``` java
import java.util.Scanner;

public class MainMenuExample {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;  // To track whether to exit the menu or not

        while (!exit) {
            // Display main menu
            System.out.println("Main Menu:");
            System.out.println("1. Option 1");
            System.out.println("2. Option 2");
            System.out.println("3. Option 3");
            System.out.println("4. Exit");
            System.out.print("Please choose an option: ");

            int choice = scanner.nextInt();  // Read user input

            // Switch case to handle different options
            switch (choice) {
                case 1:
                    System.out.println("You selected Option 1.");
                    // Add your code for Option 1 here
                    break;
                case 2:
                    System.out.println("You selected Option 2.");
                    // Add your code for Option 2 here
                    break;
                case 3:
                    System.out.println("You selected Option 3.");
                    // Add your code for Option 3 here
                    break;
                case 4:
                    System.out.println("Exiting the program...");
                    exit = true;  // Set to true to exit the loop
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
                    break;
            }

            System.out.println();  // Print a blank line for readability
        }

        scanner.close();  // Close the scanner when done
    }
}


```


