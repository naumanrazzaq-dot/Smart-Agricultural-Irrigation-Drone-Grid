#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class AgriculturalUnit {
protected:
    string unitCode;
    bool operational;

public:
    static int activeUnitsCount;

    AgriculturalUnit(string code) : unitCode(code), operational(true) {
        activeUnitsCount++;
    }

    virtual ~AgriculturalUnit() {
        activeUnitsCount--;
    }

    virtual void generateFieldReport() = 0;
};

int AgriculturalUnit::activeUnitsCount = 0;

class SoilSensorModule : virtual public AgriculturalUnit {
protected:
    double moistureLevelPct;

public:
    SoilSensorModule(string code, double moisture) : AgriculturalUnit(code), moistureLevelPct(moisture) {}

    void checkSoil() {
        cout << "Soil sensor [" << unitCode << "] moisture level: " << moistureLevelPct << "%." << endl;
    }
};

class IrrigationSprayerModule : virtual public AgriculturalUnit {
protected:
    double waterTankLevelLiters;

public:
    IrrigationSprayerModule(string code, double tank) : AgriculturalUnit(code), waterTankLevelLiters(tank) {}

    void checkSprayer() {
        cout << "Irrigation sprayer [" << unitCode << "] tank reserve: " << waterTankLevelLiters << "L." << endl;
    }
};

class SmartCropDrone : public SoilSensorModule, public IrrigationSprayerModule {
private:
    double areaCoveredHectares;

public:
    SmartCropDrone(string code, double moisture, double tank, double area)
        : AgriculturalUnit(code),
          SoilSensorModule(code, moisture),
          IrrigationSprayerModule(code, tank),
          areaCoveredHectares(area) {}

    ~SmartCropDrone() {
        cout << "Crop drone " << unitCode << " returned to station and docked." << endl;
    }

    void generateFieldReport() override {
        cout << "\n--- Smart Crop Drone Field Report: " << unitCode << " ---" << endl;
        checkSoil();
        checkSprayer();
        cout << "Area Covered Today: " << areaCoveredHectares << " Hectares" << endl;
        cout << "System Status: Optimal" << endl;
    }
};

int main() {
    AgriculturalUnit* drone = new SmartCropDrone("AGRI-DRONE-07", 42.5, 150.0, 12.4);

    drone->generateFieldReport();

    cout << "\nActive Agricultural Units: " << AgriculturalUnit::activeUnitsCount << endl;

    delete drone;

    cout << "Active Units After Docking: " << AgriculturalUnit::activeUnitsCount << endl;

    return 0;
}
