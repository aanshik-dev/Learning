import java.util.Scanner;

class InvalidRegistrationNumberException extends Exception {
  public InvalidRegistrationNumberException(String message) {
    super(message);
  }
}

class InvalidContactNumberException extends Exception {
  public InvalidContactNumberException(String message) {
    super(message);
  }
}

class InvalidPINException extends Exception {
  public InvalidPINException(String message) {
    super(message);
  }
}

class InvalidChassisNumberException extends RuntimeException {
  public InvalidChassisNumberException(String message) {
    super(message);
  }
}

class InvalidEngineNumberException extends RuntimeException {
  public InvalidEngineNumberException(String message) {
    super(message);
  }
}

class Vehicle {
  String registrationNumber;
  String ownerName;
  String contactNumber;
  String addressPIN;

  public Vehicle(String registrationNumber, String ownerName, String contactNumber, String addressPIN) {
    this.registrationNumber = registrationNumber;
    this.ownerName = ownerName;
    this.contactNumber = contactNumber;
    this.addressPIN = addressPIN;
  }

  public void validate() throws InvalidRegistrationNumberException, InvalidContactNumberException, InvalidPINException,
      InvalidChassisNumberException, InvalidEngineNumberException {
    if (!registrationNumber.matches("^[A-Z]{2}[0-9]{2} [0-9]{4}$")) {
      throw new InvalidRegistrationNumberException("Invalid Registration Number");
    }
    if (!contactNumber.matches("^[6-9][0-9]{9}$")) {
      throw new InvalidContactNumberException("Invalid Contact Number");
    }
    if (!addressPIN.matches("^[0-9]{6}$")) {
      throw new InvalidPINException("Invalid PIN Code");
    }
  }
}

class Car extends Vehicle {
  String carModel;
  String chassisNumber;

  public Car(String registrationNumber, String ownerName, String contactNumber, String addressPIN, String carModel,
      String chassisNumber) throws InvalidRegistrationNumberException, InvalidContactNumberException,
      InvalidPINException, InvalidChassisNumberException, InvalidEngineNumberException {
    super(registrationNumber, ownerName, contactNumber, addressPIN);
    this.carModel = carModel;
    this.chassisNumber = chassisNumber;
    validate();
  }

  @Override
  public void validate() throws InvalidRegistrationNumberException, InvalidContactNumberException, InvalidPINException,
      InvalidChassisNumberException, InvalidEngineNumberException {
    super.validate();
    if (!chassisNumber.matches("^CAR[0-9]{5}$")) {
      throw new InvalidChassisNumberException("Invalid Chassis Number");
    }
    System.out.println("Car Registered Successfully !!\n");
    display();
    System.out.println("\n");
  }

  public void display() {
    System.out.println("Registration Number: " + registrationNumber);
    System.out.println("Owner Name: " + ownerName);
    System.out.println("Contact Number: " + contactNumber);
    System.out.println("Address PIN: " + addressPIN);
    System.out.println("Car Model: " + carModel);
    System.out.println("Chassis Number: " + chassisNumber);
  }
}

class Bike extends Vehicle {
  String bikeModel;
  String engineNumber;

  public Bike(String registrationNumber, String ownerName, String contactNumber, String addressPIN, String bikeModel,
      String engineNumber)
      throws InvalidRegistrationNumberException, InvalidContactNumberException, InvalidPINException,
      InvalidChassisNumberException, InvalidEngineNumberException {
    super(registrationNumber, ownerName, contactNumber, addressPIN);
    this.bikeModel = bikeModel;
    this.engineNumber = engineNumber;
    validate();
  }

  @Override
  public void validate() throws InvalidRegistrationNumberException, InvalidContactNumberException, InvalidPINException,
      InvalidChassisNumberException, InvalidEngineNumberException {
    super.validate();
    if (!engineNumber.matches("^BIKE[0-9]{4}$")) {
      throw new InvalidEngineNumberException("Invalid Engine Number");
    }
    System.out.println("Bike Registered Successfully !!\n");
    display();
    System.out.println("\n");
  }

  public void display() {
    System.out.println("Registration Number: " + registrationNumber);
    System.out.println("Owner Name: " + ownerName);
    System.out.println("Contact Number: " + contactNumber);
    System.out.println("Address PIN: " + addressPIN);
    System.out.println("Bike Model: " + bikeModel);
    System.out.println("Engine Number: " + engineNumber);
  }
}

public class VehicleSys {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter the type of vehicle: ");
    String type = sc.nextLine().toLowerCase();
    System.out.print("Enter vehicle Registration Number: ");
    String registrationNumber = sc.nextLine();
    System.out.print("Enter vehicle Owner Name: ");
    String ownerName = sc.nextLine();
    System.out.print("Enter vehicle Contact Number: ");
    String contactNumber = sc.nextLine();
    System.out.print("Enter vehicle Address PIN: ");
    String addressPIN = sc.nextLine();
    try {
      if (type.equals("car")) {
        System.out.print("Enter Car Model: ");
        String carModel = sc.nextLine();
        System.out.print("Enter Chassis Number: ");
        String chassisNumber = sc.nextLine();
        Car car = new Car(registrationNumber, ownerName, contactNumber, addressPIN, carModel, chassisNumber);
      } else if (type.equals("bike")) {
        System.out.print("Enter Bike Model: ");
        String bikeModel = sc.nextLine();
        System.out.print("Enter Engine Number: ");
        String engineNumber = sc.nextLine();
        Bike bike = new Bike(registrationNumber, ownerName, contactNumber, addressPIN, bikeModel, engineNumber);
      } else {
        System.out.println("Invalid vehicle type !!");
      }
    } catch (Exception e) {
      System.out.println(e.getMessage());
    }
    sc.close();
  }
}
