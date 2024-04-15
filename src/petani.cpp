#include <iostream>
#include <vector>
#include "petani.hpp"

using namespace std;

// EXTRA FUNCTIONS

Petani::Petani() : Pemain()
{
    this->tipe = "petani";
    int FieldRow = ParserMisc::getFieldSize().first;
    int FieldCol = ParserMisc::getFieldSize().second;
    MatrixArea<Tanaman> n(FieldRow, FieldCol);
    this->ladang = n;
    this->username = "Petani1";
}

Petani::Petani(string usn, float guld, int bb, int smol, int med, int big, int ladrows, int ladcols) : Pemain(usn, guld, bb, smol, med, big)
{
    this->tipe = "petani";
    MatrixArea<Tanaman> n(ladrows, ladcols);
    this->ladang = n;
}

Petani::Petani(const Petani &other) : Pemain(other)
{
    this->tipe = "petani";
    MatrixArea<Tanaman> n(other.ladang);
    this->ladang = n;
}

Petani::~Petani()
{
    this->inventory.~MatrixArea();
    this->ladang.~MatrixArea();
}

void Petani::beli()
{
    std::cout << endl
              << endl;

    GameObject *itemToBuy = nullptr;
    bool isSubMenuCancelled = false;
    int wantToBuy;
    while (!isSubMenuCancelled)
    {
        wantToBuy = Toko::buyProcess();
        std::cout << endl;
        try
        {
            if (wantToBuy == 0)
            {
                std::cout << "Ditunggu Kedatangan Selanjutnya!!" << endl;
                isSubMenuCancelled = true;
            }
            else if (wantToBuy == -1)
            {
                isSubMenuCancelled = true;
            }
            else
            {
                string subResponse;
                int validSubResponse;
                int counterAvailableItem;
                if (wantToBuy == 1)
                {
                    Toko::displayAvailableHewan();
                    std::cout << "Barang yang ingin dibeli : ";
                    std::cin >> subResponse;

                    if (isAllDigits(subResponse))
                    {
                        validSubResponse = stoi(subResponse);
                    }
                    else
                    {
                        throw InvalidSubResponse();
                    }

                    if (validSubResponse != Toko::availableHewan.size() + 1)
                    {
                        if (validSubResponse >= 1 && validSubResponse <= Toko::availableHewan.size())
                        {
                            itemToBuy = &Toko::availableHewan[validSubResponse - 1];
                            isSubMenuCancelled = true;
                        }
                        else
                        {
                            throw InvalidSubResponse();
                        }
                    }
                    else
                    {
                        std::cout << endl; // cancel
                    }
                }
                else if (wantToBuy == 2)
                {
                    Toko::displayAvailableTanaman();
                    std::cout << "Barang yang ingin dibeli : ";
                    std::cin >> subResponse;

                    if (isAllDigits(subResponse))
                    {
                        validSubResponse = stoi(subResponse);
                    }
                    else
                    {
                        throw InvalidSubResponse();
                    }

                    if (validSubResponse != Toko::availableTanaman.size() + 1)
                    {
                        if (validSubResponse >= 1 && validSubResponse <= Toko::availableTanaman.size())
                        {
                            itemToBuy = &Toko::availableTanaman[validSubResponse - 1];
                            isSubMenuCancelled = true;
                        }
                        else
                        {
                            throw InvalidSubResponse();
                        }
                    }
                    else
                    {
                        std::cout << endl; // cancel
                    }
                }
                else if (wantToBuy == 3 && !Toko::isProductEmptyStock())
                {
                    counterAvailableItem = Toko::displayAvailableProduct();
                    std::cout << "Barang yang ingin dibeli : ";
                    std::cin >> subResponse;

                    if (isAllDigits(subResponse))
                    {
                        validSubResponse = stoi(subResponse);
                    }
                    else
                    {
                        throw InvalidSubResponse();
                    }

                    if (validSubResponse != counterAvailableItem + 1)
                    {
                        if (validSubResponse >= 1 && validSubResponse <= counterAvailableItem)
                        {
                            int count = 0;
                            bool found = false;
                            for (int i = 0; i < Toko::availableProduct.size(); i++)
                            {
                                if (Toko::availableProduct[i].second != 0)
                                {
                                    count++;
                                }
                                if (validSubResponse == count && !found)
                                {
                                    itemToBuy = &Toko::availableProduct[i].first;
                                    // itemToBuy = &Toko::availableProduct[count].first;
                                    found = true;
                                    isSubMenuCancelled = true;
                                }
                            }
                        }
                        else
                        {
                            throw InvalidSubResponse(); // response < 0 atau > seharusnya
                        }
                    }
                    else
                    {
                        std::cout << endl; // cancel
                    }
                }
                else if (((wantToBuy == 3 && Toko::isProductEmptyStock()) || (wantToBuy == 4)) && !Toko::isBangunanEmptyStock())
                {
                    counterAvailableItem = Toko::displayAvailableBangunan();
                    std::cout << "Barang yang ingin dibeli : ";
                    std::cin >> subResponse;

                    if (isAllDigits(subResponse))
                    {
                        validSubResponse = stoi(subResponse);
                    }
                    else
                    {
                        throw InvalidSubResponse();
                    }

                    if (validSubResponse != counterAvailableItem + 1)
                    {
                        if (validSubResponse >= 1 && validSubResponse <= counterAvailableItem)
                        {
                            int count = 0;
                            bool found = false;
                            for (int i = 0; i < Toko::availableBangunan.size(); i++)
                            {
                                if (Toko::availableBangunan[i].second != 0)
                                {
                                    count++;
                                }
                                if (validSubResponse == count && !found)
                                {
                                    itemToBuy = &Toko::availableBangunan[i].first;
                                    // itemToBuy = &Toko::availableBangunan[count].first;
                                    this->ownedBangunan.push_back(Toko::availableBangunan[count].first);
                                    found = true;
                                    isSubMenuCancelled = true;
                                }
                            }
                        }
                        else
                        {
                            throw InvalidSubResponse();
                        }
                    }
                    else
                    {
                        std::cout << endl; // cancel
                    }
                }
            }
        }
        catch (BaseException &err)
        {
            cout << err.what();
            std::cout << endl
                      << endl;
        }
    }

    if (itemToBuy != nullptr)
    {
        std::cout << endl
                  << "Uang Anda : " << this->gulden << endl;
        this->inventory.displayRemainderSlot();
        std::cout << endl;

        string quantity;
        int validQuantity;

        try
        {
            std::cout << "Kuantitas : ";
            cin >> quantity;
            if (isAllDigits(quantity))
            {
                validQuantity = stoi(quantity);
                if (validQuantity == 0)
                {
                    throw InvalidSubResponse();
                }
            }
            else
            {
                throw InvalidSubResponse();
            }

            this->gulden -= itemToBuy->getPrice() * validQuantity;
            if (validQuantity > this->inventory.getEmptySlot())
            {
                this->gulden += itemToBuy->getPrice() * validQuantity;
                throw InventoryNotEnough();
            }
            int stock = Toko::getStock(itemToBuy->getName());
            if (stock != -1 && stock < validQuantity)
            {
                this->gulden += itemToBuy->getPrice() * validQuantity;
                throw StockTokoNotEnough();
            }
            if (this->gulden < 0)
            {
                this->gulden += itemToBuy->getPrice() * validQuantity;
                throw NotEnoughGulden();
            }
            std::cout << endl;
            std::cout << "Selamat Anda berhasil membeli " << validQuantity << " " << itemToBuy->getName();
            std::cout << ". Uang yang tersisa " << this->gulden << "." << endl
                      << endl;

            std::cout << "Pilih slot untuk menyimpan barang yang anda beli!" << endl;
            this->inventory.displayObject();
            string slot;
            bool isValid = false;
            for (int i = 0; i < validQuantity; i++)
            {
                isValid = false;
                while (!isValid)
                {
                    try
                    {
                        std::cout << "Petak slot " << i + 1 << ": ";
                        std::cin >> slot;
                        pair<int, int> position;
                        position = this->inventory.getPositionFromSlot(slot);
                        if (this->inventory.getElement(position.first, position.second) != nullptr)
                        {
                            throw SlotFilled();
                        }

                        this->inventory.setElement(position.first, position.second, itemToBuy);
                        isValid = true;
                    }
                    catch (BaseException &err)
                    {
                        cout << err.what();
                        cout << endl;
                    }
                }
            }
            std::cout << itemToBuy->getName() << " berhasil disimpan dalam penyimpanan!" << endl;
            Toko::itemDibeli(itemToBuy, validQuantity);
        }
        catch (BaseException &err)
        {
            std::cout << err.what();
            std::cout << endl;
        }
    }
}

