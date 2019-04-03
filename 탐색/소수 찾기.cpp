#include <string>
#include <algorithm>
#include <cstring>
#include <vector>

const int Max = 10000000;   // �Է� ���ڿ��� ���� �� �ִ� �ִ� ������ ũ��
bool primeTables[10000001]; // �Ҽ� �Ǻ��� ���� �Ҽ� ���̺�
bool have[10000001];        // �̹� Ȯ���ߴ� ������ Ȯ���ϴ� ���̺�
bool check[7];              // ���� ���� � �ε����� ��������� Ȯ���ϴ� ���̺�

using namespace std;

int FindPrime(string str, string word, int nowIndex)
{
	int cnt = 0;
    
    int nowVal = stoi(word);                    // string�� ������ ��ȯ
    if(!have[nowVal] && primeTables[nowVal])    // ó�� ���� �����̰�, �Ҽ��� �´ٸ�
    {
        have[nowVal] = true;                    // �ش� ������ Ȯ�� ó��
        ++cnt;                                  // �Ҽ� ���� ī����
    }
    check[nowIndex] = true;                     // ���� �߰��� string�� ���� ������ �ε��� ��� üũ
	for (int i = 0; i < str.size(); ++i)
	{
		if (!check[i])                          // str[i]�� ���� �ʾҴٸ� 
		{
			cnt += FindPrime(str, word + str[i], i);    // �ش� str[i]�� �˻��Ϸ��� string�� �߰��ϰ� ���
			check[i] = false;                           
		}
	}

	return cnt;
}

int solution(string numbers) {
	int answer = 0;

	memset(primeTables, true, sizeof(primeTables)); // �����佺�׳׽��� ü�� ����ϱ� ���� �ʱ�ȭ
    primeTables[1] = false;                         // 1�� �Ҽ����� �����Ѵ�
    
	for (int i = 2; i * i <= Max; ++i)              // �����佺�׳׽��� ü ����
		for (int j = i * i; j <= Max; j += i)       
			primeTables[j] = false;

	for (int i = 0; i < numbers.size(); ++i)        
	{
        if(numbers[i] == '0') continue;             // ù ���ڰ� 0���� �����ϸ� �ȵǹǷ� �ѱ��
        
		string temp;                                
		temp.push_back(numbers[i]);
		check[i] = true;                            // ����� ���� üũ
		answer += FindPrime(numbers, temp, i);      // �Ҽ� ã�� ����Լ� ����
		check[i] = false;                           // ����� ���ڸ� �ٽ� �ʱ�ȭ
	}

	return answer;
}