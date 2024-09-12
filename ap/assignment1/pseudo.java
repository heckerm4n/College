// Abstract class representing a general user
public abstract class User {
    private String userID;
    private String name;
    private String email;
    private String password;

    // Constructor
    public User(String userID, String name, String email, String password) {
        this.userID = userID;
        this.name = name;
        this.email = email;
        this.password = password;
    }

    // Encapsulated getters and setters
    public String getUserID() { return userID; }
    public void setUserID(String userID) { this.userID = userID; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }

    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }

    // Abstract methods to be implemented by subclasses
    public abstract void login();
    public abstract void viewProfile();
}

// Interface for managing courses
public interface CourseManagement {
    void manageCourses();
}

// Interface for handling complaints
public interface ComplaintHandling {
    void handleComplaint();
}

// Student class inheriting from User
import java.util.List;

public class Student extends User {
    private String studentID;
    private int semester;
    private int credits;
    private List<Course> coursesEnrolled;
    private List<Complaint> complaints;

    // Constructor
    public Student(String userID, String name, String email, String password,
                   String studentID, int semester, int credits) {
        super(userID, name, email, password);
        this.studentID = studentID;
        this.semester = semester;
        this.credits = credits;
        // Initialize lists as needed
    }

    // Getters and setters
    public String getStudentID() { return studentID; }
    public void setStudentID(String studentID) { this.studentID = studentID; }

    public int getSemester() { return semester; }
    public void setSemester(int semester) { this.semester = semester; }

    public int getCredits() { return credits; }
    public void setCredits(int credits) { this.credits = credits; }

    public List<Course> getCoursesEnrolled() { return coursesEnrolled; }
    public void setCoursesEnrolled(List<Course> coursesEnrolled) { this.coursesEnrolled = coursesEnrolled; }

    public List<Complaint> getComplaints() { return complaints; }
    public void setComplaints(List<Complaint> complaints) { this.complaints = complaints; }

    // Implement abstract methods
    @Override
    public void login() {
        // Student login implementation
    }

    @Override
    public void viewProfile() {
        // View student profile implementation
    }

    // Student specific methods
    public void viewAvailableCourses() { /* Implementation */ }
    public void registerForCourses() { /* Implementation */ }
    public void viewSchedule() { /* Implementation */ }
    public void trackAcademicProgress() { /* Implementation */ }
    public void dropCourse() { /* Implementation */ }
    public void submitComplaint() { /* Implementation */ }
}

// Professor class inheriting from User and implementing CourseManagement
import java.util.List;

public class Professor extends User implements CourseManagement {
    private String professorID;
    private List<Course> coursesTaught;

    // Constructor
    public Professor(String userID, String name, String email, String password,
                     String professorID) {
        super(userID, name, email, password);
        this.professorID = professorID;
    }

    // Getters and setters
    public String getProfessorID() { return professorID; }
    public void setProfessorID(String professorID) { this.professorID = professorID; }

    public List<Course> getCoursesTaught() { return coursesTaught; }
    public void setCoursesTaught(List<Course> coursesTaught) { this.coursesTaught = coursesTaught; }

    // Implement abstract methods
    @Override
    public void login() {
        // Professor login implementation
    }

    @Override
    public void viewProfile() {
        // View professor profile implementation
    }

    // Implement interface method
    @Override
    public void manageCourses() {
        // Manage courses implementation
    }

    // Professor specific method
    public void viewEnrolledStudents() { /* Implementation */ }
}

// Admin class inheriting from User and implementing CourseManagement and ComplaintHandling
import java.util.List;

public class Admin extends User implements CourseManagement, ComplaintHandling {
    private String adminID;

    // Constructor
    public Admin(String userID, String name, String email, String password, String adminID) {
        super(userID, name, email, password);
        this.adminID = adminID;
    }

    // Getters and setters
    public String getAdminID() { return adminID; }
    public void setAdminID(String adminID) { this.adminID = adminID; }

