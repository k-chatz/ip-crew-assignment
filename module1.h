struct fulldate
{
	int DAY;
	int MONTH;
	int YEAR;
	int HOUR;
	int MINUTE;
};

struct flight
{
	int CF;
	int FLIGHT;
	char AIRDEP[4];
	char AIRARR[4];
	struct fulldate START;
	struct fulldate END;
};

struct cf
{
	int SN;
	struct fulldate START;
	struct fulldate END;
	int TIME;
	int WORKDAYS;
	int FLYTIME;
	int FLIGHTS;
	int CAPTAIN;
	struct cf *NEXT;
}*TOP;

struct captain
{
	int ID;
	int WORKDAYS;
	int FLYTIME;
};
