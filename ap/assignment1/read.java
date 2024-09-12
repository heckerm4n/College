import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ReadCourseDataSimpleSplit {
    public static void main(String[] args) {
        List<String[]> courses = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader("courselist.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                // Simply split by commas
                String[] courseDetails = line.split(",");
                courses.add(courseDetails);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Printing the 2D array (list of arrays)
        for (String[] course : courses) {
            System.out.println("Course Code: " + course[0]);
            System.out.println("Course Name: " + course[1]);
            System.out.println("Lecture-Tutorial-Lab: " + course[2]);
            System.out.println("Credits: " + course[3]);
            System.out.println("Type: " + course[4]);
            System.out.println();
        }
    }
}

