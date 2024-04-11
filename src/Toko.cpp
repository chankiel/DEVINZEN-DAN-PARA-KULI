#include <iostream>
#include <vector>
#include <string>
#include "Toko.hpp"
using namespace std;

Toko::Toko(){
    int idDummyToko;
    for(int i = 0; i < ParserHewan::getConfigSize(); i++){
        idDummyToko = ParserHewan::getID(i);
        Hewan hewanDummyToko(i);
        availableHewan.push_back(make_pair(hewanDummyToko,-1));
    }

    for(int i = 0; i < ParserTanaman::getConfigSize(); i++){
        idDummyToko = ParserTanaman::getID(i);
        Tanaman tanamanDummyToko(i);
        availableTanaman.push_back(make_pair(tanamanDummyToko,-1));
    }

    for(int i = 0; i < ParserProduk::getConfigSize(); i++){
        idDummyToko = ParserProduk::getID(i);
        Product productDummyToko(i);
        availableProduct.push_back(make_pair(productDummyToko,0));
    }

    for(int i = 0; i < ParserResep::getConfigSize.; i++){
        idDummyToko = ParserResep::getID(i);
        Bangunan bangunanDummyToko(i);
        availableBangunan.push_back(make_pair(bangunanDummyToko,0));
    }
};

void Toko::buyProcess(){
    cout << "Selamat datang di toko!!" << endl;
    cout << "Berikut merupakan hal yang dapat anda Beli :" << endl;
    int response;
    bool isBuying = false;
    int i = 2;
    while(!isBuying){
        cout << "1. Hewan" << endl;
        cout << "2. Tanaman" << endl;
        if (!isProductEmptyStock()){
            i++;
            cout << i << ". Product" << endl;
        }
        if (!isBangunanEmptyStock()){
            i++;
            cout << i << ". Bangunan" << endl;
        }
        i++;
        cout << i << ". Cancel Buy" << endl;
        cout << "Masukklah pilihan (1-4) :";
        cin >> response;
        if (response == 1){
            displayAvailableHewan();
        } else if (response == 2){
            displayAvailableTanaman();
        } else if (response == 3 && i >= 3 && !isProductEmptyStock()){
            displayAvailableProduct();
        } else if (response == 3 && i >= 3 && !isBangunanEmptyStock() && isProductEmptyStock()){
            displayAvailableBangunan();
        } else if (response == 4 && !isBangunanEmptyStock){
            displayAvailableBangunan();
        } else if (response == i){
            isBuying = true;
        } else {
            //throw exception
            cout << "Input tidak valid" << endl; //sementara
        }
    }

}

bool Toko::isProductEmptyStock(){
    for(int i = 0; i < ParserProduk::getConfigSize();i++){
        if (availableProduct[i].second != 0){
            return false;
        }
    }
    return true;
}

bool Toko::isBangunanEmptyStock(){
    for(int i = 0; i < ParserResep::getConfigSize();i++){
        if (availableBangunan[i].second != 0){
            return false;
        }
    }
    return true;
}

void Toko::displayAvailableHewan(){
    int idx = 1;
    for (int i = 0; i < ParserHewan::getConfigSize(); i++){
        cout << idx << ". " << availableHewan[i].getName();
        cout << " - " << availableHewan[i].getPrice() << endl;
        idx++;
    }
    cout << idx << ". Cancel" << endl;
}

void Toko::displayAvailableTanaman(){
    int idx = 1;
    for (int i = 0; i < ParserTanaman::getConfigSize(); i++){
        cout << idx << ". " << availableTanaman[i].getName();
        cout << " - " << availableTanaman[i].getPrice() << endl;
        idx++;
    }
}

void Toko::displayAvailableProduct(){
    int idx = 1;
    for (int i = 0; i < ParserProduk::getConfigSize(); i++){
        if (availableProduct[i].second != 0){
            cout << idx << ". " << availableProduct[i].first.getName();
            cout << " - " << availableProduct[i].first.getPrice() << endl;
            idx++;
        }
    }
}

void Toko::displayAvailableBangunan(){
    int idx = 1;
    for (int i = 0; i < ParserResep::getConfigSize(); i++){
        if (availableBangunan[i].second != 0){
            cout << idx << ". " << availableBangunan[i].first.getName();
            cout << " - " << availableBangunan[i].first.getPrice();
            cout << " (" << availableBangunan[i].second << ")" << endl;
            idx++;
        }
    }
}
void Toko::displayResepBangunan(){
    int idx = 1;
    for (int i = 0; i < ParserResep::getConfigSize(); i++){
        cout << idx << ". " << availableBangunan[i].first.getName();
        cout << " - " << availableBangunan[i].first.getPrice();
        cout << " (" << availableBangunan[i].second << ")" << endl;
        idx++;
    }
}