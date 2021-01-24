/*This project created by
                OZAN PEKER
                151110051
                ozanpekerai@gmail.com
                ozanpeker52@gmail.com*/;
/*Programın ana ekranı bu şekildedir.Burada yapmak istediğimiz işlemin index numarasını gireriz.MEsela rehberi görüntülemek istiyorsak 1 
girdisi programa gönderilir.Bu şekilde alt menülerde de seçenekler mevcuttur.Girilmesi istenen değerler kullanıcıya belirtilmiştir.
Kullanıcının hatalı girdide bulunması sonucunda ya program ana menüye döner ya da doğru bilgi alana dek kullanıcıdan aynı bilgiyi ister.
**Welcome to Address Book**
Lütfen Yapılacak İşlemi Seçiniz:
1. Rehberi Göster
2. Kayıt Ara
3. Yeni Kişi Ekle
4. Kişi Sil
5. Kaydı Düzenle
6. Programdan Çık
(Büyük-Küçük Harf Duyarlılığı Vardır)*/
#include<iostream> //projede kullnılacak gerekli kütüphaneler indirildi
#include<cstdlib>
#include<string>
#include<cstdio>
#include <clocale> 
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
const int T_S = 350;//hash table mantığında bir dizi kullnacağı için ve bu dizinin rehber oluşturacağından dolayı dizi boyutu 350 yapıldı
class HashTableEntry {
public:
    string isim,soyisim,adres,telefon2,telefon3,mail,mail2;//projenin genelinde kullanılacak değişkenlerin tip tanımı yapıldı
    int telefon;
    HashTableEntry(int telefon, string isim, string soyisim, string adres, string telefon2, string telefon3, string mail, string mail2)
    {
        this->isim = isim;//hash table yapısındaki her dizi elemanının sahip olduğu alt bilgileri içeren genel yapı tanımlandı
        this->soyisim = soyisim;
        this->adres = adres;
        this->telefon = telefon;//raporda üç adte telefon ve 2 adet e-mail girilebilmesinin muhtemel olmasından dolayı ekstradan 3 yer tahsis edildi.
        this->telefon2 = telefon2;
        this->telefon3 = telefon3;
        this->mail = mail;
        this->mail2 = mail2;
    }
};
class hash_adres_defteri //tüm fonksiyonlların yer alacağı sınıf yapısı oluşturuldu
{
private:
    HashTableEntry** dizi;//dizi değişkeninin yukarıda tanımlanan yapıyı refer ederek kullanılacağı belirtildi
public:
    hash_adres_defteri()
    {
        dizi = new HashTableEntry * [T_S];/*bu ksımda boyutu yukarıda belirtelen(350) sayı kadar olan
                                          ve hashtableEntry yapısını referasn alan bir dizi yapısı oluşturuldu*/
        for (int i = 0; i < T_S; i++) /*bu döngü sayesinde eleman yerleştirirken yada
            diziyi hafızada tutarken bir sıkıntı yaşamamak amacıyla tüm elemanlar NULL değerini aldı.*/
        {
            dizi[i] = NULL;
        }
    }
    int mod_fonksiyonu(int k) //mod mantığına göre yerleştrdiğimiz için gelen sayının modunu alıp geri döndüren bir fonksiyon tanımlandı.
    {
        return k % T_S;
    }
    void rehberi_goster()//bu fonksiyon rehberi ekrana bastırmak için kullanıldı
    {
        int counter = 0;
        for (int i = 0; i < T_S; i++)//tüm fonksiyon for döngüsü ile gezildi ve if ile eleman içininboş olmama koşulu değerlendirilip rehber ekrana bastırıldı
        {
            if (dizi[i] != NULL)
            {
                counter++;
                //cout << "key = " << dizi[i]->telefon << endl;
                /*aşağıdaki satırda eleman içi if şartını sağladıysa alt bilgiler belirli bir düzende ekrana bastırıldı.
                En başta yaptıpımız NULL ataması burada diziyi gezerken önem arz etmektedir
                İleri fonksiyonlarda herhangi bir eleman siliminde  eleman değeri silme işlemi ardından yine NULL yapılacaktır.*/
                cout << "Ad:" << dizi[i]->isim << endl << "Soyad:" << dizi[i]->soyisim << endl << "Telefon Numarası(I):" << dizi[i]->telefon << endl << "Telefon Numarası(II):" << dizi[i]->telefon2 << endl << "Telefon Numarası:(III)" << dizi[i]->telefon3 << endl << "Adres:" << dizi[i]->adres << endl << "E-Mail(I):" << dizi[i]->mail << endl << "E-Mail(II):" << dizi[i]->mail2 << endl;
                cout << "***********************************************************************************************" << endl;
            }
        }
        if (counter == 0)//yukarıdaki sayac işlememişse rehber boş olduğu anlamına gelmektedir.Kullanıcıya bu bilgi yansıtılır.
        {
            cout << "Rehber Boş!!" << endl;
        }
    }
    void numaraya_göre_ara(int k,string n)
        /*Bu fonksiyonda numaraya göre arama yapılır.Hash mantığını kullanabilmek için burada özgün bir yol izlenmiştir.
        Öncelikle kullanıcıdan int tipinde bir girdi alınır ve bu girdi string formatına çevrilerek başka bir değişkene atanır.
        Ardından iki değişken bu fonksiyona gönderilir.Gelen int değişkenine göre hash tablosunda arama yapılır.
        Buradaki amaç kullanıcının ilk numaraya göre arama yapmış olma ihtimalidir.
        Peki burada kullanıcı 2 ve 3 numaraları telefona göre arama yaparsa ne olacak?
        Eğer hash tablosunda bulunmazsa tüm kayıt gezilecek ve 2 ve 3 numaralar aranacak.*/
    {
        string state;
        int counter = 0;
        int h = mod_fonksiyonu(k);
        while (dizi[h] != NULL && dizi[h]->telefon != k)
        {
            h = mod_fonksiyonu(h + 1);
        }
        if (dizi[h] == NULL)
        {
            for (int i = 0; i < T_S; i++)//tüm fonksiyon for döngüsü ile gezildi
            {
                if (dizi[i] != NULL)
                {
                    if (dizi[i]->telefon2 == n || dizi[i]->telefon3 == n)
                    {
                        cout << "Ad:" << dizi[i]->isim << endl << "Soyad:" << dizi[i]->soyisim << endl << "Telefon Numarası(I):" << dizi[i]->telefon << endl << "Telefon Numarası(II):" << dizi[i]->telefon2 << endl << "Telefon Numarası:(III)" << dizi[i]->telefon3 << endl << "Adres:" << dizi[i]->adres << endl << "E-Mail(I):" << dizi[i]->mail << endl << "E-Mail(II):" << dizi[i]->mail2 << endl;
                        cout << "***********************************************************************************************" << endl;
                        cout << "Bulmak İstediğiniz Kişi Bu Kayıt Mı?(evet-hayır)" << endl;
                        cin >> state;
                        while (state != "evet" && state != "hayır")
                        {
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout << "\nGeçersiz  girdi !!!.Lütfen Geçerli Bir Girdi Giriniz(evet-hayır)." << endl;
                            cout << "\n";
                            cin >> state;
                        }
                        if (state == "evet")
                        {
                            break;
                        }
                        if (state == "hayır")
                        {
                            continue;
                        }
                        counter++;
                    }
                }
            }
            if (counter != 0)
                cout << "Aranan Kişi Yok!!! " << endl;
        }
        else
            cout << "Ad:" << dizi[h]->isim << endl << "Soyad:" << dizi[h]->soyisim << endl << "Telefon Numarası(I):" << dizi[h]->telefon << endl << "Telefon Numarası(II):" << dizi[h]->telefon2 << endl << "Telefon Numarası:(III)" << dizi[h]->telefon3 << endl << "Adres:" << dizi[h]->adres << endl << "E-Mail(I):" << dizi[h]->mail << endl << "E-Mail(II):" << dizi[h]->mail2 << endl;
        cout << "***********************************************************************************************" << endl;
    }
    void isme_göre_kayit_ara(string aranan)//isme göre arama yapan fonksiyondur.
    {   
        string state;
        int counter = 0;
        for (int i = 0; i < T_S; i++)//tüm dizi for ile gezildi ve if ile doluluk kontrollü yapıldı.
        {
            if (dizi[i] != NULL)
            {
                size_t found = dizi[i]->isim.find(aranan);/*eleman içi doluysa yani o keywordde
                kayıt varsa bu kayıtta bizim aramak isteidğimiz yazıyı içermesi değerlendirildi
                eğer eşleşen var ise ekrana yazdırıldı.İstenirse bu kısımda  kullanıcıya isme göre sil de yapılan gibi tek tek aradğınız kişi bu mu diye sorulabilir.
                fakar kullanıcıya kullanım kolaylığı sağlamak amacyla eşleşen tüm kullanılar sırayla ekrana bastırılır.
                Kullanıcıdan evet hayır girdisi alınarak arama devam ettirilir.Eğer sayac artmamışsa kayıt bulunamamılştır*/
                if (found != string::npos)
                {
                    counter++;
                    
                    cout << "Ad:" << dizi[i]->isim << endl << "Soyad:" << dizi[i]->soyisim << endl << "Telefon Numarası(I):" << dizi[i]->telefon << endl << "Telefon Numarası(II):" << dizi[i]->telefon2 << endl << "Telefon Numarası:(III)" << dizi[i]->telefon3 << endl << "Adres:" << dizi[i]->adres << endl << "E-Mail(I):" << dizi[i]->mail << endl << "E-Mail(II):" << dizi[i]->mail2 << endl;
                    cout << "Aradığım kayıt bu. [Y] Aradığım Kayıt Bu değil. [N]" << endl;
                    cin >> state;
                    while (state != "Y" && state != "N")
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "\nGeçersiz  girdi !!!.Lütfen Geçerli Bir Girdi Giriniz(Y-N)." << endl;
                        cout << "\n";
                        cin >> state;
                    }
                    if (state == "Y")
                    {
                        break;
                    }
                    if (state == "N")
                    {
                        
                        continue;

                    }
                }
            }
            
        }
        if (counter == 0)
        {
            cout << "Kişi Bulunamadı " << endl;
            return;
        }
    }
    void kayit_ekle(int telefon, string isim, string soyisim, string adres, string telefon2, string telefon3, string mail, string mail2) //yeni kayıt ekleme
    {/*Bu fonksiyonda kullanıcıdan alınan bilgiler kullanılır.Önecelikle telefon numarası keyword olarak kullanıldığı için mod fonksiyonuna gönderilir
     ve hangi elemana yerleştirileceği öğrenilir.Gelen indx numarasının boş olmasına göre eleman yerleştirilir.
     Doluysa sağ tarfatan başlayarak en yakın NULL değerine sahip indekse yazılır.Ayrıca burada keyword ler aynıysa kullnıcıya zaten şelşen bir kullnıcı var uyarısı veirlir.
     TC kimlik numarası ,kredi kartı numarası nasıl eşsiz ise telefon numarası da eşssizdir.*/
        int h = mod_fonksiyonu(telefon);
        while (dizi[h] != NULL && dizi[h]->telefon != telefon)
        {
            h = mod_fonksiyonu(h + 1);
        }
        if (dizi[h] != NULL && dizi[h]->telefon == telefon)
        {
            cout << "\nBirinci Telefon Numarası Eşleşen Başka Bir Kullanıcı Var" << endl;
        }
        if (dizi[h] == NULL)
        {
            dizi[h] = new HashTableEntry(telefon, isim, soyisim, adres, telefon2, telefon3, mail, mail2);
        }
    }
    void isme_göre_kayit_sil(string aranan)//isme göre silme
    {   /*Bu fonksiyonda bir sayac ve bir dönü değişkeni kullanılmıştır.Bu dönü kullanıcıya silmek istediğimiz kişinin o olup olmadığını sorar.
        Dizi arama yapılır gibi baştan sona gezilir ve içeriği konrol edilir.Eşleşen kayıtlar kullnıcıya gösterilip silinmek istenilen kaydın o olup olmadığı sorulur.
        Eğer cevabı evet ise kayıt silinir,o indeks içi NULL yapılır ve break ile ayrılınır.
        Eğer cevap hayır ise continue ile döngü devam ettirilir.*/
        int counter = 0;
        string state;
        for (int i = 0; i < T_S; i++)
        {
            if (dizi[i] != NULL && dizi[i])
            {
                size_t found = dizi[i]->isim.find(aranan);
                if (found != string::npos)
                {
                    cout << "Ad:" << dizi[i]->isim << endl << "Soyad:" << dizi[i]->soyisim << endl << "Telefon Numarası(I):" << dizi[i]->telefon << endl << "Telefon Numarası(II):" << dizi[i]->telefon2 << endl << "Telefon Numarası:(III)" << dizi[i]->telefon3 << endl << "Adres:" << dizi[i]->adres << endl << "E-Mail(I):" << dizi[i]->mail << endl << "E-Mail(II):" << dizi[i]->mail2 << endl;
                    cout << "Silmek İstedğiniz Kişi Bu Kayıt Mı?(evet-hayır)" << endl;
                    cin >> state;
                    while (state!="evet"&&state!="hayır")
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "\nGeçersiz  girdi !!!.Lütfen Geçerli Bir Girdi Giriniz(evet-hayır)." << endl;
                        cout << "\n";
                        cin >> state;
                    }
                    if (state == "evet")
                    {
                        delete dizi[i];
                        dizi[i] = NULL;
                        break;
                    }
                    if (state == "hayır")
                    {
                        continue;
                    }
                }
                counter++;
            }
        }
        if (counter == 0)
        {
            cout << "Kişi Bulunamadı " << endl;
            return;
        }
    }
    void numaraya_göre_kayit_sil(int k)
    {
        int h = mod_fonksiyonu(k);
        while (dizi[h] != NULL && dizi[h]->telefon != k)
        {
            h = mod_fonksiyonu(h + 1);
        }
        if (dizi[h] == NULL)
            cout << "Aranan Kişi Yok!!! " << endl;
        else
            delete dizi[h];
        dizi[h] = NULL;
        cout << "***********************************************************************************************" << endl;
    }
    void kaydi_duzenle()//kayıt düzenleme fonksiyonu
    {/* Bu fonksiyonda öncelikle tüm rehber ekrana yazırılır ve kullanıcya düzelnemek istediği kaydın telefon numarasını girmesi istenir.
     Ardından kayıdın  hangi bilgisini düzeltmek istediği sorulur.
     Bu esnada her iki seçim ekranında  kullnaıcnın farklı bir girdi girip girmediği kontorl edilir ve doğru bir girdi girene kadar kullnıcıya aynı soru sorulur.
     Kullanıcı doğru girdi girdikten sonra kullnıcdan yeni bilgi istenr ve o bilgi elemanın o bilgiyi refer eden birimine yazar.
     Bu ksıımda dikkat edilmesi gerek bir şey vardır.Bu da kullanıcının kayıdın ilk numarasını değiştirmesi durumu.Çünkü projede ilk numara keywrod olarak kullnılmaktaydı.
     Eğer bu durumla karşılaşılırsa öncelikle yeni numara istenir ve ardından o numara diziye yeni kayıt ekle gibi diğer bilgiler ile eklenir.
     Ardınan hafızayı temizlemek için eski numaranın gösterdiği indkese NULL değeri atanır.*/
        int counter = 0;
        int choice, k, newkey,temp;
        string temp1, temp2, temp3, temp4, temp5, temp6, temp7;
        string yeni,kontrol;
        bool state;
        state = true;
        for (int i = 0; i < T_S; i++)
        {
            if (dizi[i] != NULL)
            {
                counter++;
                cout << "Ad:" << dizi[i]->isim << endl << "Soyad:" << dizi[i]->soyisim << endl << "Telefon Numarası(I):" << dizi[i]->telefon << endl << "Telefon Numarası(II):" << dizi[i]->telefon2 << endl << "Telefon Numarası:(III)" << dizi[i]->telefon3 << endl << "Adres:" << dizi[i]->adres << endl << "E-Mail(I):" << dizi[i]->mail << endl << "E-Mail(II):" << dizi[i]->mail2 << endl;
                cout << "***********************************************************************************************" << endl;
            }
        }
        if (counter == 0)
        {
            cout << "Rehber Boş!!" << endl;
            return;
        }
        cout << "\nDüzenlemek İstedeğiniz Kullanıcının Birinci Telefon Numarasını Giriniz...";
        cin >> k;
        int h = mod_fonksiyonu(k);
        while (dizi[h] != NULL && dizi[h]->telefon != k)
        {
            h = mod_fonksiyonu(h + 1);
        }
        if (dizi[h] == NULL)
            cout << "Aranan Kişi Yok!!! " << endl;
        else
            cout << "Düzenlenecek Kişi Bilgileri; " << endl<<"***********************"<<endl;
            cout << "Ad:" << dizi[h]->isim << endl << "Soyad:" << dizi[h]->soyisim << endl << "Telefon Numarası(I):" << dizi[h]->telefon << endl << "Telefon Numarası(II):" << dizi[h]->telefon2 << endl << "Telefon Numarası:(III)" << dizi[h]->telefon3 << endl << "Adres:" << dizi[h]->adres << endl << "E-Mail(I):" << dizi[h]->mail << endl << "E-Mail(II):" << dizi[h]->mail2 << endl;
            cout << "\nDeğiştirmek İstediğiniz Bilgiyi Seçiniz:";
            cout << "\n1.) İsmi Düzenle";
            cout << "\n2.) Soyismi Düzenle";
            cout << "\n3.) Birinci Telefon Numarasını Düzenle";
            cout << "\n4.) İkinci Telefon Numarasını Ekle/Düzenle";
            cout << "\n5.) Üçüncü Telefon Numarasını Ekle/Düzenle";
            cout << "\n6.) Adresi Düzenle";
            cout << "\n7.) E-Mail Düzenle";
            cout << "\n8.) İkinci E-Mail Ekle/Düzenle";
            cout << "\n9.) Çıkış";
            cout << "\n";
        cin >> choice;
        while (!choice || (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nGeçersiz  girdi !!!.Lütfen Geçerli Bir Girdi Giriniz(1-2)." << endl;
            cout << "\nDeğiştirmek İstediğiniz Bilgiyi Seçiniz:";
            cout << "\n1.) İsmi Düzenle";
            cout << "\n2.) Soyismi Düzenle";
            cout << "\n3.) Telefon Numarasını Düzenle";
            cout << "\n4.) İkinci Telefon Numarasını Ekle/Düzenle";
            cout << "\n5.) Üçüncü Telefon Numarasını Ekle/Düzenle";
            cout << "\n6.) Adresi Düzenle";
            cout << "\n7.) E-Mail Düzenle";
            cout << "\n8.) İkinci E-Mail Ekle/Düzenle";
            cout << "\n9.) Çıkış";
            cout << "\n";
            cin >> choice;
        }
        switch (choice)
        {
        case 1: cout << "\nYeni İsmi Giriniz:";
            cin.ignore();
            getline(cin, yeni);
            dizi[h]->isim = yeni;
            break;
        case 2: cout << "\nYeni Soyismi Giriniz:";
            cin.ignore();
            getline(cin, yeni);
            dizi[h]->soyisim = yeni;
            break;
        case 3: cout << "\nYeni Telefon Numarasını Giriniz:";
            /*Bu ddüzenleme diğerlerine göre önem arz etmektedir.Çünkü key olarak kullanığımız numara değişimi söz konusudur.Öncelikle
            kullanıcıdan yeni numara alınır ve tüm kayıtlarla karşılaştırılıp eşleşen var mı diye kontrol edilir.
            Ardından eşleşme yoksa(bu durum bool ile kontrol edilmektedir.)yeni kayıt ekleme yapılır ve eski kayıt silinip 
            içerisi NULL yapılır.*/
            cin >> newkey;
            for (int i = 0; i < T_S; i++)//tüm dizi for ile gezildi ve if ile doluluk kontrollü yapıldı.
            {
                if (dizi[i] != NULL)
                {
                    if (dizi[i]->telefon==newkey)
                    {
                        cout << "Birinci Telefon Numarası Eşleşen Başka Bir Kayıt Var..." << endl;
                        cout<<"Bilgiyi üzerine yazmak istiyor musunuz?" <<"evet-hayır"<< endl;
                        cin >> kontrol;
                        if (kontrol == "evet");
                        {
                            temp1 = dizi[i]->isim;
                            temp2 = dizi[i]->soyisim;
                            temp3 = dizi[i]->adres;
                            temp4 = dizi[i]->telefon2;
                            temp5 = dizi[i]->telefon3;
                            temp6 = dizi[i]->mail;
                            temp7 = dizi[i]->mail2;
                            cout << temp1 << endl << temp2 << endl  ;
                            delete dizi[i];
                            dizi[i] = NULL;
                            database();
                            kayit_ekle(newkey, temp1,temp2, temp3, temp4, temp5, temp6, temp7);
                            state = false;
                            break;
                        }
                        if (kontrol == "hayır")
                        {   cout << "Düzenleme Başarısız..." << endl;
                            database();
                            state = false;
                            break;
                        }
                    }
                }
            }
            if (state == true)
            {
                temp1, temp2, temp3, temp4, temp5, temp6, temp7 = dizi[h]->isim, dizi[h]->soyisim, dizi[h]->adres, dizi[h]->telefon2, dizi[h]->telefon3, dizi[h]->mail, dizi[h]->mail2;
                delete dizi[h];
                dizi[h] = NULL;
                database();
                kayit_ekle(newkey, temp1, temp2, temp3, temp4, temp5, temp6, temp7);
                break;
            }
            else;
                break;
        case 4: cout << "\nYeni Telefon Numarasını Giriniz:";
            cin >> yeni;
            dizi[h]->telefon2 = yeni;
            break;
        case 5: cout << "\nYeni Telefon Numarasını Giriniz:";
            cin >> yeni;
            dizi[h]->telefon3 = yeni;
            break;
        case 6: cout << "\nYeni Adresi Giriniz:";
            cin.ignore();
            getline(cin, yeni);
            dizi[h]->adres = yeni;
            break;
        case 7: cout << "\nYeni E-Mail Giriniz:";
            cin >> yeni;
            dizi[h]->mail = yeni;
            break;
        case 8: cout << "\nYeni E-Mail Giriniz.:";
            cin >> yeni;
            dizi[h]->mail2 = yeni;
            break;
        case 9:
            break;
        default:
            cout << choice << " geçerli bir girdi değil.Lütfen geçerli bir girdi giriniz" << endl;
            break;
        }
    }
    void database()
    {/*Bu fonksiyonun temel kullanım amacı ,başlangıçta sunulan 5 seçeneğin ardından .txt uzantılı veritabanını güncellemektir.
     bunu yaparken tüm rehber for ile gezilir ve içi boş değilse içinde kayıt bilgileri satır satır veritabanına yazdırılır
     tüm rehber gezildikten sonra dosya kapatılır.*/
        fstream myfile;
        myfile.open("database.txt", ios::out);
        int counter = 0;
        for (int i = 0; i < T_S; i++)
        {
            if (dizi[i] != NULL)
            {
                if (myfile.is_open()) {
                    myfile << dizi[i]->isim << endl;
                    myfile << dizi[i]->soyisim << endl;
                    myfile << dizi[i]->telefon << endl;
                    myfile << dizi[i]->telefon2 << endl;
                    myfile << dizi[i]->telefon3 << endl;
                    myfile << dizi[i]->adres << endl;
                    myfile << dizi[i]->mail << endl;
                    myfile << dizi[i]->mail2 << endl;
                }
            }
        }
        myfile.close();
    }
    void veritabanı_aktar()
    {/*Veri tabanından tüm rehberi programı aktarmak için kullanılır.Öncelikle biz biliyoruz ki bir kayıt için maksimum 8 bilgi mevcut.
     Bu fonksşyon içinde de 8 elamanlı bir dizi tanımlanır.Bu dizi bizim her bir kaydın bilgilerini programa aktarmada yardımcı olacaktır
     Öncelikle dosya açılır ve while içinde for döngüsü kullanılarak satır satır okuma işlemi yapılır.
     Okunan her satır bir kaydın bir bilgisini vermektedir.Bu böyule devam ederek 8 satırlık bir bilgi alınır.Yani bir kayıdın tüm bilgileri.
     İŞte bu mantıkla her okunan 8 satır bir kaydın tüm bilgileri olarak yeni kayıt kelme fonksiyonu ile programa aktarılır.*/
        int ozimozi, key;
        string line;
        string kayit[8];
        fstream myfile("database.txt");
        if (myfile.is_open())
        {
            ozimozi = 10;
            while (ozimozi == 10)
            {
                for (int i = 0; i < 8; i++)
                {
                    getline(myfile, line);
                    if (line == "")
                    {
                        ozimozi = 9;
                        break;
                    }
                    kayit[i] = line;
                }
                if (line != "")
                {
                    key = std::stoi(kayit[2]);
                    kayit_ekle(key, kayit[0], kayit[1], kayit[5], kayit[3], kayit[4], kayit[6], kayit[7]);
                }
            }
            myfile.close();
        }
        else
        { 
            fstream myfile;
            myfile.open("database.txt", ios::out);
        }
    }
    ~hash_adres_defteri()
    {
        for (int i = 0; i < T_S; i++)
        {
            if (dizi[i] != NULL)
                delete dizi[i];
            delete[] dizi;
        }
    }
};
int main()
{/*main programın kendisi olarak değerlendirilebilr.Amaç yukarıda tanımlanan sınıf yapısını kulllanarak işlevsel adres defteri yapmaktır.
 öncelikle yeni kayıtta,seçim ekranlarında kullanılacak değişkenler tanımlanmıştır.Ardındana ana menü gelmeden önce veritabanındaki kayıtlar 
 programa aktalır.Daha sonrasında witch-case yapısı kulllanılarak ana menüden yapılacak işlemin seçimi istenir.Kullanıcıdan alınan girdiler while
 kontrole sokulur ve geçerli bir girdinin programa verilmesi sağlanır.Her switch-case durumu sonrası txt uzantılı veritabanı güncellenir.*/
    setlocale(LC_ALL, "turkish");
    hash_adres_defteri defter;
    int telefon;
    stringstream ss;
    string telefonara;
    string isim, soyisim, telefon2, telefon3, adres, mail, mail2, aranan;
    int c, search_choice, i = 0;
    int choice, kont, kont1, kont2;
    defter.veritabanı_aktar();
    cout << "**Welcome to Address Book**" << endl;
    while (1)
    {
        cout << "\nLütfen Yapılacak İşlemi Seçiniz: " << endl;
        cout << "1. Rehberi Göster" << endl;
        cout << "2. Kayıt Ara" << endl;
        cout << "3. Yeni Kişi Ekle" << endl;
        cout << "4. Kişi Sil" << endl;
        cout << "5. Kaydı Düzenle" << endl;
        cout << "6. Programdan Çık" << endl;
        cout << "(Büyük-Küçük Harf Duyarlılığı Vardır)\n" << endl;
        cin >> choice;
        if (!cin)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Geçersiz  girdi !!!.Lütfen geçerli bir girdi giriniz.(1-6)" << endl;
        }
        else
        {
            switch (choice)
            {
            case 1:
                cout << endl;
                defter.rehberi_goster();
                defter.database();
                break;
            case 2:
                cout << "\nİsme göre aramak için 1 , Telefon numarasına göre aramak için 2 giriniz: ";
                cin >> search_choice;
                while (!search_choice || (search_choice != 1 && search_choice != 2))
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "\nGeçersiz  girdi !!!.Lütfen Geçerli Bir Girdi Giriniz(1-2)." << endl;
                    cout << "\nİsme göre aramak için 1 , Telefon numarasına göre aramak için 2 giriniz: ";
                    cin >> search_choice;
                }
                switch (search_choice)
                {
                case 1:
                    cout << "\nİsmi tam&kısım giriniz: ";
                    cin >> aranan;
                    defter.isme_göre_kayit_ara(aranan);
                    defter.database();
                    break;
                case 2:
                    cout << "\nTelefon numarasını tam giriniz: ";
                    cin >> telefon;
                    ss << telefon;
                    telefonara = ss.str();
                    defter.numaraya_göre_ara(telefon,telefonara);
                    defter.database();
                    break;
                default:
                    cout << "Geçersiz  girdi !!!.Lütfen geçerli bir girdi giriniz.(1-2)" << endl;
                    break;
                }
                defter.database();
                break;
            case 3:
                cout << "\nİsmi Giriniz: ";
                cin.ignore();
                getline(cin, isim);
                cout << "\nSoyismi Giriniz: ";
                cin.ignore();
                getline(cin, soyisim);
                cout << "\nTelefon Numarasını Giriniz: ";
                cin >> telefon;
                while (!cin) 
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "\nGeçersiz  girdi !!!.Lütfen sadece nümerik karakter kullnın." << endl;
                    cout << "\nTelefon Numarasını Giriniz: ";
                    cin >> telefon;
                }
                cout << "\nİkinci Telefon Numarasını Girecek Misiniz?(EVET=>1,HAYIR=>2): ";
                cin >> kont;
                while (!cin || (kont != 1 && kont != 2)) 
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "\nGeçersiz  girdi !!!.Lütfen geçerli girdi giriniz(1-2)" << endl;
                    cout << "\nİkinci Telefon Numarasını Girecek Misiniz?(EVET=>1,HAYIR=>2): ";
                    cin >> kont;
                }
                if (kont==1)
                {
                    cout << "\nİkinci Telefon Numarasını Giriniz: ";
                    cin >> telefon2;
                    cout << telefon2 << endl;
                    cout << "\nÜçüncü Telefon Numarasını Girecek Misiniz?(EVET=>1,HAYIR=>2): ";
                    cin >> kont1;
                    while (!cin || (kont1 != 1 && kont1 != 2))
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "\nGeçersiz  girdi !!!.Lütfen geçerli girdi giriniz(1-2)" << endl;
                        cout << "\nÜçüncü Telefon Numarasını Girecek Misiniz?(EVET=>1,HAYIR=>2): ";
                        cin >> kont1;
                    }
                    if (kont1 == 1)
                    {
                        cout << "\nÜçüncü Telefon Numarasını Giriniz: ";
                        cin >> telefon3;
                    }
                    if (kont1 == 2)
                    {
                        telefon3 = "---";
                    }
                }
                if (kont==2)
                {
                    telefon2 = "---";
                    telefon3 = "---";
                }
                cout << "\nAdres Giriniz: ";
                cin.ignore();
                getline(cin, adres);
                cout << "\nE-Mail Giriniz: ";
                cin >> mail;
                cout << "\nİkinci Mail Adresi Girecek Misiniz?(EVET=>1,HAYIR=>2): ";
                cin >> kont2;
                while (!cin || (kont2 != 1 && kont2 != 2)) 
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "\nGeçersiz  girdi !!!.Lütfen geçerli girdi giriniz(1-2)" << endl;
                    cout << "\nİkinci Mail Adresi Girecek Misiniz?(EVET=>1,HAYIR=>2): ";
                    cin >> kont2;
                }
                switch (kont2)
                {
                case 1:
                    cout << "\nİkinci Mail Adresini Giriniz: ";
                    cin >> mail2;
                case 2:
                    mail2 = "---";
                }
                defter.kayit_ekle(telefon, isim, soyisim, adres, telefon2, telefon3, mail, mail2);
                cout << endl;
                defter.database();
                break;
            case 4:
                cout << "\nİsme göre silmek için 1 , Telefon numarasına göre silmek için 2 giriniz: ";
                cin >> search_choice;
                if (search_choice == 1)
                {
                    cout << "Silmek İstediğiniz Kayıdın İsmini tam&kısım Giriniz ";
                    cin >> aranan;
                    defter.isme_göre_kayit_sil(aranan);
                    defter.database();
                    break;
                }
                if (search_choice == 2)
                {
                    cout << "Silmek İstediğiniz Kayıdın Telefon Numarasını tam Giriniz ";
                    cin >> telefon;
                    defter.numaraya_göre_kayit_sil(telefon);
                    defter.database();
                    break;
                }
                if (search_choice != 1 && search_choice != 2)
                {
                    cout << "\n" << search_choice << "geçerli bir girdi değil.Lütfen geçerli bir girdi giriniz" << endl;
                    break;
                }
                defter.database();
                break;
            case 5:
                cout << endl;
                defter.kaydi_duzenle();
                defter.database();
                break;
            case 6:
                cout << "***********" << endl << "İyi Günler Dileriz" << endl << "***********" << endl;
                defter.database();
                exit(1);
            default:
                cout << "Geçersiz  girdi !!!.Lütfen geçerli bir girdi giriniz.(1-6)" << endl;
                break;
            }
        }
    }
    system("pause");
    return 0;
}
/*this program created by;
 ____ozan peker_____
 ________151110051________*/