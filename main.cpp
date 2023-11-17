#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Airplane {
private:
    int numberOfSeats;
    std::vector<bool> seatAvailability;
    std::vector<std::pair<int, int>> seatPrices;

public:
    Airplane(int seats) : numberOfSeats(seats), seatAvailability(seats, true) {}


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

    int getSeatPrice(int seatNumber) const {
        for (const auto& pair : seatPrices) {
            if (seatNumber >= pair.first && seatNumber <= pair.second) {
                return pair.second;
            }
        }
        return 0;
    }
};

class ConfigReader {
public:
    static std::vector<Airplane> readConfig(const std::string& filename) {
        std::vector<Airplane> airplanes;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return airplanes;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int seats;
            std::string date, flightNumber;
            ss >> date >> flightNumber >> seats;

            Airplane airplane(seats);

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

        file.close();
        return airplanes;
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


int main() {
    // Зчитування конфігурації з файлу
    std::vector<Airplane> airplanes = ConfigReader::readConfig("/home/nastia/CLionProjects/first_homework_oopd/Data.txt");

    // Виведення інформації про всі рейси
    for (const auto& airplane : airplanes) {
        airplane.viewAirplaneInfo();
        std::cout << std::endl;
    }

    return 0;
}