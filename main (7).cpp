#include <iostream>
#include <cmath>

const double g = 9.81;

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

    double yCoordinate(double t) {
        return y0 + t * t * ((fuelBurnRate * gasFlowRate / (m + fuel - fuelBurnRate * t)) * sin(alpha) - g) / 2;
    }

    double speedX(double t) {
        return fuelBurnRate * gasFlowRate / (m + fuel - fuelBurnRate * t) * cos(alpha) * t;
    }

    double speedY(double t) {
        return ((fuelBurnRate * gasFlowRate / (m + fuel - fuelBurnRate * t)) * sin(alpha) - g) * t;
    }

    double speedModule(double t) {
        return fabs(((fuelBurnRate * gasFlowRate / (m + fuel - fuelBurnRate * t)) - g) * t);
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
    while (true) {
        std::cout << "Current time: " << t << " seconds from the start.\n";
        std::cout << "Current x-axis coordinate: " << r.xCoordinate(t) << '\n';
        std::cout << "Current y-axis coordinate: " << r.yCoordinate(t) << '\n';
        std::cout << "Current x-axis speed: " << r.speedX(t) << '\n';
        std::cout << "Current y-axis speed: " << r.speedY(t) << '\n';
        std::cout << "Current speed: " << r.speedModule(t) << '\n';
        std::cout << "Current fuel mass: " << r.fuelMass(t) << "\n\n";
        fprintf(file, "%f\t%f\n", r.xCoordinate(t), r.yCoordinate(t));
        if (r.fuelMass(t) == 0)
            break;
        t++;
    }
    fclose(file);
    return 0;
}
