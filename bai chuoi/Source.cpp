#include <iostream>
#include <set>
using namespace std;

void Process2()
{
	string sentence;
	set<char> charSet;
	set<string> words;

	for (char c : sentence)
	{
		if (isalpha(c))
		{
			charSet.insert(c);
		}

		else if (c == ' ' && !charSet.empty())
		{
			string word(charSet.begin(), charSet.end());
			words.insert(word);
			charSet.clear();
		}
	}

	if (!charSet.empty())
	{
		string word(charSet.begin(), charSet.end());
		words.insert(word);
	}

	int maxDistinctChar = 0;
	string maxWord;

	for (string word : words)
	{
		if (word.size() > maxDistinctChar)
		{
			maxDistinctChar = word.size();
			maxWord = word;
		}
	}
}