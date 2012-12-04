#pragma warning(disable:4786)

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stack>
#include <map>
#include <vector>
#include <set>

using namespace std;

#define MYOUTPUT

class CFG
{
public:
	CFG();
public:
	bool ParseFile(char* testFile);
	void ChkProcess();
private:
	void RetriveRule(string strParse);
	bool chkCase(string strCase);
	bool chkTop(string strCase);
	bool pushStack(string strPush);
	string RetriveStack();
	string TerminalStk();
	void ReCompare(stack<string> stk, int index);
	int ValidRegion(string str);
	bool HaveExist(string strIns);
protected:
private:
	stack<string> stkRule;   //Rule's stack
	multimap<string,string> mapRule;   //rules' left and right pairs after transforming the rules
	vector<string> vecCase;  //vector, string set of samples. vector, container, set of the same type.
	string strSet;
	string strTerminals;
	string strEmpty;
	string strRoot;
	string::size_type iPos;
	set<string> setStk;
};

CFG::CFG()
{
	strSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";      //variable characters' set
	strTerminals = "abcdefghijklmnopqrstuvwxyz_";   //terminal characters' set
	strEmpty = "!";                                 //empty string
}

bool CFG::ParseFile(char* sampleFile)           //seperate rule and sample
{
	ifstream inFile(sampleFile,ios::in);  //open sample file
	if (!inFile)    //if open error
	{
		cerr << "open sample file error, please check sample file exist or not";
		return false;
	}

	cout << sampleFile << ":\n";
	string linesOfText;   //store each lines 
	int iRuleCount,iLineNo =0;
	while ( getline(inFile,linesOfText,'\n') )    //get each lines and analyze
	{
		cout << "\t" << linesOfText << "\n";
		if(iLineNo == 0)                        
			iRuleCount = atoi(linesOfText.c_str());	  //line No.1, get # of rules
		else if (iLineNo <= iRuleCount)        // get all lines of rules
			RetriveRule(linesOfText);
		else                                   // continue to get all lines of samples£¬store in vecCase;
			vecCase.push_back(linesOfText);

		if(iLineNo == 1)                       //get start Variable,--> strRoot
			strRoot = linesOfText[0];

		iLineNo++;
	}

	return true;
}

void CFG::RetriveRule(string strParse)   //store rules
{
	typedef multimap<string,string>::value_type valType;  //unfixed sequence of string pairs,each pair,
	//the left is key value, the right is value.
	string strLeft,strRight;
	strLeft = strParse[0];   //rule left part: variable
	strRight = strParse.substr(3);   //rule right part: terminal and variable
	mapRule.insert(valType(strLeft,strRight));  //mapRule store all the transformed rules. 
}

void CFG::ChkProcess()   		//Sample verificaiton one by one.
{
	cout << "\nVerification RESULT:\n";
	for(vector<string>::iterator iter = vecCase.begin(); iter != vecCase.end();iter++)
	{
		string strCase = *iter;
		if(chkCase(strCase))     //strCase is one sample string. chkCase() for verification.
			cout << "\tyes\n";
		else
			cout << "\tno\n";
	}
}

bool CFG::chkCase(string strCase)    
{
	while (!stkRule.empty())        //Empty stack stkRule. to empty stack can only use pop(); to empty vector just use clear()
		stkRule.pop();
	stkRule.push(strRoot);          //push start variable into stack

	setStk.clear();     //Empty set(string)
	setStk.insert(strRoot);  //insert start variable
	iPos = 0;

	return chkTop(strCase);   //check one sample line
}

int CFG::ValidRegion(string strSource)
{
	if (strSource[0] == '!')  //if start variable is empty
		return 0;

	int iRet = 0;
	int iStrSize = strSource.size();
	int iEmpty =0;

	for(int i=0; i<iStrSize; i++)
	{
		string strIndex = strSource.substr(i,1);
		int iMatchNo = mapRule.count(strIndex);
		multimap<string,string>::iterator iter = mapRule.find(strIndex);
		pair<string,string> pairUnit;
		for(int cnt =0; cnt < iMatchNo; ++cnt,++iter)
		{
			pairUnit = *iter;
			string strRight = pairUnit.second;
			if (strRight[0] == '!') 
			{
				iEmpty++;
				break;
			}
		}
	}
	iRet = iStrSize - iEmpty;
	return iRet;
}

bool CFG::HaveExist(string strIns)
{
	stack<string> stkTmp = stkRule;
	stkRule.pop();
	pushStack(strIns);
	string strStk = RetriveStack(); //·µ»Ørule stackµÄ×ó²¿.
	char sPos[10] = {0};
	sprintf (sPos, "%d",iPos);
//	cout << "pushstack"<<endl;
	string strCon = sPos + strStk;
	bool bRet = (setStk.count(strCon) >0 ? true : false);
	setStk.insert(strCon);
	stkRule = stkTmp;
	return bRet;
}

