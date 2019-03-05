/*void listAll(string path, const MenuItem* m) // two-parameter overload
{
	if (m->menuItems() == nullptr)  //base case
		return;
	for (vector<MenuItem*>::const_iterator it = (m->menuItems())->begin(); it != (m->menuItems())->end(); it++)
	{
		cout << path + (*it)->name() << endl;
		if ((*it)->menuItems() != nullptr)
			listAll(path + (*it)->name() + "/", (*it));
	}
}*/