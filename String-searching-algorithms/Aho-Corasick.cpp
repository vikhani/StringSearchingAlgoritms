#include "pch.h"
#include "SearchingAlgorithms.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

vector<bohrVertex> bohr;
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

void BohrIni() 
{
  bohr.push_back(CreatingBohrVertex(0, '$'));
}

void AddingStringToBohr(const string& needle)
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

bool IsStringAddedToBohr(const string& needle)
{
  int num = 0;
  for (int i = 0; i < needle.length(); i++)
  {
    char ch = needle[i];
    if (bohr[num].nextVertex[ch] == -1)
    {
      return false;
    }

    num = bohr[num].nextVertex[ch];
  }

  return true;
}

int GetAutoMoving(int vertexIndex, char ch);

int GettingSuffLink(int vertexIndex)
{
  if (bohr[vertexIndex].suffLink == -1)
  {
    if (vertexIndex == 0 || bohr[vertexIndex].parent == 0)
    {
      bohr[vertexIndex].suffLink = 0;
    }
    else
    {
      bohr[vertexIndex].suffLink = GetAutoMoving(GettingSuffLink(bohr[vertexIndex].parent), bohr[vertexIndex].symb);
    }
  }

  return bohr[vertexIndex].suffLink;
}

int GetAutoMoving(int vertexIndex, char ch)
{
  if (bohr[vertexIndex].auto_move[ch] == -1)
  {
    if (bohr[vertexIndex].nextVertex[ch] != -1)
    {
      bohr[vertexIndex].auto_move[ch] = bohr[vertexIndex].nextVertex[ch];
    }
    else
    {
      if (vertexIndex == 0)
      {
        bohr[vertexIndex].auto_move[ch] = 0;
      }
      else
      {
        bohr[vertexIndex].auto_move[ch] = GetAutoMoving(GettingSuffLink(vertexIndex), ch);
      }
    }
  }
  return bohr[vertexIndex].auto_move[ch];
}

int GettingGoodSuffLink(int vertex)
{
  if (bohr[vertex].suffGoodLink == -1)
  {
    int u = GettingSuffLink(vertex);
    if (u == 0)
    {
      bohr[vertex].suffGoodLink = 0;
    }
    else
    {
      bohr[vertex].suffGoodLink = (bohr[u].flag) ? u : GettingGoodSuffLink(u);
    }
  }
  return bohr[vertex].suffGoodLink;
}

void Check(int vertex, int positionEnd, vector<size_t> &result)
{
  for (int u = vertex; u != 0; u = GettingGoodSuffLink(u))
  {
    if (bohr[u].flag)
    {
      //cout << i - needle[bohr[u].needleSize].length() << " " << needle[bohr[u].needleSize] << endl;
      result.push_back( positionEnd - needlesInBohr[bohr[u].needleNumber].length() );
    }
  }
}

void FindAllPositions(const string& haystack, vector<size_t> &result)
{
  int vertex = 0;
  for (int i = 0; i < haystack.length(); i++)
  {
    vertex = GetAutoMoving(vertex, haystack[i]);
    Check(vertex, i + 1, result);
  }
}

vector<size_t> CheckAhoCorWork(const vector<string> &needles, const string &haystack)
{
  vector<size_t> result;
  BohrIni();

  for (int i = 0; i < needles.size(); i++)
  {
    AddingStringToBohr(needles[i]);
  }

  FindAllPositions(haystack, result);

  return result;
}

