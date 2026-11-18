#include <iostream>
#include "simulador.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    // Caja rectangular de 100 x 100 unidades con paso discreto dt = 0.01 s
    Simulador sim(100.0, 100.0, 0.01);

    // 4 obstaculos cuadrados estaticos con coeficiente de restitucion e = 0.8
    sim.agregarObstaculo(Obstaculo(1, Vector2D(30.0, 30.0), 10.0, 0.8));
    sim.agregarObstaculo(Obstaculo(2, Vector2D(70.0, 30.0), 10.0, 0.8));
    sim.agregarObstaculo(Obstaculo(3, Vector2D(30.0, 70.0), 10.0, 0.8));
    sim.agregarObstaculo(Obstaculo(4, Vector2D(70.0, 70.0), 10.0, 0.8));

    // 4 particulas simultaneas
    sim.agregarParticula(Particula(1, 2.0, 2.5, Vector2D(15.0, 50.0), Vector2D(18.0, 12.0)));
    sim.agregarParticula(Particula(2, 3.0, 3.0, Vector2D(85.0, 50.0), Vector2D(-16.0, 14.0)));
    sim.agregarParticula(Particula(3, 1.5, 2.0, Vector2D(50.0, 15.0), Vector2D(10.0, 22.0)));
    sim.agregarParticula(Particula(4, 2.5, 2.8, Vector2D(50.0, 85.0), Vector2D(-12.0, -19.0)));

    sim.ejecutar(15.0);
    std::cout << "Simulacion completada. Archivos generados: trayectorias.txt y colisiones.txt" << std::endl;

    return 0;
}