    // Implement abstract methods
    @Override
    public void login() {
        // Admin login implementation
    }

    @Override
    public void viewProfile() {
        // View admin profile implementation
    }

    // Implement interface methods
    @Override
    public void manageCourses() {
        // Admin manages course catalog (add/delete courses)
    }

    @Override
    public void handleComplaint() {
        // Admin handles complaints
    }

    // Admin specific methods
    public void manageCourseCatalog() { /* Implementation */ }
    public void manageStudentRecords() { /* Implementation */ }
    public void assignProfessorsToCourses() { /* Implementation */ }
    public void handleComplaints() { /* Implementation */ }
}

// Course class
import java.util.List;

public class Course {
    private String courseCode;
    private String title;
    private Professor professor;
    private int credits;
    private List<Course> prerequisites;
    private String timings;
    private List<Student> enrolledStudents;

    // Constructor
    public Course(String courseCode, String title, Professor professor, int credits,
                  List<Course> prerequisites, String timings) {
        this.courseCode = courseCode;
        this.title = title;
        this.professor = professor;
        this.credits = credits;
        this.prerequisites = prerequisites;
        this.timings = timings;
    }

    // Getters and setters
    public String getCourseCode() { return courseCode; }
    public void setCourseCode(String courseCode) { this.courseCode = courseCode; }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public Professor getProfessor() { return professor; }
    public void setProfessor(Professor professor) { this.professor = professor; }

    public int getCredits() { return credits; }
    public void setCredits(int credits) { this.credits = credits; }

    public List<Course> getPrerequisites() { return prerequisites; }
    public void setPrerequisites(List<Course> prerequisites) { this.prerequisites = prerequisites; }

    public String getTimings() { return timings; }
    public void setTimings(String timings) { this.timings = timings; }

    public List<Student> getEnrolledStudents() { return enrolledStudents; }
    public void setEnrolledStudents(List<Student> enrolledStudents) { this.enrolledStudents = enrolledStudents; }

    // Course specific methods
    public void updateCourseDetails() { /* Implementation */ }
    public void checkEnrollmentLimit() { /* Implementation */ }
}

// Complaint class
public class Complaint {
    private String complaintID;
    private String description;
    private String status; // Pending, Resolved

    // Constructor
    public Complaint(String complaintID, String description, String status) {
        this.complaintID = complaintID;
        this.description = description;
        this.status = status;
    }

    // Getters and setters
    public String getComplaintID() { return complaintID; }
    public void setComplaintID(String complaintID) { this.complaintID = complaintID; }

    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

    public String getStatus() { return status; }
    public void setStatus(String status) { this.status = status; }

    // Method to update status
    public void updateStatus(String newStatus) {
        this.status = newStatus;
    }
}

// RegistrationSystem class (Singleton)
import java.util.List;

public class RegistrationSystem {
    private static RegistrationSystem instance = null;

    private List<User> users;
    private List<Course> courses;
    private List<Complaint> complaints;

    // Private constructor to enforce singleton pattern
    private RegistrationSystem() { 
        // Initialize lists
    }

    // Public method to get the singleton instance
    public static RegistrationSystem getInstance() {
        if (instance == null) {
            instance = new RegistrationSystem();
        }
        return instance;
    }

    // Getters and setters
    public List<User> getUsers() { return users; }
    public void setUsers(List<User> users) { this.users = users; }

    public List<Course> getCourses() { return courses; }
    public void setCourses(List<Course> courses) { this.courses = courses; }

    public List<Complaint> getComplaints() { return complaints; }
    public void setComplaints(List<Complaint> complaints) { this.complaints = complaints; }

    // System methods
    public User authenticateUser(String email, String password) { 
        // Authentication logic
        return null;
    }
    
    public void manageCourses() { /* Implementation */ }
    public void manageComplaints() { /* Implementation */ }
}