void Petani::jual() // perlu catch ItemQuantityToSellNotEnough
{
    try
    {
        std::cout << "Berikut merupakan penyimpanan Anda" << endl;
        this->inventory.displayObject();
        string quantity;
        int quantityint;
        std::cout << "Masukkan kuantitas barang yang ingin dijual : ";
        std::cin >> quantity;
        std::cout << endl;
        if (!isAllDigits(quantity))
        {
            throw InvalidPanenIdx();
        }
        else
        {
            quantityint = std::stoi(quantity);
            if ((quantityint - this->ownedBangunan.size()) > ((this->inventory.getCols() * this->inventory.getRows()) - this->inventory.getEmptySlot()))
            {
                throw ItemQuantityToSellNotEnough();
            }
        }

        std::cout << endl
                  << "Silahkan pilih petak yang ingin anda jual!"
                  << endl;
        string slot;
        pair<int, int> position;
        int profit = 0;
        GameObject *itemToSell;

        bool isValid;
        for (int i = 0; i < quantityint; i++)
        {
            isValid = false;
            while (!isValid)
            {
                std::cout << "Petak slot " << i + 1 << ": ";
                std::cin >> slot;
                std::cout << endl;

                int idx1 = slot[0] - 'A' + 1;
                int idx2 = std::stoi(slot.substr(1));
                try
                {
                    if (slot.length() != 3)
                    {
                        throw InvalidIndexMatrixArea();
                    }
                    else if (idx2 > this->inventory.getRows() || idx1 > this->inventory.getCols())
                    {
                        throw InvalidIndexMatrixArea();
                    }
                    // position = this->inventory.getPositionFromSlot(slot);
                    // itemToSell = this->inventory.getElement(position.first, position.second);
                    else
                    {
                        if (this->inventory.getElement(idx2, idx1) != nullptr)
                        {
                            if (this->inventory.getElement(idx2, idx1)->getTipeObject() == "BANGUNAN")
                            {
                                throw CantSellBangunan();
                            }
                            else
                            {
                                isValid = true;
                            }
                        }
                        else
                        {
                            throw InvalidEmptySlot();
                        }
                    }
                }
                catch (BaseException &e)
                {
                    std::cout << e.what() << endl;
                }
            }
            int idx1 = slot[0] - 'A' + 1;
            int idx2 = std::stoi(slot.substr(1));
            profit += this->inventory.getElement(idx2, idx1)->getPrice();
            cout << this->inventory.getElement(idx2, idx1)->getPrice() << endl;
            Toko::itemDijual(this->inventory.getElement(idx2, idx1), quantityint);
            this->inventory.deleteElement(idx2, idx1);
        }
        this->gulden += profit;
        cout << this->gulden << ' ' << profit << endl;
        cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << profit << " gulden!" << endl;
    }
    catch (BaseException &e)
    {
        std::cout << e.what() << endl;
    }
}

