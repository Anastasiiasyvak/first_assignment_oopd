//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <random>
//
//std::string generateRandomDate() {
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> year(2022, 2023);
//    std::uniform_int_distribution<> month(1, 12);
//    std::uniform_int_distribution<> day(1, 28);
//
//    std::stringstream date;
//    date << day(gen) << "." << month(gen) << "." << year(gen);
//    return date.str();
//}
//
//std::string generateFlightData(int i) {
//    std::stringstream data;
//    data << "Flight" << i + 1 << "\n";
//    data << generateRandomDate() << "\n";
//    data << "FL" << i + 1 << "H" << (rand() % 90 + 10) << "\n";
//    data << (rand() % 5 + 6) << "\n";
//
//    for (int j = 1; j < 20; j += 10) {
//        data << j << "-" << (j + 10) << " " << (rand() % 100 + 50) << "$ ";
//    }
//    data << "\n";
//
//    return data.str();
//}
//
//int main() {
//    srand(static_cast<unsigned int>(time(0)));
//
//    std::ofstream file("PlaneData.txt");
//    if (file.is_open()) {
//        for (int i = 0; i < 89; ++i) {
//            std::string flightData = generateFlightData(i);
//            file << flightData << "//\n";
//        }
//        file.close();
//        std::cout << "File created successfully." << std::endl;
//    } else {
//        std::cerr << "Unable to create file." << std::endl;
//    }
//
//    return 0;
//}

#include <iostream>
#include <vector>

class Airplane {
private:
    int numberOfSeats; // кількість місць
    std::vector<bool> seatAvailability; // статус місця, воно або зайняте або ні (true or false)

public:
    Airplane(int seats) : numberOfSeats(seats), seatAvailability(seats, true) {
        // Конструктор для ініціалізації кількості місць та доступності
    }

    bool checkSeatAvailability(int seatNumber) const { // перевіряється доступність місця
        if (seatNumber > 0 && seatNumber <= numberOfSeats) {
            return seatAvailability[seatNumber - 1];
        } else {
            std::cout << "Invalid seat number." << std::endl;
            return false;
        }
    }

    bool bookSeat(int seatNumber) { // забронювати місце
        if (checkSeatAvailability(seatNumber)) {
            seatAvailability[seatNumber - 1] = false;
            std::cout << "Seat " << seatNumber << " booked successfully." << std::endl;
            return true;
        } else {
            std::cout << "Seat " << seatNumber << " is not available." << std::endl;
            return false;
        }
    }


    void viewAirplaneInfo() const {
        std::cout << "Airplane Information: Total Seats: " << numberOfSeats << std::endl;
        std::cout << "Available Seats: ";
        for (int i = 0; i < numberOfSeats; ++i) {
            if (seatAvailability[i]) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;
    }

    std::vector<int> getAvailableSeats() const {
        std::vector<int> availableSeats;
        for (int i = 0; i < numberOfSeats; ++i) {
            if (seatAvailability[i]) {
                availableSeats.push_back(i + 1);
            }
        }
        return availableSeats;
    }
};



class Ticket {
private:
    std::string passengerName;
    int seatNumber;
    std::string flightInformation;
    bool bookingStatus;

public:
    Ticket(const std::string& name, int seat, const std::string& flightInfo)
            : passengerName(name), seatNumber(seat), flightInformation(flightInfo), bookingStatus(true) {
        // Конструктор для ініціалізації інформації про квиток
    }

    void viewTicketInfo() const {
        std::cout << "Passenger: " << passengerName << ", Seat: " << seatNumber
                << ", Flight Information: " << flightInformation << ", Booking Status: " << (bookingStatus ? "Booked" : "Not Booked") << std::endl;
    }

    void cancelBooking() { // відмінити броню
        if (bookingStatus) {
            bookingStatus = false;
            std::cout << "Booking canceled for seat " << seatNumber << "." << std::endl;
        } else {
            std::cout << "This ticket is not booked." << std::endl;
        }
    }

    bool isBooked() const { // перевіряє чи воно заброньоване
        return bookingStatus;
    }

    void changePassengerName(const std::string& newName) {
        passengerName = newName;
        std::cout << "Passenger name changed to " << newName << "." << std::endl;
    }
};
