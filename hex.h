#include "button.h"

class Hex {
private:
    int q, r, s;
    Button button;
public:
    int getQ() const;

    int getR() const;

    int getS() const;

    const Button &getButton() const;

    Hex(int q, int r, int s, Button button);

    int getDistance(const Hex &other) const;
};