struct Configuration{
	int phase;
	int round;
	bool scanForCharacters;
	int startNode;
	int endNode;
	int boardXDimension;
	int boardYDimension;
};

class ConfigurationFactory{
	public:
		virtual Configuration* createConfiguration() = 0;
		Configuration* constructBlankConfig();
};
