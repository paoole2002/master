#include <iostream>
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/home/x3.hpp>
#include <string>
#include <vector>
#include <variant>

#define print(x) std::cout << x << '\n';

enum class location {BUS, AREA, ZONE, OWNER, KV, KVRANGE, SUBSYSTEM};

struct LocTypeTable : boost::spirit::x3::symbols<location>
{
  LocTypeTable()
  {
    add("BUS", location::BUS)
        ("AREA", location::AREA)
        ("ZONE", location::ZONE)
        ("OWNER", location::OWNER)
        ("KV", location::KV)
        ("KVRANGE", location::KV)
        ("SUBSYSTEM", location::SUBSYSTEM)
        ("SYSTEM", location::SUBSYSTEM);
  }
} const locTypeTable;

using namespace boost::fusion;
namespace x3 = boost::spirit::x3;

static const auto spcCmt =  x3::lit('\t') | x3::lit('\n') | x3::lit(' ');

static const auto grm = locTypeTable >> +spcCmt >> *x3::double_ >> *x3::double_ >> *x3::int_ >> *spcCmt;
static const auto grammar = x3::lit("MONITOR") >> +spcCmt >> grm >> *spcCmt;

struct Cond {
  location mLocType;
  double mVal1 = 0.;
  double mVal2 = 0.;
  std::string mSubName;
};


BOOST_FUSION_ADAPT_STRUCT(Cond, mLocType, mDb, mSubName)

int main()
{
  std::string str = "MONITOR AREA 2 KV 100.15";
  auto first = str.begin();
  auto last = str.end();
  std::vector<Cond> allConds;
  Cond cond;
  while (first != last) {
    if (x3::parse(first, last, grammar, cond)) {
      allConds.push_back(cond);
    }
    else if (x3::parse(first, last, grm, cond)) {
      allConds.push_back(cond);
    }
    else {
      std::cout << "Parse failed\n";
      break;
    }
  }
  if (first != last)
      std::cout << "Remaining input: '" << std::string(first, last) << "'\n";
  else {
    std::cout <<  "Parsed succesfully\n";
  }
  print(allConds.size());
  print(allConds[0].mInt);
  print(allConds[1].mInt);
}