bool CFG::chkTop(string strCase)
{
#ifdef MYOUTPUT
	cout << "chkTop\n";
	cout << "\tstack\t"<< RetriveStack() << endl;
	cout <<"\tpos\t" << iPos << endl;
#endif

	if (strCase == "!")                 //if sample line is empty string
		if (ValidRegion(strRoot) ==0)   //check ! situation in Maprule.
			return true;
		else
			return false;
	
	string strTop = stkRule.top(); //top of stkRule 
	//to maintaince stack state, i use two location variable
	stack<string> stkTmp = stkRule;
	int iPosTmp = iPos;	
	
	if (strTop.find_first_of(strSet,0) != string::npos)   //strSet, all variables.
		//search the first postion of strSet in strTop, if no finding, return ::npos.
	{//A...Z && !
		set<string> setLowStk;//S->a;
		set<string> setLowUpStk;//S->aQ;
		set<string> setLowInStk;//S->aS;
		set<string> setUpStk;//S->AQ;
		set<string> setUpInStk;//S->AS;
		bool bEmpty = false;//S->!;
		
		int iMatchNo = mapRule.count(strTop);
		multimap<string,string>::iterator iter = mapRule.find(strTop);
		pair<string,string> pairUnit;

		//get all match rule,include: !,UpSet,and first char matched
		for(int cnt =0; cnt < iMatchNo; ++cnt,++iter)
		{
			pairUnit = *iter;
			string strRight = pairUnit.second;
			int iRight = ValidRegion(strRight);
			int iStk = stkRule.size();
			int iSum = iRight + iStk-1;
			int iPosRest = strCase.length() - iPos;
			
			if (iSum > iPosRest +1) continue;//size of stack > the rest of test case
			
			if (strRight.find_first_of(strEmpty,0) != string::npos)//S->!
			{
				bEmpty = true;
				continue;
			}

			if (strRight.find_first_of(strTerminals,0) == string::npos)//UpChar
			{
				if (strRight.find_first_of(strTop,0) == string::npos)//S->AQ;
				{
					if (HaveExist(strRight)) continue;
					setUpStk.insert(strRight);					
				}
				else//S->AS;
				{
					if (HaveExist(strRight)) continue;
					setUpInStk.insert(strRight);
				}
				continue;
			}

			if (strRight.find_first_of(strSet, 0) == string::npos)//S->a;
			{
				if(strRight[0] == strCase[iPos])
				{
					if (HaveExist(strRight)) continue;
					setLowStk.insert(strRight);
				}
				continue;
			}

			if((strRight.find_first_of(strTerminals,0) != string::npos) 
				&& (strRight.find_first_of(strSet,0) != string::npos))   //S->aS or S->aQ
			{
				if(strRight[0] == strCase[iPos])//LowChar && first char matched
				{
					if (strRight.find_first_of(strTop,0) == string::npos) //if right part doesn't contain S.
					{
						if (HaveExist(strRight)) continue;
						setLowUpStk.insert(strRight);//S->aQ;
					}
					else
					{
						if (HaveExist(strRight)) continue;
						setLowInStk.insert(strRight);//S->aS;
					}
				}
				continue;
			}
		}
		
		//order: 1,empty; 2,setLowStk; 3,setLowUpStk; 4,setLowInStk; 5,setUpStk; 6,setUpInStk;
		//1,empty
		if (bEmpty)
		{
			bEmpty = false;
			stkRule.pop();
			
			if(stkRule.empty())
			{
				if (strCase[iPos] == '!' || strCase[iPos] == '/0' || iPos >= strCase.length())
				{
					return true;
				}
				else 
				{
					ReCompare(stkTmp,iPosTmp);
				}
			}
			else
			{
				string strNextTop = stkRule.top();
				if(strNextTop.find_first_of(strTerminals,0) == 0)
				{
					if(strNextTop[0] == strCase[iPos])
					{
						if( chkTop(strCase)) return true;					
						ReCompare(stkTmp,iPosTmp);
					}
					else
					{
						ReCompare(stkTmp,iPosTmp);
					}
				}
				else
				{
					if( chkTop(strCase)) return true;					
					ReCompare(stkTmp,iPosTmp);
				}
			}						
		}

		//2,setLowStk
		while (!setLowStk.empty()) 
		{
			string strBegin = *setLowStk.begin();
			setLowStk.erase(strBegin);
			stkRule.pop();
			pushStack(strBegin); 
			if( chkTop(strCase)) return true;					
			ReCompare(stkTmp,iPosTmp);
		} 

		//3,setLowUpStk
		while (!setLowUpStk.empty()) 			
		{
			string strBegin = *setLowUpStk.begin();
			setLowUpStk.erase(strBegin);
			stkRule.pop();
			pushStack(strBegin);
			string strStackTmp = RetriveStack();
			string::size_type iLast = 0;
			iLast = strStackTmp.find_last_of(strSet,strStackTmp.length());
			if (iLast != string::npos) 
			{
				string strSub2 = strStackTmp.substr(iLast+1);
				string strSub3 = strCase.substr(iPos);
				int istrSub4 = strCase.length() - iPos;
				int istrSub5 = strStackTmp.length() - iLast - 1;
				if (istrSub5 > istrSub4) 
				{//example: strSub2=aSab, strSub3=b
					ReCompare(stkTmp,iPosTmp);
					continue;
				}
				if (istrSub5 == istrSub4 && strSub2 != strSub3) 
				{//example: strSub2=aSab, strSub3=bb
					ReCompare(stkTmp,iPosTmp);
					continue;
				}
			}
			if( chkTop(strCase)) return true;					
			ReCompare(stkTmp,iPosTmp);			
		}
		
		//4,setLowInStk
		while (!setLowInStk.empty()) 			
		{
			string strBegin = *setLowInStk.begin();
			setLowInStk.erase(strBegin);
			stkRule.pop();
			pushStack(strBegin);
			string strStackTmp = RetriveStack();
			string::size_type iLast = 0;
			iLast = strStackTmp.find_last_of(strSet,strStackTmp.length());
			if (iLast != string::npos) 
			{
				string strSub2 = strStackTmp.substr(iLast+1);
				string strSub3 = strCase.substr(iPos);
				int istrSub4 = strCase.length() - iPos;
				int istrSub5 = strStackTmp.length() - iLast - 1;
				if (istrSub5 > istrSub4) 
				{
					ReCompare(stkTmp,iPosTmp);
					continue;
				}
				if (istrSub5 == istrSub4 && strSub2 != strSub3) 
				{
					ReCompare(stkTmp,iPosTmp);
					continue;
				}
			}
			if( chkTop(strCase)) return true;					
			ReCompare(stkTmp,iPosTmp);			
		}

		//5,setUpStk
		while (!setUpStk.empty()) 
		{
			string strBegin = *setUpStk.begin();
			setUpStk.erase(strBegin);
			stkRule.pop();
			pushStack(strBegin); 			
			if( chkTop(strCase)) return true;					
			ReCompare(stkTmp,iPosTmp);			
		}
		
		//6,setUpInStk
		while (!setUpInStk.empty()) 
		{
			string strBegin = *setUpInStk.begin();
			setUpInStk.erase(strBegin);
			stkRule.pop();
			pushStack(strBegin);			
			if( chkTop(strCase)) return true;					
			ReCompare(stkTmp,iPosTmp);			
		}

		return false;
	}
	
	else//low terminal char
	{
		if (strTop[0] == strCase[iPos]) 
		{
			stkRule.pop();
			iPos++;
			if(stkRule.empty() && (iPos >= strCase.length() || strCase[iPos] == '\0' || strCase[iPos] == '!'))
			{
				return true;
			}
			else if(stkRule.empty() == false && (iPos >= strCase.length() || strCase[iPos] != '\0' || strCase[iPos] != '!'))
			{
				return chkTop(strCase);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool CFG::pushStack(string strPush)
{
	for(int i =strPush.length()-1; i >=0; i--)
	{
		char strTmp[2] ={0};
//		cout << "push stack"<<endl;
		sprintf(strTmp,"%c",strPush[i]);
		stkRule.push(strTmp);
	}
	return false;
}

string CFG::RetriveStack()
{
	string strStack;
	stack<string> stkTmp = stkRule;
	while(!stkTmp.empty())
	{
		strStack += stkTmp.top();
		stkTmp.pop();
	}
	return strStack;
}

void CFG::ReCompare(stack<string> stk, int index)
{
	stkRule = stk;
	iPos = index;
#ifdef MYOUTPUT
	cout << "ReCompare\n";
	cout << "\tstack\t"<< RetriveStack() << endl;
	cout <<"\tpos\t" << iPos << endl;
#endif 
}

int main(int argc, char* argv[])
{	
	CFG cfg;
	char csampleFile[256] = {0};    
	strcpy(csampleFile, argv[1]);    //copy sample file name to cTestFile
	if(!cfg.ParseFile(csampleFile))     //start parse the sample file into MapRule and Sample lines.
		return -2;
	cfg.ChkProcess();                //verify processing.
	return 0;
}

//2
//S->aSb
//S->!
//ab
//aabb
//!
//abb
