#ifndef TOKO_HPP
#define TOKO_HPP
#include <vector>
#include <utility>
#include "GameObject.hpp"
#include "./misc/helper.hpp"
#include "./Header/GameObject.hpp"
#include "./Header/Hewan.hpp"
#include "./Header/Tanaman.hpp"
#include "./Header/Product.hpp"
#include "./Header/Bangunan.hpp"
#include "./parsers/ParserHewan.hpp"
#include "./parsers/ParserTanaman.hpp"
#include "./parsers/ParserProduk.hpp"
#include "./parsers/ParserResep.hpp"
using namespace std;
class Toko {
    public:
        static vector<Hewan> availableHewan;
        static vector<Tanaman> availableTanaman;
        static vector<pair<Product,int>> availableProduct;
        static vector<pair<Bangunan,int>> availableBangunan;
        Toko();
        static int buyProcess();
        static void itemDibeli(); //handle keadaan toko setelah player membeli item
        static void itemDijual(); //handle keadaan toko setelah player menjual item
        static bool isProductEmptyStock();
        static bool isBangunanEmptyStock();
        static void displayAvailableHewan();
        static void displayAvailableTanaman();
        static int displayAvailableProduct();
        static int displayAvailableBangunan();
        static void displayResepBangunan();
};
#endif