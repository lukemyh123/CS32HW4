//Problem 1
/*#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void test()
{
	Set<int> si;
	Set<string> ss;
	assert(si.empty());
	assert(ss.empty());
	assert(si.size() == 0);
	assert(ss.size() == 0);
	assert(si.insert(10));
	assert(ss.insert("hello"));
	assert(si.contains(10));
	assert(ss.contains("hello"));
	int i;
	assert(si.get(0, i) && i == 10);
	string s;
	assert(ss.get(0, s) && s == "hello");
	assert(si.erase(10));
	assert(ss.erase("hello"));
	Set<int> si2(si);
	Set<string> ss2(ss);
	si.swap(si2);
	ss.swap(ss2);
	si = si2;
	ss = ss2;
	unite(si, si2, si);
	unite(ss, ss2, ss);
	subtract(si, si2, si);
	subtract(ss, ss2, ss);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}*/

//Problem 2
/*#include "Set.h"  // class template from problem 1
using namespace std;

class Coord
{
public:
	Coord(int r, int c) : m_r(r), m_c(c) {}
	Coord() : m_r(0), m_c(0) {}
	double r() const { return m_r; }
	double c() const { return m_c; }
private:
	double m_r;
	double m_c;
};

int main()
{
	Set<int> si;
	si.insert(7);               // OK
	Set<string> ss;
	ss.insert("7-Up");         // OK
	Set<Coord> sc;
	sc.insert(Coord(7, -7));    // error!
}
*/
/*#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MenuItem
{
public:
	MenuItem(string nm) : m_name(nm) {}
	virtual ~MenuItem() {}
	string name() const { return m_name; }
	virtual bool add(MenuItem* m) = 0;
	virtual const vector<MenuItem*>* menuItems() const = 0;
private:
	string m_name;
};

class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
{
public:
	PlainMenuItem(string nm) : MenuItem(nm) {}
	virtual bool add(MenuItem* m) { return false; }
	virtual const vector<MenuItem*>* menuItems() const { return nullptr; }
};

class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
{
public:
	CompoundMenuItem(string nm) : MenuItem(nm) {}
	virtual ~CompoundMenuItem();
	virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
	virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
private:
	vector<MenuItem*> m_menuItems;
};

CompoundMenuItem::~CompoundMenuItem()
{
	for (int k = 0; k < m_menuItems.size(); k++)
		delete m_menuItems[k];
}

void listAll(const MenuItem* m, string path) // two-parameter overload
{
	if (m->menuItems() == nullptr)  //base case
		return;
	for (vector<MenuItem*>::const_iterator it = (m->menuItems())->begin(); it != (m->menuItems())->end(); it++)
	{
		cout << path + (*it)->name() << endl;
		if ((*it)->menuItems() != nullptr)
			listAll((*it), path + (*it)->name() + "/");
	}
}

void listAll(const MenuItem* m)  // one-parameter overload
{
	if (m != nullptr)
		listAll(m, "");
}

int main()
{
	CompoundMenuItem* cm0 = new CompoundMenuItem("New");
	cm0->add(new PlainMenuItem("Window"));
	CompoundMenuItem* cm1 = new CompoundMenuItem("File");
	cm1->add(cm0);
	cm1->add(new PlainMenuItem("Open"));
	cm1->add(new PlainMenuItem("Exit"));
	CompoundMenuItem* cm2 = new CompoundMenuItem("Help");
	cm2->add(new PlainMenuItem("Index"));
	cm2->add(new PlainMenuItem("About"));
	CompoundMenuItem* cm3 = new CompoundMenuItem("");  // main menu bar
	cm3->add(cm1);
	cm3->add(new PlainMenuItem("Refresh"));  // no submenu
	cm3->add(new CompoundMenuItem("Under Development")); // no submenus yet
	cm3->add(cm2);
	listAll(cm3);
	delete cm3;
}
*/