#include <vector>

typedef unsigned int uint;

struct trkpoint{
	uint  ID;
	uint  trksegID;
	float lat;
	float lon;
	float ele;
};

class track{
public:
	typedef std::vector<trkpoint> trkdata;

	void fromGarminText(char const* file);
	
	float calcAscendStupid() const;
	float calcHills() const;

	void filterSmooth();

private:
	trkdata m_data;
};