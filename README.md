# Hospital-Management-System-OOP
This is my Object oriented programming project which uses fstream, sstream, string and vector libraries for efficient file handling, string parsing and data handling.
<br>
Functionalities:
<br>
Logs in patients by matching their ID and passwords from file
<br>
Filters doctors by speciality,can further filter these by name or fee
<br>
Updates Room status/Medicine quantity/AppointmentNo. on use
<br>
Deducts balance on booking appointment/reserving room/purchasing medicine
<br>
View medicines and rooms
<br>
Throws exceptions in case of room already booked/insufficient funds
<br>
The csv files have info in the following order;
docFile.csv: ID,Name,Speciality,Timing,Fee,No.of appointments
medicines.csv: ID,Name,Price,Quantity
patients.csv: ID,Name,Password,Age,Height,Weight,Bloodtype,Balance
rooms.csv: ID,Roomtype,AvailiblityStatus,Rentfee
<br>
Enter ID/Password exactly as in file and ensure there are no spaces/spelling/case differences. Hope you like it!