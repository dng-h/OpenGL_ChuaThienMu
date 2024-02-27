#ifndef READ_INPUT_FILE_H
#define READ_INPUT_FILE_H
#include <iostream>
#include <string>

using namespace std;



void readV(string line, float &a, float &b, float &c)
{
	int count_space = 0;
	string numa = "", numb = "", numc = "";
	for (int i = 2; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			count_space++;
			continue;
		}
		if (count_space == 0)
		{
			numa += line[i];
		}
		if (count_space == 1)
		{
			numb += line[i];
		}
		if (count_space == 2)
		{
			numc += line[i];
		}
	}
	a = atof(numa.c_str());
	b = atof(numb.c_str());
	c = atof(numc.c_str());
}

void readVT(string line, float &a, float &b)
{
	int count_space = 0;
	string numa = "", numb = "";
	for (int i = 3; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			count_space++;
			continue;
		}
		if (count_space == 0)
		{
			numa += line[i];
		}
		if (count_space == 1)
		{
			numb += line[i];
		}
	}
	a = atof(numa.c_str());
	b = atof(numb.c_str());
}

void readVN(string line, float &a, float &b, float &c)
{
	int count_space = 0;
	string numa = "", numb = "", numc = "";
	for (int i = 3; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			count_space++;
			continue;
		}
		if (count_space == 0)
		{
			numa += line[i];
		}
		if (count_space == 1)
		{
			numb += line[i];
		}
		if (count_space == 2)
		{
			numc += line[i];
		}
	}
	a = atof(numa.c_str());
	b = atof(numb.c_str());
	c = atof(numc.c_str());
}

void readF(string line, int v[], int t[], int &n, int &num)
{
	string numv = "", numt = "", numn = "";
	int countt = 0, counts = 0;
	for (int i = 2; i <= line.size(); i++)
	{
		if (line[i] == ' ' || line[i] == '\0')
		{
			countt = 0;
			//cout << "numv = " << numv << endl;
			if (numv == "") v[counts] = 0;
			else v[counts] = atoi(numv.c_str());
			//cout << "numt = " << numt << endl;
			if (numt == "") t[counts] = 0;
			else t[counts] = atoi(numt.c_str());
			//cout << "numn = " << numn << endl;
			if (numn == "") n = 0;
			else n = atoi(numn.c_str());
			counts++;
			numv = ""; numt = ""; numn = "";
		}
		if (i < line.size() && line[i] == '/' && line[i + 1] == '/')
		{
			countt++;
			continue;
		}
		if (i < line.size() && line[i] == '/' && line[i + 1] == ' ')
			continue;
		if (line[i] == '/')
		{
			countt++;
			continue;
		}
		if (countt == 0)
		{
			numv += line[i];
		}
		if (countt == 1)
		{
			numt += line[i];
		}
		if (countt == 2)
		{
			numn += line[i];
		}
	}
	num = counts;
}

void readMaterialName(string line, string &name)
{
	name = "";
	for (int i = 7; i < line.size(); i++)
	{
		name += line[i];
	}
}

void readK(string line, float* &a, float* &d, float* &s)
{
	string str1 = "", str2 = "", str3 = "";
	int space = 0;
	for (int i = 3; i < line.size(); i++)
	{
		if (line[i] == ' ') space++;
		if (space == 0)
		{
			str1 += line[i];
		}
		if (space == 1)
		{
			str2 += line[i];
		}
		if (space == 2)
		{
			str3 += line[i];
		}
	}

	if (line[1] == 'a')
	{
		a[0] = stof(str1.c_str());
		a[1] = stof(str2.c_str());
		a[2] = stof(str3.c_str());
	}
	if (line[1] == 'd')
	{
		d[0] = stof(str1.c_str());
		d[1] = stof(str2.c_str());
		d[2] = stof(str3.c_str());
	}
	if (line[1] == 's')
	{
		s[0] = stof(str1.c_str());
		s[1] = stof(str2.c_str());
		s[2] = stof(str3.c_str());
	}
}

void readMTL(string line, string &mtlName)
{
	mtlName = "";
	for (int i = 7; i < line.size(); i++)
	{
		mtlName += line[i];
	}
}

void readUsemtl(string line, string& mtl)
{
	mtl = "";
	for (int i = 7; i < line.size(); i++)
	{
		mtl += line[i];
	}
}

void readMap_Kd(string line, string& name)
{
	name = "";
	for (int i = 7; i < line.size(); i++)
	{
		name += line[i];
	}
}
#endif