#include <memory>
#include "button.h"
#include <vector>

using std::vector, std::unique_ptr;

class Hex {
private:
    int q, r, s;
    unique_ptr<Button> button;
public:
    [[nodiscard]] auto getQ() const -> int;

    [[nodiscard]] auto getR() const -> int;

    [[nodiscard]] auto getS() const -> int;

    [[nodiscard]] auto getButton() const -> const unique_ptr<Button> &;

    Hex(int q, int r, int s, unique_ptr<Button> &btn);

    /**
     * Function which calculates and returns distance between two cells.
     * @param other
     * @return int
     */
    [[nodiscard]] auto getDistance(const unique_ptr<Hex> &other) const -> int;

    /**
     * Function for adding two cells.
     * @param offset
     * @return
     */
    [[nodiscard]] auto add(int qq, int rr, int ss) const -> vector<int>;
};