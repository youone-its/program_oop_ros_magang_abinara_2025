#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Vehicle {
private:
    string licensePlate;
    string make;
    string model;
    int year;

public:
    Vehicle(const string& licensePlate, const string& make, 
            const string& model, int year)
        : licensePlate(licensePlate), make(make), model(model), year(year) {}
    
    string getLicensePlate() const { return licensePlate; }
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    
    void setMake(const string& make) { this->make = make; }
    void setModel(const string& model) { this->model = model; }
    void setYear(int year) { this->year = year; }
    
    void display() const {
        cout << "License: " << licensePlate << ", " << year << " " 
                  << make << " " << model << endl;
    }
};

class VehicleManager {
private:
    vector<Vehicle> vehicles;
    
public:
    void registerVehicle(const string& licensePlate, const string& make,
                        const string& model, int year) {
        vehicles.emplace_back(licensePlate, make, model, year);
        cout << "Vehicle registered successfully!\n";
    }
    
    void displayAllVehicles() const {
        if (vehicles.empty()) {
            cout << "No vehicles registered.\n";
            return;
        }
        for (const auto& vehicle : vehicles) {
            vehicle.display();
        }
    }
    
    Vehicle* findVehicle(const string& licensePlate) {
        auto it = find_if(vehicles.begin(), vehicles.end(),
            [&licensePlate](const Vehicle& v) { return v.getLicensePlate() == licensePlate; });
        return (it != vehicles.end()) ? &(*it) : nullptr;
    }
    
    bool updateVehicle(const string& licensePlate, const string& make,
                      const string& model, int year) {
        Vehicle* vehicle = findVehicle(licensePlate);
        if (vehicle) {
            vehicle->setMake(make);
            vehicle->setModel(model);
            vehicle->setYear(year);
            cout << "Vehicle updated successfully!\n";
            return true;
        }
        cout << "Vehicle not found!\n";
        return false;
    }
    
    bool unregisterVehicle(const string& licensePlate) {
        auto it = find_if(vehicles.begin(), vehicles.end(),
            [&licensePlate](const Vehicle& v) { return v.getLicensePlate() == licensePlate; });
        if (it != vehicles.end()) {
            vehicles.erase(it);
            cout << "Vehicle unregistered successfully!\n";
            return true;
        }
        cout << "Vehicle not found!\n";
        return false;
    }
};

int main() {
    VehicleManager vm;
    vm.registerVehicle("ABC123", "Toyota", "Camry", 2020);
    vm.registerVehicle("XYZ789", "Honda", "Civic", 2019);
    vm.displayAllVehicles();
    vm.updateVehicle("ABC123", "Toyota", "Corolla", 2021);
    vm.unregisterVehicle("XYZ789");
    vm.displayAllVehicles();
    return 0;
}