#include <memory>
#include "button.h"
#include <vector>

using std::vector, std::unique_ptr;

class Hex {
private:
    int q, r, s;
    unique_ptr<Button> button;
public:
    auto getQ() const -> int;

    auto getR() const -> int;

    auto getS() const -> int;

    auto getButton() const -> const unique_ptr<Button> &;

    Hex(int q, int r, int s, unique_ptr<Button> &btn);

//    Hex(int q, int r, int s);

    /**
     * Function which calculates and returns distance between two cells.
     * @param other
     * @return int
     */
    auto getDistance(const unique_ptr<Hex> &other) const -> int;

    /**
     * Function for adding two cells.
     * @param offset
     * @return
     */
    auto add(vector<int> offset) const -> vector<int>;

//    vector<vector<int>> getOffsets() const;

//    static const vector<vector<int>> directions;
};