MatrixArea<Tanaman> Petani::getLadang()
{
    return this->ladang;
}

void Petani::cetakLadang()
{
    this->ladang.displayObject();
    this->ladang.displayRemainderSlot();
}

void Petani::tanam()
{
    std::cout << "Pilih Tanaman dari penyimpanan" << endl;
    this->cetakPenyimpanan();
    this->cetakLadang();

    bool isValid = false;
    string slot;

    while (!isValid)
    {
        std::cout << "Slot: ";
        std::cin >> slot;
        std::cout << endl;
        // Validasi
        int idx1 = slot[0] - 'A' + 1;
        int idx2 = std::stoi(slot.substr(1));
        try
        {
            this->cetakLadang();

            if (slot.length() != 3)
            {
                throw InvalidIndexMatrixArea();
            }
            else if (idx2 > this->inventory.getRows() || idx1 > this->inventory.getCols())
            {
                throw InvalidIndexMatrixArea();
            }
            else
            {
                if (this->inventory.getElement(idx2, idx1) != nullptr)
                {
                    if (this->inventory.getElement(idx2, idx1)->getTipeObject() != "TANAMAN")
                    {
                        throw InvalidNotTanaman();
                    }
                    else
                    {
                        isValid = true;
                    }
                }
                else
                {
                    throw InvalidEmptySlot();
                }
            }
        }
        catch (BaseException &e)
        {
            std::cout << e.what() << endl;
        }
    }

    int idx1 = slot[0] - 'A' + 1;
    int idx2 = std::stoi(slot.substr(1));

    std::cout << "Kamu memilih " << this->inventory.getElement(idx2, idx1)->getName() << endl; // Nama Objeknya
    std::cout << "Pilih petak tanah yang akan ditanami" << endl;
    this->cetakLadang();

    isValid = false;
    string petak;
    while (!isValid)
    {
        std::cout << "Petak Tanah: ";
        std::cin >> petak;
        std::cout << endl;
        // Validasi
        int idx3 = petak[0] - 'A' + 1;
        int idx4 = std::stoi(petak.substr(1));
        try
        {
            if (petak.length() != 3)
            {
                throw InvalidIndexMatrixArea();
            }
            else if (idx4 > this->ladang.getRows() || idx3 > this->ladang.getCols())
            {
                throw InvalidIndexMatrixArea();
            }
            else
            {
                if (this->ladang.getElement(idx4, idx3) == nullptr)
                {
                    isValid = true;
                }
                else
                {
                    InvalidFilledSlot();
                }
            }
        }
        catch (BaseException &e)
        {
            std::cout << e.what() << endl;
        }
    }
    int idx3 = petak[0] - 'A' + 1;
    int idx4 = std::stoi(petak.substr(1));

    Tanaman *temp = dynamic_cast<Tanaman *>(this->inventory.getElement(idx2, idx1));

    if (temp)
    {
        std::cout << "SUCCC" << endl;
        std::cout << temp->getKode() << endl;
    }
    else
    {
        std::cout << "GAGGG" << endl;
    }

    this->ladang.setElement(idx4, idx3, temp); // karna tanaman
    this->inventory.deleteElement(idx2, idx1);
    std::cout << this->ladang.getElement(idx4, idx3)->getKode() << endl;
    std::cout << "Berhasil ditanam" << endl;
    // this->cetakPenyimpanan();
    // this->cetakLadang();
}

