#include <iostream>


using namespace std;

class WrongMaxSpeedException : public invalid_argument {
    int value;
public:
    WrongMaxSpeedException(const int& value, const string& message) : invalid_argument(message), value{value} {}
    
    int getValue() const {
        return value;
    }
};

class WrongSpeedException : public invalid_argument {
    int value;
public:
    WrongSpeedException(const int& value, const string& message) : invalid_argument(message), value{ value } {}
    int getValue() const {
        return value;
    }
};

class InvalidNumberException : public invalid_argument {
    string value;
public:
    InvalidNumberException(const string& value, const string& message) : invalid_argument(message), value{ value } {}
    string getValue() const {
        return value;
    }
};

class Auto {
private:
    string number_plate;
    int max_speed;
    int current_speed;

public:
    Auto(const string& plate, const int& current_speed, const int& max_speed = 360) : number_plate(validateNumberPlate(plate)), current_speed(current_speed), max_speed(max_speed) {
        if (current_speed > max_speed) {
            throw WrongMaxSpeedException(current_speed, "Maximum speed cannot be greater than 360");
        }
    }

    string getNumberPlate() const {
        return number_plate;
    }

    void setNumberPlate(const string& plate) {
        number_plate = validateNumberPlate(plate);
    }

    int getMaxSpeed() const {
        return max_speed;
    }

    void setMaxSpeed(int speed) {
        if (speed > 360) {
            throw WrongMaxSpeedException(speed, "Maximum speed cannot be greater than 360");
        } 
        max_speed = speed;
    }

    int getCurrentSpeed() const {
        return current_speed;
    }

    void setCurrentSpeed(int speed) {
        if (0 <= speed && speed <= max_speed) {
            current_speed = speed;
        }
        else {
            throw WrongSpeedException(speed, "Invalid speed");
        }
    }

    void accelerate(int increment = 5) {
        int new_speed = current_speed + increment;
        if (new_speed <= max_speed) {
            current_speed = new_speed;
        }
        else {
            throw WrongSpeedException(new_speed, "Exceeded maximum speed");
        }
    }

    void decelerate(int decrement = 5) {
        int new_speed = current_speed - decrement;
        if (new_speed >= 0) {
            current_speed = new_speed;
        }
        else {
            throw WrongSpeedException(new_speed, "Speed cannot be negative");
        }
    }

private:
    string validateNumberPlate(const string& plate) {
        if (plate.length() == 8 && isalpha(plate[0]) && isalpha(plate[1]) &&
            isdigit(plate[2]) && isdigit(plate[3]) &&
            isdigit(plate[4]) && isdigit(plate[5]) &&
            isalpha(plate[6]) && isalpha(plate[7])) {
            return plate;
        }
        else {
            throw InvalidNumberException(plate, "Invalid auto number format");
        }
    }
};

int main() {
    try {
        Auto auto1("AB1234CD", 200);
        auto1.setMaxSpeed(380);
        cout << "Maximum speed: " << auto1.getMaxSpeed() << endl;

        //auto1.accelerate(250);
        //cout << "Current speed after acceleration: " << auto1.getCurrentSpeed() << endl;

        //auto1.setNumberPlate("XYg678ZW");
        //cout << "New auto number: " << auto1.getNumberPlate() << endl;

        auto1.decelerate(500);
        cout << "Current speed after deceleration: " << auto1.getCurrentSpeed() << endl;

    }
    catch (const WrongMaxSpeedException& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "Value: " << e.getValue() << endl;
    }
    catch (const WrongSpeedException& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "Value: " << e.getValue() << endl;
    }
    catch (const InvalidNumberException& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "Value: " << e.getValue() << endl;
    }
    catch (const exception& e) {
        cerr << "Unknown error: " << e.what() << endl;
    }

}

