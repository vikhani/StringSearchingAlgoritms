#include "pch.h"
#include "SearchingAlgorithms.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//vector<bohrVertex> bohr;
vector<string> needlesInBohr;

bohrVertex CreatingBohrVertex(int parentName, char curSymbol)
{
  bohrVertex vertex;

  memset(vertex.nextVertex, 255, sizeof(vertex.nextVertex));
  memset(vertex.auto_move, 255, sizeof(vertex.auto_move));
  vertex.flag = false;
  vertex.suffLink = -1;
  vertex.parent = parentName;
  vertex.symb = curSymbol;
  vertex.suffGoodLink = -1;

  return vertex;
}

void BohrIni(vector<bohrVertex> &bohr)
{
  bohr.push_back(CreatingBohrVertex(0, '$'));
}

void AddingStringToBohr(const string &needle, vector<bohrVertex> &bohr)
{
  int num = 0;
  for (int i = 0; i < needle.length(); i++)
  {
    char ch = needle[i];
    if (bohr[num].nextVertex[ch] == -1)
    {
      bohr.push_back(CreatingBohrVertex(num, ch));
      bohr[num].nextVertex[ch] = bohr.size() - 1;
    }

    num = bohr[num].nextVertex[ch];
  }

  bohr[num].flag = true;
  needlesInBohr.push_back(needle);
  bohr[num].needleNumber = needlesInBohr.size() - 1;
}

bool IsStringAddedToBohr(const string &needle, vector<bohrVertex> &bohr)
{
  int num = 0;
  for (char ch : needle/*int i = 0; i < needle.length(); i++*/)
  {
    //char ch = needle[i];
    if (bohr[num].nextVertex[ch] == -1)
    {
      return false;
    }

    num = bohr[num].nextVertex[ch];
  }

  return true;
}

int GetAutoMoving(int vertexIndex, char ch, vector<bohrVertex> &bohr);

int GettingSuffLink(int vertexIndex, vector<bohrVertex> &bohr)
{
  if (bohr[vertexIndex].suffLink == -1)
  {
    if (vertexIndex == 0 || bohr[vertexIndex].parent == 0)
    {
      bohr[vertexIndex].suffLink = 0;
    }
    else
    {
      bohr[vertexIndex].suffLink = GetAutoMoving(GettingSuffLink(bohr[vertexIndex].parent, bohr),
                                                 bohr[vertexIndex].symb,
                                                 bohr);
    }
  }

  return bohr[vertexIndex].suffLink;
}

int GetAutoMoving(int vertexIndex, char ch, vector<bohrVertex> &bohr)
{
  if (bohr[vertexIndex].auto_move[ch] == -1)
  {
    if (bohr[vertexIndex].nextVertex[ch] != -1)
    {
      bohr[vertexIndex].auto_move[ch] = bohr[vertexIndex].nextVertex[ch];
    }
    else
    {
      bohr[vertexIndex].auto_move[ch] = vertexIndex == 0 ? 0 : GetAutoMoving(GettingSuffLink(vertexIndex, bohr), ch, bohr);
    }
  }
  return bohr[vertexIndex].auto_move[ch];
}

int GettingGoodSuffLink(int vertex, vector<bohrVertex> &bohr)
{
  if (bohr[vertex].suffGoodLink == -1)
  {
    int u = GettingSuffLink(vertex, bohr);
    if (u == 0)
    {
      bohr[vertex].suffGoodLink = 0;
    }
    else
    {
      bohr[vertex].suffGoodLink = (bohr[u].flag) ? u : GettingGoodSuffLink(u, bohr);
    }
  }

  return bohr[vertex].suffGoodLink;
}

vector<size_t> FindAllPositions(const string& haystack, vector<bohrVertex> &bohr, vector<size_t> &needleNums)
{
  vector<size_t> result;
  result.reserve(needleNums.size() * 2);
  size_t vertex = 0;
  for (size_t i = 0; i < haystack.length(); i++)
  {
    vertex = GetAutoMoving(vertex, haystack[i], bohr);
    for (size_t u = vertex; u != 0; u = GettingGoodSuffLink(u, bohr))
    {
      if (bohr[u].flag)
      {
       // cout << i - needle[bohr[u].needleSize].length() << " " << needle[bohr[u].needleSize] << endl;
        result.push_back(i + 1 - needlesInBohr[bohr[u].needleNumber].length());
        needleNums.push_back(bohr[u].needleNumber);
      }
    }
  }
  return result;
}
