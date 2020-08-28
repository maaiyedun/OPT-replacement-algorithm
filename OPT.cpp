 // LRU page replacement VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

#include <map>
#include <string.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdio.h>


using namespace std;


int main() {
	int n= 0;
	int i= 0;
	int j= 0;
	int k= 0;
	int hit= 0;
	int con = 0;
	int m=0;
	string line;
	cout << "Enter the cache Size" << endl;
	cin >> n;



	ifstream myfile("gli.trc");

	while (getline(myfile, line)) {

		m++;
	}

		myfile.close();


	vector<int> p(m);
	vector<int> hi(m);

	ifstream Cfile("gli.trc");
	if (Cfile.is_open()) {
	for (i = 0; i < m; i++) {
		getline(Cfile, line);
		stringstream geek(line);
		geek>>con;

		 p[i]=con;
		}
		Cfile.close();
	}

	vector<vector<int>> a(n);
	for (i = 0; i < n; i++) {
		a[i] = vector<int>(m, -1);
	}
	map <int, int> mp;
	for (i = 0; i < m; i++) {
		vector<pair<int, int>> c;
		for (auto q : mp) {
			c.push_back({ q.second,q.first });
		}
		sort(c.begin(), c.end());
		bool hasrun = false;
		for (j = 0; j < n; j++) {
			if (a[j][i] == p[i]) {
				hit++;
				hi[i] = 1;
				mp[p[i]] = 1;
				hasrun = true;
				break;
			}
			if (a[j][i] == -1) {
				for (k = i; k < m; k++)
					a[j][k] = p[i];
				mp[p[i]]++;
				hasrun = true;
				break;
			}
		}
		if (j == n || hasrun == false) {
			for (j = 0; j < n; j++) {
				if (a[j][i] == c[c.size() - 1].second) {
					mp.erase(a[j][i]);
					for (k = i; k < m; k++)
						a[j][k] = p[i];
					mp[p[i]]++;
					break;
				}
			}
		}
		for (auto q : mp) {
			if (q.first != p[i]) {
				mp[q.first]++;
			}
		}
	}
	cout << "Page Hit " << hit << endl << "Page Fault " << m - hit << endl;
	return 0;
}


