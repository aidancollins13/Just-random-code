#ifndef PRINCESS_H
#define PRINCESS_H

#import <string>

namespace Fantasy {
	class FrogPrince;

	class Princes{
	public:
		Princess(const std::string& name) : name(name), spouce(NULL) {}
		void display() const;
	private:
		string name;
		FrogPrince* spouce;

	};
}

#endif