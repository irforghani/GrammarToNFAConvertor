#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdio>
using namespace std;
ifstream file;
struct trans
{
	trans(string s,string d,char v )
	{
		source = s;
		destination = d;
		value = v;
	}
	string source;
	string destination;
	char value;
};
struct state
{
	state(string n)
	{
		name = n;
	}
	string name;
	vector<trans> t;


};
int getnum(vector<state>vec, string f)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (strcmp(vec[i].name.c_str(),f.c_str()) == 0)
			return i;
	}
	return -1;
}
int main()
{
	int sn=0;
	state cur("S");
	file.open("input.txt");
	int tnum,vnum;
	char *t,*v;
	vector<string>*pr;
	file >> tnum;
	t = new char[tnum-1];
	for (int i = 0; i < tnum; i++)
	{
		file >> t[i];
	}
	file >> vnum;
	v = new char[vnum - 1];
	for (int i = 0; i < tnum; i++)
	{
		file >> v[i];
	}
	pr = new vector<string>[vnum];
	int temp;
	string temp2;
	
	for (int i = 0; i < vnum; i++)
	{
		file >> temp;
		for (int j = 0; j < temp; j++)
		{
			file >> temp2;
			pr[i].push_back(temp2);
		}
		
	}
	vector<state>nfa;

	for (int i = 0; i < vnum; i++)
	{
		state temp(to_string(v[i]));
		nfa.push_back(temp);
	}
	cur = nfa[getnum(nfa, to_string(v[0]))].name;
	for (int i = 0; i <vnum; i++)
	{
		for (int j = 0; j < pr[i].size(); j++)
		{
			cur = nfa[getnum(nfa, to_string(v[i]))];
			state temp1(to_string(sn++));
			nfa.push_back(temp1);
			trans trans1(cur.name, temp1.name, '&');
			nfa[getnum(nfa, cur.name)].t.push_back(trans1);
			cur = temp1;
			for (int k = 0; k < pr[i][j].size(); k++)
			{

				if (islower(pr[i][j][k]))
				{
					state temp2(to_string(sn++));
					nfa.push_back(temp2);
					trans trans2(cur.name, temp2.name, pr[i][j][k]);
					nfa[getnum(nfa, cur.name)].t.push_back(trans2);
					cur = temp2;
				}
				else
				{
					trans trans2(cur.name, to_string(pr[i][j][k]), '&');
					nfa[getnum(nfa, cur.name)].t.push_back(trans2);
					cur = nfa[getnum(nfa, to_string(pr[i][j][k]))];
				}
			}
		}

	}
	for (int i = 0; i < nfa.size(); i++)
	{
		cout << "state " << nfa[i].name << endl;
		for (int j = 0; j < nfa[i].t.size(); j++)
		{
			cout << "from " << nfa[i].t[j].source << " with " << nfa[i].t[j].value << " to " << nfa[i].t[j].destination << endl;
		}

	}
	system("pause>null");
	return 0;
}

