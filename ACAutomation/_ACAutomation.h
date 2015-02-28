#include <queue>

const int KIND = 16;

struct Node{
	Node *fail;
	Node *next[KIND];
	const char *word;
	bool end;

	Node()
	{
		fail = NULL;
		word = NULL;
		end = false;
		memset(next, 0, sizeof(next));
	}
};

struct Result
{
    unsigned long position;
    const char *word;
};


class ACAutomation
{
    private:
    Node *root;
    std::queue<Node*> q;

    public :
    ACAutomation();
    ~ACAutomation();
    void insert(const char *str);
    void build();
    void match(const char *str, bool multi, std::queue<Result> &ret);
};