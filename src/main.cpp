// #include <iostream>
// #include <vector>
// #include <string>
#include "./Implementation/GameManager.cpp"
#include "petani.cpp"
#include "peternak.cpp"
#include "walikota.cpp"
#include "pemain.cpp"
#include "Toko.cpp"
// #include "./Implementation/ParserMisc.cpp"
#include <iostream>
// #include "./Header/Exception.hpp"
// #include "./Header/GameManager.hpp"
using namespace std;

// inisialisasi atribut static di semua parser
vector<string> ParserHewan::validAnimalTypes = {"HERBIVORE", "CARNIVORE", "OMNIVORE"};
vector<int> ParserHewan::animalID = vector<int>();
vector<string> ParserHewan::animalCode = vector<string>();
vector<string> ParserHewan::animalName = vector<string>();
vector<string> ParserHewan::animalType = vector<string>();
vector<int> ParserHewan::harvestWeight = vector<int>();
vector<int> ParserHewan::price = vector<int>();
map<int, int> ParserHewan::IndexToIDMap = map<int, int>();
map<int, int> ParserHewan::IDToIndexMap = map<int, int>();
vector<int> ParserProduk::productID = vector<int>();
vector<string> ParserProduk::productCode = vector<string>();
vector<string> ParserProduk::productName = vector<string>();
vector<string> ParserProduk::productType = vector<string>();
vector<string> ParserProduk::productOrigin = vector<string>();
vector<int> ParserProduk::addedWeight = vector<int>();
vector<int> ParserProduk::price = vector<int>();
vector<string> ParserProduk::validProductTypes = vector<string>();
map<int, int> ParserProduk::IndexToIDMap = map<int, int>();
map<int, int> ParserProduk::IDToIndexMap = map<int, int>();
vector<int> ParserResep::recipeID = vector<int>();
vector<string> ParserResep::recipeCode = vector<string>();
vector<string> ParserResep::recipeName = vector<string>();
vector<int> ParserResep::recipePrice = vector<int>();
vector<vector<pair<string, int>>> ParserResep::recipeMaterialQuantity = vector<vector<pair<string, int>>>();
map<int, int> ParserResep::IndexToIDMap = map<int, int>();
map<int, int> ParserResep::IDToIndexMap = map<int, int>();
vector<int> ParserTanaman::plantID = vector<int>();
vector<string> ParserTanaman::plantCode = vector<string>();
vector<string> ParserTanaman::plantName = vector<string>();
vector<string> ParserTanaman::plantType = vector<string>();
vector<int> ParserTanaman::harvestDuration = vector<int>();
vector<int> ParserTanaman::price = vector<int>();
vector<string> ParserTanaman::validPlantTypes = vector<string>();
map<int, int> ParserTanaman::IndexToIDMap = map<int, int>();
map<int, int> ParserTanaman::IDToIndexMap = map<int, int>();
vector<Hewan> Toko::availableHewan = vector<Hewan>();
vector<Tanaman> Toko::availableTanaman = vector<Tanaman>();
vector<pair<Product, int>> Toko::availableProduct = vector<pair<Product, int>>();
vector<pair<Bangunan, int>> Toko::availableBangunan = vector<pair<Bangunan, int>>();

int main()
{
    ParserHewan PH;
    ParserMisc PM;
    ParserTanaman PT;
    ParserProduk PP;
    ParserResep PR;
    string animalConfigDirectory = "../config/animal.txt";
    string miscConfigDirectory = "../config/misc.txt";
    string plantConfigDirectory = "../config/plant.txt";
    string productConfigDirectory = "../config/product.txt";
    string recipeConfigDirectory = "../config/recipe.txt";

    PH.ParseFile(animalConfigDirectory);
    PM.ParseFile(miscConfigDirectory);
    PT.ParseFile(plantConfigDirectory);
    PP.ParseFile(productConfigDirectory);
    PR.ParseFile(recipeConfigDirectory);
    // Toko::initialize();
    // WaliKota w;
    // Product *teak = new Product(1, false);
    // Product *sandal = new Product(2, false);
    // Product *aloe = new Product(3, false);
    // Product *iron = new Product(4, false);
    // w.setInv(1, 1, teak);
    // for (int i = 2; i <= 10; i++)
    // {
    //     w.setInv(1, i, teak);
    // }

    // for (int i = 2; i <= 10; i++)
    // {
    //     for (int j = 1; j <= 9; j++)
    //     {
    //         w.setInv(i, j, sandal);
    //     }
    // }
    // cout << w.getGulden() << "\n";
    // w.cetakPenyimpanan();
    // w.bangunBangunan();
    // cout << w.getGulden() << "\n";
    // w.cetakPenyimpanan();
    // w.jual();
    // w.cetakPenyimpanan();
    // w.beli();

    WaliKota p;
    Product *pr = new Product();
    Hewan h(1);
    Bangunan *b = new Bangunan();
    p.setInv(1, 1, &h);
    p.setInv(2, 1, b);
    p.setInv(3, 1, pr);
    p.jual();
    p.makan();

    return 0;
}