class Coords {
private:
    int q, r, s;

public:
    Coords(int q, int r, int s);

    [[nodiscard]] auto getR() const -> int;

    [[nodiscard]] auto getQ() const -> int;

    [[nodiscard]] auto getS() const -> int;
};