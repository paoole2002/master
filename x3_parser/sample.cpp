#include <iostream>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>

#define print(x) std::cout << x << std::endl;

namespace x3 = boost::spirit::x3;

static const auto space_comment =  x3::lit('\t') | x3::lit('\n') | x3::lit(' ');
static const auto single_line_comment = "/" >> *(x3::char_ - x3::eol) >> (x3::eol | x3::eoi);
static const auto double_line_comment = "//" >> *(x3::char_ - x3::eol) >> (x3::eol | x3::eoi);

enum class gender {male, female, neutral};
enum class deviceType {shunt, generator, load};
enum class action {switchOff, switchOn};
enum class locType {area, zone, owner, bus, kv, sys};

namespace ast {
  struct Branch {
    int mFrom;
    std::vector<int> mTo;
    std::string mCkt;
  };

  struct OneTerm {
    action mAction;
    deviceType mDev;
    std::string mId;
    int mBus;
    std::string mCmts;
  };

  struct ThreeWindXfmr {
    int mI;
    int mJ;
    int mK;
    std::string mCkt;
  };

  struct Move {
    double mAmount;
    std::string mType;
    std::string mDevice;
    int mFrom;
    int mTo;
    std::string mCmts;
  };

  struct QuantChng {
    std::string mAdjType;
    int mBus;
    std::string mQuantType;
    double mAmount;
    std::string mValType;
    std::string mDisp;
    std::string mCmts;
  };

  struct Person{
    std::string mName;
    gender mGender; 
    int mInt;
    double mDoub;   
  };

  struct BusVoltage {
    locType mLocType;
    int mLocation;
    double mKv;
    std::string mSubName;
    double mLo;
  };

  struct MonBranchList {
    int i;
    double j;
    // int k;
  };

  using boost::fusion::operator<<;
}

namespace parser
{
  x3::rule<class Branch, ast::Branch> const branch = "Branch";
  x3::rule<class OneTerm, ast::OneTerm> const oneTerm = "OneTerm";
  x3::rule<class ThreeWindXfmr, ast::ThreeWindXfmr> const threeWindXfmr = "ThreeWindXfmr";
  x3::rule<class Move, ast::Move> const move = "Move";
  x3::rule<class QuantChng, ast::QuantChng> const quantChng = "QuantChng";

  auto const branch_def = (x3::lit("OPEN") | x3::lit("TRIP")) >> x3::lit("BRANCH") >> x3::lit("FROM") >>
                            x3::lit("BUS") >> x3::int_ >>
                            +(x3::lit("TO") >> x3::lit("BUS") >> x3::int_) >>
                            x3::lit("CIRCUIT") >> x3::lexeme[+(x3::char_ - '/')];
  
  // const auto oneTerm_def = x3::lit("TRIP") >> +space_comment >> x3::lit("SHUNT") >>
  //                           +space_comment >> +(x3::char_ - space_comment) >> +space_comment >>
  //                           x3::lit("FROM") >> +space_comment >> x3::lit("BUS") >> +space_comment >>
  //                           *(x3::int_ - space_comment) >> +space_comment >>
  //                           *single_line_comment;
  
  const auto threeWindXfmr_def = (x3::lit("OPEN") | x3::lit("TRIP")) >> x3::lit("THREEWINDING") >> x3::lit("AT") >>
                            x3::lit("BUS") >> x3::int_ >>
                            x3::lit("TO") >> x3::lit("BUS") >> x3::int_ >>
                            x3::lit("TO") >> x3::lit("BUS") >> x3::int_ >>
                            *(x3::lit("CKT") >> x3::lexeme[+(x3::char_ - '/')]);
  
