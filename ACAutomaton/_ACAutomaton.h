#include <cstddef>
#include <cstring>
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


class ACAutomaton
{
    private:
    Node *root;
    std::queue<Node*> q;

    public :
    ACAutomaton();
    ~ACAutomaton();
    void insert(const char *str);
    void build();
    void match(const char *str, bool multi, std::queue<Result> &ret);
};