#include<iostream>
#include <conio.h>
#include <windows.h>
using namespace std;



void mySetColor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}
class Menu {
private:
	int _id;
	char* _name;
	double _menuRating;
	char* _category;
	double _price;
	double _tax;
public:
	Menu()
	{
		_id = 0;
		_name = nullptr;
		_menuRating = 0;
		_category = nullptr;
		_price = 0;
		_tax = 0;
	}
	Menu(const int id, const char* name, const double menurating, const char* category, const int price, const int tax)
	{
		SetId(id);
		SetName(name);
		SetMenuRating(menurating);
		SetCategory(category);
		SetPrice(price);
		SetTax(tax);
	}
	int GetId() { return _id; }
	char* GetName() { return _name; }
	double GetMenuRating() { return _menuRating; }
	char* GetCategory() { return _category; }
	double GetPrice() { return _price; }
	double GetTax() { return _tax; }
	void SetId(const int id) {
		if (id >= 0) _id = id;
	}
	void SetName(const char* name) {
		if (name == nullptr) return;

		int len = strlen(name);
		_name = new char[len + 1];
		strcpy_s(_name, len + 1, name);
	}
	void SetMenuRating(const double menurating) {
		if (menurating >= 0) _menuRating = menurating;
	}
	void SetCategory(const char* category) {
		if (category == nullptr) return;

		int len = strlen(category);
		_category = new char[len + 1];
		strcpy_s(_category, len + 1, category);
	}
	void SetPrice(const double price) {
		if (price >= 0) _price = price;
	}
	void SetTax(const double tax) {
		if (tax >= 0) _tax = tax;
	}
	friend ostream& operator<<(ostream& out, const Menu& menu);
	friend istream& operator>>(istream& in, Menu& menu);
	void Print() {
		cout << "ID:-> " << _id << endl;
		cout << "Name: " << GetName() << endl;
		cout << "Menu rating: " << _menuRating << endl;
		cout << "Category: " << GetCategory() << endl;
		cout << "Price: " << _price << endl;
		cout << "Tax: " << _tax << endl;
	}

};




class Restaurant {
private:
	int _restoran_no;
	char* _name;
	char* _adress;
	char* _phoneNumber;
	int _rating;
	double _avgCost;
	int _size;

public:
	int MaxMenuCount = 10;
	Menu* _menus;

	Restaurant() :_restoran_no(), _name(), _adress(), _phoneNumber(), _rating(), _avgCost(), _size() {}
	Restaurant(const int restoranno, const char* name, const char* adress, const char* phonenumber, Menu* menus, int size)
	{
		SetRestoranNo(restoranno);
		SetName(name);
		SetAdress(adress);
		SetSize(size);
		SetPhoneNumber(phonenumber);
		SetMenus(menus);


	}
	int GetRestoranNo() {
		return _restoran_no;
	}
	int GetSize() {
		return _size;
	}
	char* GetName() {
		return _name;
	}
	char* GetAdress() {
		return _adress;
	}
	char* GetPhoneNumber() {
		return _phoneNumber;
	}
	double GetRating() {
		return _rating;
	}
	double GetAvgCost() {
		return _avgCost;
	}
	Menu* GetMenus() {
		return _menus;
	}
	void SetRestoranNo(const int restoranno) {
		if (restoranno >= 0) _restoran_no = restoranno;
	}
	void SetName(const char* name) {
		if (name == nullptr) return;
		int len = strlen(name);
		_name = new char[len + 1];
		strcpy_s(_name, len + 1, name);
	}
	void SetAdress(const char* adress) {
		if (adress == nullptr) return;
		int len = strlen(adress);
		_adress = new char[len + 1];
		strcpy_s(_adress, len + 1, adress);
	}
	void SetPhoneNumber(const char* phonenumber) {
		if (phonenumber == nullptr) return;
		int len = strlen(phonenumber);
		_phoneNumber = new char[len + 1];
		strcpy_s(_phoneNumber, len + 1, phonenumber);
	}
	void SetSize(int size) {
		if (_size >= 0) _size = size;
	}

