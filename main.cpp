#include <iostream>
#include <string>
#include <vector>
//#include <map>
#include <algorithm>
#include <functional>

template<class Key, class Val>
class sortable_map {
   std::vector<std::pair<Key,Val>> v_;
   public:
   sortable_map(){}
   sortable_map(std::vector<std::pair<Key, Val>> v) {
     for(const auto& p:v){
       Key f = p.first;
       Val s = p.second;
       auto result{std::find_if(v_.begin(), v_.end(), [&f] (auto el){return el.first==f;})};
        if(result==v_.end()){
          v_.push_back(std::pair<Key,Val>(f,s));
        }else{
          std::cout << "Key " << f << " already exists, overwriting value to " << s <<"\n";
          result->second = s; //OVERWRITE IF KEY ALREADY THERE
        }
     }
   }
   Val& map(const Key& ch){
     auto result{std::find_if(v_.begin(), v_.end(), [ch] (auto el){return el.first==ch;})};
     if(result==v_.end()){
       v_.push_back(std::pair<Key,Val>(ch,0));
       result = v_.end() - 1;
     }
     return result->second;
   }
   void erase(const Key& ch){
      auto result{std::find_if(v_.begin(), v_.end(), [ch] (auto el){return el.first==ch;})};
      if(result==v_.end()){
        std::cout << "Key not found, nothing is erased";
      }else
        v_.erase(result);
    }
   const std::pair<Key,Val> operator[](int i) const{
     return v_[i];
   }
   typename std::vector<std::pair<Key,Val>>::iterator begin(){
     return v_.begin();
   }
   typename std::vector<std::pair<Key,Val>>::iterator end(){
     return v_.end();
   }
   int size(){ return v_.size();}
   static bool cmp (std::pair<Key,Val> const &p1, std::pair<Key,Val> const &p2)
   {
      return p1.second != p2.second?  p1.second > p2.second : p1.first < p2.first;
   };
   std::function<bool(std::pair<Key,Val> const &,std::pair<Key,Val> const &)> get_cmp(bool byvalue = true ){
       return byvalue? cmp : [](std::pair<Key,Val> const &p1, std::pair<Key,Val> const &p2){
         return p1.first != p2.first?  p1.first < p2.first : p1.second > p2.second;
       };
   }
};

class unique_char_counter : public sortable_map<char,int> {
  std::string s_;
  public:
  unique_char_counter(std::string s): s_(s){
    for(auto ch: s_){
      map(ch)++;
    }
  }
};

int main() {
  std::string str = "Hello world!!";
  std::cout << "[IN]: " << str << std::endl;
  //std::map<char, int> m{}; MAP CAN ONLY BE SORTED BY KEYS
  unique_char_counter ucc(str);
  std::cout << "[OUT]:\n";
  std::cout<<"Number of unique characters is "<<ucc.size()<<std::endl;
  //std::sort(ucc.begin(),ucc.end(), ucc.cmp);
  std::sort(ucc.begin(),ucc.end(), ucc.get_cmp(true));
  for(const auto& el : ucc){
    std::cout << el.first << ": " << el.second << std::endl;
  };

  //CHECKING VARIOUS CONSTRUCTORS AND OTHER METHODS
  /*sortable_map<char,int> sm({{'a',1},{'b',2},{'a',3}});
  std::cout << "sm contents:\n";
  for(const auto& el : sm){
    std::cout << el.first << ": " << el.second << std::endl;
  };*/
  /*
  unique_char_counter ucc2 = ucc;
  for(const auto& el : ucc2){
    std::cout << el.first << ": " << el.second << std::endl;
  }
  unique_char_counter ucc3(ucc);
  for(const auto& el : ucc3){
    std::cout << el.first << ": " << el.second << std::endl;
  }
  ucc.erase('l');
  std::cout<<"Number of unique characters is "<<ucc.size()<<std::endl;
  for(const auto& el : ucc){
    std::cout << el.first << ": " << el.second << std::endl;
  }
  ucc.erase('y');*/
}
