#include <iostream>
using namespace std;

class Reproductor {
public:
    virtual void reproducir() = 0;
    virtual void pausar() = 0;
    virtual void detener() = 0;
    virtual ~Reproductor() {}
};

class ReproductorMP3 : public Reproductor {
public:
    void reproducir() override {
        cout << "Reproduciendo archivo MP3...\n";
    }
    void pausar() override {
        cout << "Reproduccion pausada.\n";
    }
    void detener() override {
        cout << "Reproduccion detenida.\n";
    }
};

int main() {
    Reproductor* mp3 = new ReproductorMP3();
    mp3->reproducir();
    mp3->pausar();
    mp3->detener();
    delete mp3;

    return 0;
}