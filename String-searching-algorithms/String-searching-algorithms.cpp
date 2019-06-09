// String-searching-algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "SearchingAlgorithms.h"
#include <functional>

#define CYCLES_NUMBER 1;

int main()
{
  setlocale(LC_ALL, "Russian");

  cout << "Loading file with code\n";

  string filenameHay = "bible.txt";
  ifstream infileHay(filenameHay);
  string haystack = (std::stringstream() << infileHay.rdbuf()).str();

  infileHay.close();
  cout << "\nFile loaded\n";

  haystack.erase(remove_if(haystack.begin(), haystack.end(),
    [](const std::string::value_type& value) {return value == '\n' || value == '\r'; }), haystack.end());


  cout << "Loading file with patterns\n";

  string filenamePat = "patterns.txt";
  ifstream infilePat(filenamePat);
  string patterns = (std::stringstream() << infilePat.rdbuf()).str();

  infilePat.close();
  cout << "\nFile loaded\n";

  vector<string> needles;
  ReadingPatterns(patterns, needles);

  //vector<string> needles = { "void ThisIsATestForSearch()",
  //                           "MoonKnighttt",
  //                           "Phoenixxx",
  //                           "De\nserttt",
  //                           "Renegateee",
  //                           "if (IsErrorActive(1011) && !isOK)",
  //                           "ApplyRuleG_1011_RawFunCall(*this, result, pSrcPtree);",
  //                           "if (IsErrorActive(1023))",
  //                           "ApplyRuleG_1023(*this, result);",
  //                           "ApplyRuleG_1025(*this, result);",
  //                           "if (IsErrorActive(1025))",
  //                           "Unicornsss",
  //                           "void ChangeLanguage(char *langgg)",
  //                           "strcpy_s(Config.Lannnggg, lang);",
  //                           "SaveConfiiigg",
  //                           "void ThisIsATestForTheSearch()"};
  SortingStrings(needles);

  for (auto &needle : needles)
  {
    needle.erase(remove_if(needle.begin(), needle.end(),
      [](const std::string::value_type& value) {return value == '\n' || value == '\r'; }), needle.end());
  }




  clock_t start, end; // часы

  size_t haystack_len = haystack.length();
  vector<size_t> needles_length;
  needles_length.reserve(needles.size());
  for ( size_t i = 0; i < needles.size(); ++i )
  {
    needles_length.push_back(needles[i].length());
  }

  vector<prefix_function> p_func;
  vector<occtable_type>   occ;
  vector<skiptable_type>  skip;

  for (size_t i = 0; i < needles.size(); ++i)
  {
    p_func.push_back(PrefFunction(needles[i]+(string)"#"+(string)haystack, needles_length[i])); // префикс-функция
    occ.push_back(OccTable(needles[i].data(), needles_length[i])); // таблица стоп-символов
    skip.push_back(SkipTable(needles[i].data(), needles_length[i])); // таблица суффиксов
  }

  vector<size_t> needle_hash;
  for (size_t i = 0; i < needles.size(); i++)
  {
    needle_hash.push_back(0);
  }

  for (size_t i = 0; i < needles.size(); ++i)
  {
    for (size_t j = 0; j < needles_length[i]; j++)
    {
      needle_hash[i] = needle_hash[i] + (needles[i][j]) * FastPower(BASE, (needles_length[i] - j - 1));
    }
  }

  const size_t cycles_max = CYCLES_NUMBER; // количесвто циклов прогонки "тестового" поиска

  vector<size_t> result_placeNaive,
                 result_placeRK,
                 result_placeBM,
                 result_placeBMH,
                 result_placeBMHR,
                 result_placeKMP,
                 result_placeCPP,
                 result_placeRKR,
                 result_placeAhoCor;
  result_placeNaive.reserve(needles.size()*2);
  result_placeRK.reserve(needles.size() * 2);
  result_placeBM.reserve(needles.size() * 2);
  result_placeBMH.reserve(needles.size() * 2);
  result_placeBMHR.reserve(needles.size() * 2);
  result_placeKMP.reserve(needles.size() * 2);
  result_placeCPP.reserve(needles.size() * 2);
  result_placeRKR.reserve(needles.size() * 2);
  result_placeAhoCor.reserve(needles.size() * 2);

  vector<bohrVertex> bohr;

  BohrIni(bohr);

  for (int i = 0; i < needles.size(); i++)
  {
    AddingStringToBohr(needles[i], bohr);
  }

  vector<size_t> needleNums;
  needleNums.reserve(needles.size() * 2);

  start = clock();
  for (int i = 0; i < cycles_max; ++i)
  {
    needleNums.erase(needleNums.begin(), needleNums.end());
    result_placeAhoCor = FindAllPositions(haystack, bohr, needleNums);
  }
  end = clock();
  long double secondsAhoCor = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "AhoCor done\n";

  cout << "Среднее время работы: " << secondsAhoCor << '\n';

  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    //vector<size_t> positions;
    for (size_t j = 0; j < needles.size(); ++j)
    {
      size_t pos = haystack.find(needles[j], 0);
      while (pos != string::npos)
      {
        result_placeCPP.push_back(pos);
        pos = haystack.find(needles[j], pos+1);
      }
    }
   // positions.clear();
    cout << "CPP /";
  }
  end = clock();
  long double secondsCPP = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "CPP done\n";

  cout << "Результат встроенной функции СРР:\n";
  for (size_t i = 0; i < needles.size(); ++i)
  {
    cout << result_placeCPP[i] << '\n';
  }
  cout << "Среднее время работы: " << secondsCPP << "\n\n";

  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    for (size_t j = 0; j < needles.size(); j++)
      result_placeNaive.push_back(NaiveSearch(haystack.data(), haystack_len, needles[j].data(), needles_length[j]));
    cout << "Naive /";
  }
  end = clock();
  long double secondsNaive = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "Naive done\n";

  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    result_placeRK = RabinKarpwithBernstein(haystack, haystack_len, needles, needles_length);
    cout << "RK /";
  }
  end = clock();
  long double secondsRK = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "RK done\n";

  start = clock();
  for (int i = 0; i < cycles_max; ++i)
  {
    for (string_view needle : needles)
    {
      std::search(haystack.begin(), haystack.end(), boyer_moore_horspool_searcher(needle.begin(), needle.end()));
    }
  }
  end = clock();

  long double secondsCPP17 = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "CPP17:" << secondsCPP17<< '\n';
  start = clock();

  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
      result_placeKMP = KnuthMorrisPratt(haystack, haystack_len, p_func, needles, needles_length);
    cout << "KMP /";
  }
  end = clock();
  long double secondsKMP = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << secondsKMP<<"\nKMP done\n";


  for (size_t i = 0; i < cycles_max; i++)
  {
    result_placeRKR = RabinKarpwithRolling(haystack, needles, needle_hash);
    cout << "RKR /";
  }
  end = clock();
  long double secondsRKR = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "RKR done\n";

  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    for(size_t j = 0; j < needles.size(); j++)
      result_placeBM.push_back(BoyerMoore(haystack.data(), haystack_len, occ[j], skip[j], needles[j].data(), needles_length[j]));
    cout << "BM /";
  }
  end = clock();
  long double secondsBM = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "BM done\n";


  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    for (size_t j = 0; j < needles.size(); j++)
      result_placeBMH.push_back(BoyerMooreHorspool(haystack.data(), haystack_len, occ[j], needles[j].data(), needles_length[j]));
    cout << "BMH /";

  }
  end = clock();
  long double secondsBMH = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "BMH done\n";


  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    for (size_t j = 0; j < needles.size(); j++)
      result_placeBMHR.push_back(BoyerMooreHorspoolRaita(haystack.data(), haystack_len, occ[j], needles[j].data(), needles_length[j]));
    cout << "BMHR /";
  }
  end = clock();
  long double secondsBMHR = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "BMHR done\n";




  cout << "Результат наивного алгоритма:\n";
  for (size_t i = 0; i < needles.size(); ++i)
  {
    cout  << result_placeNaive[i]  << '\n';
  }
  cout << "Среднее время работы: " << secondsNaive << "\n\n";

  for (int i = 0; i < result_placeKMP.size(); ++i)
  {
    cout << result_placeCPP[i] <<"    "<<result_placeKMP[i]<<"    "<<result_placeAhoCor[i] << "    " << result_placeRKR[i] << '\n';
  }
  cout << "Результат наивного алгоритма:                                  " << result_placeNaive[0] << ". Среднее время работы: " << secondsNaive << '\n';
  cout << "Результат алгоритма Кнута-Морриса-Пратта:                      " << result_placeKMP[0] << ". Среднее время работы: " << secondsKMP << '\n';
  cout << "Результат алгоритма Бойера-Мура:                               " << result_placeBM[0] << ". Среднее время работы: " << secondsBM << '\n';
  cout << "Результат алгоритма Бойера-Мура-Хорспула:                      " << result_placeBMH[0]    << ". Среднее время работы: " << secondsBMH << '\n';
  cout << "Результат алгоритма Бойера-Мура-Хорспула c оптимизацией Раита: " << result_placeBMHR[0]   << ". Среднее время работы: " << secondsBMHR << '\n';
  cout << "Результат алгоритма Рабина-Карпа:                              " << result_placeRK[0]      << ". Среднее время работы: " << secondsRKR << '\n';
  cout << "Результат алгоритма Рабина-Карпа c rolling хэшем:              " << result_placeRKR[0]    << ". Среднее время работы: " << secondsRK << '\n';
  cout << "Результат алгоритма Ахо-Корасик:                               " << result_placeAhoCor[0] << ". Среднее время работы: " << secondsAhoCor << '\n';

  //cout << "Искомые строки: \n";
  //for (size_t i = 0; i < needles.size(); i++)
  //{
  //    cout << needles[i] << '\n';
  //}
  //cout << "\n\n";
  //cout << "Найденные строки: \n";
  //for (size_t i = 0; i < result_placeAhoCor.size(); i++)
  //{
  //  cout << "\n";
  //  for (size_t j = 0; j < needles[needleNums[i]].size(); j++)
  //  {
  //    cout << haystack[result_placeAhoCor[i] + j];
  //  }
  //}
  //cout << "\n";

  return 0;
}