	double  RestaurantRating() {
		double temp = 0;
		for (size_t i = 0; i < _size; i++)
		{
			temp += _menus[i].GetMenuRating();

		}
		temp /= _size;
		_rating = temp;
		return _rating;

	}
	void SetMenus(Menu* menus) {
		this->_menus = new Menu[_size];
		_menus = menus;
	}
	double RestaurantAvgCost() {
		double temp = 0;
		for (size_t i = 0; i < _size; i++)
		{
			temp += _menus[i].GetPrice();

		}
		temp /= _size;
		_avgCost = temp;
		return _avgCost;
	}
	void SortWithRatingandColor() {
		double* arr = new double[_size - 1]{};
		for (size_t i = 0; i < _size; i++)
		{
			arr[i] = _menus[i].GetMenuRating();
		}

		int temp, n, i, j;
		for (i = 0; i < _size; i++)
		{
			for (j = i + 1; j < _size; j++)
			{
				if (arr[i] > arr[j])
				{
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}

		for (i = 0; i < _size; i++)
		{
			for (j = 0; j < _size; j++)
			{
				if (arr[i] == _menus[j].GetMenuRating()) {
					if (_menus[j].GetMenuRating() > 5) {
						mySetColor(6, 0);
						_menus[j].Print();
						mySetColor(7, 0);

					}
					else {
						mySetColor(2, 0);
						_menus[j].Print();
						mySetColor(7, 0);
					}
				}
			}
		}
	}
	void AddMenu() {
		Menu temp;
		cin >> temp;
		int newsize = _size + 1;
		Menu* newmenus = new Menu[newsize]{};
		for (size_t i = 0; i < newsize; i++)
		{
			if (i == newsize - 1) {
				newmenus[i] = temp;
				break;
			}
			newmenus[i] = _menus[i];
		}
		delete[]_menus;
		_menus = newmenus;
		newmenus = nullptr;
		SetSize(_size + 1);

	}
	void DeleteMenu(const int id) {
		for (size_t i = 0; i < _size; i++)
		{
			if (_menus[i].GetId() == id) {
				continue;
			}
			_menus[i].Print();
		}
	}
	void IncreaseById(int id) {
		for (size_t i = 0; i < _size; i++)
		{
			if (_menus[i].GetId() == id) {
				double temp = _menus[i].GetMenuRating();
				_menus[i].SetMenuRating(temp + 1);
			}
		}
	}
	void DecraeseById(int id) {
		for (size_t i = 0; i < _size; i++)
		{
			if (_menus[i].GetId() == id) {
				double temp = _menus[i].GetMenuRating();
				_menus[i].SetMenuRating(temp - 1);
			}
		}
	}
	void UpdateMenu(int id) {
		for (size_t i = 0; i < _size; i++)
		{
			if (_menus[i].GetId() == id) {
				int change;
				char* changedName = new char[50];
				double changedMenuRating;
				char* changedCategory = new char[50];
				double changedPrice;
				double changedTax;

				cout << "1)Change Name " << endl;
				cout << "2)Change Menu rating  " << endl;
				cout << "3)Change Category " << endl;
				cout << "4)Change Price " << endl;
				cout << "5)Change Tax " << endl;
				cout << "Enter your number for change menu: ";
				cin >> change;
				if (change == 1) {
					cout << "New  Name: ";
					cin >> changedName;
					_menus[i].SetName(changedName);
				}
				else if (change == 2) {
					cout << "New  Menu Rating: ";
					cin >> changedMenuRating;
					_menus[i].SetMenuRating(changedMenuRating);
				}
				else if (change == 3) {
					cout << "New  Category: ";
					cin >> changedCategory;
					_menus[i].SetCategory(changedCategory);
				}
				else if (change == 4) {
					cout << "New Price: ";
					cin >> changedPrice;
					_menus[i].SetPrice(changedPrice);
				}
				else if (change == 5) {
					cout << "New Tax: ";
					cin >> changedTax;
					_menus[i].SetTax(changedTax);
				}

			}
		}
	}

	friend istream& operator>>(istream& in, const Restaurant& restaurant);

	friend ostream& operator<<(ostream& out, const  Restaurant& restaurant);
	void Print() {
		mySetColor(4, 0);
		if (_name != nullptr) cout << "Restaurant Name: " << GetName() << endl;
		if (_adress != nullptr) cout << "Restaurant Adress: " << GetAdress() << endl;
		if (_phoneNumber != nullptr) cout << "Phone Number +" << GetPhoneNumber() << endl;
		cout << "Restaurant Rating: " << RestaurantRating() << endl;
		cout << "Restaurant Average Cost : " << RestaurantAvgCost() << endl;
		mySetColor(7, 0);
		SortWithRatingandColor();
	}

};
ostream& operator<<(ostream& out, const  Menu& menu) {
	out << "Id : " << menu._id << endl;
	out << "Name : " << menu._name << endl;
	out << "MenuRating : " << menu._menuRating << endl;
	out << "Category : " << menu._category << endl;
	out << "Price : " << menu._price << endl;
	out << "Tax : " << menu._tax << endl;
	return out;
}
istream& operator>>(istream& in, Menu& menu) {

	cout << "Enter Id : ";
	int id;
	in >> id;
	menu.SetId(id);
	in.ignore();
	cout << "Enter name : ";
	char* buffer1 = new char[50];
	in.getline(buffer1, 50);
	menu.SetName(buffer1);

	cout << "Enter category : ";
	char* buffer2 = new char[50];
	in.getline(buffer2, 50);
	menu.SetCategory(buffer2);
	delete[] buffer2;

	cout << "Enter menu rating : ";
	double menuRating;
	in >> menuRating;
	menu.SetMenuRating(menuRating);


	cout << "Enter Price : ";
	int price;
	in >> price;
	menu.SetPrice(price);
	cout << "Enter Tax : ";
	int tax;
	in >> tax;
	menu.SetTax(tax);

	return in;

}
ostream& operator<<(ostream& out, const  Restaurant& restaurant) {
	mySetColor(4, 0);
	out << "Restaurant No: " << restaurant._restoran_no << endl;
	out << "Restaurant Name: " << restaurant._name << endl;
	out << "Restaurant Adress: " << restaurant._adress << endl;
	out << "Restaurant Phone Number: " << restaurant._phoneNumber << endl;
	cout << "Restaurant Rating: " << restaurant._rating << endl;
	cout << "Restaurant Average Cost : " << restaurant._avgCost << endl;
	mySetColor(7, 0);
	double* arr = new double[restaurant._size - 1]{};
	for (size_t i = 0; i < restaurant._size; i++)
	{
		arr[i] = restaurant._menus[i].GetMenuRating();
	}

	int temp, n, i, j;
	for (i = 0; i < restaurant._size; i++)
	{
		for (j = i + 1; j < restaurant._size; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	for (i = 0; i < restaurant._size; i++)
	{
		for (j = 0; j < restaurant._size; j++)
		{
			if (arr[i] == restaurant._menus[j].GetMenuRating()) {
				if (restaurant._menus[j].GetMenuRating() > 5) {
					mySetColor(6, 0);
					restaurant._menus[j].Print();
					mySetColor(7, 0);

				}
				else {
					mySetColor(2, 0);
					restaurant._menus[j].Print();
					mySetColor(7, 0);
				}
			}
		}
	}




	return out;
}
istream& operator>>(istream& in, Restaurant& restaurant) {
	cout << "Enter menus size: ";
	int size;
	in >> size;
	for (int i = 0;; i++)
	{
		if (size > restaurant.MaxMenuCount) {
			cout << "Warning:Size is bigger than max menu count size!!!!!" << endl;
			cout << "Try again: " << endl;
			in >> size;
		}
		else break;
	}
	restaurant.SetSize(size);

	Menu* menus = new Menu[size];
	cout << "Enter restoran No: ";
	int restoranNo;
	cin >> restoranNo;
	restaurant.SetRestoranNo(restoranNo);
	in.ignore();
	char* buffer = new char[50];
	cout << "Enter Restaurant Name: ";
	cin.getline(buffer, 50);
	restaurant.SetName(buffer);
	char* buffer2 = new char[50];
	cout << "Enter Restaurant Adress: ";
	cin.getline(buffer2, 50);
	restaurant.SetAdress(buffer2);
	char* buffer3 = new char[50];
	cout << "Enter Restaurant Phone Number: ";
	cin.getline(buffer3, 50);
	restaurant.SetPhoneNumber(buffer3);

	for (size_t i = 0; i < size; i++)
	{
		cin >> menus[i];
	}
	restaurant.SetMenus(menus);
	return in;
}


void main() {
	//CIN COUT OVERLOADING
	/*Restaurant A1;
	cin >> A1;
	cout << A1;*/



	int size = 3;
	Menu menu1(1, "Coco-cola", 8, "Ickiler", 20, 5);
	Menu menu2(2, "Kabab", 3, "Yemekler", 200, 50);
	Menu menu3(3, "Alma", 12, "Meyveler", 20, 2);
	Menu* menus = new Menu[size]{
		menu1,menu2,menu3
	};
	Restaurant A1(356, "Zeytun", "Baki 20 yanvar", "994557134655", menus, size);
	A1.Print();
	/*A1.UpdateMenu(3);//Gonderdiyimiz id ye menyunun yeni fieldlerini daxil ederek update edir
	cout << A1;*/
	//A1.DecraeseById(2);//ID ye gore menu ratingini 1 vahid azaldir
	//cout << A1;
	//A1.DeleteMenu(3);//Id ye gore menunu silir
	//A1.IncreaseById(2);//ID ye gore menu ratingini 1 vahid artirir
	//cout << A1;
	/*A1.AddMenu();//Girdiyimiz fieldleri menu siyahisina elave edir
	cout << A1;*/

}