  // std::string mvStr = "MOVE 100  PERCENT  LOAD  \n FROM BUS 123 TO BUS 456";
  const auto move_def = x3::lit("MOVE") >> +space_comment >> x3::double_ >>
                        +space_comment >> +(x3::char_ - space_comment) >> +space_comment >>
                        +(x3::char_ - space_comment) >> +space_comment >> x3::lit("FROM") >>
                        +space_comment >> x3::lit("BUS") >>
                        +space_comment >> x3::int_ - space_comment >> +space_comment >>
                        x3::lit("TO") >> +space_comment >> x3::lit("BUS") >>
                         +space_comment >> x3::int_ - space_comment >>
                        *space_comment >> *single_line_comment;
  
  // [ADJUSTMENT TYPE] BUS [busNum] [quantityType] BY [amount] [MW/PERCENT] [DISPATCH]
  const auto quantChng_def = +(x3::char_ - space_comment) >> +space_comment >>
                              x3::lit("BUS") >> +space_comment >>
                              x3::int_ >> +space_comment >>
                              +(x3::char_ - space_comment) >>  +space_comment >>
                              x3::lit("BY") >> +space_comment >>
                              x3::double_ >> +space_comment >>
                              +(x3::char_ - space_comment) >> +space_comment >>
                              *(x3::char_ - space_comment) >> *space_comment >> *single_line_comment;
  
  
  BOOST_SPIRIT_DEFINE(branch);
  // BOOST_SPIRIT_DEFINE(oneTerm);
  BOOST_SPIRIT_DEFINE(threeWindXfmr);
  BOOST_SPIRIT_DEFINE(move);
  BOOST_SPIRIT_DEFINE(quantChng);
}

BOOST_FUSION_ADAPT_STRUCT(ast::Branch, mFrom, mTo, mCkt)
BOOST_FUSION_ADAPT_STRUCT(ast::OneTerm, mAction, mDev, mId, mBus, mCmts)
BOOST_FUSION_ADAPT_STRUCT(ast::ThreeWindXfmr, mI, mJ, mK, mCkt)
BOOST_FUSION_ADAPT_STRUCT(ast::Move, mAmount, mType, mDevice, mFrom, mTo, mCmts)
BOOST_FUSION_ADAPT_STRUCT(ast::QuantChng, mAdjType, mBus, mQuantType, mAmount, mValType, mDisp, mCmts)
BOOST_FUSION_ADAPT_STRUCT(ast::Person, mName, mGender, mInt, mDoub)
BOOST_FUSION_ADAPT_STRUCT(ast::BusVoltage, mLocType, mLocation, mKv, mSubName, mLo)

