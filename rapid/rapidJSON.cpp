#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/pointer.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/filereadstream.h"
#include "iostream"
#include <vector>
#include <cassert>
#include <iomanip>

#include "zlib.h"

using namespace std;
using namespace rapidjson;

struct Point{
  int mX = 1; int mY = 1; double mZ = 1.;
  Point() = default;
  Point(int x, int y, double z) : mX(x), mY(y), mZ(z) {}

  void toJSON(Writer<StringBuffer>& writer) const {
    writer.StartObject();
      writer.Key("x");
      writer.Int(mX);
      writer.Key("y");
      writer.Int(mY);
      writer.Key("z");
      writer.Double(mZ);
    writer.EndObject();
  }

  void fromJSON(const Value& val) {
    mX = val["x"].GetInt();
    mY = val["y"].GetInt();
    mZ = val["z"].GetDouble();
  }
};

struct Dot{
  int mX = 1; int mY = 1;
  Dot() = default;
  Dot(int x, int y) : mX(x), mY(y) {}

  void toJSON(Writer<StringBuffer>& writer) const {
    writer.StartObject();
      writer.Key("x");
      writer.Int(mX);
      writer.Key("y");
      writer.Int(mY);
    writer.EndObject();
  }
  void fromJSON(const Value& val) {
    mX = val["x"].GetInt();
    mY = val["y"].GetInt();
  }
};

/**
 * Shows how to write and read jsons containing many instances of custom objects
 */
int main(){
  // Initialize a vector of points
  vector<Point> vec;
  for(int i = 0; i < 3; i++){
    vec.emplace_back(i, i + 2, i * 1. + 0.053246781344);
  }

  // initialze and fill a vector of Dots
  vector<Dot> dt;
  for(int i=  0; i < 3; i++){
    dt.emplace_back(i, i + 2);
  }

  // ********* WRITE JSON ******************
  StringBuffer s;
  Writer<StringBuffer> writer(s);
  
  writer.StartObject();
  writer.Key("system");
    writer.StartObject();
      writer.Key("points");
      writer.StartArray();
      for(const Point& p : vec){
        p.toJSON(writer);
      }
      writer.EndArray();
      writer.Key("dots");
      writer.StartArray();
        for(const Dot& d : dt){
          d.toJSON(writer);
        }
      writer.EndArray();
    writer.EndObject();
  writer.EndObject();

  cout <<  s.GetString() << endl;

  Document d;
  d.Parse(s.GetString());

  char writeBuffer[65536];
  FILE* fp = fopen("output.json", "w"); // non-Windows use "w"
  FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
  Writer<FileWriteStream> writer1(os);
  // While you can use the Stream backing the Writer for any number of documents, each Writer must only be used once
  d.Accept(writer1);
  fclose(fp);


  // ********* READ JSON ******************
  FILE* fp1 = fopen("output.json", "r"); // non-Windows use "r"
  char readBuffer[65536];
  FileReadStream is(fp1, readBuffer, sizeof(readBuffer));
  
  Document d1;
  d1.ParseStream(is);
  fclose(fp1);

  assert(d1.IsObject());

  const Value& system = d1["system"];
  const Value& points = system["points"];

  cout << points.GetArray().Size() << endl;

  int idx = 0;
  for(const auto& pt : points.GetArray()) {
    vec[idx++].fromJSON(pt);
  }

  // Make sure we deserialized correctly
  for(const auto& pt : vec){
    cout << setprecision(12);
    cout << pt.mX << ", " << pt.mY << ", " <<  pt.mZ << endl;
  }
  return 0;
}