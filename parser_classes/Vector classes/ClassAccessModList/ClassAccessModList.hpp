#include <vector>

class ClassAccessMod;

class ClassAccessModList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<ClassAccessMod*>* vector;

  static ClassAccessModList* Create(std::vector<ClassAccessMod*>* vector);
  void Insert(ClassAccessMod* element);
};