int main() {
  #if 0
  const auto gram1 = x3::no_case[x3::lit("COM")] >> *x3::char_;
  const auto gram2 = x3::lit("/") >> *x3::char_;
  std::string str = "COM ABCS\n";
  std::string::iterator startIt = str.begin();
  std::string::iterator endIt = str.end();
  bool r = x3::parse(startIt, endIt, gram1 | gram2);
  #endif

  #if 0
  std::string label;
  std::string labelStr = "CoNtINgEnCy 'E2d:500:EeS-EAI:OUCHITA' / and a comment\n";
  std::string::iterator startIt = labelStr.begin();
  std::string::iterator endIt = labelStr.end();
  bool r = x3::phrase_parse(startIt, endIt,
                            x3::no_case[x3::lit("CONTINGENCY")] >> *(x3::char_ - '/'),
                            space_comment | single_line_comment | double_line_comment, label);
  print(label);
  #endif

  #if 0
  std::string comStr = "ab / This is a big 3rd nice ! comment\n";
  std::string::iterator startIt = comStr.begin();
  std::string::iterator endIt = comStr.end();
  bool r = x3::phrase_parse(startIt, endIt,
                            *(x3::char_),
                            space_comment | single_line_comment | double_line_comment);
  #endif

  // bool r = x3::par

  #if 0
  std::string busStr = "DISCONNECT  BUS    23";
  std::string::iterator startIt = busStr.begin();
  std::string::iterator endIt = busStr.end();
  int num
  bool r1 = x3::phrase_parse(startIt, endIt,
                             x3::lit("DISCONNECT") >> x3::lit("BUS") >> x3::int_,
                             space_comment | single_line_comment, num);
  #endif


  #if 0
  std::string branchStr = "TRIP  BRANCH FROM BUS 123 TO BUS     1234  TO BUS 12345    CIRCUIT SA / This is a 3 comment\n";
  std::string::iterator startIt = branchStr.begin();
  std::string::iterator endIt = branchStr.end();
  ast::Branch br;

  bool r = x3::phrase_parse(startIt, endIt, parser::branch, space_comment | single_line_comment, br);

  for (const auto& toBus : br.mTo) {
    std::cout << toBus << std::endl;
  }

  std::cout << br.mCkt << std::endl;
  #endif

  #if 0
  std::string blkStr = "BLOCK  TWOTERMDC    ABC // comment\n";
  std::string::iterator startIt = blkStr.begin();
  std::string::iterator endIt = blkStr.end();
  static const auto blkDevGrm = x3::lit("BLOCK") >> +space_comment >> *(x3::char_ - space_comment) >>
                      +space_comment >> +(x3::char_ - space_comment) >> *space_comment >>
                      *single_line_comment | *double_line_comment;
  std::vector<std::string> vec;
  bool r1 = x3::parse(startIt, endIt, blkDevGrm, vec);
  for (const auto& str : vec) {
    print(str);
  }
  #endif

  #if 0
  std::string str = "REMOVE GENERATION 212+2 FROM BUS 12\n";
  std::string::iterator startIt = str.begin();
  std::string::iterator endIt = str.end();
  ast::OneTerm dev;
  static const auto oneTermHelp = x3::lit("FROM") | x3::lit("TO");
  struct DeviceTypeTable : boost::spirit::x3::symbols<deviceType> {
      DeviceTypeTable() {
          add ("GENERATIONS", deviceType::generator)
              ("UNIT", deviceType::generator)
              ("MACHINE", deviceType::generator)
              ("LOAD", deviceType::load)
              ("SHUNT", deviceType::shunt)
              ("SWSHUNT", deviceType::shunt);
      }
  } const deviceTypeTable;

  struct ActionTable : boost::spirit::x3::symbols<action> {
      ActionTable() {
          add ("OPEN", action::switchOff)
              ("TRIP", action::switchOff)
              ("REMOVE", action::switchOff)
              ("DISCONNECT", action::switchOff)
              ("CLOSE", action::switchOn)
              ("ADD", action::switchOn);
      }
  } const actionTable;
  
  static const auto oneTermGrm = actionTable >> +space_comment >> deviceTypeTable >>
                            +space_comment >> +(x3::char_ - space_comment) >> +space_comment >>
                            x3::lit("FROM") >> +space_comment >> x3::lit("BUS") >> +space_comment >>
                            x3::int_ >> *(single_line_comment | space_comment);
  bool r1 = x3::parse(startIt, endIt, oneTermGrm, dev);
  print(dev.mId);
  print(dev.mBus);
  #endif

  #if 0
  // DISCONNECT THREEWINDING AT BUS 620238 TO BUS 620338 TO BUS 657758 CKT 1
  std::string threeXfmr = "TRIP  THREEWINDING AT BUS 123 TO BUS     1234  TO BUS 12345     / This is a 3 comment\n";
  std::string::iterator startIt = threeXfmr.begin();
  std::string::iterator endIt = threeXfmr.end();
  ast::ThreeWindXfmr br;

  bool r = x3::phrase_parse(startIt, endIt, parser::threeWindXfmr, space_comment | single_line_comment, br);
  print(br.mI);
  print(br.mJ);
  print(br.mK);
  print(br.mCkt);
  #endif
  
  #if 0
  // MOVE 100 PERCENT LOAD FROM BUS 346023 TO BUS 346024
  std::string mvStr = "MOVE 100 PERCENT LOAD FROM BUS 123 TO BUS 456";
  std::string::iterator startIt = mvStr.begin();
  std::string::iterator endIt = mvStr.end();
  ast::Move mv;
  bool r1 = x3::parse(startIt, endIt, parser::move, mv);
  print(mv.mAmount);
  print(mv.mType);
  print(mv.mDevice);
  print(mv.mFrom);
  print(mv.mTo);
  #endif

  #if 0
  std::string qStr = "REDUCE BUS 243442 GENERATION BY 400 MW DISPATCH";
  std::string::iterator startIt = qStr.begin();
  std::string::iterator endIt = qStr.end();
  ast::QuantChng q;
  bool r1 = x3::parse(startIt, endIt, parser::quantChng, q);
  print(q.mAdjType);
  print(q.mBus);
  print(q.mQuantType);
  print(q.mAmount);
  print(q.mValType);
  print(q.mDisp)
  #endif

  #if 0
  std::string str = "bob neutral  1   1.5";
  std::string::iterator startIt = str.begin();
  std::string::iterator endIt = str.end();
  struct gender_table : x3::symbols<gender> {
      gender_table() {
          add ("male"   , gender::male)
              ("female" , gender::female)
              ("neutral" , gender::neutral);
      }
  } const gender;

  auto const word = x3::lexeme[+~x3::space];

  const auto parser = word >> gender >> x3::int_ >> x3::double_;
                      // >> (gender | x3::attr(gender::female)) >> *space_comment;

  ast::Person ret;
  x3::phrase_parse(startIt, endIt, parser, space_comment, ret);
  switch (ret.mGender) {
    case gender::male: std::cout << "male\n"; break;
    case gender::female: std::cout << "female\n"; break;
    case gender::neutral: std::cout << "neutral\n"; break;
  }
  #endif

  #if 0
  std::string str = "MONITOR SUBSYSTEM NASSOS_100 0.15";
  std::string::iterator startIt = str.begin();
  std::string::iterator endIt = str.end();
  struct locTypeTable : x3::symbols<locType> {
      locTypeTable() {
          add ("AREA"   , locType::area)
              ("ZONE" , locType::zone)
              ("OWNER" , locType::owner)
              ("KV", locType::kv)
              ("SUBSYSTEM", locType::sys);
      }
  } const locTable;

  auto const word = x3::lexeme[+~x3::space];

  const auto parser = x3::lit("MONITOR") >> +space_comment >> locTable >> +space_comment >>
                     (*x3::int_ >> *x3::double_ >> *word) >> +space_comment
                     >> x3::double_ >> *space_comment;

  ast::BusVoltage ret;
  x3::parse(startIt, endIt, parser, ret);
  switch (ret.mLocType) {
    case locType::area: std::cout << "area\n"; break;
    case locType::zone: std::cout << "zone\n"; break;
    case locType::owner: std::cout << "owner\n"; break;
    case locType::kv: std::cout << "kv\n"; break;
    case locType::sys: std::cout << "subsys\n"; break;
  }
  std::cout << "location " << ret.mLocation << '\n';
  std::cout << "kv " << ret.mKv << '\n';
  std::cout << "subsystem " << ret.mSubName << '\n';
  #endif

  #if 0
  std::string str = "123 56.12 ";
  std::string::iterator startIt = str.begin();
  std::string::iterator endIt = str.end();
  ast::MonBranchList br;
  // >> +(x3::char_ - space_comment)
  bool r1 = x3::phrase_parse(startIt, endIt, x3::int_ >> x3::double_, space_comment, br);
  // print(q.mAdjType);
  // print(q.mBus);
  // print(q.mQuantType);
  // print(q.mAmount);
  // print(q.mValType);
  // print(q.mDisp)
  #endif

  if (startIt != endIt) {
    auto distance = endIt - startIt;
    std::cout << "Failed: didn't parse everything\n";
    std::cout << "stopped " << distance << " characters from the end "
              << "( '" << *startIt << "' )\n";
    return 1;
  }

  if (startIt == endIt)
    std::cout << "Parsed succesfully" << std::endl;
  else
    std::cout << "Failed to parse the string" << std::endl;

  return 0;
}