void Petani::panenTani()
{
    try
    {
        if (this->ladang.isEmpty())
        {
            throw NoHarvestablePlant();
        }
        else
        {
            bool existHarvest = false;
            for (int a = 1; a < this->ladang.getRows(); a++)
            {
                for (int b = 1; b < this->ladang.getCols(); b++)
                {
                    if (this->ladang.getElement(a, b) != nullptr)
                    {
                        if (this->ladang.getElement(a, b)->getTipeObject() == "TANAMAN")
                        {
                            if (this->ladang.getElement(a, b)->isHarvestable())
                            {
                                existHarvest = true;
                            }
                        }
                    }
                }
            }
            if (!existHarvest)
            {
                throw NoHarvestablePlant();
            }
            else
            {
                this->cetakLadang();
                vector<string> ownedTan = {};
                vector<string> ownedTanName = {};
                vector<string> readyPanen = {};
                vector<int> readyPanenAmt = {};

                for (int i = 1; i < this->ladang.getRows() + 1; i++)
                {
                    for (int j = 1; j < this->ladang.getCols() + 1; j++)
                    {
                        if (this->ladang.getElement(i, j) != nullptr)
                        {
                            cout << this->ladang.getElement(i, j)->getKode() << endl;
                            if (this->ladang.getElement(i, j)->getTipeObject() == "TANAMAN")
                            {
                                bool found = false;
                                int it = 0;
                                while (it < ownedTan.size())
                                {

                                    if (ownedTan[it] == this->ladang.getElement(i, j)->getKode())
                                    {
                                        found = true;
                                        it = ownedTan.size() + 1;
                                    }
                                    it++;
                                }

                                if (!found)
                                {
                                    string temp1 = this->ladang.getElement(i, j)->getKode();
                                    string temp2 = this->ladang.getElement(i, j)->getName();

                                    ownedTan.push_back(temp1);
                                    ownedTanName.push_back(temp2);

                                    // cout << "awdasdwdasdawd" << endl;
                                    // this->cetakLadang();
                                }
                            }
                        }
                    }
                }
                cout << " BATAS " << endl;
                // this->cetakLadang();
                // cout << this->ladang.getElement(5, 4)->getKode() << endl;

                // Output tanaman yang ada
                for (size_t i = 0; i < ownedTan.size(); ++i)
                {
                    cout << ownedTan[i] << " - " << ownedTanName[i] << endl;
                }

                // Output pilihan tanaman berdasarkan siap panennnya
                for (size_t i = 0; i < ownedTan.size(); ++i)
                {
                    int count = 0;
                    int num = 1;

                    for (int j = 1; j < this->ladang.getRows(); j++)
                    {
                        for (int k = 1; k < this->ladang.getCols(); k++)
                        {
                            if (this->ladang.getElement(j, k) != nullptr)
                            {
                                cout << j << k << endl;
                                cout << this->ladang.getElement(j, k)->getKode() << endl;
                                if (this->ladang.getElement(j, k)->getKode() == ownedTan[i])
                                {
                                    if (this->ladang.getElement(j, k)->isHarvestable())
                                    {
                                        count += 1;
                                        bool found = false;
                                        size_t it = 0;
                                        cout << "1" << endl;
                                        while (it < readyPanen.size())
                                        {
                                            cout << "2" << endl;
                                            // readyPanen[it] == this->ladang.getElement(i, j)->getKode();
                                            cout << "3" << endl;

                                            if (readyPanen[it] == this->ladang.getElement(j, k)->getKode())
                                            {
                                                found = true;
                                                it = readyPanen.size() + 1;
                                            }
                                            it++;
                                        }
                                        if (!found)
                                        {
                                            string temp = this->ladang.getElement(j, k)->getKode();
                                            readyPanen.push_back(temp);
                                        }
                                        cout << "-----------------" << endl;
                                    }
                                }
                            }
                        }
                    }
                    if (count > 0)
                    {
                        readyPanenAmt.push_back(count);
                    }
                    count = 0;
                }

                for (int i = 0; i < readyPanen.size(); i++)
                {
                    cout << i + 1 << ". " << readyPanen[i] << " (" << readyPanenAmt[i] << ")" << endl;
                }

                bool isValid = false;
                string maupanen;
                int maupanenint;

                if (readyPanen.size() > 0)
                {
                    // cout << this->ladang.getElement(5, 4)->getKode() << endl;

                    while (!isValid)
                    {
                        try
                        {
                            cout << "Nomor tanaman yang ingin dipanen: ";
                            cin >> maupanen;
                            cout << endl;

                            if (!isAllDigits(maupanen))
                            {
                                throw InvalidPanenIdx();
                            }
                            else
                            {
                                maupanenint = std::stoi(maupanen);

                                if (maupanenint > readyPanen.size() || maupanenint < 0)
                                {
                                    throw InvalidPanenIdx();
                                }
                                else
                                {
                                    isValid = true;
                                }
                            }
                        }
                        catch (BaseException &e)
                        {
                            cout << e.what() << endl;
                        }
                    }

                    isValid = false;
                    string brppanen;
                    int brppanenint;
                    while (!isValid)
                    {
                        try
                        {
                            cout << "Berapa petak yang ingin dipanen: ";
                            cin >> brppanen;
                            cout << endl;
                            if (!isAllDigits(brppanen))
                            {
                                throw InvalidPanenIdx();
                            }
                            else
                            {
                                brppanenint = std::stoi(brppanen);
                                if (brppanenint > this->inventory.getEmptySlot())
                                {
                                    throw InvalidInventorySpace();
                                }
                                else if (brppanenint > readyPanenAmt[maupanenint - 1])
                                {
                                    throw InvalidPanenAmountOver();
                                }
                                else if (brppanenint < 1)
                                {
                                    throw InvalidPanenAmount();
                                }
                                else
                                {
                                    isValid = true;
                                }
                            }
                            // Validasi
                            // if tidak valid ada output
                        }
                        catch (BaseException &e)
                        {
                            cout << e.what() << endl;
                        }
                    }

                    int i = 0;
                    string want;
                    vector<string> wants;
                    cout << "Pilih petak yang ingin dipanen: " << endl;
                    for (i; i < brppanenint; i++)
                    {
                        isValid = false;
                        while (!isValid)
                        {
                            try
                            {
                                cout << "Petak ke-" << i + 1 << ": ";
                                cin >> want;
                                int idx1 = want[0] - 'A' + 1;
                                int idx2 = std::stoi(want.substr(1));
                                cout << idx2 << idx1 << endl;
                                if (want.length() != 3)
                                {
                                    throw InvalidIndexMatrixArea();
                                }
                                else if (idx2 > this->ladang.getRows() || idx1 > this->ladang.getCols())
                                {
                                    throw InvalidIndexMatrixArea();
                                }
                                else
                                {
                                    if (this->ladang.getElement(idx2, idx1) != nullptr)
                                    {
                                        cout << "a" << endl;
                                        cout << this->ladang.getElement(idx2, idx1)->getKode() << endl;
                                        if (this->ladang.getElement(idx2, idx1)->getKode() != readyPanen[maupanenint - 1])
                                        {
                                            cout << "b" << endl;
                                            throw InvalidPlantChoice();
                                        }
                                        else
                                        {
                                            cout << "c" << endl;
                                            isValid = true;
                                        }
                                    }
                                    else
                                    {
                                        throw InvalidEmptySlot();
                                    }
                                }
                            }
                            catch (BaseException &e)
                            {
                                cout << e.what() << endl;
                            }
                            // Validasi want, kalau valid wants.push_back(want);
                        }
                        wants.push_back(want);
                    }

                    cout << "WS" << wants.size() << endl;
                    for (int i = 0; i < wants.size(); i++)
                    {

                        bool foundslot = false;

                        int idx1 = wants[i][0] - 'A' + 1;
                        int idx2 = std::stoi(wants[i].substr(1));
                        for (int j = 1; j < this->inventory.getRows() + 1; j++)
                        {
                            for (int k = 1; k < this->inventory.getCols() + 1; k++)
                            {
                                if (this->inventory.getElement(j, k) == nullptr)
                                {
                                    cout << j << k << endl;
                                    cout << idx2 << idx1 << endl;
                                    // cout << this->ladang.getElement(idx2, idx1)->hasilPanen()->getName() << endl;
                                    // cout<<"PEPEK"<<endl;
                                    // cout << this->ladang.getElement(idx2, idx1)->hasilPanen()->getName() << endl;
                                    this->inventory.setElement(j, k, this->ladang.getElement(idx2, idx1)->hasilPanen());
                                    // this->setInv(j, k, this->ladang.getElement(idx2, idx1)->hasilPanen());
                                    cout << this->inventory.getElement(j, k)->getName() << endl;
                                    cout << this->inventory.getElement(1, 1)->getName() << endl;

                                    this->ladang.deleteElement(idx2, idx1);
                                    foundslot = true;
                                    break;
                                }
                            }
                            if (foundslot)
                            {
                                break;
                            }
                        }
                        this->cetakPenyimpanan();
                    }
                    cout << this->inventory.getElement(1, 1)->getName() << endl;
                    cout << "Panen Berhasil" << endl;
                    this->cetakPenyimpanan();
                }
            }
        }
    }
    catch (BaseException &e)
    {
        cout << e.what() << endl;
    }
}

int Petani::countKekayaanLadang()
{
    int sum = 0;
    for (int i = 1; i < ladang.getRows(); i++)
    {
        for (int j = 1; j < ladang.getCols(); j++)
        {
            Tanaman *ptr = ladang.getElement(i, j);
            if (ptr != nullptr)
            {
                sum += ptr->getPrice();
            }
        }
    }
    return sum;
}

float Petani::calculateTax()
{
    int KKP = countKekayaanInven() + countKekayaanLadang() - KTKP_PETANI;
    std::cout << KKP << endl;
    return getTaxRate(KKP) * KKP;
}