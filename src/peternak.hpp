#ifndef PETERNAK_HPP
#define PETERNAK_HPP

#include "pemain.hpp"

class Peternak : public Pemain
{
protected:
    MatrixArea<Hewan> ternakan;

public:
    Peternak();
    Peternak(string usn, int guld, int bb, int smol, int med, int big, int terrows, int tercols);
    Peternak(const Peternak &);
    ~Peternak();

    MatrixArea<Hewan> getTernakan();
    void cetakTernak();
    void ternak();     // coords hewan yg ingin diternak, coords letak ternakan
    void kasihMakan(); // coords letak hewan, coords letak makanan yg ingin diberikan
    void panenTernak();
    void beli();
    void jual();
    int countKekayaanTernakan();
    int calculateTax();
};

#endif
