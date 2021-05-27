#include <iostream>
#include <cmath>

const long double M = 5.9736 * 1e24;
const long long int R = 6371000;
const long double G = 6.6743 * 1e-11;

class Rocket {
private:
    double x0;
    double y0;
    double alpha;
    double m;
    double fuel;
    double gasFlowRate;
    double fuelBurnRate;
public:

    explicit Rocket(double x0 = 0, double y0 = 0, double alpha = 0, double m = 0, double fuel = 0,
                    double gasFlowRate = 0, double fuelBurnRate = 0) : x0(x0), y0(y0), alpha(alpha), m(m),
                                                                       fuel(fuel), gasFlowRate(gasFlowRate),
                                                                       fuelBurnRate(fuelBurnRate) {};

    double xCoordinate(double t) {
        return x0 + t * t * (fuelBurnRate * gasFlowRate / (m + fuel - fuelBurnRate * t)) * cos(alpha) / 2;
    }

    double speedX(double t) {
        return fuelBurnRate * gasFlowRate / (m + fuel - fuelBurnRate * t) * cos(alpha) * t;
    }

    double speedModule(double t, double curG) {
        return fabs(((fuelBurnRate * gasFlowRate / (m + fuel - fuelBurnRate * t)) - curG * sin(alpha)));
    }

    double fuelMass(double t) {
        return fuel - fuelBurnRate * t;
    }
};

int main() {
    double x0, y0, alpha, m, fuel, gasFlowRate, fuelBurnRate;
    std::cin >> x0 >> y0 >> alpha >> m >> fuel >> gasFlowRate >> fuelBurnRate;
    Rocket r(x0, y0, alpha, m, fuel, gasFlowRate, fuelBurnRate);
    double t = 0;
    FILE *file = fopen("data.txt", "w");
    double curY = y0, curM, curFuel, curSpeedY;
    long double curG;
    while (true) {
        std::cout << "Current time: " << t << " seconds from the start.\n";
        curG = G * M / pow(R + curY, 2);
        curFuel = r.fuelMass(t);
        curM = m + curFuel;
        curY += ((fuelBurnRate * gasFlowRate / (curM)) * sin(alpha) - curG) / 2;
        curSpeedY = ((fuelBurnRate * gasFlowRate / (curM)) * sin(alpha) - curG) * t;
        std::cout << "Current x-axis coordinate: " << r.xCoordinate(t) << '\n';
        std::cout << "Current y-axis coordinate: " << curY << '\n';
        std::cout << "Current x-axis speed: " << r.speedX(t) << '\n';
        std::cout << "Current y-axis speed: " << curSpeedY << '\n';
        std::cout << "Current speed: " << r.speedModule(t, curG) << '\n';
        std::cout << "Current fuel mass: " << curFuel<< "\n\n";
        fprintf(file, "%f\t%f\n", r.xCoordinate(t), curY);
        if (curFuel == 0)
            break;
        t++;
    }
    fclose(file);
    return 0;
}
