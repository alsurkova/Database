#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
  Date() {
	  year = 0;
	  month = 0;
	  day = 0;
  }
  Date(int y, int m, int d) {
	  year = y;
	  month = m;
	  day = d;
  }
  int GetYear() const {
	  return year;
  }
  int GetMonth() const {
	  return month;
  }
  int GetDay() const {
	  return day;
  }
private:
  int year;
  int month;
  int day;
};

bool operator==(const Date& l, const Date& r) {
	return l.GetDay() == r.GetDay() && l.GetMonth() == r.GetMonth() && l.GetYear() == r.GetYear();
}

bool operator<(const Date& l, const Date& r) {
	if (l.GetYear() < r.GetYear()) {
		return true;
	}
	if (l.GetYear() > r.GetYear()) {
		return false;
	}
	if (l.GetMonth() < r.GetMonth()) {
		return true;
	}
	if (l.GetMonth() > r.GetMonth()) {
		return false;
	}
	return l.GetDay() < r.GetDay();
}

ostream& operator<<(ostream& stream, const Date& d) {
	stream << setw(4) << setfill('0') << d.GetYear()
					  << '-' << setw(2) << d.GetMonth() << '-' << setw(2) << d.GetDay();
    return stream;
}


class Database {
public:
  void AddEvent(const Date& date, const string& event) {
	  base[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
      if (base.count(date) && base[date].count(event)) {
    	  base[date].erase(event);
    	  if (!base[date].size()) {
    		  base.erase(date);
    	  }
    	  return true;
      }
      return false;
  }
  int DeleteDate(const Date& date) {
	  int cnt = 0;
	  if (base.count(date)) {
		  cnt = base[date].size();
		  base[date].clear();
		  base.erase(date);
	  }
	  return cnt;
  }

  void Find(const Date& date) const {
	  if (!base.count(date)) {
		  return;
	  }
	  for (const auto& event : base.at(date)) {
		  cout << event << endl;
	  }

  }

  void Print() const {
	  for (const auto& item : base) {
		  for (const auto& event : item.second) {
			  cout << item.first << " " << event << endl;
		  }
	  }
  }
private:
  map<Date, set<string>> base;
};

bool ReadRightDate(Date & date, stringstream & s) {
	string date_str;
	s >> date_str;
	stringstream ss;
    ss << date_str;
	int y, m, d;
	char c1, c2, c3;
	if (!(ss >> y) || !(ss >> c1) || (c1 != '-') || !(ss >> m) || !(ss >> c2) || (c2 != '-') ||
			!(ss >> d) || (ss >> c3)) {
        cout << "Wrong date format: " << date_str << endl;
        return false;
	}
	if (m < 1 || m > 12) {
		cout << "Month value is invalid: " << m << endl;
		return false;
	}
	if (d < 1 || d > 31) {
		cout << "Day value is invalid: " << d << endl;
		return false;
	}
	date = Date(y, m, d);
	return true;
}
int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
	stringstream ss;
	ss << command;
	string cmd;
	ss >> cmd;
	if (cmd == "") {
        continue;
    } else if (cmd == "Add") {
    	Date date;
    	if (!ReadRightDate(date, ss)) {
    		return 0;
    	}
    	string event;
    	ss >> event;
    	db.AddEvent(date, event);
	} else if (cmd == "Del") {
		Date date;
		if (!ReadRightDate(date, ss)) {
			return 0;
		}
		string event;
    	if(ss >> event) {
    		if (db.DeleteEvent(date, event)) {
    			cout << "Deleted successfully" << endl;
    		} else {
    			cout << "Event not found" << endl;
    		}
    	} else {
    		int cnt = db.DeleteDate(date);
    		cout << "Deleted " << cnt << " events" << endl;
    	}

	} else if (cmd == "Find") {
    	Date date;
    	if (!ReadRightDate(date, ss)) {
    		return 0;
    	}
    	db.Find(date);
	} else if (cmd == "Print") {
    	db.Print();
	} else {
		cout << "Unknown command: " << command << endl;
		return 0;
	}
  }
  return 0;
}



