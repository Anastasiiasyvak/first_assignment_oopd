#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

class FileHandler {
public:
    static std::vector<std::string> readLines(const std::string& filename) {
        std::vector<std::string> lines;

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        file.close();
        return lines;
    }

    static bool writeLines(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file " + filename + " for writing");
        }

        for (const auto& line : lines) {
            file << line << '\n';
        }

        file.close();
        return true;
    }
};

class Airplane {
private:
    std::string date;
    std::string flightNumber;
    int numberOfSeats;
    std::vector<bool> seatAvailability;
    std::vector<std::pair<int, int>> seatPrices;

    void updateSeatAvailability(int seatNumber, bool status) {
        if (seatNumber > 0 && seatNumber <= numberOfSeats) {
            seatAvailability[seatNumber - 1] = status;
        } else {
            std::cout << "Invalid seat number." << std::endl;
        }
    }

    bool validateSeatForBooking(int seatNumber) const {
        // Add any additional validation logic here

        // Example: Check if the seat is in the first-class section (seats 1-10)
        if (seatNumber >= 1 && seatNumber <= 10) {
            std::cout << "Seat " << seatNumber << " is in the first-class section." << std::endl;
            return true;
        } else {
            std::cout << "Seat " << seatNumber << " is not valid for booking." << std::endl;
            return false;
        }
    }

public:
    Airplane(const std::string& date, const std::string& flightNumber, int seats)
            : date(date), flightNumber(flightNumber), numberOfSeats(seats), seatAvailability(seats, true) {}

    void setNumberOfSeats(int seats) {
        numberOfSeats = seats;
        seatAvailability.assign(seats, true);
    }

    void setSeatPrices(const std::vector<std::pair<int, int>>& prices) {
        seatPrices = prices;
    }

    bool checkSeatAvailability(int seatNumber) const {
        if (seatNumber > 0 && seatNumber <= numberOfSeats) {
            return seatAvailability[seatNumber - 1];
        } else {
            std::cout << "Invalid seat number." << std::endl;
            return false;
        }
    }

