#include <string>
#include <algorithm>
#include <cstring>
#include <vector>

const int Max = 10000000;   // 입력 문자열로 만들 수 있는 최대 숫자의 크기
bool primeTables[10000001]; // 소수 판별을 위한 소수 테이블
bool have[10000001];        // 이미 확인했던 것인지 확인하는 테이블
bool check[7];              // 현재 내가 어떤 인덱스를 사용중인지 확인하는 테이블

using namespace std;

int FindPrime(string str, string word, int nowIndex)
{
	int cnt = 0;
    
    int nowVal = stoi(word);                    // string을 정수로 변환
    if(!have[nowVal] && primeTables[nowVal])    // 처음 보는 정수이고, 소수가 맞다면
    {
        have[nowVal] = true;                    // 해당 정수를 확인 처리
        ++cnt;                                  // 소수 개수 카운팅
    }
    check[nowIndex] = true;                     // 현재 추가로 string에 붙인 문자의 인덱스 사용 체크
	for (int i = 0; i < str.size(); ++i)
	{
		if (!check[i])                          // str[i]를 쓰지 않았다면 
		{
			cnt += FindPrime(str, word + str[i], i);    // 해당 str[i]를 검사하려는 string에 추가하고 재귀
			check[i] = false;                           
		}
	}

	return cnt;
}

int solution(string numbers) {
	int answer = 0;

	memset(primeTables, true, sizeof(primeTables)); // 에라토스테네스의 체를 사용하기 위한 초기화
    primeTables[1] = false;                         // 1은 소수에서 제외한다
    
	for (int i = 2; i * i <= Max; ++i)              // 에라토스테네스의 체 구현
		for (int j = i * i; j <= Max; j += i)       
			primeTables[j] = false;

	for (int i = 0; i < numbers.size(); ++i)        
	{
        if(numbers[i] == '0') continue;             // 첫 문자가 0으로 시작하면 안되므로 넘긴다
        
		string temp;                                
		temp.push_back(numbers[i]);
		check[i] = true;                            // 사용한 문자 체크
		answer += FindPrime(numbers, temp, i);      // 소수 찾는 재귀함수 시작
		check[i] = false;                           // 사용한 문자를 다시 초기화
	}

	return answer;
}