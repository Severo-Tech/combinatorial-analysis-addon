#include <iostream>
#include <vector>
#include <chrono>

#include "combinations.h"

using namespace std;

vector<vector<ICombinationsValue>> findCombination(
    const vector<ICombinationsValue> &current,
    const vector<ICombinationsValue> &remaining,
    double remainingValue)
{
  vector<vector<ICombinationsValue>> result;

  if (remainingValue == 0)
  {
    return {current};
  }

  if (remainingValue < 0)
  {
    return {};
  }

  vector<ICombinationsValue> innerRemaining;
  for (const auto &el : remaining)
  {
    if (el.value <= remainingValue)
    {
      innerRemaining.push_back(el);
    }
  }

  if (innerRemaining.empty())
  {
    return {};
  }

  double sumOfRemaining = 0;
  for (const auto &el : innerRemaining)
  {
    sumOfRemaining += el.value;
  }

  if (sumOfRemaining < remainingValue)
  {
    return {};
  }

  const ICombinationsValue &invoice = innerRemaining[0];
  double invoiceValue = invoice.value;

  vector<ICombinationsValue> newCurrent = {current.begin(), current.end()};
  newCurrent.push_back(invoice);

  auto includeNote = findCombination(
      newCurrent,
      {innerRemaining.begin() + 1, innerRemaining.end()},
      remainingValue - invoiceValue);

  auto excludeNote = findCombination(
      {current.begin(), current.end()},
      {innerRemaining.begin() + 1, innerRemaining.end()},
      remainingValue);

  result.insert(result.end(), includeNote.begin(), includeNote.end());
  result.insert(result.end(), excludeNote.begin(), excludeNote.end());

  return result;
}

vector<vector<ICombinationsValue>> combineByValue(const vector<ICombinationsValue> &list, double target)
{
  vector<ICombinationsValue> sortedList = list;
  sort(sortedList.begin(), sortedList.end(), [](const ICombinationsValue &a, const ICombinationsValue &b)
       { return b.value < a.value; });

  return findCombination({}, sortedList, target);
}

int main()
{
  vector<ICombinationsValue> list = {
      {"a23c00c6-3ff7-4f3b-872d-06e0f986c9a8", 8.04},
      {"6743d757-209a-4a3d-b017-8b9dcf174dd9", 58.72},
      {"76976296-1113-4b6c-ab86-7bca5969ffae", 3.54},
      {"ef7fd7b5-ddba-4592-9703-7c69baa64edf", 46.56},
      {"f486b486-ca17-4e86-a718-5e3c7b53bf00", 42.56},
      {"9d0a270f-0198-45a1-a36b-80990231ed23", 15.84},
      {"01077532-b232-4238-8008-b12a93adaa94", 4.46},
      {"db03157e-21e5-4f49-b494-ec4a89bd157b", 3.23},
      {"a025cd1c-d2d6-414e-b3de-3f698624c968", 12.56},
      {"04516998-6cd3-497c-bed7-e6396de66291", 357.25},
      {"d2370a50-e03d-4a5a-9955-276d049943ab", 15.19},
      {"5468e048-e14d-4e80-952d-ce6ad869cf42", 326.57},
      {"8077b03f-d596-4a89-89de-4f55e0b5a505", 196.37},
      {"a51a70d0-1de1-4fec-b6e6-b47a6e90d74a", 11.47},
      {"860f9ce6-399d-4fd5-a7f4-cad1fcaa4454", 270.96},
      {"ccc84420-215c-468e-80ef-f60a1093efcd", 450.62},
      {"8983f97c-baaa-4ca7-9c2b-21106c6ae4af", 17.91},
      {"25108789-2537-4b79-91f1-abe955bad49a", 162.98},
      {"54484e2f-fb7c-43af-ab7e-5ec63c813ea8", 214.80},
      {"87c8a386-e4f0-44a2-928c-4d9966a7779e", 129.21},
      {"861dde67-925a-4a22-a001-e98b8d8e6fa3", 118.11},
      {"0f0395b3-de45-48ce-97dc-cdff445248f4", 9.89},
      {"4bc056b2-38dc-469d-b1a6-675da1b3c8d6", 24.71},
      {"29ebd54d-11c6-4dac-9dcb-66ccc140e000", 19.59},
      {"bfc5769e-bb34-4e42-b4cb-cc151799eb0d", 8.66},
      {"811c93d2-d467-46de-a64b-13514d04e637", 316.49},
      {"8b67fb1d-c874-4724-a62e-0a7d0987d2e3", 7.91},
      {"22d6801a-27cd-4750-8be3-c3f35fff1229", 10.92},
      {"c8e93189-54c8-4235-bd90-6cb418078cba", 10.82},
      {"03adf52d-0e56-4b91-b27a-ddac8aa51ed0", 13.65},
      {"fba70572-1f6c-4b1a-9eef-006fed2778b1", 19.17},
      {"f5c26d01-cbd2-4995-8d9a-840bda4cb43e", 13.88},
      { "b94e4622-c746-466e-862c-842ac1e60946", 2116.48 },
      // { "2b649b8c-fecf-4e23-a744-8bf58426ab5f", 164.61 },
      // { "8d9ecc5a-7260-4187-ba79-1338e576cc33", 436.70 },
      // { "de2cf79d-ab14-4e28-acc3-0a5915982f8e", 180.07 },
      // { "aea65c1f-0bd2-4f16-b550-ce1946dc0a92", 2920.35 },
      // { "077b0482-c657-4336-9394-4f72228d95ee", 346.21 },
      // { "6324a973-74b1-47e7-9a02-10065b1882c0", 2315.22 },
      // { "7493e843-3499-4719-ac1e-5fbfe4393560", 227.1 }
  };
  double target = 2120.58;

  auto start = chrono::high_resolution_clock::now();
  auto combinations = combineByValue(list, target);
  auto end = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
  cout << "Tempo de execução: " << duration / 1000 << " milisegundos\n";

  // // Imprimir as combinações encontradas
  // for (const auto &combination : combinations)
  // {
  //   cout << "Combinação: " << endl;
  //   for (const auto &el : combination)
  //   {
  //     cout << "    [" << el.id << ", " << el.value << "] " << endl;
  //   }
  // }

  return 0;
}