    bool bookSeat(int seatNumber) {
        if (checkSeatAvailability(seatNumber)) {
            try {
                if (validateSeatForBooking(seatNumber)) {
                    updateSeatAvailability(seatNumber, false);
                    std::cout << "Seat " << seatNumber << " booked successfully." << std::endl;
                    return true;
                } else {
                    std::cout << "Invalid seat for booking. Please choose another seat." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Seat " << seatNumber << " is not available." << std::endl;
        }
        return false;
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

    int getSeatPrice(int seatNumber) const {
        for (const auto& pair : seatPrices) {
            if (seatNumber >= pair.first && seatNumber <= pair.second) {
                return pair.second;
            }
        }
        return 0;
    }

    // Add getter methods for date and flight number
    std::string getDate() const {
        return date;
    }

    std::string getFlightNumber() const {
        return flightNumber;
    }
};

class ConfigReader {
public:
    static std::vector<Airplane> readConfig(const std::vector<std::string>& lines) {
        std::vector<Airplane> airplanes;

        for (const auto& line : lines) {
            std::stringstream ss(line);
            std::string date, flightNumber;
            int seats;
            ss >> date >> flightNumber >> seats;

            Airplane airplane(date, flightNumber, seats);

            std::vector<std::pair<int, int>> seatPrices;
            while (ss >> seats) {
                char dash;
                int price;
                ss >> dash >> price;
                seatPrices.emplace_back(seats, price);
            }

            airplane.setSeatPrices(seatPrices);
            airplanes.push_back(airplane);
        }

        return airplanes;
    }
};



/**
 * @brief A class representing a ticket with booking information.
 *
 * This class encapsulates ticket details, such as passenger name, seat
 * number, flight information, and booking status.
 */

class Ticket {
private:
    std::string passengerName;
    int seatNumber;
    std::string flightInformation;
    bool bookingStatus;

public:
    Ticket(const std::string& name, int seat, const std::string& flightInfo)
            : passengerName(name), seatNumber(seat), flightInformation(flightInfo), bookingStatus(true) {}

    int getSeatNumber() const {
        return seatNumber;
    }

    bool isBooked() const {
        return bookingStatus;
    }

    void cancelBooking() {
        if (bookingStatus) {
            bookingStatus = false;
            std::cout << "Booking canceled for seat " << seatNumber << "." << std::endl;
        } else {
            std::cout << "This ticket is not booked." << std::endl;
        }
    }

    void changePassengerName(const std::string& newName) {
        passengerName = newName;
        std::cout << "Passenger name changed to " << newName << "." << std::endl;
    }

    void viewTicketInfo() const {
        std::cout << "Passenger: " << passengerName << ", Seat: " << seatNumber
                  << ", Flight Information: " << flightInformation << ", Booking Status: " << (bookingStatus ? "Booked" : "Not Booked") << std::endl;
    }
};


/**
 * @brief A class representing an airline system with booking operations.
 *
 * This class encapsulates the interactions between airplanes, tickets, and
 * booking operations, providing a high-level interface for managing the
 * airline system.
 */


class AirlineSystem {
private:
    std::vector<Airplane> airplanes;
    std::vector<Ticket> bookedTickets;

public:
    AirlineSystem(const std::vector<Airplane>& airplanes) : airplanes(airplanes) {}

    void checkSeatAvailability(int airplaneIndex, int seatNumber) {
        if (airplaneIndex >= 0 && airplaneIndex < airplanes.size()) {
            const Airplane& airplane = airplanes[airplaneIndex];
            if (airplane.checkSeatAvailability(seatNumber)) {
                std::cout << "Seat " << seatNumber << " is available on this flight." << std::endl;
            } else {
                std::cout << "Seat " << seatNumber << " is not available on this flight." << std::endl;
            }
        } else {
            std::cout << "Invalid airplane index." << std::endl;
        }
    }

    void bookTicket(int airplaneIndex, const std::string& passengerName, int seatNumber) {
        if (airplaneIndex >= 0 && airplaneIndex < airplanes.size()) {
            Airplane& airplane = airplanes[airplaneIndex];
            if (airplane.bookSeat(seatNumber)) {
                Ticket ticket(passengerName, seatNumber, "Flight Info"); // You can replace "Flight Info" with actual flight information.
                bookedTickets.push_back(ticket);
            }
        } else {
            std::cout << "Invalid airplane index." << std::endl;
        }
    }

    void returnTicket(int ticketIndex) {
        if (ticketIndex >= 0 && ticketIndex < bookedTickets.size()) {
            Ticket& ticket = bookedTickets[ticketIndex];
            int seatNumber = ticket.isBooked() ? ticket.getSeatNumber() : -1;
            if (seatNumber != -1) {
                for (Airplane& airplane : airplanes) {
                    if (airplane.checkSeatAvailability(seatNumber)) {
                        airplane.bookSeat(seatNumber);
                        ticket.cancelBooking();
                        std::cout << "Ticket returned successfully." << std::endl;
                        return;
                    }
                }
            } else {
                std::cout << "Invalid seat number for the returned ticket." << std::endl;
            }
        } else {
            std::cout << "Invalid ticket index." << std::endl;
        }
    }

    void viewBookedTickets() const {
        std::cout << "Booked Tickets:" << std::endl;
        for (const Ticket& ticket : bookedTickets) {
            ticket.viewTicketInfo();
        }
    }
};



int main() {
    try {
        // Read configuration from file
        std::vector<std::string> fileLines = FileHandler::readLines("/home/nastia/CLionProjects/first_homework_oopd/Data.txt");
        std::vector<Airplane> airplanes = ConfigReader::readConfig(fileLines);
        // Initialize the airline system
        AirlineSystem airlineSystem(airplanes);

        // Command-line interface
        std::string choice;
        do {
            std::cout << "check. Check Flight Availability\n0. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == "check") {
                std::string date, flightNumber;
                std::cout << "Enter date and flight number: ";
                std::cin >> date >> flightNumber;

                // Знаходження відповідного літака
                int airplaneIndex = -1;
                for (int i = 0; i < airplanes.size(); ++i) {
                    if (airplanes[i].getDate() == date && airplanes[i].getFlightNumber() == flightNumber) {
                        airplaneIndex = i;
                        break;
                    }
                }

                if (airplaneIndex != -1) {
                    const Airplane& airplane = airplanes[airplaneIndex];
                    std::vector<int> availableSeats = airplane.getAvailableSeats();
                    std::cout << "Available Seats for Flight " << flightNumber << " on " << date << ":" << std::endl;
                    for (int seat : availableSeats) {
                        std::cout << seat << " " << airplane.getSeatPrice(seat) << "$, ";
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "Flight not found." << std::endl;
                }
            } else if (choice == "0") {
                std::cout << "Exiting the program.\n";
            } else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != "0");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}