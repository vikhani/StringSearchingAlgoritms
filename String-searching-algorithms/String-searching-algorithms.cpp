// String-searching-algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "SearchingAlgorithms.h"

#define CYCLES_NUMBER 15;

int main()
{
  setlocale(LC_ALL, "Russian");

  cout << "Loading file\n";

  string filename = "example.txt";
  ifstream infile(filename);
  //string line;
  string haystack = /*static_cast<std::stringstream const&>*/(std::stringstream() << infile.rdbuf()).str();

  //std::experimental::filesystem::path p{ filename };
  //p = std::experimental::filesystem::canonical(p);
  //size_t i = std::experimental::filesystem::file_size(p);

  //while (true) 
  //{
  //  if (!getline(infile, line)) break;
  //  haystack += (line + '\n');
  //}

  infile.close();
  cout << "\nFile loaded\n";

  vector<string> needles = { "void ThisIsATestForSearch()",
                             "MoonKnight",
                             "Phoenix",
                             "Desert",
                             "Renegate",
                             "if (IsErrorActive(1011) && !isOK)",
                             " ApplyRuleG_1011_RawFunCall(*this, result, pSrcPtree);",
                             "if (IsErrorActive(1023))",
                             "ApplyRuleG_1023(*this, result);",
                             "ApplyRuleG_1025(*this, result);",
                             "if (IsErrorActive(1025))",
                             "Unicorns",
                             "void ChangeLanguage(char *langgg)",
                             "strcpy_s(Config.Lannnggg, lang);",
                             "SaveConfiiigg",
                             "void ThisIsATestForTheSearch()"};
  SortingStrings(needles);

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
    p_func.push_back(PrefFunction(needles[i].data(), needles_length[i])); // префикс-функция
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
      needle_hash[i] = needle_hash[i] + (needles[i][j]) * pow(PRIME, (needles_length[i] - j - 1));
    }
  }


  const size_t cycles_max = CYCLES_NUMBER; // количесвто циклов прогонки "тестового" поиска
  clock_t start, end; // часы

  vector<size_t> result_placeNaive,
               //result_placeRK,
                 result_placeBM,
                 result_placeBMH,
                 result_placeBMHR,
                 result_placeKMP,
                 result_placeCPP,
                 result_placeRKR;
  //result_placeNaive.reserve(cycles_max);

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

  //start = clock();
  //for (size_t i = 0; i < cycles_max; i++)
  //{
  //  result_placeRK = RabinKarpwithBernstein(haystack.data(), n, needle.data(), m);
  //  cout << "RK /";
  //}
  //end = clock();
  //long double secondsRK = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  //cout << "RK done\n";

  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    result_placeRKR.push_back(RabinKarpwithRolling(haystack.data(), haystack_len, needles, needle_hash, needles_length));
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


  start = clock();
  for (size_t i = 0; i < cycles_max; i++)
  {
    for (size_t j = 0; j < needles.size(); j++)
      result_placeKMP.push_back(KnuthMorrisPratt(haystack.data(), haystack_len, p_func[j], needles[j].data(), needles_length[j]));
    cout << "KNP /";

  }
  end = clock();
  long double secondsKMP = (long double)(end - start) / CLOCKS_PER_SEC / cycles_max;
  cout << "KNP done\n";



  cout << "Результат наивного алгоритма:\n";
  for (size_t i = 0; i < needles.size(); ++i)
  {
    cout  << result_placeNaive[i]  << '\n';
  }
  cout << "Среднее время работы: " << secondsNaive << "\n\n";

  cout << "Результат встроенной функции СРР:\n";
  for (size_t i = 0; i < needles.size(); ++i)
  {
    cout << result_placeCPP[i]  << '\n';
  }
  cout << "Среднее время работы: " << secondsCPP << "\n\n";

  cout << "Результат алгоритма Бойера-Мура:                               " << result_placeBM[0]     << ". Среднее время работы: "  << secondsBM << '\n';
 // cout << "Результат алгоритма Рабина-Карпа:                              " << result_placeRK      << ". Среднее время работы: " << secondsRK << '\n';
  cout << "Результат алгоритма Рабина-Карпа c rolling хэшем:              " << result_placeRKR[0]    << ". Среднее время работы: " << secondsRKR << '\n';
                                                                         
  cout << "Результат алгоритма Бойера-Мура-Хорспула:                      " << result_placeBMH[0]    << ". Среднее время работы: " << secondsBMH << '\n';
  cout << "Результат алгоритма Бойера-Мура-Хорспула c оптимизацией Раита: " << result_placeBMHR[0]   << ". Среднее время работы: " << secondsBMHR << '\n';
  cout << "Результат алгоритма Кнута-Морриса-Пратта:                      " << result_placeKMP[0]    << ". Среднее время работы: " << secondsKMP << '\n';

  cout << "Искомые строки: \n";
  for (size_t i = 0; i < needles.size(); i++)
  {
      cout << needles[i] << '\n';
  }
  cout << "\n\n";
  cout << "Найденные строки: \n";
  for (size_t i = 0; i < needles.size(); i++)
  {
    cout << "\n";
    for (size_t j = 0; j < needles_length[i]; j++)
    {
      cout << haystack[result_placeNaive[i] + j];
    }
  }
  cout << "\n";

  return 0;
}



