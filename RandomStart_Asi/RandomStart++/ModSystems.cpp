/*
			Random Start++ Systems
		--Created By Adoppocalipt 2023--
*/

#include "ModSystems.h"
#include "keyboard.h"

using namespace Mod_Data;
using namespace Mod_Systems;

#include <cstdlib>		//sRand - Random Number Generator
#include <ctime>		//time_t - Get the current date/time
#include <cmath>		//Math Functions Cos Tan etc...
#include <filesystem>	//Directory control Add/Remove Folders
#include <iostream>		//Header that defines the standard input/output stream objects:

#include <wchar.h>		//Support for w_Chars
#include <locale>		//streamng Support for w_Chars
//#include <stdio.h>			//Makes Stream Pointers to files
//#include <sys/stat.h>			//File Type Finder


#pragma comment(lib, "Winmm.lib")

namespace Mod_Systems
{
	std::string ConvertWideToANSI(const std::wstring& wstr)
	{//ouputs chinese... sometimes???
		int count = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
		std::string str(count, 0);
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
		return str;
	}
	std::string ConvertWideToUtf8(const std::wstring& wstr)
	{
		int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
		std::string str(count, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
		return str;
	}
	std::wstring ConvertAnsiToWide(const std::string& str)
	{
		int count = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.length(), NULL, 0);
		std::wstring wstr(count, 0);
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.length(), &wstr[0], count);
		return wstr;
	}

	std::string GetExeFileName()
	{
		WCHAR buffer[MAX_PATH]{};
		GetModuleFileNameW(NULL, buffer, ARRAYSIZE(buffer));

		return ConvertWideToUtf8(std::wstring(buffer));
	}
	std::string GetDir()
	{
		std::string f = GetExeFileName();
		std::string Dir = f.substr(0, f.find_last_of("\\/"));

		return Dir;
	}
	std::string TimeDate()
	{
		time_t curr_time;
		curr_time = time(NULL);
		std::string tm = ctime(&curr_time);
		tm[tm.length() - 1] = char(32);//32 is this fails testing the _s version..
		return tm;
	}
	bool FileExists(const std::string& filename)
	{
		try
		{
			std::ifstream Infield(filename);
			return Infield.good();
		}
		catch (...)
		{
			return false;
		}
	}

	void Play_Wav(const std::string& soundFile)
	{
		const wchar_t* path = ConvertAnsiToWide((LPSTR)soundFile.c_str()).c_str();
		PlaySound(path, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		//(LPCWSTR)soundFile.c_str()
	}

	bool FileRemoval(const std::string& filename)
	{
		bool Removed = false;
		try {
			if (std::filesystem::remove(filename))
				Removed = true;
		}
		catch (const std::filesystem::filesystem_error& err)
		{
			Removed = false;
		}
		return Removed;
	}

	void RemoveBlankStrings(std::vector<std::string>& stringlist)
	{
		for (int i = 0; i < (int)stringlist.size(); i++)
		{
			if (stringlist[i] == "")
				stringlist.erase(stringlist.begin() + i);
		}
	}
	const std::string sLogThis = GetDir() + "/RandomStart/LoggerLight.txt";
	bool startLogs = false;
	bool ListContains(std::vector<int>& List, int item)
	{
		bool b = false;
		for (int i = 0; i < List.size(); i++)
		{
			if (List[i] == item)
				b = true;
		}
		return b;
	}
	std::vector<std::string> Space38(const std::string& myLine)
	{
		std::vector<std::string> output = {};
		if ((int)myLine.length() < 38)
			output.push_back(myLine);
		else
		{
			std::string sLine = "";
			int i20 = 20;
			for (int i = 0; i < (int)myLine.length(); i++)
			{
				if ((int)sLine.length() < 38)
				{
					sLine += myLine[i];
					if (i20 < 0)
					{
						if (myLine[i] == char(46) || myLine[i] == char(44) || myLine[i] == char(32))
						{
							output.push_back(sLine);
							i20 = 20;
							sLine = "";
						}
					}
					i20--;
				}
				else
				{
					output.push_back(sLine);
					i20 = 20;
					sLine = "";
				}
			}
			output.push_back(sLine);
		}
		return output;
	}
	void LoggerLight(const std::string& text)
	{
		std::string RSFolder = GetDir() + "/RandomStart";
		if (CreateDirectoryA((LPSTR)RSFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			First_Load = true;
		else
			LoggerLight("Settings_Ini Folder Load Fail...");

		if (Mod_Settings.Loging)
		{
			if (startLogs)
			{
				std::ofstream MyFile(sLogThis, std::ios_base::app | std::ios_base::out);
				std::string Mess = TimeDate() + text;

				MyFile << Mess;
				MyFile << "\n";

				MyFile.close();
			}
			else
			{
				startLogs = true;

				std::ofstream MyFile(sLogThis);

				std::string Mess = TimeDate() + text;
				MyFile << Mess;
				MyFile << "\n";
				MyFile.close();
			}
		}
	}
	void WriteFile(const std::string& file, std::vector<std::string>& text)
	{
		std::ofstream MyFile(file);
		for (int i = 0; i < text.size(); i++)
		{
			MyFile << text[i];
			MyFile << "\n";
		}
		MyFile.close();
	}
	std::vector<std::string> IntoString(std::vector<int>& text)
	{
		std::vector<std::string> output = {};

		for (int i = 0; i < text.size(); i++)
			output.push_back(std::to_string(text[i]));

		return output;
	}
	std::vector<std::string> ReadSetFile(const std::string& fileName)
	{
		std::string myText;
		std::vector<std::string> textList = {};

		if (FileExists(fileName))
		{
			std::ifstream MyReadFile(fileName);

			while (std::getline(MyReadFile, myText))
			{
				// Output the text from the file
				textList.push_back(myText);
			}
			MyReadFile.close();
		}

		return textList;
	}
	bool StringContains(const std::string& line, const std::string& wholeString)
	{
		bool Contain = false;
		int iLine = 0;
		std::string Word = "";
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (iLine < line.length())
			{
				if (line[iLine] == wholeString[i])
				{
					Contain = true;
					Word += wholeString[i];
					iLine++;
				}
				else
				{
					iLine = 0;
					Word = "";
				}
			}
			else if (iLine > 0)
			{
				if (line == Word)
					break;
				else
				{
					iLine = 0;
					Word = "";

					if (line[0] == wholeString[i])
					{
						Contain = true;
						Word += wholeString[i];
						iLine++;
					}
				}
			}
		}

		if (Contain)
		{
			if (line != Word)
				Contain = false;
		}

		return Contain;
	}
	bool StringContains(char line, const std::string& wholeString)
	{
		bool Contain = false;
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (line == wholeString[i])
			{
				Contain = true;
				break;
			}
		}
		return Contain;
	}
	int FindCharicter(char chars, const std::string& wholeString)
	{
		int iLine = -1;
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (chars == wholeString[i])
			{
				iLine = i;
				break;
			}
		}
		return iLine;
	}
	int FindCharicter(const std::string& chars, const std::string& wholeString)
	{
		int iLine = -1;
		for (int i = 0; i < wholeString.length(); i++)
		{
			if (chars[0] == wholeString[i])
			{
				iLine = i;
				break;
			}
		}
		return iLine;
	}
	int StingNumbersInt(const std::string& line)
	{
		int iNum = 0;
		int iTimes = 0;
		bool bNegative = false;
		for (int i = (int)line.size(); i > -1; i--)
		{
			bool bSkip = false;
			int iAdd = 0;
			char sComp = line[i];

			if (sComp == char(45))
				bNegative = true;
			else if (sComp == char(49))
			{
				bNegative = false;
				iAdd = 1;
			}
			else if (sComp == char(50))
			{
				bNegative = false;
				iAdd = 2;
			}
			else if (sComp == char(51))
			{
				bNegative = false;
				iAdd = 3;
			}
			else if (sComp == char(52))
			{
				bNegative = false;
				iAdd = 4;
			}
			else if (sComp == char(53))
			{
				bNegative = false;
				iAdd = 5;
			}
			else if (sComp == char(54))
			{
				bNegative = false;
				iAdd = 6;
			}
			else if (sComp == char(55))
			{
				bNegative = false;
				iAdd = 7;
			}
			else if (sComp == char(56))
			{
				bNegative = false;
				iAdd = 8;
			}
			else if (sComp == char(57))
			{
				bNegative = false;
				iAdd = 9;
			}
			else if (sComp == char(48))
			{

			}
			else
				bSkip = true;

			if (!bSkip)
			{
				if (iTimes == 0)
				{
					iNum = iAdd;
					iTimes = 1;
				}
				else
					iNum += iAdd * iTimes;
				iTimes *= 10;
			}
		}

		if (bNegative)
			iNum = iNum * (-1);

		return iNum;
	}
	std::string AfterEqual(const std::string& tag)
	{
		int iSt = 0;
		std::string out;
		for (int i = 0; i < tag.length(); i++)
		{
			if (tag[i] == char(61))
			{
				iSt = i + 1;
				break;
			}
		}
		for (int i = iSt; i < tag.length(); i++)
			out += tag[i];

		return out;
	}
	float StingNumbersFloat(const std::string& line)
	{
		float fNum = 0;
		bool bNegative = false;
		bool DecDone = false;
		if (StringContains(".", line))
		{
			int iTimes = 0;
			for (int i = (int)line.size(); i > -1; i--)
			{
				bool bSkip = false;
				float fAdd = 0;
				char sComp = line[i];
				if (sComp == char(45))
					bNegative = true;
				else if (sComp == char(46))
				{
					fNum = fNum / iTimes;
					iTimes = 0;
					bSkip = true;
					DecDone = true;
				}
				else if (sComp == char(48))
				{
					if (DecDone)
					{
						DecDone = false;
						bSkip = true;
					}
				}
				else if (sComp == char(49))
				{
					bNegative = false;
					fAdd = 1;
				}
				else if (sComp == char(50))
				{
					bNegative = false;
					fAdd = 2;
				}
				else if (sComp == char(51))
				{
					bNegative = false;
					fAdd = 3;
				}
				else if (sComp == char(52))
				{
					bNegative = false;
					fAdd = 4;
				}
				else if (sComp == char(53))
				{
					bNegative = false;
					fAdd = 5;
				}
				else if (sComp == char(54))
				{
					bNegative = false;
					fAdd = 6;
				}
				else if (sComp == char(55))
				{
					bNegative = false;
					fAdd = 7;
				}
				else if (sComp == char(56))
				{
					bNegative = false;
					fAdd = 8;
				}
				else if (sComp == char(57))
				{
					bNegative = false;
					fAdd = 9;
				}
				else
					bSkip = true;

				if (!bSkip)
				{
					if (iTimes == 0)
					{
						fNum = fAdd;
						iTimes = 1;
					}
					else
						fNum += fAdd * iTimes;
					iTimes *= 10;
				}
			}

			if (bNegative)
				fNum = fNum * (-1);
		}
		else
			fNum = (float)StingNumbersInt(line);

		return fNum;
	}
	bool StringBool(const std::string& line)
	{
		if (StringContains("True", line))
			return true;
		else if (StringContains("true", line))
			return true;
		else if (StringContains("TRUE", line))
			return true;
		else if (StringContains("1", line))
			return true;
		else
			return false;
	}
	std::string BoolToString(bool bOut)
	{
		std::string s = "false";
		if (bOut)
			s = "true";

		return s;
	}
	float TwoDecimal(const std::string& Number)
	{
		int iSize = (int)Number.length();
		std::string Output = "";
		for (int i = 0; i < iSize; i++)
		{
			Output += Number[i];
			if (Number[i] == char(46) && i + 3 < Number.length())
				iSize = i + 3;
		}
		return StingNumbersFloat(Output);
	}
	bool ListstringContains(std::vector<std::string>& List, const std::string& item)
	{
		bool b = false;
		for (int i = 0; i < List.size(); i++)
		{
			if (StringContains(item, List[i]))
				b = true;
		}
		return b;
	}
	int DayOfWeek()
	{
		int iDay;
		std::string t = TimeDate();
		if (StringContains("Mon", t))
			iDay = 1;
		else if (StringContains("Tue", t))
			iDay = 2;
		else if (StringContains("Wed", t))
			iDay = 3;
		else if (StringContains("Thu", t))
			iDay = 4;
		else if (StringContains("Fri", t))
			iDay = 5;
		else
			iDay = 6;

		return iDay;
	}

	float RandomFloat(float min, float max)
	{
		if (min < max)
		{
			std::string BigNumbers = std::to_string(GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(min, max));
			float f = TwoDecimal(BigNumbers);
			return f;
		}
		else
			return min;
	}
	bool ERando = false;
	int RandomInt(int min, int max)
	{
		int EllRando = max - min;
		if (EllRando > 10)
		{
			if (ERando)
			{
				min /= 2;
				max /= 2;
			}
			else
			{
				if (min > -1 && min > max / 2)
				{
					min = max / 2;
				}
			}
			ERando = !ERando;
		}

		if (min < max)
		{
			srand((unsigned)time(NULL));

			return min + (rand() % max);
		}
		else
			return min;
	}
	std::vector<int> NewNums(int min, int max)
	{
		std::vector<int> Nums = {};
		for (int i = min; i < max + 1; i++)
			Nums.push_back(i);
		return Nums;
	}
	bool DirTest = true;
	const std::string RandNumFolder = GetDir() + "/RandomStart/Randoms";
	int LessRandomInt(const std::string& sName, int min, int max)
	{
		if (DirTest)
		{
			LoggerLight("LessRandomInt, Direct Test");
			if (CreateDirectoryA((LPSTR)RandNumFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			{
				LoggerLight("LessRandomInt, Direct Working");
				DirTest = false;
			}
			else
			{
				LoggerLight("LessRandomInt, Direct failed");
				if (min < max || min == max)
				{

				}
				else
				{
					max = RandomInt(min, max);
					min = max;
				}
			}
		}

		if (min < max || min == max)
		{
			int yourPlace = 0;
			int yourNum = min;
			std::vector<std::string> MyNums = ReadSetFile(RandNumFolder + "/" + sName + ".txt");
			std::vector<int> NumList = {};

			if (MyNums.size() < 2)
				NumList = NewNums(min, max);
			else
			{
				bool newWrite = false;
				if (StringContains("min=", MyNums[0]))
				{
					if (StingNumbersInt(MyNums[0]) != min)
						newWrite = true;

					if (StringContains("max=", MyNums[1]))
					{
						if (StingNumbersInt(MyNums[1]) != max)
							newWrite = true;
					}
				}
				else
					newWrite = true;

				for (int i = 2; i < MyNums.size(); i++)
					NumList.push_back(StingNumbersInt(MyNums[i]));

				if (NumList.size() == 0 || newWrite)
					NumList = NewNums(min, max);
			}
			yourPlace = RandomInt(0, (int)NumList.size());
			yourNum = NumList[yourPlace];
			NumList.erase(NumList.begin() + yourPlace);

			std::vector<std::string> output = { "min=" + std::to_string(min) , "max=" + std::to_string(max) };

			for (int i = 0; i < NumList.size(); i++)
				output.push_back(std::to_string(NumList[i]));

			WriteFile(RandNumFolder + "/" + sName + ".txt", output);

			return yourNum;
		}
		else
			return min;
	}
	int LessRandomInt(const std::string& sName, std::vector<int>& ranNum)
	{
		if (DirTest)
		{
			LoggerLight("LessRandomInt, Direct Test");
			if (CreateDirectoryA((LPSTR)RandNumFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			{
				LoggerLight("LessRandomInt, Direct Working");
				DirTest = false;
			}
		}

		if ((int)ranNum.size() > 0)
		{
			int yourPlace = 0;
			int yourNum = 0;
			std::vector<std::string> MyNums = ReadSetFile(RandNumFolder + "/" + sName + ".txt");
			std::vector<int> NumList = {};

			for (int i = 0; i < MyNums.size(); i++)
				NumList.push_back(StingNumbersInt(MyNums[i]));;

			if (NumList.size() == 0)
				NumList = ranNum;

			yourPlace = RandomInt(0, (int)NumList.size());
			yourNum = NumList[yourPlace];
			NumList.erase(NumList.begin() + yourPlace);

			std::vector<std::string> output = {};

			for (int i = 0; i < NumList.size(); i++)
				output.push_back(std::to_string(NumList[i]));

			WriteFile(RandNumFolder + "/" + sName + ".txt", output);

			return yourNum;
		}
		else
			return 0;
	}

	void StartScript(const std::string& scriptName, int buffer)
	{
		SCRIPT::REQUEST_SCRIPT((LPSTR)scriptName.c_str());
		while (!SCRIPT::HAS_SCRIPT_LOADED((LPSTR)scriptName.c_str()))
		{
			SCRIPT::REQUEST_SCRIPT((LPSTR)scriptName.c_str());
			WAIT(1);
		}

		SYSTEM::START_NEW_SCRIPT((LPSTR)scriptName.c_str(), buffer);
		SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED((LPSTR)scriptName.c_str());
	}

	void ReBuildIni(Mod_Class::Settings_Ini* PSet)
	{
		if (PSet != nullptr)
		{
			LoggerLight("ReBuildIni");
			std::string RSFolder = GetDir() + "/RandomStart";
			std::vector<std::string> AddIni = {
				"[Settings]",
				"MenuKey=" + std::to_string(PSet->MenuKey),
				"Auto_Run=" + BoolToString(PSet->Auto_Run),
				"Random_Ped=" + BoolToString(PSet->Random_Ped),
				"Saved_Ped=" + BoolToString(PSet->Saved_Ped),
				"Disable_Record_Key=" + BoolToString(PSet->Disable_Record_Key),
				"Random_Weapons=" + BoolToString(PSet->Random_Weapons),
				"Funeral=" + BoolToString(PSet->Funeral),
				"Prison=" + BoolToString(PSet->Prison),
				"BeachPart=" + BoolToString(PSet->BeachPart),
				"[Reincarnation]",
				"Reincarnate=" + BoolToString(PSet->Reincarnate),
				"ReCurr=" + BoolToString(PSet->ReCurr),
				"[Controler]",
				"ControlSupport=" + BoolToString(PSet->ControlSupport),
				"ControlA=" + std::to_string(PSet->ControlA),
				"ControlB=" + std::to_string(PSet->ControlB),
				"[Language]",
				"Lang_Set=" + std::to_string(PSet->Lang_Set),
				"[Senarios]",
				"BeachPed=" + BoolToString(PSet->BeachPed),
				"Tramps=" + BoolToString(PSet->Tramps),
				"Highclass=" + BoolToString(PSet->Highclass),
				"Midclass=" + BoolToString(PSet->Midclass),
				"Lowclass=" + BoolToString(PSet->Lowclass),
				"Business=" + BoolToString(PSet->Business),
				"Bodybuilder=" + BoolToString(PSet->Bodybuilder),
				"GangStars=" + BoolToString(PSet->GangStars),
				"Epsilon=" + BoolToString(PSet->Epsilon),
				"Jogger=" + BoolToString(PSet->Jogger),
				"Golfer=" + BoolToString(PSet->Golfer),
				"Hiker=" + BoolToString(PSet->Hiker),
				"Methaddict=" + BoolToString(PSet->Methaddict),
				"Rural=" + BoolToString(PSet->Rural),
				"Cyclist=" + BoolToString(PSet->Cyclist),
				"LGBTWXYZ=" + BoolToString(PSet->LGBTWXYZ),
				"PoolPeds=" + BoolToString(PSet->PoolPeds),
				"Workers=" + BoolToString(PSet->Workers),
				"Jetski=" + BoolToString(PSet->Jetski),
				"BikeATV=" + BoolToString(PSet->BikeATV),
				"Services=" + BoolToString(PSet->Services),
				"Pilot=" + BoolToString(PSet->Pilot),
				"Animals=" + BoolToString(PSet->Animals),
				"Yankton=" + BoolToString(PSet->Yankton),
				"Cayo=" + BoolToString(PSet->Cayo),
				"[Additional]",
				"Loging=" + BoolToString(PSet->Loging),
				"[Snow Months]",
				"SDJan=" + BoolToString(PSet->SnowMonths.Jan),
				"SDFeb=" + BoolToString(PSet->SnowMonths.Feb),
				"SDMar=" + BoolToString(PSet->SnowMonths.Mar),
				"SDApr=" + BoolToString(PSet->SnowMonths.Apr),
				"SDMay=" + BoolToString(PSet->SnowMonths.May),
				"SDJun=" + BoolToString(PSet->SnowMonths.Jun),
				"SDJul=" + BoolToString(PSet->SnowMonths.Jul),
				"SDAug=" + BoolToString(PSet->SnowMonths.Aug),
				"SDSep=" + BoolToString(PSet->SnowMonths.Sep),
				"SDOct=" + BoolToString(PSet->SnowMonths.Oct),
				"SDNov=" + BoolToString(PSet->SnowMonths.Nov),
				"SDDec=" + BoolToString(PSet->SnowMonths.Dec)
			};

			std::ofstream MyFile(GetDir() + "/RandomStart/Settings.ini");

			for (int i = 0; i < AddIni.size(); i++)
			{
				MyFile << AddIni[i];
				MyFile << "\n";
			}

			MyFile.close();
		}

	}
	void FindSettings(Mod_Class::Settings_Ini* mySets)
	{
		if (mySets != nullptr)
		{

			LoggerLight("FindSettings");
			std::vector<std::string> MySet = ReadSetFile(GetDir() + "/RandomStart/Settings.ini");
			std::string RSFolder = GetDir() + "/RandomStart";
			if (MySet.size() == 0)
			{
				if (CreateDirectoryA((LPSTR)RSFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
					First_Load = true;
				else
					LoggerLight("Settings_Ini Folder Load Fail...");
			}
			else
			{
				for (int i = 0; i < (int)MySet.size(); i++)
				{
					std::string line = MySet[i];
					if (StringContains("MenuKey", line))
						mySets->MenuKey = StingNumbersInt(line);
					else if (StringContains("Auto_Run", line))
						mySets->Auto_Run = StringBool(line);
					else if (StringContains("Random_Ped", line))
						mySets->Random_Ped = StringBool(line);
					else if (StringContains("Saved_Ped", line))
						mySets->Saved_Ped = StringBool(line);
					else if (StringContains("Disable_Record_Key", line))
						mySets->Disable_Record_Key = StringBool(line);
					else if (StringContains("Random_Weapons", line))
						mySets->Random_Weapons = StringBool(line);
					else if (StringContains("Funeral", line))
						mySets->Funeral = StringBool(line);
					else if (StringContains("Prison", line))
						mySets->Prison = StringBool(line);
					else if (StringContains("BeachPart", line))
						mySets->BeachPart = StringBool(line);
					else if (StringContains("Reincarnate", line))
						mySets->Reincarnate = StringBool(line);
					else if (StringContains("ReCurr", line))
						mySets->ReCurr = StringBool(line);
					else if (StringContains("ControlSupport", line))
						mySets->ControlSupport = StringBool(line);
					else if (StringContains("ControlA", line))
						mySets->ControlA = StingNumbersInt(line);
					else if (StringContains("ControlB", line))
						mySets->ControlB = StingNumbersInt(line);
					else if (StringContains("Lang_Set", line))
						mySets->Lang_Set = StingNumbersInt(line);
					else if (StringContains("BeachPed", line))
						mySets->BeachPed = StringBool(line);
					else if (StringContains("Tramps", line))
						mySets->Tramps = StringBool(line);
					else if (StringContains("Highclass", line))
						mySets->Highclass = StringBool(line);
					else if (StringContains("Midclass", line))
						mySets->Midclass = StringBool(line);
					else if (StringContains("Lowclass", line))
						mySets->Lowclass = StringBool(line);
					else if (StringContains("Business", line))
						mySets->Business = StringBool(line);
					else if (StringContains("Bodybuilder", line))
						mySets->Bodybuilder = StringBool(line);
					else if (StringContains("GangStars", line))
						mySets->GangStars = StringBool(line);
					else if (StringContains("Epsilon", line))
						mySets->Epsilon = StringBool(line);
					else if (StringContains("Jogger", line))
						mySets->Jogger = StringBool(line);
					else if (StringContains("Golfer", line))
						mySets->Golfer = StringBool(line);
					else if (StringContains("Hiker", line))
						mySets->Hiker = StringBool(line);
					else if (StringContains("Methaddict", line))
						mySets->Methaddict = StringBool(line);
					else if (StringContains("Rural", line))
						mySets->Rural = StringBool(line);
					else if (StringContains("Cyclist", line))
						mySets->Cyclist = StringBool(line);
					else if (StringContains("LGBTWXYZ", line))
						mySets->LGBTWXYZ = StringBool(line);
					else if (StringContains("PoolPeds", line))
						mySets->PoolPeds = StringBool(line);
					else if (StringContains("Workers", line))
						mySets->Workers = StringBool(line);
					else if (StringContains("Jetski", line))
						mySets->Jetski = StringBool(line);
					else if (StringContains("BikeATV", line))
						mySets->BikeATV = StringBool(line);
					else if (StringContains("Services", line))
						mySets->Services = StringBool(line);
					else if (StringContains("Pilot", line))
						mySets->Pilot = StringBool(line);
					else if (StringContains("Animals", line))
						mySets->Animals = StringBool(line);
					else if (StringContains("Yankton", line))
						mySets->Yankton = StringBool(line);
					else if (StringContains("Cayo", line))
						mySets->Cayo = StringBool(line);
					else if (StringContains("Loging", line))
						mySets->Loging = StringBool(line);
					else if (StringContains("SDJan", line))
						mySets->SnowMonths.Jan = StringBool(line);
					else if (StringContains("SDFeb", line))
						mySets->SnowMonths.Feb = StringBool(line);
					else if (StringContains("SDMar", line))
						mySets->SnowMonths.Mar = StringBool(line);
					else if (StringContains("SDApr", line))
						mySets->SnowMonths.Apr = StringBool(line);
					else if (StringContains("SDMay", line))
						mySets->SnowMonths.May = StringBool(line);
					else if (StringContains("SDJun", line))
						mySets->SnowMonths.Jun = StringBool(line);
					else if (StringContains("SDJul", line))
						mySets->SnowMonths.Jul = StringBool(line);
					else if (StringContains("SDAug", line))
						mySets->SnowMonths.Aug = StringBool(line);
					else if (StringContains("SDSep", line))
						mySets->SnowMonths.Sep = StringBool(line);
					else if (StringContains("SDOct", line))
						mySets->SnowMonths.Oct = StringBool(line);
					else if (StringContains("SDNov", line))
						mySets->SnowMonths.Nov = StringBool(line);
					else if (StringContains("SDDec", line))
						mySets->SnowMonths.Dec = StringBool(line);
				}
			}

			ReBuildIni(mySets);
		}

	}

	void SaveMyWeaps()
	{
		std::vector<std::string> NewSave = {};

		for (int i = 0; i < (int)Player_Weaps.size(); i++)
		{
			NewSave.push_back("[WeaponSaver]");
			NewSave.push_back("MyWeapon=" + Player_Weaps[i].MyWeapon);
			NewSave.push_back("MyAmmo=" + std::to_string(Player_Weaps[i].Ammo));
			NewSave.push_back("[Addons]");

			for (int j = 0; j < Player_Weaps[i].MyAddons.size(); j++)
				NewSave.push_back("MyAddon=" + Player_Weaps[i].MyAddons[j]);
		}


		std::ofstream MyFile(GetDir() + "/RandomStart/MyWeaps.ini");

		for (int i = 0; i < (int)NewSave.size(); i++)
		{
			MyFile << NewSave[i];
			MyFile << "\n";
		}

		MyFile.close();
	}
	std::vector<Mod_Class::WeaponSaver> LoadSavedWeapons()
	{
		bool Addons = false;
		std::vector<Mod_Class::WeaponSaver> MyWeaopns = {};
		std::vector<std::string> MyColect = ReadSetFile(GetDir() + "/RandomStart/MyWeaps.ini");

		std::string weapon = "";
		int ammo = 0;
		std::vector<std::string> MyAddons = {};

		for (int i = 0; i < MyColect.size(); i++)
		{
			std::string line = MyColect[i];
			if (Addons)
			{
				if (StringContains("[WeaponSaver]", line))
				{
					Addons = false;
					MyWeaopns.push_back(Mod_Class::WeaponSaver(weapon, MyAddons, ammo));
					MyAddons.clear();
				}
				else
					MyAddons.push_back(AfterEqual(line));
			}
			else if (StringContains("MyWeapon=", line))
				weapon = AfterEqual(line);
			else if (StringContains("MyAmmo", line))
				ammo = StingNumbersInt(line);
			else if (StringContains("[Addons]", line))
				Addons = true;
		}

		return MyWeaopns;
	}

	void LoadLang()
	{
		LoggerLight("LoadLang");

		const std::vector<std::string> LangEng = {
			"Enter",                                                                                    //0
			"Back",                                                                                     //1
			"Left",                                                                                     //2
			"Right",                                                                                    //3
			"Random Scenarios",                                                                         //4
			"Select available or launch a random scenario.",                                            //5
			"Save Ped Menu",                                                                            //6
			"Change customize and save characters.",                                                    //7
			"Random Start",                                                                             //8
			"Select a random scenario when game loads.",                                                //9
			"Random Ped",                                                                               //10
			"Load as or re-spawn as a random ped (includes animals).",                                  //11
			"Saved Ped",                                                                                //12
			"Load as or re-spawn as a saved ped.",                                                      //13
			"Reincarnation",                                                                            //14
			"Life after death?",                                                                        //15
			"Re-spawn",                                                                                 //16
			"Return as your current character in the area you died in.",                                //17
			"Funeral",                                                                                  //18
			"If you are using a random or non main character have a funeral service on death.",         //19
			"Prison",                                                                                   //20
			"Go straight to Bolingbroke do not pass go do not collect 200.",                            //21
			"Random Weapons",                                                                           //22
			"Get a random weapon selection or keep your current weapons.",                              //23
			"Capture Weapon Load-out",                                                                  //24
			"Save you current weapon selection.",                                                       //25
			"Change Key-bindings",                                                                      //26
			"Select menu load key.",                                                                    //27
			"Beach Ped",                                                                                //28
			"Sun bathing and motor boating.",                                                           //29
			"Tramps",                                                                                   //30
			"Down and out in Los Santos.",                                                              //31
			"High class",                                                                               //32
			"Nice house, nice car, nice weather.",                                                      //33
			"Mid class",                                                                                //34
			"Reasonable house, reasonable car, reasonable weather.",                                    //35
			"Low class",                                                                                //36
			"Rubbish house, trash car, crap weather.",                                                  //37
			"Business",                                                                                 //38
			"The high flying Los Santos elite.",                                                        //39
			"Body builder",                                                                             //40
			"Use the facilities at muscle beach.",                                                      //41
			"Gangsters",                                                                                //42
			"Defend your turf in the Los Santos war zones.",                                            //43
			"Epsilon ",                                                                                 //44
			"Join a cult and look down on the non-believers.",                                          //45
			"Jogger",                                                                                   //46
			"Take a run in some random location.",                                                      //47
			"Golfer",                                                                                   //48
			"Play a round or just burn up the turf in your caddy.",                                     //49
			"Hiker",                                                                                    //50
			"Explore the wilderness of Los Santos.",                                                    //51
			"Meth addict",                                                                              //52
			"Strawberry fields for ever.",                                                              //53
			"Rural",                                                                                    //54
			"Down on the farm.",                                                                        //55
			"Cyclist",                                                                                  //56
			"Put on the lycra and start peddling.",                                                     //57
			"LGBTWXYZ",                                                                                 //58
			"I am the very model of a modern Major-General I've information vegetable, animal, and mineral.",//59
			"Pool Peds",                                                                                //60
			"Take a swim or just chill by the pool.",                                                   //61
			"Workers",                                                                                  //62
			"The many trades and occupations in Los Santos.",                                           //63
			"Jet ski",                                                                                  //64
			"Race your jet-ski or just ride around for fun.",                                           //65
			"Bike/ATV",                                                                                 //66
			"Do some off-roading around Los Santos.",                                                   //67
			"Services",                                                                                 //68
			"Do your civic duty with fire, police, ambulance or military.",                             //69
			"Pilot",                                                                                    //70
			"Earn your wings gallivanting above Los Santos.",                                           //71
			"Animals",                                                                                  //72
			"Soar like a bird, strut like a deer, swim like a fish.",                                   //73
			"Yankton",                                                                                  //74
			"Visit snowy Yankton.",                                                                     //75
			"Cayo Piero",                                                                               //76
			"Visit sunny Cayo Piero.",                                                                  //77
			"Saved Peds",                                                                               //78
			"Select and edit your ped collection.",                                                     //79
			"Save current ped",                                                                         //80
			"save your current character.",                                                             //81
			"Freemode Ped",                                                                             //82
			"Generate a random freemode ped.",                                                          //83
			"Reposes Ped",                                                                              //84
			"Become a nearby ped.",                                                                     //85
			"Select a Ped",                                                                             //86
			"Rename Ped",                                                                               //87
			"Change the name of your ped.",                                                             //88
			"Change Outfit",                                                                            //89
			"Change your outfit.",                                                                      //90
			"Tattoo Pallor",                                                                            //91
			"Add Tattoos to your character.",                                                           //92
			"Set Hair Style",                                                                           //93
			"Eye Colour",                                                                               //94
			"Pick the colour of your eyes .",                                                           //95
			"Pick Hair Colour",                                                                         //96
			"Pick Hair Streaks",                                                                        //97
			"Set Overlays",                                                                             //98
			"Ped decals like age blush facial hair and make-up.",                                       //99
			"Alter Face Shape",                                                                         //100
			"Change position of chin, mouth, nose.",                                                    //101
			"Change Parents",                                                                           //102
			"Alter the base parents of your freemode character.",                                       //103
			"Set Voice",                                                                                //104
			"Save Changes",                                                                             //105
			"Create or update saved peds ini.",                                                         //106
			"Delete Ped",                                                                               //107
			"Remove this ped from saved peds directory.",                                               //108
			"Select outfit",                                                                            //109  
			"Create New Outfit",                                                                        //110
			"Save a new outfit on your character.",                                                     //111
			"Edit Outfits",                                                                             //112
			"edit the components on current outfit.",                                                   //113
			"Edit Props",                                                                               //114
			"Pick hats and glasses.",                                                                   //115
			"Pre-made outfits",                                                                         //116
			"Base Component",                                                                           //117
			"Texture",                                                                                  //118
			"Select ",                                                                                  //119
			"Opacity",                                                                                  //120
			"Colour",                                                                                   //121
			"First Parent",                                                                             //122
			"Second Parent",                                                                            //123
			"Shape Mix",                                                                                //124
			"Skin Mix",                                                                                 //125
			"Third Mix",                                                                                //126
			"Face",                                                                                     //127
			"Head",                                                                                     //128
			"Hair",                                                                                     //129
			"Torso",                                                                                    //130
			"Legs",                                                                                     //131
			"Back Packs",                                                                               //132
			"Feet",                                                                                     //133
			"Accessories",                                                                              //134
			"Top Add-ons",                                                                              //135
			"Armour",                                                                                   //136
			"Textures",                                                                                 //137
			"Coats",                                                                                    //138
			"Hats",                                                                                     //139
			"Glasses",                                                                                  //140
			"Ears",                                                                                     //141
			"Watches",                                                                                  //142
			"Torso",                                                                                    //143
			"Head",                                                                                     //144
			"Left Arm",                                                                                 //145
			"Right Arm",                                                                                //146
			"Left Leg",                                                                                 //147
			"Right Leg",                                                                                //148
			"Back",                                                                                     //149
			"Chest",                                                                                    //150
			"Stomach",                                                                                  //151
			"Nose Width",                                                                               //152
			"Nose Peak Hight",                                                                          //153
			"Nose Peak Length",                                                                         //154
			"Nose Bone_High",                                                                           //155
			"Nose Peak Lowering",                                                                       //156
			"Nose Bone Twist",                                                                          //157
			"Eye Brow High",                                                                            //158
			"Eye Brow Forward",                                                                         //159
			"Cheeks Bone High",                                                                         //160
			"Cheeks Bone Width",                                                                        //161
			"Cheeks Width",                                                                             //162
			"Eyes Opening",                                                                             //163
			"Lips Thickness",                                                                           //164
			"Jaw Bone Width 'Bone size to sides",                                                       //165
			"Jaw Bone Back Length 'Bone size to back",                                                  //166
			"Chimp_Bone_Lowering 'Go Down",                                                             //167
			"Chimp Bone Length 'Go forward",                                                            //168
			"Chimp Bone Width", "Chimp Hole",                                                           //169
			"Neck Thickness",                                                                           //170
			"Blemishes",                                                                                //171
			"Facial Hair",                                                                              //172
			"Eyebrows",                                                                                 //173
			"Ageing",                                                                                   //174
			"Make-up",                                                                                  //175
			"Blush",                                                                                    //176
			"Complexion",                                                                               //177
			"Sun Damage",                                                                               //178
			"Lipstick",                                                                                 //179
			"Moles & Freckles",                                                                         //180
			"Chest Hair",                                                                               //181
			"Body Blemishes",                                                                           //182
			"Add Body Blemishes",                                                                       //183
			"Select a Keyboard Key",                                                                    //184
			"Sets the menu open key.",                                                                  //185
			"Select a Controller Combo",                                                                //186
			"Choose two controller keys to open menu.",                                                 //187
			"Hold ~INPUT_VEH_EXIT~ to take control",                                                    //188
			"Hold the key you would like to use.",                                                      //189
			"Key Changed",                                                                              //190
			"Hold ~INPUT_VEH_EXIT~ to hide under van",                                                  //191
			"Hold ~INPUT_VEH_EXIT~ to hide in waste bin",                                               //192
			"Top Decal",                                                                                //193
			"Explore the World: GTA games often feature vast open worlds with a lot of hidden content, collectibles, and easter eggs. Take your time to explore and enjoy the scenery.",
			"Follow the Story: While you can engage in random chaos, the main story missions provide structure and context for the game. Completing these missions often unlocks new content and areas.",
			"Use Cover: In gunfights, always use cover to protect yourself. Pop out to shoot, then take cover again. This reduces the chances of getting shot.",
			"Manage Your Health: Keep an eye on your health and armor levels. You can usually find health packs and armor scattered throughout the game world. Stock up before difficult missions.",
			"Plan Your Getaways: After committing a crime, have an escape plan. Know where you're going and what you'll do to evade the police.",
			"Invest in Properties: In some GTA games, you can buy properties. These can provide a passive income and sometimes even offer other benefits.",
			"Experiment with Vehicles: GTA games have a wide variety of vehicles, from cars to planes to bicycles. Experiment with different vehicles to see which ones suit your style and mission needs.",
			"Customize Your Character: Many GTA games allow you to customize your character's appearance. Experiment with clothing and accessories to create your own unique style.",
			"Use the Internet: In later GTA games, characters have smartphones and access to the internet. You can use it to buy vehicles, properties, and more.",
			"Save Your Game: Don't forget to save your progress regularly, especially after completing important missions. This will prevent you from losing a lot of progress in case you fail a mission or get busted.",
			"Don't Ignore Side Missions: Side missions can offer fun and unique experiences, as well as rewards like weapons, money, and even character upgrades.",
			"Respect Traffic Rules (or Not): Sometimes following traffic rules can help you blend in and avoid the attention of the police. On the other hand, reckless driving can be a lot of fun. It's up to you!",
			"Be Mindful of Police: Committing crimes will get the attention of the police. Pay attention to wanted levels and use Pay 'n' Spray or other hiding spots to lose the cops.",
			"Play with Friends: If the game supports it, playing GTA with friends can be a blast. You can complete missions together or engage in chaotic, open-world mayhem.",
			"Have Fun: Ultimately, GTA games are meant to be enjoyed. Whether you prefer causing chaos, following the story, or just exploring, remember that it's a game, and the goal is to have fun.",
			"Press ~INPUT_TALK~ to change dance, hold ~INPUT_VEH_EXIT~ to  stop Dancing",              //209
			"Press ~INPUT_TALK~ to start dancing",                                                       //210
			"press ~INPUT_DUCK~ to select a ped, press ~INPUT_SPRINT~ to  become this ped, Press ~INPUT_RELOAD~ to Close.",                                                       //211
			"Press ~INPUT_TALK~ to change action, hold ~INPUT_VEH_EXIT~ to exit.",                                                       //212
			"Winter is Coming",                                                       //213
			"January",                                                       //214
			"February",                                                       //215
			"March",                                                       //216
			"April",                                                       //217
			"May",                                                       //218
			"June",                                                       //219
			"July",                                                       //220
			"August",                                                     //221
			"September",                                                     //222
			"October",                                                     //223
			"November",                                                     //224
			"December",                                                     //225
			"Set your winter months",                                    //226
			"Blank",                                                       //227
			"Blank",                                                       //228
			"Blank",                                                       //229
			"Blank"                                                       //230
		};

		int MyLan = Mod_Settings.Lang_Set;
		
		if (MyLan == -1)
			MyLan = UNK::_GET_UI_LANGUAGE_ID(); // 2BDD44CC428A7EAE

		if (MyLan == 0)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/English.txt");
		else if (MyLan == 1)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/French.txt");
		else if (MyLan == 2)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/German.txt");
		else if (MyLan == 3)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Italian.txt");
		else if (MyLan == 4)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Spanish.txt");
		else if (MyLan == 5)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Portuguese.txt");
		else if (MyLan == 6)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Polish.txt");
		else if (MyLan == 7)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Russian.txt");
		else if (MyLan == 8)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Korean.txt");
		else if (MyLan == 9)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Chinese.txt");
		else if (MyLan == 10)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Japanese.txt");
		else if (MyLan == 11)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/Spanish.txt");
		else if (MyLan == 12)
			RSLangMenu = ReadSetFile(GetDir() + "/RandomStart/Translate/ChineseSimplify.txt");

		if ((int)RSLangMenu.size() < 224)
			RSLangMenu = LangEng;

		Mod_Settings.Lang_Set = MyLan;
	}

	Hash MyHashKey(const std::string& name)
	{
		return GAMEPLAY::GET_HASH_KEY((LPSTR)name.c_str());
	}

	const std::vector<std::string> ControlSym = {
	" ~INPUT_NEXT_CAMERA~ ",//V~ ");//BACK
	" ~INPUT_LOOK_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_LOOK_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_LOOK_UP_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_LOOK_DOWN_ONLY~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_LOOK_LEFT_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_LOOK_RIGHT_ONLY~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_CINEMATIC_SLOWMO~ ",//(NONE);~ ");//R3
	" ~INPUT_SCRIPTED_FLY_UD~ ",//S~ ");//LEFT STICK
	" ~INPUT_SCRIPTED_FLY_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_SCRIPTED_FLY_ZUP~ ",//PAGEUP~ ");//LT
	" ~INPUT_SCRIPTED_FLY_ZDOWN~ ",//PAGEDOWN~ ");//RT
	" ~INPUT_WEAPON_WHEEL_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_WEAPON_WHEEL_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_WEAPON_WHEEL_NEXT~ ",//SCROLLWHEEL DOWN~ ");//DPAD RIGHT
	" ~INPUT_WEAPON_WHEEL_PREV~ ",//SCROLLWHEEL UP~ ");//DPAD LEFT
	" ~INPUT_SELECT_NEXT_WEAPON~ ",//SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_SELECT_PREV_WEAPON~ ",//SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_SKIP_CUTSCENE~ ",//ENTER / LEFT MOUSE BUTTON / SPACEBAR~ ");//A
	" ~INPUT_CHARACTER_WHEEL~ ",//LEFT ALT~ ");//DPAD DOWN
	" ~INPUT_MULTIPLAYER_INFO~ ",//Z~ ");//DPAD DOWN
	" ~INPUT_SPRINT~ ",//LEFT SHIFT~ ");//A
	" ~INPUT_JUMP~ ",//SPACEBAR~ ");//X
	" ~INPUT_ENTER~ ",//F~ ");//Y
	" ~INPUT_ATTACK~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_AIM~ ",//RIGHT MOUSE BUTTON~ ");//LT
	" ~INPUT_LOOK_BEHIND~ ",//C~ ");//R3
	" ~INPUT_PHONE~ ",//ARROW UP / SCROLLWHEEL BUTTON (PRESS);~ ");//DPAD UP
	" ~INPUT_SPECIAL_ABILITY~ ",//(NONE);~ ");//L3
	" ~INPUT_SPECIAL_ABILITY_SECONDARY~ ",//B~ ");//R3
	" ~INPUT_MOVE_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_MOVE_UD~ ",//S~ ");//LEFT STICK
	" ~INPUT_MOVE_UP_ONLY~ ",//W~ ");//LEFT STICK
	" ~INPUT_MOVE_DOWN_ONLY~ ",//S~ ");//LEFT STICK
	" ~INPUT_MOVE_LEFT_ONLY~ ",//A~ ");//LEFT STICK
	" ~INPUT_MOVE_RIGHT_ONLY~ ",//D~ ");//LEFT STICK
	" ~INPUT_DUCK~ ",//LEFT CTRL~ ");//L3
	" ~INPUT_SELECT_WEAPON~ ",//TAB~ ");//LB
	" ~INPUT_PICKUP~ ",//E~ ");//LB
	" ~INPUT_SNIPER_ZOOM~ ",//[~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_IN_ONLY~ ",//]~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_OUT_ONLY~ ",//[~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_IN_SECONDARY~ ",//]~ ");//DPAD UP
	" ~INPUT_SNIPER_ZOOM_OUT_SECONDARY~ ",//[~ ");//DPAD DOWN
	" ~INPUT_COVER~ ",//Q~ ");//RB
	" ~INPUT_RELOAD~ ",//R~ ");//B
	" ~INPUT_TALK~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_DETONATE~ ",//G~ ");//DPAD LEFT
	" ~INPUT_HUD_SPECIAL~ ",//Z~ ");//DPAD DOWN
	" ~INPUT_ARREST~ ",//F~ ");//Y
	" ~INPUT_ACCURATE_AIM~ ",//SCROLLWHEEL DOWN~ ");//R3
	" ~INPUT_CONTEXT~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_CONTEXT_SECONDARY~ ",//Q~ ");//DPAD LEFT
	" ~INPUT_WEAPON_SPECIAL~ ",//(NONE);~ ");//Y
	" ~INPUT_WEAPON_SPECIAL_TWO~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_DIVE~ ",//SPACEBAR~ ");//RB
	" ~INPUT_DROP_WEAPON~ ",//F9~ ");//Y
	" ~INPUT_DROP_AMMO~ ",//F10~ ");//B
	" ~INPUT_THROW_GRENADE~ ",//G~ ");//DPAD LEFT
	" ~INPUT_VEH_MOVE_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_UD~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_UP_ONLY~ ",//LEFT SHIFT~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_DOWN_ONLY~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_LEFT_ONLY~ ",//A~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_RIGHT_ONLY~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_SPECIAL~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_VEH_GUN_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_VEH_AIM~ ",//RIGHT MOUSE BUTTON~ ");//LB
	" ~INPUT_VEH_ATTACK~ ",//LEFT MOUSE BUTTON~ ");//RB
	" ~INPUT_VEH_ATTACK2~ ",//RIGHT MOUSE BUTTON~ ");//A
	" ~INPUT_VEH_ACCELERATE~ ",//W~ ");//RT
	" ~INPUT_VEH_BRAKE~ ",//S~ ");//LT
	" ~INPUT_VEH_DUCK~ ",//X~ ");//A
	" ~INPUT_VEH_HEADLIGHT~ ",//H~ ");//DPAD RIGHT
	" ~INPUT_VEH_EXIT~ ",//F~ ");//Y
	" ~INPUT_VEH_HANDBRAKE~ ",//SPACEBAR~ ");//RB
	" ~INPUT_VEH_HOTWIRE_LEFT~ ",//W~ ");//LT
	" ~INPUT_VEH_HOTWIRE_RIGHT~ ",//S~ ");//RT
	" ~INPUT_VEH_LOOK_BEHIND~ ",//C~ ");//R3
	" ~INPUT_VEH_CIN_CAM~ ",//R~ ");//B
	" ~INPUT_VEH_NEXT_RADIO~ ",//.~ ");//(NONE);
	" ~INPUT_VEH_PREV_RADIO~ ",//,~ ");//(NONE);
	" ~INPUT_VEH_NEXT_RADIO_TRACK~ ",//=~ ");//(NONE);
	" ~INPUT_VEH_PREV_RADIO_TRACK~ ",//-~ ");//(NONE);
	" ~INPUT_VEH_RADIO_WHEEL~ ",//Q~ ");//DPAD LEFT
	" ~INPUT_VEH_HORN~ ",//E~ ");//L3
	" ~INPUT_VEH_FLY_THROTTLE_UP~ ",//W~ ");//RT
	" ~INPUT_VEH_FLY_THROTTLE_DOWN~ ",//S~ ");//LT
	" ~INPUT_VEH_FLY_YAW_LEFT~ ",//A~ ");//LB
	" ~INPUT_VEH_FLY_YAW_RIGHT~ ",//D~ ");//RB
	" ~INPUT_VEH_PASSENGER_AIM~ ",//RIGHT MOUSE BUTTON~ ");//LT
	" ~INPUT_VEH_PASSENGER_ATTACK~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_VEH_SPECIAL_ABILITY_FRANKLIN~ ",//(NONE);~ ");//R3
	" ~INPUT_VEH_STUNT_UD~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_VEH_CINEMATIC_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_VEH_CINEMATIC_UP_ONLY~ ",//NUMPAD- / SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_VEH_CINEMATIC_DOWN_ONLY~ ",//NUMPAD+ / SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_VEH_CINEMATIC_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_SELECT_NEXT_WEAPON~ ",//SCROLLWHEEL UP~ ");//X
	" ~INPUT_VEH_SELECT_PREV_WEAPON~ ",//[~ ");//(NONE);
	" ~INPUT_VEH_ROOF~ ",//H~ ");//DPAD RIGHT
	" ~INPUT_VEH_JUMP~ ",//SPACEBAR~ ");//RB
	" ~INPUT_VEH_GRAPPLING_HOOK~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_SHUFFLE~ ",//H~ ");//DPAD RIGHT
	" ~INPUT_VEH_DROP_PROJECTILE~ ",//X~ ");//A
	" ~INPUT_VEH_MOUSE_CONTROL_OVERRIDE~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_FLY_ROLL_LR~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_ROLL_LEFT_ONLY~ ",//NUMPAD 4~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_ROLL_RIGHT_ONLY~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_PITCH_UD~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_PITCH_UP_ONLY~ ",//NUMPAD 8~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_PITCH_DOWN_ONLY~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_FLY_UNDERCARRIAGE~ ",//G~ ");//L3
	" ~INPUT_VEH_FLY_ATTACK~ ",//RIGHT MOUSE BUTTON~ ");//A
	" ~INPUT_VEH_FLY_SELECT_NEXT_WEAPON~ ",//SCROLLWHEEL UP~ ");//DPAD LEFT
	" ~INPUT_VEH_FLY_SELECT_PREV_WEAPON~ ",//[~ ");//(NONE);
	" ~INPUT_VEH_FLY_SELECT_TARGET_LEFT~ ",//NUMPAD 7~ ");//LB
	" ~INPUT_VEH_FLY_SELECT_TARGET_RIGHT~ ",//NUMPAD 9~ ");//RB
	" ~INPUT_VEH_FLY_VERTICAL_FLIGHT_MODE~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_FLY_DUCK~ ",//X~ ");//A
	" ~INPUT_VEH_FLY_ATTACK_CAMERA~ ",//INSERT~ ");//R3
	" ~INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_SUB_TURN_LR~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_TURN_LEFT_ONLY~ ",//NUMPAD 4~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_TURN_RIGHT_ONLY~ ",//NUMPAD 6~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_PITCH_UD~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_PITCH_UP_ONLY~ ",//NUMPAD 8~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_PITCH_DOWN_ONLY~ ",//NUMPAD 5~ ");//LEFT STICK
	" ~INPUT_VEH_SUB_THROTTLE_UP~ ",//W~ ");//RT
	" ~INPUT_VEH_SUB_THROTTLE_DOWN~ ",//S~ ");//LT
	" ~INPUT_VEH_SUB_ASCEND~ ",//LEFT SHIFT~ ");//X
	" ~INPUT_VEH_SUB_DESCEND~ ",//LEFT CTRL~ ");//A
	" ~INPUT_VEH_SUB_TURN_HARD_LEFT~ ",//A~ ");//LB
	" ~INPUT_VEH_SUB_TURN_HARD_RIGHT~ ",//D~ ");//RB
	" ~INPUT_VEH_SUB_MOUSE_CONTROL_OVERRIDE~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_PUSHBIKE_PEDAL~ ",//W~ ");//A
	" ~INPUT_VEH_PUSHBIKE_SPRINT~ ",//CAPSLOCK~ ");//A
	" ~INPUT_VEH_PUSHBIKE_FRONT_BRAKE~ ",//Q~ ");//LT
	" ~INPUT_VEH_PUSHBIKE_REAR_BRAKE~ ",//S~ ");//RT
	" ~INPUT_MELEE_ATTACK_LIGHT~ ",//R~ ");//B
	" ~INPUT_MELEE_ATTACK_HEAVY~ ",//Q~ ");//A
	" ~INPUT_MELEE_ATTACK_ALTERNATE~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_MELEE_BLOCK~ ",//SPACEBAR~ ");//X
	" ~INPUT_PARACHUTE_DEPLOY~ ",//F / LEFT MOUSE BUTTON~ ");//Y
	" ~INPUT_PARACHUTE_DETACH~ ",//F~ ");//Y
	" ~INPUT_PARACHUTE_TURN_LR~ ",//D~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_TURN_LEFT_ONLY~ ",//A~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_TURN_RIGHT_ONLY~ ",//D~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_PITCH_UD~ ",//S~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_PITCH_UP_ONLY~ ",//W~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_PITCH_DOWN_ONLY~ ",//S~ ");//LEFT STICK
	" ~INPUT_PARACHUTE_BRAKE_LEFT~ ",//Q~ ");//LB
	" ~INPUT_PARACHUTE_BRAKE_RIGHT~ ",//E~ ");//RB
	" ~INPUT_PARACHUTE_SMOKE~ ",//X~ ");//A
	" ~INPUT_PARACHUTE_PRECISION_LANDING~ ",//LEFT SHIFT~ ");//(NONE);
	" ~INPUT_MAP~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_UNARMED~ ",//1~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_MELEE~ ",//2~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_HANDGUN~ ",//6~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SHOTGUN~ ",//3~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SMG~ ",//7~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_AUTO_RIFLE~ ",//8~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SNIPER~ ",//9~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_HEAVY~ ",//4~ ");//(NONE);
	" ~INPUT_SELECT_WEAPON_SPECIAL~ ",//5~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_MICHAEL~ ",//F5~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_FRANKLIN~ ",//F6~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_TREVOR~ ",//F7~ ");//(NONE);
	" ~INPUT_SELECT_CHARACTER_MULTIPLAYER~ ",//F8 (CONSOLE);~ ");//(NONE);
	" ~INPUT_SAVE_REPLAY_CLIP~ ",//F3~ ");//B
	" ~INPUT_SPECIAL_ABILITY_PC~ ",//CAPSLOCK~ ");//(NONE);
	" ~INPUT_CELLPHONE_UP~ ",//ARROW UP~ ");//DPAD UP
	" ~INPUT_CELLPHONE_DOWN~ ",//ARROW DOWN~ ");//DPAD DOWN
	" ~INPUT_CELLPHONE_LEFT~ ",//ARROW LEFT~ ");//DPAD LEFT
	" ~INPUT_CELLPHONE_RIGHT~ ",//ARROW RIGHT~ ");//DPAD RIGHT
	" ~INPUT_CELLPHONE_SELECT~ ",//ENTER / LEFT MOUSE BUTTON~ ");//A
	" ~INPUT_CELLPHONE_CANCEL~ ",//BACKSPACE / ESC / RIGHT MOUSE BUTTON~ ");//B
	" ~INPUT_CELLPHONE_OPTION~ ",//DELETE~ ");//Y
	" ~INPUT_CELLPHONE_EXTRA_OPTION~ ",//SPACEBAR~ ");//X
	" ~INPUT_CELLPHONE_SCROLL_FORWARD~ ",//SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_CELLPHONE_SCROLL_BACKWARD~ ",//SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_CELLPHONE_CAMERA_FOCUS_LOCK~ ",//L~ ");//RT
	" ~INPUT_CELLPHONE_CAMERA_GRID~ ",//G~ ");//RB
	" ~INPUT_CELLPHONE_CAMERA_SELFIE~ ",//E~ ");//R3
	" ~INPUT_CELLPHONE_CAMERA_DOF~ ",//F~ ");//LB
	" ~INPUT_CELLPHONE_CAMERA_EXPRESSION~ ",//X~ ");//L3
	" ~INPUT_FRONTEND_DOWN~ ",//ARROW DOWN~ ");//DPAD DOWN
	" ~INPUT_FRONTEND_UP~ ",//ARROW UP~ ");//DPAD UP
	" ~INPUT_FRONTEND_LEFT~ ",//ARROW LEFT~ ");//DPAD LEFT
	" ~INPUT_FRONTEND_RIGHT~ ",//ARROW RIGHT~ ");//DPAD RIGHT
	" ~INPUT_FRONTEND_RDOWN~ ",//ENTER~ ");//A
	" ~INPUT_FRONTEND_RUP~ ",//TAB~ ");//Y
	" ~INPUT_FRONTEND_RLEFT~ ",//(NONE);~ ");//X
	" ~INPUT_FRONTEND_RRIGHT~ ",//BACKSPACE~ ");//B
	" ~INPUT_FRONTEND_AXIS_X~ ",//D~ ");//LEFT STICK
	" ~INPUT_FRONTEND_AXIS_Y~ ",//S~ ");//LEFT STICK
	" ~INPUT_FRONTEND_RIGHT_AXIS_X~ ",//]~ ");//RIGHT STICK
	" ~INPUT_FRONTEND_RIGHT_AXIS_Y~ ",//SCROLLWHEEL DOWN~ ");//RIGHT STICK
	" ~INPUT_FRONTEND_PAUSE~ ",//P~ ");//START
	" ~INPUT_FRONTEND_PAUSE_ALTERNATE~ ",//ESC~ ");//(NONE);
	" ~INPUT_FRONTEND_ACCEPT~ ",//ENTER / NUMPAD ENTER~ ");//A
	" ~INPUT_FRONTEND_CANCEL~ ",//BACKSPACE / ESC~ ");//B
	" ~INPUT_FRONTEND_X~ ",//SPACEBAR~ ");//X
	" ~INPUT_FRONTEND_Y~ ",//TAB~ ");//Y
	" ~INPUT_FRONTEND_LB~ ",//Q~ ");//LB
	" ~INPUT_FRONTEND_RB~ ",//E~ ");//RB
	" ~INPUT_FRONTEND_LT~ ",//PAGE DOWN~ ");//LT
	" ~INPUT_FRONTEND_RT~ ",//PAGE UP~ ");//RT
	" ~INPUT_FRONTEND_LS~ ",//LEFT SHIFT~ ");//L3
	" ~INPUT_FRONTEND_RS~ ",//LEFT CONTROL~ ");//R3
	" ~INPUT_FRONTEND_LEADERBOARD~ ",//TAB~ ");//RB
	" ~INPUT_FRONTEND_SOCIAL_CLUB~ ",//HOME~ ");//BACK
	" ~INPUT_FRONTEND_SOCIAL_CLUB_SECONDARY~ ",//HOME~ ");//RB
	" ~INPUT_FRONTEND_DELETE~ ",//DELETE~ ");//X
	" ~INPUT_FRONTEND_ENDSCREEN_ACCEPT~ ",//ENTER~ ");//A
	" ~INPUT_FRONTEND_ENDSCREEN_EXPAND~ ",//SPACEBAR~ ");//X
	" ~INPUT_FRONTEND_SELECT~ ",//CAPSLOCK~ ");//BACK
	" ~INPUT_SCRIPT_LEFT_AXIS_X~ ",//D~ ");//LEFT STICK
	" ~INPUT_SCRIPT_LEFT_AXIS_Y~ ",//S~ ");//LEFT STICK
	" ~INPUT_SCRIPT_RIGHT_AXIS_X~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_SCRIPT_RIGHT_AXIS_Y~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_SCRIPT_RUP~ ",//RIGHT MOUSE BUTTON~ ");//Y
	" ~INPUT_SCRIPT_RDOWN~ ",//LEFT MOUSE BUTTON~ ");//A
	" ~INPUT_SCRIPT_RLEFT~ ",//LEFT CTRL~ ");//X
	" ~INPUT_SCRIPT_RRIGHT~ ",//RIGHT MOUSE BUTTON~ ");//B
	" ~INPUT_SCRIPT_LB~ ",//(NONE);~ ");//LB
	" ~INPUT_SCRIPT_RB~ ",//(NONE);~ ");//RB
	" ~INPUT_SCRIPT_LT~ ",//(NONE);~ ");//LT
	" ~INPUT_SCRIPT_RT~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_SCRIPT_LS~ ",//(NONE);~ ");//L3
	" ~INPUT_SCRIPT_RS~ ",//(NONE);~ ");//R3
	" ~INPUT_SCRIPT_PAD_UP~ ",//W~ ");//DPAD UP
	" ~INPUT_SCRIPT_PAD_DOWN~ ",//S~ ");//DPAD DOWN
	" ~INPUT_SCRIPT_PAD_LEFT~ ",//A~ ");//DPAD LEFT
	" ~INPUT_SCRIPT_PAD_RIGHT~ ",//D~ ");//DPAD RIGHT
	" ~INPUT_SCRIPT_SELECT~ ",//V~ ");//BACK
	" ~INPUT_CURSOR_ACCEPT~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_CURSOR_CANCEL~ ",//RIGHT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_CURSOR_X~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_CURSOR_Y~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_CURSOR_SCROLL_UP~ ",//SCROLLWHEEL UP~ ");//(NONE);
	" ~INPUT_CURSOR_SCROLL_DOWN~ ",//SCROLLWHEEL DOWN~ ");//(NONE);
	" ~INPUT_ENTER_CHEAT_CODE~ ",//~ / `~ ");//(NONE);
	" ~INPUT_INTERACTION_MENU~ ",//M~ ");//BACK
	" ~INPUT_MP_TEXT_CHAT_ALL~ ",//T~ ");//(NONE);
	" ~INPUT_MP_TEXT_CHAT_TEAM~ ",//Y~ ");//(NONE);
	" ~INPUT_MP_TEXT_CHAT_FRIENDS~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_MP_TEXT_CHAT_CREW~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_PUSH_TO_TALK~ ",//N~ ");//(NONE);
	" ~INPUT_CREATOR_LS~ ",//R~ ");//L3
	" ~INPUT_CREATOR_RS~ ",//F~ ");//R3
	" ~INPUT_CREATOR_LT~ ",//X~ ");//LT
	" ~INPUT_CREATOR_RT~ ",//C~ ");//RT
	" ~INPUT_CREATOR_MENU_TOGGLE~ ",//LEFT SHIFT~ ");//(NONE);
	" ~INPUT_CREATOR_ACCEPT~ ",//SPACEBAR~ ");//A
	" ~INPUT_CREATOR_DELETE~ ",//DELETE~ ");//X
	" ~INPUT_ATTACK2~ ",//LEFT MOUSE BUTTON~ ");//RT
	" ~INPUT_RAPPEL_JUMP~ ",//(NONE);~ ");//A
	" ~INPUT_RAPPEL_LONG_JUMP~ ",//(NONE);~ ");//X
	" ~INPUT_RAPPEL_SMASH_WINDOW~ ",//(NONE);~ ");//RT
	" ~INPUT_PREV_WEAPON~ ",//SCROLLWHEEL UP~ ");//DPAD LEFT
	" ~INPUT_NEXT_WEAPON~ ",//SCROLLWHEEL DOWN~ ");//DPAD RIGHT
	" ~INPUT_MELEE_ATTACK1~ ",//R~ ");//B
	" ~INPUT_MELEE_ATTACK2~ ",//Q~ ");//A
	" ~INPUT_WHISTLE~ ",//(NONE);~ ");//(NONE);
	" ~INPUT_MOVE_LEFT~ ",//D~ ");//LEFT STICK
	" ~INPUT_MOVE_RIGHT~ ",//D~ ");//LEFT STICK
	" ~INPUT_MOVE_UP~ ",//S~ ");//LEFT STICK
	" ~INPUT_MOVE_DOWN~ ",//S~ ");//LEFT STICK
	" ~INPUT_LOOK_LEFT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_LOOK_RIGHT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_LOOK_UP~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_LOOK_DOWN~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_SNIPER_ZOOM_IN~ ",//[~ ");//RIGHT STICK
	" ~INPUT_SNIPER_ZOOM_OUT~ ",//[~ ");//RIGHT STICK
	" ~INPUT_SNIPER_ZOOM_IN_ALTERNATE~ ",//[~ ");//LEFT STICK
	" ~INPUT_SNIPER_ZOOM_OUT_ALTERNATE~ ",//[~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_LEFT~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_RIGHT~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_UP~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_MOVE_DOWN~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_GUN_LEFT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_RIGHT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_UP~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_GUN_DOWN~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_LOOK_LEFT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_LOOK_RIGHT~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_REPLAY_START_STOP_RECORDING~ ",//F1~ ");//A
	" ~INPUT_REPLAY_START_STOP_RECORDING_SECONDARY~ ",//F2~ ");//X
	" ~INPUT_SCALED_LOOK_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_UP_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_DOWN_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_LEFT_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_SCALED_LOOK_RIGHT_ONLY~ ",//(NONE);~ ");//RIGHT STICK
	" ~INPUT_REPLAY_MARKER_DELETE~ ",//DELETE~ ");//X
	" ~INPUT_REPLAY_CLIP_DELETE~ ",//DELETE~ ");//Y
	" ~INPUT_REPLAY_PAUSE~ ",//SPACEBAR~ ");//A
	" ~INPUT_REPLAY_REWIND~ ",//ARROW DOWN~ ");//LB
	" ~INPUT_REPLAY_FFWD~ ",//ARROW UP~ ");//RB
	" ~INPUT_REPLAY_NEWMARKER~ ",//M~ ");//A
	" ~INPUT_REPLAY_RECORD~ ",//S~ ");//(NONE);
	" ~INPUT_REPLAY_SCREENSHOT~ ",//U~ ");//DPAD UP
	" ~INPUT_REPLAY_HIDEHUD~ ",//H~ ");//R3
	" ~INPUT_REPLAY_STARTPOINT~ ",//B~ ");//(NONE);
	" ~INPUT_REPLAY_ENDPOINT~ ",//N~ ");//(NONE);
	" ~INPUT_REPLAY_ADVANCE~ ",//ARROW RIGHT~ ");//DPAD RIGHT
	" ~INPUT_REPLAY_BACK~ ",//ARROW LEFT~ ");//DPAD LEFT
	" ~INPUT_REPLAY_TOOLS~ ",//T~ ");//DPAD DOWN
	" ~INPUT_REPLAY_RESTART~ ",//R~ ");//BACK
	" ~INPUT_REPLAY_SHOWHOTKEY~ ",//K~ ");//DPAD DOWN
	" ~INPUT_REPLAY_CYCLEMARKERLEFT~ ",//[~ ");//DPAD LEFT
	" ~INPUT_REPLAY_CYCLEMARKERRIGHT~ ",//]~ ");//DPAD RIGHT
	" ~INPUT_REPLAY_FOVINCREASE~ ",//NUMPAD +~ ");//RB
	" ~INPUT_REPLAY_FOVDECREASE~ ",//NUMPAD -~ ");//LB
	" ~INPUT_REPLAY_CAMERAUP~ ",//PAGE UP~ ");//(NONE);
	" ~INPUT_REPLAY_CAMERADOWN~ ",//PAGE DOWN~ ");//(NONE);
	" ~INPUT_REPLAY_SAVE~ ",//F5~ ");//START
	" ~INPUT_REPLAY_TOGGLETIME~ ",//C~ ");//(NONE);
	" ~INPUT_REPLAY_TOGGLETIPS~ ",//V~ ");//(NONE);
	" ~INPUT_REPLAY_PREVIEW~ ",//SPACEBAR~ ");//(NONE);
	" ~INPUT_REPLAY_TOGGLE_TIMELINE~ ",//ESC~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_PICKUP_CLIP~ ",//X~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_DUPLICATE_CLIP~ ",//C~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_PLACE_CLIP~ ",//V~ ");//(NONE);
	" ~INPUT_REPLAY_CTRL~ ",//LEFT CTRL~ ");//(NONE);
	" ~INPUT_REPLAY_TIMELINE_SAVE~ ",//F5~ ");//(NONE);
	" ~INPUT_REPLAY_PREVIEW_AUDIO~ ",//SPACEBAR~ ");//RT
	" ~INPUT_VEH_DRIVE_LOOK~ ",//LEFT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_DRIVE_LOOK2~ ",//RIGHT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_VEH_FLY_ATTACK2~ ",//RIGHT MOUSE BUTTON~ ");//(NONE);
	" ~INPUT_RADIO_WHEEL_UD~ ",//MOUSE DOWN~ ");//RIGHT STICK
	" ~INPUT_RADIO_WHEEL_LR~ ",//MOUSE RIGHT~ ");//RIGHT STICK
	" ~INPUT_VEH_SLOWMO_UD~ ",//SCROLLWHEEL DOWN~ ");//LEFT STICK
	" ~INPUT_VEH_SLOWMO_UP_ONLY~ ",//SCROLLWHEEL UP~ ");//LEFT STICK
	" ~INPUT_VEH_SLOWMO_DOWN_ONLY~ ",//SCROLLWHEEL DOWN~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE~ ",//X~ ");//A
	" ~INPUT_VEH_HYDRAULICS_CONTROL_LEFT~ ",//A~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_RIGHT~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_UP~ ",//LEFT SHIFT~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_DOWN~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_UD~ ",//D~ ");//LEFT STICK
	" ~INPUT_VEH_HYDRAULICS_CONTROL_LR~ ",//LEFT CTRL~ ");//LEFT STICK
	" ~INPUT_SWITCH_VISOR~ ",//F11~ ");//DPAD RIGHT
	" ~INPUT_VEH_MELEE_HOLD~ ",//X~ ");//A
	" ~INPUT_VEH_MELEE_LEFT~ ",//LEFT MOUSE BUTTON~ ");//LB
	" ~INPUT_VEH_MELEE_RIGHT~ ",//RIGHT MOUSE BUTTON~ ");//RB
	" ~INPUT_MAP_POI~ ",//SCROLLWHEEL BUTTON (PRESS);~ ");//Y
	" ~INPUT_REPLAY_SNAPMATIC_PHOTO~ ",//TAB~ ");//X
	" ~INPUT_VEH_CAR_JUMP~ ",//E~ ");//L3
	" ~INPUT_VEH_ROCKET_BOOST~ ",//E~ ");//L3
	" ~INPUT_VEH_FLY_BOOST~ ",//LEFT SHIFT~ ");//L3
	" ~INPUT_VEH_PARACHUTE~ ",//SPACEBAR~ ");//A
	" ~INPUT_VEH_BIKE_WINGS~ ",//X~ ");//A
	" ~INPUT_VEH_FLY_BOMB_BAY~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_FLY_COUNTER~ ",//E~ ");//DPAD RIGHT
	" ~INPUT_VEH_TRANSFORM~ ",//X~ ");//A
	" ~INPUT_QUAD_LOCO_REVERSE~ ",//~ ");//RB
	" ~INPUT_RESPAWN_FASTER~ ",//~ ");//
	" ~INPUT_HUDMARKER_SELECT~ "
	};
	void menu_beep()
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	}
	void ButtonDisabler(int LButt)
	{
		CONTROLS::ENABLE_CONTROL_ACTION(0, LButt, false);
		CONTROLS::ENABLE_CONTROL_ACTION(1, LButt, false);
		CONTROLS::ENABLE_CONTROL_ACTION(2, LButt, false);
	}
	bool WhileButtonDown(int CButt, bool bDisable)
	{
		if (bDisable)
			ButtonDisabler(CButt); ;

		bool bButt = (bool)CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, CButt);

		if (bButt)
		{
			while (!(bool)CONTROLS::IS_DISABLED_CONTROL_JUST_RELEASED(0, CButt))
				WAIT(1);
		}
		return bButt;
	}
	bool ButtonDown(int CButt, bool bDisable)
	{
		if (bDisable)
			ButtonDisabler(CButt);
		return (bool)CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, CButt);
	}

	void get_button_state(bool* ent, bool* del, bool* up, bool* down, bool* left, bool* right, bool* shutDown)
	{
		if (ent) *ent = IsKeyDown(VK_RETURN);
		if (del) *del = IsKeyDown(VK_DELETE) || IsKeyDown(VK_BACK);
		if (up) *up = IsKeyDown(VK_UP);
		if (down) *down = IsKeyDown(VK_DOWN);
		if (left) *left = IsKeyDown(VK_LEFT);
		if (right) *right = IsKeyDown(VK_RIGHT);
		if (shutDown) *shutDown = IsKeyDown(VK_ESCAPE);
	}
	void Menu_Button_state(bool* Mb)
	{
		if (Mb) *Mb = IsKeyDown(KeyFind[Mod_Data::Mod_Settings.MenuKey]);//VK_NUMPAD0
	}

	int FindKeyBinds(bool Control)
	{
		WAIT(4000);
		int iReturn = -1;
		int TestCase = 0;

		while (true)
		{
			if ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;

			Mod_Ui::TopLeft(RSLangMenu[189]);

			if (Control)
			{
				if (TestCase < (int)ControlSym.size())
				{
					if (ButtonDown(TestCase, false))
					{
						Mod_Ui::BottomLeft(RSLangMenu[190]);
						iReturn = TestCase;
						break;
					}
					TestCase++;
				}
				else
					TestCase = 0;
			}
			else
			{
				if (TestCase < (int)KeyFind.size())
				{
					if (IsKeyDown(KeyFind[TestCase]))
					{
						Mod_Ui::BottomLeft(RSLangMenu[190]);
						iReturn = TestCase;
						break;
					}
					TestCase++;
				}
				else
					TestCase = 0;
			}
			WAIT(1);
		}
		return iReturn;
	}

	int InGameTime()
	{
		return (int)GAMEPLAY::GET_GAME_TIMER();
	}
	bool IsIsSafe(int Key)
	{
		bool isSafe = false;
		if (!(bool)PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(PLAYER::PLAYER_PED_ID()))
		{
			while (ButtonDown(Key, false))
			{
				WAIT(1000);
				if (ButtonDown(Key, false))
					isSafe = true;
				break;
			}
		}
		return isSafe;
	}

	const std::string SavedPedFolder = GetDir() + "/RandomStart/SavedPeds";
	void LoadSavedPeds()
	{
		LoggerLight("LoadSavedPeds");

		std::vector<Mod_Class::ClothBank> PzCont = {};

		if (CreateDirectoryA((LPSTR)SavedPedFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{

		}
		std::vector<std::string> Files = {};
		for (const auto& entry : std::filesystem::directory_iterator(SavedPedFolder))
			Files.push_back(entry.path().string());

		for (int i = 0; i < Files.size(); i++)
		{
			std::string model = "", name = "", walkySt = "", moods = "", HairTag = "H_FMM_3_4", HairName = "", voice = "";
			
			Hash modelHash = 0;

			int hairColour = 7, hairStreaks = 7, eyeColour = 0, comp = 3, text = 4, overLib = -1, over = 1, cloth_Pick = 0, shapeFirstID = 5, shapeSecondID = 5;
			
			float shapeMix = 0.0, skinMix = 0.92, thirdMix = 0.0;

			bool male = true, animal_Farm = false, freeMode = false;

			bool ClothBuild = false;

			int intList = 0;
			int ClothNo = -1;

			std::vector<Mod_Class::ClothX> myOutfits = {};
			std::vector<Mod_Class::FreeOverLay> myOverlay = {};
			std::vector<Mod_Class::Tattoo> myTattoo = {};
			std::vector<float> faceScale = {};

			std::vector<std::string> MyColect = ReadSetFile(Files[i]);

			for (int i = 0; i < MyColect.size(); i++)
			{
				std::string line = MyColect[i];

				if (ClothBuild)
				{
					if (StringContains("Title", line))
					{
						ClothNo++;
						myOutfits.push_back(Mod_Class::ClothX(AfterEqual(line), {}, {}, {}, {}));
					}
					else if (StringContains("DecalLib", line))
					{
						myOutfits[ClothNo].Badge.BaseName = AfterEqual(line);
					}
					else if (StringContains("DecalName", line))
					{
						myOutfits[ClothNo].Badge.TatName = AfterEqual(line);
					}
					else if (StringContains("[ClothA]", line))
					{
						intList = 1;
					}
					else if (StringContains("[ClothB]", line))
					{
						intList = 2;
					}
					else if (StringContains("[ExtraA]", line))
					{
						intList = 3;
					}
					else if (StringContains("[ExtraB]", line))
					{
						intList = 4;
					}
					else if (intList == 1)
					{
						if (StringContains("ClothA", line))
							myOutfits[ClothNo].ClothA.push_back(StingNumbersInt(line));
					}
					else if (intList == 2)
					{
						if (StringContains("ClothB", line))
							myOutfits[ClothNo].ClothB.push_back(StingNumbersInt(line));
					}
					else if (intList == 3)
					{
						if (StringContains("ExtraA", line))
							myOutfits[ClothNo].ExtraA.push_back(StingNumbersInt(line));
					}
					else if (intList == 4)
					{
						if (StringContains("ExtraB", line))
							myOutfits[ClothNo].ExtraB.push_back(StingNumbersInt(line));
					}
				}
				else if (StringContains("CharName", line))
					name = AfterEqual(line);
				else if (StringContains("Model", line))
					model = AfterEqual(line);
				else if (StringContains("XmodelHash", line))
					modelHash = (Hash)StingNumbersInt(line);
				else if (StringContains("FreeMode", line))
					freeMode = StringBool(line);
				else if (StringContains("Male", line))
					male = StringBool(line);
				else if (StringContains("Animal_Farm", line))
					animal_Farm = StringBool(line);
				else if (StringContains("Voice", line))
					voice = AfterEqual(line);
				else if (StringContains("Cloth_Pick", line))
					cloth_Pick = StingNumbersInt(line);
				else if (StringContains("EyeColour", line))
					eyeColour = StingNumbersInt(line);
				else if (StringContains("WalkStyle", line))
					walkySt = AfterEqual(line);
				else if (StringContains("ShapeFirstID", line))
					shapeFirstID = StingNumbersInt(line);
				else if (StringContains("ShapeSecondID", line))
					shapeSecondID = StingNumbersInt(line);
				else if (StringContains("ShapeMix", line))
					shapeMix = StingNumbersFloat(line);
				else if (StringContains("SkinMix", line))
					skinMix = StingNumbersFloat(line);
				else if (StringContains("ThirdMix", line))
					thirdMix = StingNumbersFloat(line);
				else if (StringContains("HairColour", line))
					hairColour = StingNumbersInt(line);
				else if (StringContains("HairStreaks", line))
					hairStreaks = StingNumbersInt(line);
				else if (StringContains("Comp", line))
					comp = StingNumbersInt(line);
				else if (StringContains("Text", line))
					text = StingNumbersInt(line);
				else if (StringContains("HairTag", line))
					HairTag = AfterEqual(line);
				else if (StringContains("HairName", line))
					HairName = AfterEqual(line);
				else if (StringContains("OverLib", line))
					overLib = StingNumbersInt(line);
				else if (StringContains("OverOb", line))
					over = StingNumbersInt(line);
				else if (StringContains("[FreeOverLay]", line))
					intList = 5;
				else if (StringContains("[Tattoo]", line))
					intList = 6;
				else if (StringContains("[FaceScale]", line))
					intList = 7;
				else if (StringContains("Mood", line))
					moods = AfterEqual(line);
				else if (StringContains("[ClothX]", line))
					ClothBuild = true;
				else if (intList == 5)
				{
					if (StringContains("Overlay", line))
						myOverlay.push_back(Mod_Class::FreeOverLay(StingNumbersInt(line), StingNumbersInt(MyColect[i + 1]), StingNumbersFloat(MyColect[i + 2])));
				}
				else if (intList == 6)
				{
					if (StringContains("BaseName", line))
						myTattoo.push_back(Mod_Class::Tattoo(AfterEqual(line), AfterEqual(MyColect[i + 1]), AfterEqual(MyColect[i + 2])));
				}
				else if (intList == 7)
				{
					if (StringContains("Face", line))
						faceScale.push_back(StingNumbersFloat(line));
				}
			}

			bool bReBuild = false;

			Mod_Class::FaceBank myFaces = Mod_Class::FaceBank(shapeFirstID, shapeSecondID, shapeMix, skinMix, thirdMix);
			Mod_Class::HairSets myHair = Mod_Class::HairSets(comp, text, HairTag, HairName, overLib, over);
			if (myOutfits[0].Title != "Default")
				myOutfits[0].Title = "Default";

			Mod_Class::ClothBank ThisBank = Mod_Class::ClothBank(name, model, modelHash, freeMode, myFaces, male, animal_Farm, myHair, hairColour, hairStreaks, eyeColour, cloth_Pick, myOverlay, myTattoo, myOutfits, faceScale, voice, walkySt, moods);

			PzCont.push_back(ThisBank);
		}

		for (int i = 0; i < PzCont.size(); i++)
		{
			if (PzCont[i].Cloth_Pick < 0 || PzCont[i].Cloth_Pick >(int)PzCont[i].Cothing.size() - 1)
				PzCont[i].Cloth_Pick = 0;

			SavedPeds.push_back(PzCont[i]);
		}
	}
	void SaveClothBank(Mod_Class::ClothBank& bank)
	{
		LoggerLight("SaveClothBank");
		if (CreateDirectoryA((LPSTR)SavedPedFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{

		}

		if (bank.CharName != "")
		{
			std::vector<std::string> NewSave = {
				"[ClothBank]",
				"CharName=" + bank.CharName,
				"Model=" + bank.Model,
				"XmodelHash=" + std::to_string(bank.ModelHash),
				"FreeMode=" + BoolToString(bank.FreeMode),
				"Male=" + BoolToString(bank.Male),
				"Animal_Farm=" + BoolToString(bank.Animal_Farm),
				"Voice=" + bank.Voice,
				"Cloth_Pick=" + std::to_string(bank.Cloth_Pick),
				"EyeColour=" + std::to_string(bank.EyeColour),
				"WalkStyle=" + bank.Walkies,
				"[FaceBank]",
				"ShapeFirstID=" + std::to_string(bank.MyFaces.ShapeFirstID),
				"ShapeSecondID=" + std::to_string(bank.MyFaces.ShapeSecondID),
				"ShapeMix=" + std::to_string(bank.MyFaces.ShapeMix),
				"SkinMix=" + std::to_string(bank.MyFaces.SkinMix),
				"ThirdMix=" + std::to_string(bank.MyFaces.ThirdMix),
				"[Hair]",
				"HairColour=" + std::to_string(bank.HairColour),
				"HairStreaks=" + std::to_string(bank.HairStreaks),
				"Comp=" + std::to_string(bank.MyHair.Comp),
				"Text=" + std::to_string(bank.MyHair.Text),
				"HairTag=" + bank.MyHair.HandName,
				"HairName=" + bank.MyHair.Name,
				"OverLib=" + std::to_string(bank.MyHair.OverLib),
				"OverOb=" + std::to_string(bank.MyHair.Over),
				"Mood=" + bank.Moods,
				"[FreeOverLay]"
			};

			for (int i = 0; i < bank.MyOverlay.size(); i++)
			{
				NewSave.push_back("[OverLay]");
				NewSave.push_back("Overlay=" + std::to_string(bank.MyOverlay[i].Overlay));
				NewSave.push_back("OverCol=" + std::to_string(bank.MyOverlay[i].OverCol));
				NewSave.push_back("OverOpc=" + std::to_string(bank.MyOverlay[i].OverOpc));
			}

			NewSave.push_back("[Tattoo]");

			for (int i = 0; i < bank.MyTattoo.size(); i++)
			{
				NewSave.push_back("[Tat]");
				NewSave.push_back("BaseName=" + bank.MyTattoo[i].BaseName);
				NewSave.push_back("TatsDesc=" + bank.MyTattoo[i].Name);
				NewSave.push_back("TatName=" + bank.MyTattoo[i].TatName);
			}

			NewSave.push_back("[FaceScale]");

			for (int i = 0; i < bank.FaceScale.size(); i++)
				NewSave.push_back("Face=" + std::to_string(bank.FaceScale[i]));

			for (int i = 0; i < bank.Cothing.size(); i++)
			{
				NewSave.push_back("[ClothX]");
				NewSave.push_back("Title=" + bank.Cothing[i].Title);
				NewSave.push_back("DecalLib=" + bank.Cothing[i].Badge.BaseName);
				NewSave.push_back("DecalName=" + bank.Cothing[i].Badge.TatName);

				NewSave.push_back("[ClothA]");
				for (int j = 0; j < bank.Cothing[i].ClothA.size(); j++)
					NewSave.push_back("ClothA=" + std::to_string(bank.Cothing[i].ClothA[j]));

				NewSave.push_back("[ClothB]");
				for (int j = 0; j < bank.Cothing[i].ClothB.size(); j++)
					NewSave.push_back("ClothB=" + std::to_string(bank.Cothing[i].ClothB[j]));

				NewSave.push_back("[ExtraA]");
				for (int j = 0; j < bank.Cothing[i].ExtraA.size(); j++)
					NewSave.push_back("ExtraA=" + std::to_string(bank.Cothing[i].ExtraA[j]));

				NewSave.push_back("[ExtraB]");
				for (int j = 0; j < bank.Cothing[i].ExtraA.size(); j++)
					NewSave.push_back("ExtraB=" + std::to_string(bank.Cothing[i].ExtraB[j]));
			}

			std::ofstream MyFile(SavedPedFolder + "/" + bank.CharName + ".ini");

			for (int i = 0; i < NewSave.size(); i++)
			{
				MyFile << NewSave[i];
				MyFile << "\n";
			}

			MyFile.close();
		}
	}

	void AddMonies(int iAmount)
	{
		Hash H1 = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());
		int iPedCred = -1;
		if (H1 == -1686040670)
			iPedCred = MyHashKey("SP2_TOTAL_CASH");
		else if (H1 == -1692214353)
			iPedCred = MyHashKey("SP1_TOTAL_CASH");
		else if (H1 == 225514697)
			iPedCred = MyHashKey("SP0_TOTAL_CASH");
		int Credit = 0;
		STATS::STAT_GET_INT(iPedCred, &Credit, -1);
		Credit += iAmount;
		STATS::STAT_SET_INT(iPedCred, Credit, 1);
	}

	void FindAddCars()
	{
		std::string OutputFolder = GetDir() + "/RandomStart/Vehicles";
		if (CreateDirectoryA((LPSTR)OutputFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{
			LoggerLight("RandomStart/Vehicles, Direct Working");
		}
		else
		{
			LoggerLight("RandomStart/Vehicles, Direct failed");
		}

		const std::string sVehList01 = GetDir() + "/RandomStart/Vehicles/Boats.ini";
		PreVeh_01 = ReadSetFile(sVehList01);
		if (PreVeh_01.size() == 0)
		{
			const std::vector<std::string> PreVehSet_01 = {
				"AVISA",//<!-- Kraken Avisa -->
				"DINGHY",//
				"DINGHY5",//<!-- Dinghy weaponized variant -->
				"JETMAX",//
				"LONGFIN",//<!-- Shitzu Longfin -->
				"MARQUIS",//
				"PREDATOR",//
				"PATROLBOAT",//<!-- Kurtz 31 Patrol Boat -->
				"SEASHARK",//
				"SPEEDER",//
				"SQUALO",//
				"SUNTRAP",//
				"TORO",//
				"TROPIC"//
			};

			PreVeh_01 = PreVehSet_01;
			WriteFile(sVehList01, PreVeh_01);
		}
		else
			RemoveBlankStrings(PreVeh_01);
		const std::string sVehList02 = GetDir() + "/RandomStart/Vehicles/HighValueVeh.ini";
		PreVeh_02 = ReadSetFile(sVehList02);
		if (PreVeh_02.size() == 0)
		{
			const std::vector<std::string> PreVehSet_02 = {
				"PFISTER811",  //<!-- 811 -->
				"ADDER",  //
				"AUTARCH",  //
				"BANSHEE2",  //<!-- Banshee 900R -->
				"BULLET",  //
				"CHAMPION",  //
				"CHEETAH",  //
				"CYCLONE",  //
				"DEVESTE",  //
				"EMERUS",  //
				"ENTITYXF",  //
				"ENTITY3",  //<!-- Entity MT -->
				"ENTITY2",  //<!-- Entity XXR -->
				"SHEAVA",  //<!-- ETR1 -->
				"FMJ",  //
				"FURIA",  //
				"GP1",  //
				"IGNUS",  //
				"INFERNUS",  //
				"ITALIGTB",  //
				"ITALIGTB2",  //<!-- Itali GTB Custom -->
				"KRIEGER",  //
				"LM87",  //
				"OSIRIS",  //
				"NERO",  //
				"NERO2",  //<!-- Nero Custom -->
				"PENETRATOR",  //
				"LE7B",  //<!-- RE-7B -->
				"REAPER",  //
				"VOLTIC2",  //<!-- Rocket Voltic -->
				"S80",  //
				"SC1",  //
				"SCRAMJET",  //
				"SULTANRS",  //
				"T20",  //
				"TAIPAN",  //
				"TEMPESTA",  //
				"TEZERACT",  //
				"THRAX",  //
				"TIGON",  //
				"TORERO2",  //<!-- Torero XO -->
				"TURISMOR",  //
				"TYRANT",  //
				"TYRUS",  //
				"VACCA",  //
				"VAGNER",  //
				"VIGILANTE",  //
				"VIRTUE",  //
				"VISIONE",  //
				"VOLTIC",  //
				"PROTOTIPO",  //<!-- X80 Proto -->
				"XA21",  //
				"ZENO",  //
				"ZENTORNO",  //
				"ZORRUSSO",  //
				"R300",  //<!-- 300R -->
				"DRAFTER",  //<!-- 8F Drafter -->
				"NINEF",  //
				"NINEF2",  //<!-- 9F Cabrio -->
				"TENF",  //
				"TENF2",  //<!-- 10F Widebody -->
				"ALPHA",  //
				"ZR380",  //<!-- Apocalypse ZR380 -->
				"BANSHEE",  //
				"BESTIAGTS",  //
				"BLISTA2",  //<!-- Blista Compact -->
				"BUFFALO",  //
				"BUFFALO2",  //<!-- Buffalo S -->
				"CALICO",  //<!-- Calico GTF -->
				"CARBONIZZARE",  //
				"COMET2",  //<!-- Comet -->
				"COMET3",  //<!-- Comet Retro Custom -->
				"COMET6",  //<!-- Comet S2 -->
				"COMET7",  //<!-- Comet S2 Cabrio -->
				"COMET4",  //<!-- Comet Safari -->
				"COMET5",  //<!-- Comet SR -->
				"COQUETTE",  //
				"COQUETTE4",  //<!-- Coquette D10 -->
				"CORSITA",  //
				"CYPHER",  //
				"TAMPA2",  //<!-- Drift Tampa -->
				"ELEGY",  //<!-- Elegy Retro Custom -->
				"ELEGY2",  //<!-- Elegy RH8 -->
				"EUROS",  //
				"FELTZER2",  //<!-- Feltzer -->
				"FLASHGT",  //
				"FUROREGT",  //
				"FUSILADE",  //
				"FUTO",  //
				"FUTO2",  //<!-- Futo GTX -->
				"ZR3802",  //<!-- Future Shock ZR380 -->
				"GB200",  //
				"BLISTA3",  //<!-- Go Go Monkey Blista -->
				"GROWLER",  //
				"EVERON2",  //<!-- Hotring Everon -->
				"GAUNTLET6",  //<!-- Hotring Hellfire -->
				"HOTRING",  //<!-- Hotring Sabre -->
				"IMORGON",  //
				"ISSI7",  //<!-- Issi Sport -->
				"ITALIGTO",  //
				"STINGERTT",  //<!-- Issi GTO Stinger TT -->
				"ITALIRSX",  //
				"JESTER",  //
				"JESTER2",  //<!-- Jester (Racecar) -->
				"JESTER3",  //<!-- Jester Classic -->
				"JESTER4",  //<!-- Jester RR -->
				"JUGULAR",  //
				"KHAMELION",  //
				"KOMODA",  //
				"KURUMA",  //
				"KURUMA2",  //<!-- Kuruma (Armored) -->
				"COUREUR",  //<!-- La Coureuse -->
				"LOCUST",  //
				"LYNX",  //
				"MASSACRO",  //
				"MASSACRO2",  //<!-- Massacro (Racecar) -->
				"NEO",  //
				"NEON",  //
				"ZR3803",  //<!-- Nightmare ZR380 -->
				"OMNIS",  //
				"OMNISEGT",  //
				"PANTHERE",  //
				"PARAGON",  //
				"PARAGON2",  //<!-- Paragon R (Armored) -->
				"PARIAH",  //
				"PENUMBRA",  //
				"PENUMBRA2",  //<!-- Penumbra FF -->
				"RAIDEN",  //
				"RAPIDGT",  //
				"RAPIDGT2",  //<!-- Rapid GT Cabrio -->
				"RAPTOR",  //
				"REMUS",  //
				"REVOLTER",  //
				"RT3000",  //
				"RUSTON",  //
				"SCHAFTER4",  //<!-- Schafter LWB -->
				"SCHAFTER3",  //<!-- Schafter V12 -->
				"SCHLAGEN",  //
				"SCHWARZER",  //
				"SENTINEL3",  //<!-- Sentinel Classic -->
				"SENTINEL4",  //<!-- Sentinel Classic Widebody -->
				"SEVEN70",  //
				"SM722",  //
				"SPECTER",  //
				"SPECTER2",  //<!-- Specter Custom -->
				"BUFFALO3",  //<!-- Sprunk Buffalo -->
				"STREITER",  //
				"SUGOI",  //
				"SULTAN",  //
				"SULTAN2",  //<!-- Sultan Classic -->
				"SULTAN3",  //<!-- Sultan RS Classic -->
				"SURANO",  //
				"TROPOS",  //
				"VSTR",  //<!-- V-STR -->
				"VECTRE",  //
				"VERLIERER2",  //
				"VETO",  //<!-- Veto Classic -->
				"VETO2",  //<!-- Veto Modern -->
				"ZR350",  //
				"turismo3", // Super
				"dominator9", // Muscle
				"driftyosemite", // Muscle
				"impaler6", // Muscle
				"Vigero3" // Muscle
			};

			PreVeh_02 = PreVehSet_02;
			WriteFile(sVehList02, PreVeh_02);
		}
		else
			RemoveBlankStrings(PreVeh_02);

		const std::string sVehList03 = GetDir() + "/RandomStart/Vehicles/MidValueVeh.ini";
		PreVeh_03 = ReadSetFile(sVehList03);
		if (PreVeh_03.size() == 0)
		{
			const std::vector<std::string> PreVehSet_03 = {
				"COGCABRIO",  //
				"EXEMPLAR",  //
				"F620",  //
				"BRIGHAM",  //
				"FELON",  //
				"FELON2",  //<!-- Felon GT -->
				"JACKAL",  //
				"KANJOSJ",  //
				"ORACLE",  //
				"ORACLE2",  //<!-- Oracle XS -->
				"POSTLUDE",  //
				"PREVION",  //
				"SENTINEL2",  //<!-- Sentinel -->
				"SENTINEL",  //<!-- Sentinel XS -->
				"WINDSOR",  //
				"WINDSOR2",  //<!-- Windsor Drop -->
				"ZION",  //
				"ZION2",  //<!-- Zion Cabrio -->
				"ASEA",  //
				"ASEA2",  //<!-- Asea North Yankton variant -->
				"ASTEROPE",  //
				"CINQUEMILA",  //
				"COGNOSCENTI",  //
				"COGNOSCENTI2",  //<!-- Cognoscenti (Armored) -->
				"COG55",  //<!-- Cognoscenti 55 -->
				"COG552",  //<!-- Cognoscenti 55 (Armored) -->
				"DEITY",  //
				"FUGITIVE",  //
				"GLENDALE2",  //<!-- Glendale Custom -->
				"INTRUDER",  //
				"PREMIER",  //
				"PRIMO2",  //<!-- Primo Custom -->
				"REGINA",  //
				"RHINEHART",  //
				"ROMERO",  //
				"SCHAFTER2",  //
				"SCHAFTER6",  //<!-- Schafter LWB (Armored) -->
				"SCHAFTER5",  //<!-- Schafter V12 (Armored) -->
				"STAFFORD",  //
				"STANIER",  //
				"STRATUM",  //
				"STRETCH",  //
				"SUPERD",  //
				"SURGE",  //
				"TAILGATER",  //
				"TAILGATER2",  //<!-- Tailgater S -->
				"LIMO2",  //<!-- Turreted Limo -->
				"WARRENER2",  //<!-- Warrener HKR -->
				"WASHINGTON",  //
				"ASTRON",  //
				"BALLER",  //
				"BALLER2",  //<!-- Baller 2nd gen variant -->
				"BALLER3",  //<!-- Baller LE -->
				"BALLER5",  //<!-- Baller LE (Armored) -->
				"BALLER4",  //<!-- Baller LE LWB -->
				"BALLER6",  //<!-- Baller LE LWB (Armored) -->
				"BALLER7",  //<!-- Baller ST -->
				"BJXL",  //
				"CAVALCADE",  //
				"CAVALCADE2",  //<!-- Cavalcade 2nd gen variant -->
				"CONTENDER",  //
				"DUBSTA",  //
				"DUBSTA2",  //<!-- Dubsta black variant -->
				"FQ2",  //
				"GRANGER",  //
				"GRANGER2",  //<!-- Granger 3600LX -->
				"GRESLEY",  //
				"HUNTLEY",  //
				"ISSI8",  //<!-- Issi Rally -->
				"IWAGEN",  //
				"JUBILEE",  //
				"LANDSTALKER",  //
				"LANDSTALKER2",  //<!-- Landstalker XL -->
				"MESA",  //
				"MESA2",  //<!-- Mesa North Yankton variant -->
				"NOVAK",  //
				"PATRIOT",  //
				"PATRIOT2",  //<!-- Patriot Stretch -->
				"RADI",  //
				"REBLA",  //
				"ROCOTO",  //
				"SEMINOLE",  //
				"SEMINOLE2",  //<!-- Seminole Frontier -->
				"SERRANO",  //
				"SQUADDIE",  //
				"TOROS",  //
				"XLS",  //
				"XLS2",  //<!-- XLS (Armored) -->
				"aleutian", // SUVs
				"baller8", // SUVs
				"cavalcade3", // SUVs
				"dorado", // SUVs
				"vivanite", // SUVs
				"asterope2", // Sedans
				"impaler5", // Sedans
				"drifteuros", // Sports
				"driftfuto", // Sports
				"driftjester", // Sports
				"driftremus", // Sports
				"drifttampa", // Sports
				"driftzr350", // Sports
				"driftfr36", // Coupes
				"fr36", // Coupes
				"terminus" // Off-Road
			};

			PreVeh_03 = PreVehSet_03;
			WriteFile(sVehList03, PreVeh_03);
		}
		else
			RemoveBlankStrings(PreVeh_03);

		const std::string sVehList04 = GetDir() + "/RandomStart/Vehicles/LowValueVeh.ini";
		PreVeh_04 = ReadSetFile(sVehList04);
		if (PreVeh_04.size() == 0)
		{
			const std::vector<std::string> PreVehSet_04 = {
				"GREENWOOD",  //
				"MOONBEAM",  //
				"DILETTANTE",  //
				"PANTO",  //
				"RHAPSODY",  //
				"EMPEROR",  //
				"EMPEROR2",  //<!-- Emperor beater variant -->
				"GLENDALE",  //
				"INGOT",  //
				"PRIMO",  //
				"WARRENER",  //
				"HABANERO"  //
			};

			PreVeh_04 = PreVehSet_04;
			WriteFile(sVehList04, PreVeh_04);
		}
		else
			RemoveBlankStrings(PreVeh_04);

		const std::string sVehList10 = GetDir() + "/RandomStart/Vehicles/Planes.ini";
		PreVeh_10 = ReadSetFile(sVehList10);
		if (PreVeh_10.size() == 0)
		{
			const std::vector<std::string> PreVehSet_10 = {
				"ALPHAZ1",  //
				"STRIKEFORCE",  //<!-- B-11 Strikeforce -->
				"BESRA",  //
				"RAIJU",  //<!-- F-160 Raiju -->
				"HYDRA",  //
				"STARLING",  //<!-- LF-22 Starling -->
				"MAMMATUS",  //
				"MOGUL",  //
				"LAZER",  //<!-- P-996 LAZER -->
				"PYRO",  //
				"BOMBUSHKA",  //<!-- RM-10 Bombushka -->
				"ROGUE",  //
				"ALKONOST",  //<!-- RO-86 Alkonost -->
				"TITAN",  //
				"TULA",  //
				"MOLOTOK",  //<!-- V-65 Molotok -->
				"VOLATOL",  //
				"CARGOPLANE",  //
				"CARGOPLANE2",  //
				"CUBAN800",  //
				"DODO",  //
				"JET",  //
				"LUXOR",  //
				"LUXOR2",  //<!-- Luxor Deluxe -->
				"MILJET",  //
				"NIMBUS",  //
				"SHAMAL",  //
				"STREAMER216",  //
				"VELUM",  //
				"VELUM2",  //<!-- Velum 5-Seater -->
				"VESTRA"  //
			};

			PreVeh_10 = PreVehSet_10;
			WriteFile(sVehList10, PreVeh_10);
		}
		else
			RemoveBlankStrings(PreVeh_10);

		const std::string sVehList11 = GetDir() + "/RandomStart/Vehicles/Helicopters.ini";
		PreVeh_11 = ReadSetFile(sVehList11);
		if (PreVeh_11.size() == 0)
		{
			const std::vector<std::string> PreVehSet_11 = {
				"CONADA",  //
				"FROGGER",  //
				"MAVERICK",  //
				"SUPERVOLITO",  //
				"SUPERVOLITO2",  //<!-- SuperVolito Carbon -->
				"SWIFT",  //
				"SWIFT2",  //<!-- Swift Deluxe -->
				"VOLATUS"  //
			};

			PreVeh_11 = PreVehSet_11;
			WriteFile(sVehList11, PreVeh_11);
		}
		else
			RemoveBlankStrings(PreVeh_11);
	}
	void FindAddPeds()
	{
		std::string OutputFolder = GetDir() + "/RandomStart/Peds";
		if (CreateDirectoryA((LPSTR)OutputFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{
			LoggerLight("RandomStart/Vehicles, Direct Working");
		}
		else
		{
			LoggerLight("RandomStart/Vehicles, Direct failed");
		}

		const std::string sPedList01 = GetDir() + "/RandomStart/Peds/Beach.ini";
		PrePed_01 = ReadSetFile(sPedList01);
		if (PrePed_01.size() == 0)
		{
			const std::vector<std::string> PrePeSet_01 = {
				"a_f_m_beach_01",//"Beach Female",  		
				"a_f_m_fatcult_01",//"Fat Cult Female",  
				"a_f_y_hippie_01",//"Hippie Female", 
				"a_f_y_yoga_01",//"Yoga Female", 
				"a_m_m_beach_01",//"Beach Male",  
				"a_m_y_beach_01",//"Beach Young Male",  
				"a_m_y_beach_02",//"Beach Young Male 2",  
				"a_m_y_beach_03",//"Beach Young Male 3", 
				"a_m_y_breakdance_01",//"Breakdancer Male",
				"a_m_y_hippy_01",//"Hippie Male",  
				"a_m_y_sunbathe_01",//"Sunbather Male",  
				"a_m_y_surfer_01",//"Surfer",
				"a_m_y_beachvesp_01",//"Vespucci Beach Male",  
				"a_m_y_beachvesp_02",//"Vespucci Beach Male 2",  
				"a_m_y_stwhi_01",//"White Street Male",  
				"a_m_y_yoga_01",//"Yoga Male",
				"a_f_m_trampbeac_01"//"Beach Tramp Female", 
			};

			PrePed_01 = PrePeSet_01;
			WriteFile(sPedList01, PrePed_01);
		}
		else
			RemoveBlankStrings(PrePed_01);

		const std::string sPedList02 = GetDir() + "/RandomStart/Peds/Tramp.ini";
		PrePed_02 = ReadSetFile(sPedList02);
		if (PrePed_02.size() == 0)
		{
			const std::vector<std::string> PrePeSet_02 = {
				"a_f_m_trampbeac_01",//"Beach Tramp Female",  
				"a_f_m_tramp_01",//"Tramp Female",  
				"a_m_o_beach_01",//"Beach Old Male",  
				"a_m_m_trampbeac_01",//"Beach Tramp Male",  
				"a_m_m_tramp_01",//"Tramp Male",  
				"a_m_o_tramp_01"//"Tramp Old Male",  
			};

			PrePed_02 = PrePeSet_02;
			WriteFile(sPedList02, PrePed_02);
		}
		else
			RemoveBlankStrings(PrePed_02);

		const std::string sPedList03 = GetDir() + "/RandomStart/Peds/HighClass.ini";
		PrePed_03 = ReadSetFile(sPedList03);
		if (PrePed_03.size() == 0)
		{
			const std::vector<std::string> PrePeSet_03 = {
				"a_f_y_scdressy_01",//"Dressy Female",  
				"a_f_y_bevhills_04",//"Beverly Hills Young Female 4", 
				"a_f_y_clubcust_01",//"Club Customer Female 1",  
				"a_f_y_clubcust_02",//"Club Customer Female 2",  
				"a_f_y_clubcust_03",//"Club Customer Female 3", 
				"a_f_y_smartcaspat_01",//"Formel Casino Guest",  
				"s_f_y_movprem_01",//"Movie Premiere Female",  
				"A_F_Y_StudioParty_01",
				"A_F_Y_StudioParty_02",
				"a_m_y_bevhills_02",//"Beverly Hills Young Male 2", 
				"a_m_y_smartcaspat_01",//"Formel Casino Guests", 
				"a_m_m_malibu_01",//"Malibu Male",  
				"a_m_y_soucent_04",//"South Central Young Male 4",  
				"s_m_m_movprem_01",//"Movie Premiere Male",  
				"A_M_M_StudioParty_01",
				"A_M_Y_StudioParty_01",
				"a_f_y_bevhills_01",//"Beverly Hills Young Female",  
				"a_f_y_bevhills_02",//"Beverly Hills Young Female 2",  
				"a_f_y_bevhills_03",//"Beverly Hills Young Female 3", 
				"a_f_y_eastsa_01",//"East SA Young Female",  
				"a_f_y_eastsa_02",//"East SA Young Female 2",  
				"a_f_y_genhot_01",//"General Hot Young Female",  
				"a_f_y_hipster_01",//"Hipster Female",  
				"a_f_y_hipster_02",//"Hipster Female 2",  
				"a_f_y_hipster_03",//"Hipster Female 3",  
				"a_f_y_hipster_04"//"Hipster Female 4", 
			};

			PrePed_03 = PrePeSet_03;
			WriteFile(sPedList03, PrePed_03);
		}
		else
			RemoveBlankStrings(PrePed_03);
	
		const std::string sPedList04 = GetDir() + "/RandomStart/Peds/MidClass.ini";
		PrePed_04 = ReadSetFile(sPedList04);
		if (PrePed_04.size() == 0)
		{
			const std::vector<std::string> PrePeSet_04 = {
				"a_f_y_indian_01",//"Indian Young Female",  
				"a_f_y_soucent_03",//"South Central Young Female 3",  
				"a_f_y_tourist_01",//"Tourist Young Female",  
				"a_f_y_vinewood_01",//"Vinewood Female",  
				"a_f_y_vinewood_02",//"Vinewood Female 2",  
				"a_f_y_vinewood_03",//"Vinewood Female 3",  
				"a_f_y_vinewood_04",//"Vinewood Female 4", 
				"A_F_Y_CarClub_01",
				"A_M_Y_CarClub_01",
				"a_m_m_afriamer_01",//"African American Male",  
				"a_m_m_bevhills_01",//"Beverly Hills Male",  
				"a_m_m_bevhills_02",//"Beverly Hills Male 2",  
				"a_m_y_bevhills_01",//"Beverly Hills Young Male",  
				"a_m_y_stbla_02",//"Black Street Male 2",
				"a_m_y_gencaspat_01",//"Casual Casino Guests",  
				"a_m_y_genstreet_01",//"General Street Young Male",  
				"a_m_y_genstreet_02",//"General Street Young Male 2",  
				"a_m_m_hasjew_01",//"Hasidic Jew Male",  
				"a_m_y_hasjew_01",//"Hasidic Jew Young Male",  
				"a_m_y_hipster_01",//"Hipster Male",  
				"a_m_y_hipster_02",//"Hipster Male 2",  
				"a_m_y_hipster_03",//"Hipster Male 3",  
				"a_m_y_indian_01",//"Indian Young Male",  
				"a_m_y_ktown_01",//"Korean Young Male",  
				"a_m_y_ktown_02",//"Korean Young Male 2",  
				"a_m_y_polynesian_01",//"Polynesian Young", 
				"a_m_y_vindouche_01",//"Vinewood Douche",  
				"a_m_y_vinewood_01",//"Vinewood Male",  
				"a_m_y_vinewood_02",//"Vinewood Male 2",  
				"a_m_y_vinewood_03",//"Vinewood Male 3",  
				"a_m_y_vinewood_04",//"Vinewood Male 4",  
				"a_m_y_stwhi_02",//"White Street Male 2", 
				"a_m_y_clubcust_01",//"Club Customer Male 1",  
				"a_m_y_clubcust_02",//"Club Customer Male 2",  
				"a_m_y_clubcust_03",//"Club Customer Male 3", 
				"A_M_Y_CarClub_01",
				"a_f_m_downtown_01",//"Downtown Female", 
				"a_f_y_gencaspat_01"//"Casual Casino Guest",  
			};

			PrePed_04 = PrePeSet_04;
			WriteFile(sPedList04, PrePed_04);
		}
		else
			RemoveBlankStrings(PrePed_04);
	
		const std::string sPedList05 = GetDir() + "/RandomStart/Peds/LowClass.ini";
		PrePed_05 = ReadSetFile(sPedList05);
		if (PrePed_05.size() == 0)
		{
			const std::vector<std::string> PrePeSet_05 = {
				"a_f_m_eastsa_01",//"East SA Female",  
				"a_f_m_eastsa_02",//"East SA Female 2",  
				"a_f_m_fatbla_01",//"Fat Black Female",  
				"a_f_m_fatwhite_01",//"Fat White Female",  
				"a_f_o_genstreet_01",//"General Street Old Female",  
				"a_f_o_indian_01",//"Indian Old Female",  
				"a_f_m_ktown_01",//"Korean Female",  
				"a_f_m_ktown_02",//"Korean Female 2",  
				"a_f_o_ktown_01",//"Korean Old Female",  
				"a_f_m_skidrow_01",//"Skid Row Female",  
				"a_f_m_soucent_01",//"South Central Female",  
				"a_f_m_soucent_02",//"South Central Female 2",  
				"a_f_m_soucentmc_01",//"South Central MC Female",  
				"a_f_o_soucent_01",//"South Central Old Female",  
				"a_f_o_soucent_02",//"South Central Old Female 2",  
				"a_f_y_soucent_01",//"South Central Young Female",  
				"a_f_y_soucent_02",//"South Central Young Female 2",  
				"a_f_m_tourist_01",//"Tourist Female",  
				"a_f_y_tourist_02",//"Tourist Young Female 2",  
				"a_m_y_stbla_01",//"Black Street Male",  
				"a_m_y_downtown_01",//"Downtown Male",  
				"a_m_m_eastsa_01",//"East SA Male",  
				"a_m_m_eastsa_02",//"East SA Male 2",  
				"a_m_y_eastsa_01",//"East SA Young Male",  
				"a_m_y_eastsa_02",//"East SA Young Male 2",  
				"a_m_m_fatlatin_01",//"Fat Latino Male",  
				"a_m_m_genfat_01",//"General Fat Male",  
				"a_m_m_genfat_02",//"General Fat Male 2",  
				"a_m_o_genstreet_01",//"General Street Old Male",  
				"a_m_m_indian_01",//"Indian Male", 
				"a_m_m_ktown_01",//"Korean Male",  
				"a_m_o_ktown_01",//"Korean Old Male", 
				"a_m_m_stlat_02",//"Latino Street Male 2",  
				"a_m_y_stlat_01",//"Latino Street Young Male",  
				"a_m_y_latino_01",//"Latino Young Male",
				"a_m_m_mexlabor_01",//"Mexican Labourer",  
				"a_m_m_mexcntry_01",//"Mexican Rural", 
				"a_m_m_polynesian_01",//"Polynesian",   
				"a_m_m_skidrow_01",//"Skid Row Male",  
				"a_m_m_socenlat_01",//"South Central Latino Male",  
				"a_m_m_soucent_01",//"South Central Male",  
				"a_m_m_soucent_02",//"South Central Male 2",  
				"a_m_m_soucent_03",//"South Central Male 3",  
				"a_m_m_soucent_04",//"South Central Male 4",  
				"a_m_o_soucent_01",//"South Central Old Male",  
				"a_m_o_soucent_02",//"South Central Old Male 2",  
				"a_m_o_soucent_03",//"South Central Old Male 3",  
				"a_m_y_soucent_01",//"South Central Young Male",  
				"a_m_y_soucent_02",//"South Central Young Male 2",  
				"a_m_y_soucent_03",//"South Central Young Male 3", 
				"a_m_m_tourist_01"//"Tourist Male",  
			};

			PrePed_05 = PrePeSet_05;
			WriteFile(sPedList05, PrePed_05);
		}
		else
			RemoveBlankStrings(PrePed_05);

		const std::string sPedList06 = GetDir() + "/RandomStart/Peds/Buisness.ini";
		PrePed_06 = ReadSetFile(sPedList06);
		if (PrePed_06.size() == 0)
		{
			const std::vector<std::string> PrePeSet_06 = {
				"g_m_m_casrn_01",//"Casino Guests?",  
				"a_f_m_bevhills_01",//"Beverly Hills Female",  
				"a_f_m_bevhills_02",//"Beverly Hills Female 2", 
				"a_f_m_business_02",//"Business Female 2",  
				"a_f_y_business_01",//"Business Young Female",  
				"a_f_y_business_02",//"Business Young Female 2",  
				"a_f_y_business_03",//"Business Young Female 3",  
				"a_f_y_business_04",//"Business Young Female 4",  
				"a_f_y_femaleagent",//"Female Agent",  
				"a_m_y_busicas_01",//"Business Casual",  
				"a_m_m_business_01",//"Business Male",  
				"a_m_y_business_01",//"Business Young Male",  
				"a_m_y_business_02",//"Business Young Male 2",  
				"a_m_y_business_03",//"Business Young Male 3",  
				"a_m_m_prolhost_01"//"Prologue Host Male",  
			};

			PrePed_06 = PrePeSet_06;
			WriteFile(sPedList06, PrePed_06);
		}
		else
			RemoveBlankStrings(PrePed_06);

		const std::string sPedList07 = GetDir() + "/RandomStart/Peds/BodyBuilders.ini";
		PrePed_07 = ReadSetFile(sPedList07);
		if (PrePed_07.size() == 0)
		{
			const std::vector<std::string> PrePeSet_07 = {
				"a_f_m_bodybuild_01",//"Bodybuilder Female",  
				"a_m_y_musclbeac_01",//"Beach Muscle Male",  
				"a_m_y_musclbeac_02"//"Beach Muscle Male 2", 
			};

			PrePed_07 = PrePeSet_07;
			WriteFile(sPedList07, PrePed_07);
		}
		else
			RemoveBlankStrings(PrePed_07);

		const std::string sPedList08 = GetDir() + "/RandomStart/Peds/Joggers.ini";
		PrePed_08 = ReadSetFile(sPedList08);
		if (PrePed_08.size() == 0)
		{
			const std::vector<std::string> PrePeSet_08 = {
				"a_f_y_fitness_01",//"Fitness Female",  
				"a_f_y_fitness_02",//"Fitness Female 2",  
				"a_f_y_runner_01",//"Jogger Female",
				"a_f_y_tennis_01",//"Tennis Player Female",  
				"a_m_y_runner_01",//"Jogger Male",  
				"a_m_y_runner_02"//"Jogger Male 2", 
			};

			PrePed_08 = PrePeSet_08;
			WriteFile(sPedList08, PrePed_08);
		}
		else
			RemoveBlankStrings(PrePed_08);

		const std::string sPedList09 = GetDir() + "/RandomStart/Peds/Golfer.ini";
		PrePed_09 = ReadSetFile(sPedList09);
		if (PrePed_09.size() == 0)
		{
			const std::vector<std::string> PrePeSet_09 = {
				"a_f_y_golfer_01",//"Golfer Young Female",  
				"a_m_m_golfer_01",//"Golfer Male",  
				"a_m_y_golfer_01"//"Golfer Young Male",  
			};

			PrePed_09 = PrePeSet_09;
			WriteFile(sPedList09, PrePed_09);
		}
		else
			RemoveBlankStrings(PrePed_09);

		const std::string sPedList10 = GetDir() + "/RandomStart/Peds/Hiker.ini";
		PrePed_10 = ReadSetFile(sPedList10);
		if (PrePed_10.size() == 0)
		{
			const std::vector<std::string> PrePeSet_10 = {
				"a_f_y_hiker_01",//"Hiker Female",  
				"a_m_y_hiker_01"//"Hiker Male",  
			};

			PrePed_10 = PrePeSet_10;
			WriteFile(sPedList10, PrePed_10);
		}
		else
			RemoveBlankStrings(PrePed_10);

		const std::string sPedList11 = GetDir() + "/RandomStart/Peds/MethodAct.ini";
		PrePed_11 = ReadSetFile(sPedList11);
		if (PrePed_11.size() == 0)
		{
			const std::vector<std::string> PrePeSet_11 = {
				"a_f_y_juggalo_01",//"Juggalo Female",  
				"a_m_y_juggalo_01",//"Juggalo Male", 
				"a_f_y_rurmeth_01",//"Rural Meth Addict Female",  
				"a_m_m_rurmeth_01",//"Rural Meth Addict Male",  
				"a_f_m_salton_01",//"Salton Female",  
				"a_f_o_salton_01",//"Salton Old Female", 
				"a_m_m_farmer_01",//"Farmer", 
				"a_m_m_hillbilly_01",//"Hillbilly Male",  
				"a_m_m_hillbilly_02",//"Hillbilly Male 2",  
				"a_m_y_methhead_01"//"Meth Addict",  
			};

			PrePed_11 = PrePeSet_11;
			WriteFile(sPedList11, PrePed_11);
		}
		else
			RemoveBlankStrings(PrePed_11);

		const std::string sPedList12 = GetDir() + "/RandomStart/Peds/Rural.ini";
		PrePed_12 = ReadSetFile(sPedList12);
		if (PrePed_12.size() == 0)
		{
			const std::vector<std::string> PrePeSet_12 = {
				"a_m_m_salton_01",//"Salton Male",  
				"a_m_m_salton_02",//"Salton Male 2",  
				"a_m_m_salton_03",//"Salton Male 3",  
				"a_m_m_salton_04",//"Salton Male 4",  
				"a_m_o_salton_01",//"Salton Old Male",  
				"a_m_y_salton_01",//"Salton Young Male",  
				"s_m_m_cntrybar_01"//"Bartender (Rural)",
			};

			PrePed_12 = PrePeSet_12;
			WriteFile(sPedList12, PrePed_12);
		}
		else
			RemoveBlankStrings(PrePed_12);

		const std::string sPedList13 = GetDir() + "/RandomStart/Peds/Cycleist.ini";
		PrePed_13 = ReadSetFile(sPedList13);
		if (PrePed_13.size() == 0)
		{
			const std::vector<std::string> PrePeSet_13 = {
				"a_f_y_skater_01",//"Skater Female",  
				"a_m_y_cyclist_01",//"Cyclist Male",  
				"a_m_y_dhill_01",//"Downhill Cyclist", 
				"a_m_y_roadcyc_01",//"Road Cyclist",  
				"a_m_y_skater_01",//"Skater Young Male",  
				"a_m_y_skater_02",//"Skater Young Male 2",  
				"a_m_m_tennis_01"//"Tennis Player Male",  
			};

			PrePed_13 = PrePeSet_13;
			WriteFile(sPedList13, PrePed_13);
		}
		else
			RemoveBlankStrings(PrePed_13);

		const std::string sPedList14 = GetDir() + "/RandomStart/Peds/LLGBQWXYZ.ini";
		PrePed_14 = ReadSetFile(sPedList14);
		if (PrePed_14.size() == 0)
		{
			const std::vector<std::string> PrePeSet_14 = {
				"a_m_y_gay_01",//"Gay Male",  
				"a_m_y_gay_02",//"Gay Male 2", 
				"a_m_m_tranvest_01",//"Transvestite Male",  
				"a_m_m_tranvest_02"//"Transvestite Male 2", 
			};

			PrePed_14 = PrePeSet_14;
			WriteFile(sPedList14, PrePed_14);
		}
		else
			RemoveBlankStrings(PrePed_14);
	}
	bool SnowOnGround = false;
	void WeatherReport(int iWet)
	{
		if (iWet == -1)
		{
			if (CanSnow)
				iWet = LessRandomInt("RanWeatherWinter", 10, 13);
			else
				iWet = LessRandomInt("RanWeatherSummer", 1, 9);
		}

		if (iWet == 1)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("EXTRASUNNY");
		else if (iWet == 2)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEAR");
		else if (iWet == 3)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLOUDS");
		else if (iWet == 4)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SMOG");
		else if (iWet == 4)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("FOGGY");
		else if (iWet == 5)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("OVERCAST");
		else if (iWet == 6)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("RAIN");
		else if (iWet == 7)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("THUNDER");
		else if (iWet == 8)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEARING");
		else if (iWet == 9)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("NEUTRAL");
		else if (iWet == 10)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SNOW");
		else if (iWet == 11)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("BLIZZARD");
		else if (iWet == 12)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SNOWLIGHT");
		else if (iWet == 13)
			GAMEPLAY::SET_WEATHER_TYPE_NOW("XMAS");

		if (CanSnow)
		{
			if (!SnowOnGround)
			{
				if (getGameVersion() > eGameVersion::VER_1_0_2944_0_NOSTEAM)
				{
					SnowOnGround = true;
					invoke<Void>(0x6E9EF3A33C8899F8, true);
					invoke<Void>(0xAEEDAD1420C65CC0, true);
					invoke<Void>(0xA342A3763B3AFB6C, true);
					invoke<Void>(0x4CC7F0FEA5283FE0, true);

					STREAMING::REQUEST_NAMED_PTFX_ASSET("core_snow");
					if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core_snow"))
						GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("core_snow");
				}
				else
				{
					CanSnow = false;
					Mod_Settings.SnowMonths = Mod_Class::SnowDates();
					Mod_Settings.SnowMonths.Dec = false;
					Mod_Settings.SnowMonths.Jan = false;
					Mod_Settings.SnowMonths.Feb = false;

					Mod_Ui::BottomLeft("This version of GTA is not compatable with this snow method.");
				}
			}
		}
		else
		{
			if (SnowOnGround)
			{
				SnowOnGround = false;
				invoke<Void>(0x6E9EF3A33C8899F8, false);
				invoke<Void>(0xAEEDAD1420C65CC0, false);
				invoke<Void>(0xA342A3763B3AFB6C, false);
				invoke<Void>(0x4CC7F0FEA5283FE0, false);

				STREAMING::_REMOVE_NAMED_PTFX_ASSET("core_snow");
			}
		}
	}
	void RandomWeatherTime()
	{
		WeatherReport(-1);

		int Times = LessRandomInt("RanTimes", 0, 23);
		TIME::SET_CLOCK_TIME(Times, 0, 0);
	}
}

namespace Mod_Maths
{
	const std::vector<std::string> MainLandIPLs = {
		"vw_casino_billboard_lod",
		"vw_casino_billboard_lod(1)",
		"vw_casino_billboard",
		"hei_dlc_windows_casino_lod",
		"hei_dlc_windows_casino",
		"hei_dlc_casino_door_lod",
		"hei_dlc_casino_door",
		"hei_dlc_casino_aircon_lod",
		"hei_dlc_casino_aircon"
	};
	const std::vector<std::string> CayoPericoIPLs = {
		"h4_islandairstrip",
		"h4_islandairstrip_props",
		"h4_islandx_mansion",
		"h4_islandx_mansion_props",
		"h4_islandx_props",
		"h4_islandxdock",
		"h4_islandxdock_props",
		"h4_islandxdock_props_2",
		"h4_islandxtower",
		"h4_islandx_maindock",
		"h4_islandx_maindock_props",
		"h4_islandx_maindock_props_2",
		"h4_IslandX_Mansion_Vault",
		"h4_islandairstrip_propsb",
		"h4_islandx_barrack_props",
		"h4_islandx_checkpoint",
		"h4_islandx_checkpoint_props",
		"h4_islandx_Mansion_Office",
		"h4_islandx_Mansion_LockUp_01",
		"h4_islandx_Mansion_LockUp_02",
		"h4_islandx_Mansion_LockUp_03",
		"h4_islandairstrip_hangar_props",
		"h4_IslandX_Mansion_B",
		"h4_islandairstrip_doorsclosed",
		"h4_Underwater_Gate_Closed",
		"h4_mansion_gate_closed",
		"h4_aa_guns",
		"h4_IslandX_Mansion_GuardFence",
		"h4_IslandX_Mansion_Entrance_Fence",
		"h4_IslandX_Mansion_B_Side_Fence",
		"h4_IslandX_Mansion_Lights",
		"h4_islandxcanal_props",
		"h4_islandX_Terrain_props_06_a",
		"h4_islandX_Terrain_props_06_b",
		"h4_islandX_Terrain_props_06_c",
		"h4_islandX_Terrain_props_05_a",
		"h4_islandX_Terrain_props_05_b",
		"h4_islandX_Terrain_props_05_c",
		"h4_islandX_Terrain_props_05_d",
		"h4_islandX_Terrain_props_05_e",
		"h4_islandX_Terrain_props_05_f",
		"H4_islandx_terrain_01",
		"H4_islandx_terrain_02",
		"H4_islandx_terrain_03",
		"H4_islandx_terrain_04",
		"H4_islandx_terrain_05",
		"H4_islandx_terrain_06",
		"h4_ne_ipl_00",
		"h4_ne_ipl_01",
		"h4_ne_ipl_02",
		"h4_ne_ipl_03",
		"h4_ne_ipl_04",
		"h4_ne_ipl_05",
		"h4_ne_ipl_06",
		"h4_ne_ipl_07",
		"h4_ne_ipl_08",
		"h4_ne_ipl_09",
		"h4_nw_ipl_00",
		"h4_nw_ipl_01",
		"h4_nw_ipl_02",
		"h4_nw_ipl_03",
		"h4_nw_ipl_04",
		"h4_nw_ipl_05",
		"h4_nw_ipl_06",
		"h4_nw_ipl_07",
		"h4_nw_ipl_08",
		"h4_nw_ipl_09",
		"h4_se_ipl_00",
		"h4_se_ipl_01",
		"h4_se_ipl_02",
		"h4_se_ipl_03",
		"h4_se_ipl_04",
		"h4_se_ipl_05",
		"h4_se_ipl_06",
		"h4_se_ipl_07",
		"h4_se_ipl_08",
		"h4_se_ipl_09",
		"h4_sw_ipl_00",
		"h4_sw_ipl_01",
		"h4_sw_ipl_02",
		"h4_sw_ipl_03",
		"h4_sw_ipl_04",
		"h4_sw_ipl_05",
		"h4_sw_ipl_06",
		"h4_sw_ipl_07",
		"h4_sw_ipl_08",
		"h4_sw_ipl_09",
		"h4_islandx_mansion",
		"h4_islandxtower_veg",
		"h4_islandx_sea_mines",
		"h4_islandx",
		"h4_islandx_barrack_hatch",
		"h4_islandxdock_water_hatch",
		"h4_beach",
		"h4_beach_props",
		"h4_beach_bar_props",
		"h4_beach_props_party",
		"h4_beach_party"
	};
	const std::vector<std::string> YanktonIPLs = {
		"plg_01",
		"prologue01",
		"prologue01_lod",
		"prologue01c",
		"prologue01c_lod",
		"prologue01d",
		"prologue01d_lod",
		"prologue01e",
		"prologue01e_lod",
		"prologue01f",
		"prologue01f_lod",
		"prologue01g",
		"prologue01h",
		"prologue01h_lod",
		"prologue01i",
		"prologue01i_lod",
		"prologue01j",
		"prologue01j_lod",
		"prologue01k",
		"prologue01k_lod",
		"prologue01z",
		"prologue01z_lod",
		"plg_02",
		"prologue02",
		"prologue02_lod",
		"plg_03",
		"prologue03",
		"prologue03_lod",
		"prologue03b",
		"prologue03b_lod",
		"prologue03_grv_dug",
		"prologue03_grv_dug_lod",
		"prologue_grv_torch",
		"plg_04",
		"prologue04",
		"prologue04_lod",
		"prologue04b",
		"prologue04b_lod",
		"prologue04_cover",
		"des_protree_end",
		"des_protree_start",
		"des_protree_start_lod",
		"plg_05",
		"prologue05",
		"prologue05_lod",
		"prologue05b",
		"prologue05b_lod",
		"plg_06",
		"prologue06",
		"prologue06_lod",
		"prologue06b",
		"prologue06b_lod",
		"prologue06_int",
		"prologue06_int_lod",
		"prologue06_pannel",
		"prologue06_pannel_lod",
		"prologue_m2_door",
		"prologue_m2_door_lod",
		"plg_occl_00",
		"prologue_occl",
		"plg_rd",
		"prologuerd",
		"prologuerdb",
		"prologuerd_lod"
	};

	Vector3 NewVector3(float X, float Y, float Z)
	{
		Vector3 NewVec = Vector3();
		NewVec.x = X;
		NewVec.y = Y;
		NewVec.z = Z;

		return NewVec;
	}
	Vector3 NewVector3(Mod_Class::Vector4 Vpos)
	{
		return NewVector3(Vpos.X, Vpos.Y, Vpos.Z);
	}
	float GetAngle(Vector3 postion1, Vector3 postion2)
	{
		double ang = (postion1.x * postion2.x) + (postion1.y * postion2.y);
		double output = 0;
		if (ang != 0)
		{
			double ang1 = sqrt((postion1.x * 2) + (postion1.y * 2)) / ang;
			double ang2 = sqrt((postion2.x * 2) + (postion2.y * 2)) / ang;
			double output = cos(ang1 + ang2 / ang);
		}
		return (float)output;
	}
	float DistanceTo(Vector3 postion1, Vector3 postion2)
	{
		double num = postion2.x - postion1.x;
		double num2 = postion2.y - postion1.y;
		double num3 = postion2.z - postion1.z;
		return (float)sqrt(num * num + num2 * num2 + num3 * num3);
	}
	float DistanceTo(Entity entity1, Entity entity2)
	{
		Vector3 postion1 = ENTITY::GET_ENTITY_COORDS(entity1, false);
		Vector3 postion2 = ENTITY::GET_ENTITY_COORDS(entity2, false);

		return DistanceTo(postion1, postion2);
	}
	float DistanceTo(Entity entity1, Mod_Class::Vector4 entity2)
	{
		Vector3 postion1 = ENTITY::GET_ENTITY_COORDS(entity1, false);
		Vector3 postion2 = NewVector3(entity2.X, entity2.Y, entity2.Z);

		return DistanceTo(postion1, postion2);
	}
	float DistanceTo(Entity entity1, Vector3 postion2)
	{
		Vector3 postion1 = ENTITY::GET_ENTITY_COORDS(entity1, false);
		return DistanceTo(postion1, postion2);
	}
	float DistanceTo(Mod_Class::Vector4 postion1, Vector3 postion2)
	{
		double num = postion2.x - postion1.X;
		double num2 = postion2.y - postion1.Y;
		double num3 = postion2.z - postion1.Z;
		return (float)sqrt(num * num + num2 * num2 + num3 * num3);
	}
	float DistanceTo(Mod_Class::Vector4 postion1, Mod_Class::Vector4 postion2)
	{
		double num = postion2.X - postion1.X;
		double num2 = postion2.Y - postion1.Y;
		double num3 = postion2.Z - postion1.Z;
		return (float)sqrt(num * num + num2 * num2 + num3 * num3);
	}

	std::string MyZone(Vector3 VPos)
	{
		static char* ZName = ZONE::GET_NAME_OF_ZONE(VPos.x, VPos.y, VPos.z);
		std::string s = ZName;
		return s;
	}
	std::string MyZone(Mod_Class::Vector4 VPos)
	{
		return MyZone(NewVector3(VPos.X, VPos.Y, VPos.Z));
	}

	Vector3 MyWayPoint()
	{
		return UI::GET_BLIP_INFO_ID_COORD(UI::GET_FIRST_BLIP_INFO_ID(8));
	}
	Vector3 EntPosition(Entity Ent)
	{
		return ENTITY::GET_ENTITY_COORDS(Ent, 0);
	}
	Vector3 PlayerPosi()
	{
		return EntPosition(PLAYER::PLAYER_PED_ID());
	}
	Vector3 RightOfEntity(Entity Object)
	{
		Vector3 Pos = ENTITY::GET_ENTITY_ROTATION(Object, 00);
		const double PI = 3.14259;
		double num = cos((double)Pos.y * (PI / 180.0));
		double num2 = cos((double)(0 - Pos.z) * (PI / 180.0)) * num;
		double num3 = sin((double)Pos.z * (PI / 180.0)) * num;
		double num4 = sin((double)(0 - Pos.y) * (PI / 180.0));

		Pos.x = (float)num2;
		Pos.y = (float)num3;
		Pos.z = (float)num4;

		return Pos;
	}
	Vector3 FowardOf(Entity ent, float multi, bool inFront)
	{
		Vector3 vec = ENTITY::GET_ENTITY_COORDS(ent, true);
		Vector3 FV = ENTITY::GET_ENTITY_FORWARD_VECTOR(ent);
		FV.x *= multi;
		FV.y *= multi;
		FV.z *= multi;

		if (inFront)
		{
			vec.x += FV.x;
			vec.y += FV.y;
			vec.z += FV.z;
		}
		else
		{
			vec.x -= FV.x;
			vec.y -= FV.y;
			vec.z -= FV.z;
		}

		return vec;
	}
	Vector3 RightOf(Entity ent, float multi, bool inFront)
	{
		Vector3 vec = ENTITY::GET_ENTITY_COORDS(ent, true);
		Vector3 FV = RightOfEntity(ent);
		FV.x *= multi;
		FV.y *= multi;
		FV.z *= multi;

		if (inFront)
		{
			vec.x += FV.x;
			vec.y += FV.y;
			vec.z += FV.z;
		}
		else
		{
			vec.x -= FV.x;
			vec.y -= FV.y;
			vec.z -= FV.z;
		}

		return vec;
	}

	Mod_Class::Vector4 GetPosV4(Entity ent)
	{
		Vector3 Vx = EntPosition(ent);

		return Mod_Class::Vector4(Vx.x, Vx.y, Vx.z, ENTITY::GET_ENTITY_HEADING(ent));
	}
	Mod_Class::Vector4 PlayerV4()
	{
		return GetPosV4(PLAYER::PLAYER_PED_ID());
	}
	Mod_Class::Vector4 InAreaOf(Mod_Class::Vector4  area, float minDist, float maxDist)
	{
		float X = RandomFloat(maxDist * -1, maxDist);
		float Y = RandomFloat(maxDist * -1, maxDist);

		if (X > -1.0 && X < minDist)
			X = minDist;
		else if (X < 1.0 && X > minDist * -1)
			X = minDist * -1;

		if (Y > -1.0 && Y < minDist)
			Y = minDist;
		else if (Y < 1.0 && Y > minDist * -1)
			Y = minDist * -1;

		float x = area.X + X;
		float y = area.Y + Y;
		float z = area.Z;
		float r = area.R;

		return Mod_Class::Vector4(x, y, z, r);
	}
	Mod_Class::Vector4 InAreaOf(Vector3 area, float minDist, float maxDist)
	{
		return InAreaOf(Mod_Class::Vector4(area.x, area.y, area.z, 0.0), minDist, maxDist);
	}
	Mod_Class::Vector4 NearByStreet(Mod_Class::Vector4 Area)
	{
		Mod_Class::Vector4 Here = InAreaOf(Area, 25.0f, 75.0f);
		Vector3 VMe = NewVector3(Here.X, Here.Y, Here.Z);
		PATHFIND::GET_SAFE_COORD_FOR_PED(Here.X, Here.Y, Here.Z, true, &VMe, 16);
		return Mod_Class::Vector4(VMe.x, VMe.y, VMe.z, 0.0f);
	}

	std::vector<int> BeenThereA = {};
	std::vector<int> BeenThereB = {};
	std::vector<int> BeenThereC = {};

	Mod_Class::Vector4 FindPedSpPoint(Vector3 Pos)
	{
		float fAr = 4000.0f;
		int Near = -1;
		if (Yankton_Loaded)
		{
			for (int i = 0; i < (int)Yankton.size(); i++)
			{
				if (DistanceTo(Yankton[i], Pos) < fAr && !Mod_Systems::ListContains(BeenThereA, i))
				{
					fAr = DistanceTo(Yankton[i], Pos);
					Near = i;
				}
			}

			BeenThereA.push_back(Near);
			if (BeenThereA.size() > 4)
				BeenThereA.erase(BeenThereA.begin());

			return Yankton[Near];
		}
		else if (Cayo_Loaded)
		{
			for (int i = 0; i < (int)CayoSpPoint.size(); i++)
			{
				if (DistanceTo(CayoSpPoint[i], Pos) < fAr && !Mod_Systems::ListContains(BeenThereB, i))
				{
					fAr = DistanceTo(CayoSpPoint[i], Pos);
					Near = i;
				}
			}

			BeenThereB.push_back(Near);
			if (BeenThereB.size() > 4)
				BeenThereB.erase(BeenThereB.begin());

			return CayoSpPoint[Near];
		}
		else
		{
			for (int i = 0; i < (int)SpPoint.size(); i++)
			{
				if (DistanceTo(SpPoint[i], Pos) < fAr && !Mod_Systems::ListContains(BeenThereC, i))
				{
					fAr = DistanceTo(SpPoint[i], Pos);
					Near = i;
				}
			}

			BeenThereC.push_back(Near);
			if (BeenThereC.size() > 4)
				BeenThereC.erase(BeenThereC.begin());

			return SpPoint[Near];
		}
	}

	bool NotTheSame(Mod_Class::Vector4 V1, Mod_Class::Vector4 V2)
	{
		bool bTrue = false;

		if (V1.X != V2.X)
			bTrue = true;

		if (V1.Y != V2.Y)
			bTrue = true;

		if (V1.Z != V2.Z)
			bTrue = true;

		if (V1.R != V2.R)
			bTrue = true;

		return bTrue;
	}
	float GroundHight(Vector3 postion)
	{
		float GHight = postion.z;
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(postion.x, postion.y, postion.z, &GHight, 1);
		return GHight;
	}

	const std::vector<Vector3> landSand = {
	 NewVector3(225.8934, 2841.527, 200.0402),
	 NewVector3(796.0992, 3011.926, 90.13193),
	 NewVector3(1495.307, 3187.998, 41.04951),
	 NewVector3(1655.049, 3249.205, 41.21964),
	 NewVector3(1561.392, 3160.818, 41.1649),
	 NewVector3(1334.507, 2924.953, 98.35621),
	 NewVector3(798.5253, 2388.362, 282.331),
	 NewVector3(413.3483, 2034.074, 425.4946),
	 NewVector3(-175.5016, 1448.899, 598.845),
	 NewVector3(-349.6658, -187.2563, 398.4032)
	};
	const std::vector<Vector3> landLS = {
		 NewVector3(-1002.727, -1650.774, 134.2087),
		 NewVector3(-1193.304, -1941.04, 59.51603),
		 NewVector3(-1571.467, -2617.15, 14.57554),
		 NewVector3(-1612.011, -2789.524, 14.62421),
		 NewVector3(-1532.074, -2835.987, 14.58676),
		 NewVector3(-991.79, -3147.605, 90.8317),
		 NewVector3(-440.5424, -3123.56, 232.0305),
		 NewVector3(-88.80471, -2403.97, 234.262),
		 NewVector3(-18.7144, -1591.593, 351.0859),
		 NewVector3(29.53166, 219.7558, 581.6113),
		 NewVector3(-169.9742, 1746.14, 484.2034)
	};
	std::vector<Vector3> BuildFlightPath(Vector3 vStart)
	{
		float f1 = DistanceTo(vStart, landSand[0]);
		float f2 = DistanceTo(vStart, landLS[0]);

		if (f1 < f2)
			return landSand;
		else
			return landLS;
	}

	const std::string ZeroYank = GetDir() + "/PlayerZero/Yankton.txt";
	const std::string ZeroCayo = GetDir() + "/PlayerZero/Cayo.txt";

	bool YanktonIPL()
	{
		LoggerLight("YankLoad == " + std::to_string(Yankton_Loaded));
		bool bFailed = false;
		if (Yankton_Loaded)
		{
			invoke<Void>(0x9BAE5AD2508DF078, false);
			invoke<Void>(0x9133955F1A2DA957, false);
			invoke<Void>(0x9BAE5AD2508DF078, false);

			for (int i = 0; i < YanktonIPLs.size(); i++)
			{
				STREAMING::REMOVE_IPL((LPSTR)YanktonIPLs[i].c_str());
				WAIT(1);
			}
			if (GotPlayZero)
				FileRemoval(ZeroYank);
			Yankton_Loaded = false;
		}
		else
		{
			invoke<Void>(0x9BAE5AD2508DF078, false);
			invoke<Void>(0x9133955F1A2DA957, true);

			std::vector<std::string> PzTest = {};

			for (int i = 0; i < YanktonIPLs.size(); i++)
			{
				STREAMING::REQUEST_IPL((LPSTR)YanktonIPLs[i].c_str());
				WAIT(1);
				if (!STREAMING::IS_IPL_ACTIVE((LPSTR)YanktonIPLs[i].c_str()))
					bFailed = true;
			}
			if (GotPlayZero)
				WriteFile(ZeroYank, PzTest);
			Yankton_Loaded = true;
		}

		return bFailed;
	}
	void LoadOnlineIps()
	{
		GAMEPLAY::_ENABLE_MP_DLC_MAPS(1);
		DLC2::_LOAD_MP_DLC_MAPS();

		invoke<Void>(0x9BAE5AD2508DF078, 1);

		/*
		for (int i = 0; i < MainLandIPLs.size(); i++)
		{
			if (!STREAMING::IS_IPL_ACTIVE((LPSTR)MainLandIPLs[i].c_str()))
				STREAMING::REQUEST_IPL((LPSTR)MainLandIPLs[i].c_str());
		}
		*/
	}
	bool CayoPericoIPL()
	{
		LoggerLight("CayoPericoIPL == " + std::to_string(Cayo_Loaded));
		bool bFailed = false;
		if (Cayo_Loaded)
		{
			invoke<Void>(0x9A9D1BA639675CF1, "HeistIsland", 0);
			invoke<Void>(0x5E1460624D194A38, 0);

			invoke<Void>(0xF74B1FFA4A15FBEA, 0);
			invoke<Void>(0x53797676AD34A9AA, 1);

			for (int i = 0; i < CayoPericoIPLs.size(); i++)
			{
				if (STREAMING::IS_IPL_ACTIVE((LPSTR)CayoPericoIPLs[i].c_str()))
					STREAMING::REMOVE_IPL((LPSTR)CayoPericoIPLs[i].c_str());
				WAIT(1);
			}

			if (GotPlayZero)
				FileRemoval(ZeroCayo);
			Cayo_Loaded = false;
		}
		else
		{
			LoadOnlineIps();

			GAMEPLAY::_ENABLE_MP_DLC_MAPS(1);
			invoke<Void>(0x9A9D1BA639675CF1, "HeistIsland", 1);
			invoke<Void>(0x5E1460624D194A38, 1);

			invoke<Void>(0xF74B1FFA4A15FBEA, 1);
			invoke<Void>(0x53797676AD34A9AA, 0);

			invoke<Void>(0xF8DEE0A5600CBB93, 1);

			std::vector<std::string> PzTest = {};

			for (int i = 0; i < CayoPericoIPLs.size(); i++)
			{
				STREAMING::REQUEST_IPL((LPSTR)CayoPericoIPLs[i].c_str());
				WAIT(1);
				if (!STREAMING::IS_IPL_ACTIVE((LPSTR)CayoPericoIPLs[i].c_str()))
					bFailed = true;
			}

			if (GotPlayZero)
				WriteFile(ZeroCayo, PzTest);

			Cayo_Loaded = true;
		}
		return bFailed;
	}

	void AnyPreActives(int iSelect, bool MainLand)
	{
		if (Meth_Act)
		{
			Meth_Act = false;
			Mod_Entitys::MethEdd(Meth_Act);
		}

		if (Deputize)
		{
			Deputize = false;
			Mod_Entitys::PoliceAcadamy(Deputize);
		}

		if (MainLand)
		{
			if (Cayo_Loaded && iSelect != 25)
			{
				CayoPericoIPL();
				Mod_Entitys::CayoAudio();
			}
			else if (Yankton_Loaded && iSelect != 24)
				YanktonIPL();
		}
	}
}

namespace Mod_Entitys
{
	int AddRelationship(const std::string& name)
	{
		Hash hash = -1;
		PED::ADD_RELATIONSHIP_GROUP((LPSTR)name.c_str(), &hash);

		return hash;
	}
	Hash GetRelationship()
	{
		return PED::GET_PED_RELATIONSHIP_GROUP_HASH(PLAYER::PLAYER_PED_ID());
	}
	void RelGroupMember(Ped Peddy, Hash group)
	{
		PED::SET_PED_RELATIONSHIP_GROUP_HASH(Peddy, group);
	}
	void SetRelBetween_Gp(Hash Group1, Hash Group2, int Rel)
	{
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(Rel, Group1, Group2);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(Rel, Group2, Group1);
	}
	void SetRelationType(bool friendly)
	{
		if (friendly)
		{
			SetRelBetween_Gp(GP_Player, Gp_Follow, 0);
			SetRelBetween_Gp(Gp_Follow, Gp_Friend, 1);
			SetRelBetween_Gp(GP_Attack, Gp_Follow, 5);
			SetRelBetween_Gp(GP_Mental, Gp_Follow, 5);
			SetRelBetween_Gp(GP_Player, Gp_Friend, 2);
			SetRelBetween_Gp(GP_Attack, Gp_Friend, 5);
			SetRelBetween_Gp(GP_Player, GP_Attack, 5);
			SetRelBetween_Gp(GP_Mental, Gp_Friend, 5);
			SetRelBetween_Gp(GP_Attack, GP_Mental, 5);
			SetRelBetween_Gp(GP_Player, GP_Mental, 5);

			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, GP_Mental, GP_Mental);
		}
		else
		{
			SetRelBetween_Gp(GP_Player, Gp_Follow, 2);
			SetRelBetween_Gp(Gp_Follow, Gp_Friend, 2);
			SetRelBetween_Gp(GP_Attack, Gp_Follow, 5);
			SetRelBetween_Gp(GP_Mental, Gp_Follow, 5);
			SetRelBetween_Gp(GP_Player, Gp_Friend, 2);
			SetRelBetween_Gp(GP_Attack, Gp_Friend, 5);
			SetRelBetween_Gp(GP_Player, GP_Attack, 5);
			SetRelBetween_Gp(GP_Mental, Gp_Friend, 5);
			SetRelBetween_Gp(GP_Attack, GP_Mental, 5);
			SetRelBetween_Gp(GP_Player, GP_Mental, 5);
		}
	}

	void MoveEntity(Entity MyEnt, Vector3 position)
	{
		ENTITY::SET_ENTITY_COORDS(MyEnt, position.x, position.y, position.z, 1, 0, 0, 1);
	}
	void MoveEntity(Entity MyEnt, Mod_Class::Vector4 position)
	{
		ENTITY::SET_ENTITY_COORDS(MyEnt, position.X, position.Y, position.Z, 1, 0, 0, 1);
		ENTITY::SET_ENTITY_HEADING(MyEnt, position.R);
	}
	void StayOnGround(Vehicle Vhick)
	{
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(Vhick);
	}

	int GetPedOverlayValues(int overlay)
	{
		return PED::_GET_NUM_HEAD_OVERLAY_VALUES(overlay);
	}
	int GetPedOverlay(Ped peddy, int overlay)
	{
		return PED::_GET_PED_HEAD_OVERLAY_VALUE(peddy, overlay);
	}

	std::vector<int> RandVehModsist()
	{
		std::vector<int> RandMods = {};

		for (int i = 0; i < 67; i++)
			RandMods.push_back(-1);

		return RandMods;
	}

	Prop BuildProps(const std::string& sObject, Vector3 vPos, Vector3 vRot, bool bPush, bool Frozen)
	{
		LoggerLight("BuildProps == " + sObject);
		Prop Plop = OBJECT::CREATE_OBJECT(MyHashKey(sObject), vPos.x, vPos.y, vPos.z, 1, 1, 1);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Plop, 1, 1);
		ENTITY::SET_ENTITY_COORDS(Plop, vPos.x, vPos.y, vPos.z, 0, 0, 0, 1);
		ENTITY::SET_ENTITY_ROTATION(Plop, vRot.x, vRot.y, vRot.z, 2, 1);
		if (bPush)
			ENTITY::APPLY_FORCE_TO_ENTITY(Plop, 1, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1, 1, 1, 1, 1, 1);
		else if (Frozen)
			ENTITY::FREEZE_ENTITY_POSITION(Plop, true);
		Prop_List.push_back(Plop);
		return Plop;
	}
	Prop BuildProps(const std::string& sObject, Mod_Class::Vector4 vPos, bool bPush, bool Frozen)
	{
		return BuildProps(sObject, Mod_Maths::NewVector3(vPos.X, vPos.Y, vPos.Z), Mod_Maths::NewVector3(0.0f, 0.0f, vPos.R), bPush, Frozen);
	}

	void EraseBlip(Blip MyBlip)
	{
		if (MyBlip != NULL)
		{
			if ((bool)UI::DOES_BLIP_EXIST(MyBlip))
				UI::REMOVE_BLIP(&MyBlip);
		}
	}
	void ClearAllPeds()
	{
		for (int i = 0; i < (int)Ped_List.size(); i++)
		{
			Entity E = Ped_List[i];
			if (ENTITY::DOES_ENTITY_EXIST(E))
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&E);
		}
		Ped_List.clear();
		CayDancers.clear();
	}
	void ClearAllEntitys(bool andPeds)
	{
		for (int i = 0; i < (int)Prop_List.size(); i++)
		{
			Prop Pops = Prop_List[i];
			if (ENTITY::DOES_ENTITY_EXIST(Pops))
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Pops);
		}
		Prop_List.clear();

		for (int i = 0; i < (int)Vehicle_List.size(); i++)
		{
			Vehicle Vic = Vehicle_List[i];
			if (ENTITY::DOES_ENTITY_EXIST(Vic))
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Vic);
		}
		Vehicle_List.clear();

		if (andPeds)
			ClearAllPeds();
	}

	const std::vector<Mod_Class::VehBlips> vehBlips = {
		Mod_Class::VehBlips("BUFFALO4",825),
		Mod_Class::VehBlips("CHAMPION",824),
		Mod_Class::VehBlips("DEITY",823),
		Mod_Class::VehBlips("GRANGER2",821),
		Mod_Class::VehBlips("JUBILEE",820),
		Mod_Class::VehBlips("PATRIOT3",818),
		Mod_Class::VehBlips("CRUSADER",800),
		Mod_Class::VehBlips("SLAMVAN2",799),
		Mod_Class::VehBlips("SLAMVAN3", 799),
		Mod_Class::VehBlips("VALKYRIE", 759),
		Mod_Class::VehBlips("VALKYRIE2", 759),
		Mod_Class::VehBlips("SQUADDIE", 757),
		Mod_Class::VehBlips("ardent", 756),///Retro Sport...       
		Mod_Class::VehBlips("cheetah2", 756),///Retro Sport...      
		Mod_Class::VehBlips("infernus2", 756),///Retro Sport...      
		Mod_Class::VehBlips("monroe", 756),///Retro Sport...      
		Mod_Class::VehBlips("stromberg", 756),///Retro Sport...      
		Mod_Class::VehBlips("torero", 756),///Retro Sport...      
		Mod_Class::VehBlips("turismo2", 756),///Retro Sport...      
		Mod_Class::VehBlips("toreador", 756),///Retro Sport...         
		Mod_Class::VehBlips("PATROLBOAT",755),
		Mod_Class::VehBlips("DINGHY5",754),
		Mod_Class::VehBlips("DINGHY5",754),
		Mod_Class::VehBlips("seasparrow2", 753),
		Mod_Class::VehBlips("barracks", 750),
		Mod_Class::VehBlips("barracks3", 750),
		Mod_Class::VehBlips("verus", 749),
		Mod_Class::VehBlips("veto2", 748),
		Mod_Class::VehBlips("veto", 747),
		Mod_Class::VehBlips("avisa", 746),
		Mod_Class::VehBlips("WINKY", 745),
		Mod_Class::VehBlips("ZHABA", 737),
		Mod_Class::VehBlips("VAGRANT", 736),
		Mod_Class::VehBlips("OUTLAW", 735),
		Mod_Class::VehBlips("everon", 734),
		Mod_Class::VehBlips("formula",726),
		Mod_Class::VehBlips("formula2",726),
		Mod_Class::VehBlips("openwheel1",726),
		Mod_Class::VehBlips("openwheel2",726),
		Mod_Class::VehBlips("STRETCH",724),
		Mod_Class::VehBlips("ZR380", 669),
		Mod_Class::VehBlips("ZR3802", 669),
		Mod_Class::VehBlips("ZR3803", 669),
		Mod_Class::VehBlips("SLAMVAN4", 668),
		Mod_Class::VehBlips("SLAMVAN5", 668),
		Mod_Class::VehBlips("SLAMVAN6", 668),
		Mod_Class::VehBlips("SCARAB", 667),
		Mod_Class::VehBlips("SCARAB2", 667),
		Mod_Class::VehBlips("SCARAB3", 667),
		Mod_Class::VehBlips("MONSTER3", 666),
		Mod_Class::VehBlips("MONSTER4", 666),
		Mod_Class::VehBlips("MONSTER5", 666),
		Mod_Class::VehBlips("ISSI4", 665),
		Mod_Class::VehBlips("ISSI5", 665),
		Mod_Class::VehBlips("ISSI6", 665),
		Mod_Class::VehBlips("IMPERATOR", 664),
		Mod_Class::VehBlips("IMPERATOR2", 664),
		Mod_Class::VehBlips("IMPERATOR3", 664),
		Mod_Class::VehBlips("IMPALER2", 663),
		Mod_Class::VehBlips("IMPALER3", 663),
		Mod_Class::VehBlips("IMPALER4", 663),
		Mod_Class::VehBlips("DOMINATOR4", 662),
		Mod_Class::VehBlips("DOMINATOR5", 662),
		Mod_Class::VehBlips("DOMINATOR6", 662),
		Mod_Class::VehBlips("CERBERUS", 660),
		Mod_Class::VehBlips("CERBERUS2", 660),
		Mod_Class::VehBlips("CERBERUS3", 660),
		Mod_Class::VehBlips("BRUTUS", 659),
		Mod_Class::VehBlips("BRUTUS2", 659),
		Mod_Class::VehBlips("BRUTUS3", 659),
		Mod_Class::VehBlips("BRUISER", 658),
		Mod_Class::VehBlips("BRUISER2", 658),
		Mod_Class::VehBlips("BRUISER3", 658),
		Mod_Class::VehBlips("STRIKEFORCE", 640),
		Mod_Class::VehBlips("OPPRESSOR2", 639),
		Mod_Class::VehBlips("SPEEDO4", 637),
		Mod_Class::VehBlips("MULE4", 636),
		Mod_Class::VehBlips("POUNDER2", 635),
		Mod_Class::VehBlips("scramjet", 634),
		Mod_Class::VehBlips("ambulance",632),
		Mod_Class::VehBlips("pbus2",631),
		Mod_Class::VehBlips("caracara",613),
		Mod_Class::VehBlips("seasparrow", 612),
		Mod_Class::VehBlips("APC", 603),
		Mod_Class::VehBlips("akula", 602),
		Mod_Class::VehBlips("insurgent", 601),
		Mod_Class::VehBlips("insurgent3", 601),
		Mod_Class::VehBlips("volatol", 600),
		Mod_Class::VehBlips("alkonost", 600),
		Mod_Class::VehBlips("KHANJALI", 598),
		Mod_Class::VehBlips("DELUXO",  596),
		Mod_Class::VehBlips("bombushka", 585),
		Mod_Class::VehBlips("seabreeze", 584),
		Mod_Class::VehBlips("STARLING", 583),
		Mod_Class::VehBlips("ROGUE", 582),
		Mod_Class::VehBlips("PYRO", 581),
		Mod_Class::VehBlips("nokota", 580),
		Mod_Class::VehBlips("MOLOTOK", 579),
		Mod_Class::VehBlips("mogul", 578),
		Mod_Class::VehBlips("microlight", 577),
		Mod_Class::VehBlips("HUNTER", 576),
		Mod_Class::VehBlips("howard", 575),
		Mod_Class::VehBlips("havok", 574),
		Mod_Class::VehBlips("tula", 573),
		Mod_Class::VehBlips("alphaz1", 572),
		Mod_Class::VehBlips("tampa3", 562),//truureted something
		Mod_Class::VehBlips("DUNE3", 561),
		Mod_Class::VehBlips("HALFTRACK", 560),
		Mod_Class::VehBlips("OPPRESSOR", 559),
		//Mod_Class::VehBlips("", 558),//something somthing turreted
		Mod_Class::VehBlips("TECHNICAL2", 534),
		Mod_Class::VehBlips("voltic2", 533),
		Mod_Class::VehBlips("wastelander", 532),
		Mod_Class::VehBlips("DUNE4", 531),
		Mod_Class::VehBlips("DUNE5", 531),
		Mod_Class::VehBlips("RUINER2", 530),
		Mod_Class::VehBlips("PHANTOM2", 528),
		Mod_Class::VehBlips("hakuchou",522),//ModSportsBike
		Mod_Class::VehBlips("hakuchou2",522),//ModSportsBike
		Mod_Class::VehBlips("shotaro",522),//ModSportsBike
		Mod_Class::VehBlips("pbus",513),//BusssAny
		Mod_Class::VehBlips("blazer",512),//QuadAny
		Mod_Class::VehBlips("blazer2",512),//QuadAny
		Mod_Class::VehBlips("blazer3",512),//QuadAny
		Mod_Class::VehBlips("blazer4",512),//QuadAny
		Mod_Class::VehBlips("blazer5",512),//QuadAny
		Mod_Class::VehBlips("cargobob", 481),
		Mod_Class::VehBlips("cargobob2", 481),
		Mod_Class::VehBlips("cargobob3", 481),
		Mod_Class::VehBlips("cargobob4", 481),
		Mod_Class::VehBlips("armytanker", 479),//Trailler Box
		Mod_Class::VehBlips("armytrailer", 479),//Trailler Box
		Mod_Class::VehBlips("baletrailer", 479),//Trailler Box
		Mod_Class::VehBlips("boattrailer", 479),//Trailler Box
		Mod_Class::VehBlips("docktrailer", 479),//Trailler Box
		Mod_Class::VehBlips("freighttrailer", 479),//Trailler Box
		Mod_Class::VehBlips("graintrailer", 479),//Trailler Box
		Mod_Class::VehBlips("tr2", 479),//Trailler Box
		Mod_Class::VehBlips("tr3", 479),//Trailler Box
		Mod_Class::VehBlips("tr4", 479),//Trailler Box
		Mod_Class::VehBlips("trflat", 479),//Trailler Box
		Mod_Class::VehBlips("tvtrailer", 479),//Trailler Box
		Mod_Class::VehBlips("tanker", 479),//Trailler Box
		Mod_Class::VehBlips("tanker2", 479),//Trailler Box
		Mod_Class::VehBlips("trailerlarge", 479),//Trailler Box
		Mod_Class::VehBlips("trailerlogs", 479),//Trailler Box
		Mod_Class::VehBlips("trailersmall", 479),//Trailler Box
		Mod_Class::VehBlips("tanker", 479),//Trailler Box
		Mod_Class::VehBlips("trailers", 479),//Trailler Box
		Mod_Class::VehBlips("trailers2", 479),//Trailler Box
		Mod_Class::VehBlips("trailers3", 479),//Trailler Box
		Mod_Class::VehBlips("trailers4", 479),//Trailler Box
		Mod_Class::VehBlips("barracks2", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("scrap", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("towtruck", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("rallytruck", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("brickade", 477),//Truck any---not intrucks
		Mod_Class::VehBlips("firetruk",477),
		Mod_Class::VehBlips("seashark", 471),//Seashark
		Mod_Class::VehBlips("seashark2", 471),//Seashark
		Mod_Class::VehBlips("seashark3", 471),//Seashark
		Mod_Class::VehBlips("limo2", 460),
		Mod_Class::VehBlips("technical", 426),
		Mod_Class::VehBlips("technical3", 426),
		Mod_Class::VehBlips("RHINO", 421),
		Mod_Class::VehBlips("marquis",410),
		Mod_Class::VehBlips("avarus",348),//lost bike
		Mod_Class::VehBlips("chimera",348),//lost bike
		Mod_Class::VehBlips("cliffhanger",348),//lost bike
		Mod_Class::VehBlips("daemon",348),//lost bike
		Mod_Class::VehBlips("daemon2",348),//lost bike
		Mod_Class::VehBlips("gargoyle",348),//lost bike
		Mod_Class::VehBlips("hexer",348),//lost bike
		Mod_Class::VehBlips("innovation",348),//lost bike
		Mod_Class::VehBlips("ratbike",348),//lost bike
		Mod_Class::VehBlips("sanctus",348),//lost bike
		Mod_Class::VehBlips("wolfsbane",348),//lost bike
		Mod_Class::VehBlips("zombiea",348),//lost bike
		Mod_Class::VehBlips("zombieb",348),//lost bike
		Mod_Class::VehBlips("trash",318),
		Mod_Class::VehBlips("trash2",318),
		Mod_Class::VehBlips("jet",307),
		Mod_Class::VehBlips("luxor",307),
		Mod_Class::VehBlips("luxor2",307),
		Mod_Class::VehBlips("miljet",307),
		Mod_Class::VehBlips("nimbus",307),
		Mod_Class::VehBlips("shamal",307),
		Mod_Class::VehBlips("vestra",307),
		Mod_Class::VehBlips("velum",251),
		Mod_Class::VehBlips("velum2",251),
		Mod_Class::VehBlips("stunt",251),
		Mod_Class::VehBlips("mammatus",251),
		Mod_Class::VehBlips("duster",251),
		Mod_Class::VehBlips("dodo",251),
		Mod_Class::VehBlips("cuban800",251),
		Mod_Class::VehBlips("taxi",198),
		Mod_Class::VehBlips("dune",147),
		Mod_Class::VehBlips("stockade",67)
	};
	int OhMyBlip(Vehicle MyVehic)
	{
		LoggerLight("OhMyBlip");

		int iBeLip = 0;
		if (MyVehic != NULL)
		{
			int iVehClass = VEHICLE::GET_VEHICLE_CLASS(MyVehic);

			if (iVehClass == 14)
				iBeLip = 427;
			else if (iVehClass == 15)
				iBeLip = 64;
			else if (iVehClass == 8)
				iBeLip = 226;
			else if (iVehClass == 16)
				iBeLip = 424;
			else if (iVehClass == 12)
				iBeLip = 616;
			else if (iVehClass == 20)//mule
				iBeLip = 477;
			else if (iVehClass == 10)//trucks
				iBeLip = 477;
			else if (iVehClass == 17)//buss
				iBeLip = 513;
			else if (iVehClass == 7)
				iBeLip = 595;
			else if (iVehClass == 6)
				iBeLip = 523;
			else if (iVehClass == 13)
				iBeLip = 376;
			else
				iBeLip = 225;


			for (int i = 0; i < vehBlips.size(); i++)
			{
				if ((bool)VEHICLE::IS_VEHICLE_MODEL(MyVehic, MyHashKey(vehBlips[i].VehicleKey)))
					iBeLip = vehBlips[i].BlipNo;
			}
		}

		return iBeLip;
	}

	Prop FindingProps(Vector3 Area, float radius, const std::string& modelHash)
	{
		return OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Area.x, Area.y, Area.z, radius, MyHashKey(modelHash), false, 1, 1);
	}
	Prop FindingProps(Mod_Class::Vector4 Area, float radius, const std::string& modelHash)
	{
		return FindingProps(Mod_Maths::NewVector3(Area.X, Area.Y, Area.Z), radius, modelHash);
	}

	Object AddDecals(Vector3 pos, int decalType, float width = 1.0f, float height = 1.0f, float rCoef = 0.1f, float gCoef = 0.1f, float bCoef = 0.1f, float opacity = 1.0f, float timeout = 20.0f)
	{
		return GRAPHICS::ADD_DECAL(decalType, pos.x, pos.y, pos.z, 0, 0, -1.0, 0, 1.0, 0, width, height, rCoef, gCoef, bCoef, opacity, timeout, 0, 0, 0);
	}

	const std::vector<std::string> GunnerSeat = {
		"MOGUL",
		"LIMO2", //><!-- Turreted Limo -->
		"INSURGENT2", //><!-- Insurgent Pick-Up -->
		"INSURGENT3", //><!-- Insurgent Pick-Up Custom -->
		"CARACARA", //>
		"MENACER", //>
		"TECHNICAL", //>
		"TECHNICAL2", //><!-- Technical Aqua -->
		"TECHNICAL3", //><!-- Technical Custom -->
		"HALFTRACK", //>
	};
	int FindUSeat(Vehicle vMe)
	{
		bool bPass = true;
		for (int i = 0; i < (int)GunnerSeat.size(); i++)
		{
			if (MyHashKey(GunnerSeat[i]) == ENTITY::GET_ENTITY_MODEL(vMe))
			{
				bPass = false;
				break;
			}
		}

		int iSeats;
		if (bPass)
		{
			iSeats = 0;
			while (iSeats < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vMe))
			{
				if ((bool)VEHICLE::IS_VEHICLE_SEAT_FREE(vMe, iSeats))
					break;
				else
					iSeats++;
			}
		}
		else
		{
			iSeats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vMe);
			while (iSeats > -1)
			{
				if ((bool)VEHICLE::IS_VEHICLE_SEAT_FREE(vMe, iSeats))
					break;
				else
					iSeats--;
			}
		}

		return iSeats;
	}
	void WarptoAnyVeh(Vehicle Vhic, Ped Peddy, int iSeat)
	{
		LoggerLight("WarptoAnyVeh");

		PED::SET_PED_INTO_VEHICLE(Peddy, Vhic, iSeat);
	}
	void GetOutVehicle(Ped Peddy)
	{
		LoggerLight("-GetOutVehicle-");

		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
			AI::TASK_LEAVE_VEHICLE(Peddy, PED::GET_VEHICLE_PED_IS_IN(Peddy, true), 4160);
	}
	void EmptyVeh(Vehicle Vhic)
	{
		LoggerLight("PedActions.EmptyVeh");

		if ((bool)ENTITY::DOES_ENTITY_EXIST(Vhic))
		{
			int iSeats = 0;
			while (iSeats < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vhic))
			{
				if (!(bool)VEHICLE::IS_VEHICLE_SEAT_FREE(Vhic, iSeats))
					GetOutVehicle(VEHICLE::GET_PED_IN_VEHICLE_SEAT(Vhic, iSeats));
				iSeats += 1;
			}
		}
	}
	bool InSameVeh(Ped Peddy)
	{
		bool bIn = false;
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
		{
			Vehicle Vic = PED::GET_VEHICLE_PED_IS_IN(Peddy, true);
			if ((bool)PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), Vic, false))
				bIn = true;
		}
		return bIn;
	}

	void BlipFiler(Blip MyBlip, int iBlippy, const std::string& sName, int iColour)
	{
		UI::SET_BLIP_SPRITE(MyBlip, iBlippy);
		UI::SET_BLIP_AS_SHORT_RANGE(MyBlip, true);
		UI::SET_BLIP_CATEGORY(MyBlip, 2);
		UI::SET_BLIP_COLOUR(MyBlip, iColour);

		std::string name = " Player: " + sName;

		if (sName != "")
		{
			UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)name.c_str());
			UI::END_TEXT_COMMAND_SET_BLIP_NAME(MyBlip);

			//UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
			//UI::_ADD_TEXT_COMPONENT_STRING(" Player: " + sName);
			//UI::END_TEXT_COMMAND_SET_BLIP_NAME( MyBlip);
		}
	}
	Blip PedBlimp(Blip CurBlip, Ped pEdd, int iBlippy, const std::string& sName, int iColour, bool heading)
	{
		LoggerLight("PedBlimp, iBlippy == " + std::to_string(iBlippy) + ", sName == " + sName + ", iColour" + std::to_string(iColour));

		EraseBlip(CurBlip);

		Blip MyBlip = UI::ADD_BLIP_FOR_ENTITY(pEdd);;

		BlipFiler(MyBlip, iBlippy, sName, iColour);
		if (heading)
			UI::_SET_BLIP_SHOW_HEADING_INDICATOR(MyBlip, true);

		return MyBlip;
	}
	Blip LocalBlip(Blip CurBlip, Mod_Class::Vector4 Vlocal, int iBlippy, const std::string& sName, int iColour)
	{
		LoggerLight("BuildObjects, iBlippy == " + std::to_string(iBlippy) + ", sName == " + sName);

		EraseBlip(CurBlip);
		Blip MyBlip = UI::ADD_BLIP_FOR_COORD(Vlocal.X, Vlocal.Y, Vlocal.Z);
		BlipFiler(MyBlip, iBlippy, sName, iColour);
		return MyBlip;
	}

	const std::vector<std::string> Mk2Weaps = {
		"WEAPON_pistol_mk2",  //0xBFE256D4",---------19
		"WEAPON_snspistol_mk2",  //0x88374054",---24
		"WEAPON_revolver_mk2",  //0xCB96392F",----29
		"WEAPON_smg_mk2",  //0x78A97CD0",-----40
		"WEAPON_pumpshotgun_mk2",  //0x555AF99A",-----------47
		"WEAPON_assaultrifle_mk2",  //0x394F415C",-------57
		"WEAPON_carbinerifle_mk2",  //0xFAD1F1C9",------59
		"WEAPON_specialcarbine_mk2",  //0x969C3D67",------62
		"WEAPON_bullpuprifle_mk2",  //0x84D6FAFD",----64
		"WEAPON_combatmg_mk2",  //0xDBBD7280",------71
		"WEAPON_heavysniper_mk2",  //0xA914799",---75
		"WEAPON_marksmanrifle_mk2"  //0x6A6C02E0"--77
	};
	bool WeaponIsMk2(Hash WeapHash)
	{
		bool b = false;
		for (int i = 0; i < Mk2Weaps.size(); i++)
		{
			if (MyHashKey(Mk2Weaps[i]) == WeapHash)
				b = true;
		}

		return b;
	}
	void ReturnPlayerWeapons()
	{
		if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) != 28)
		{
			for (int i = 0; i < (int)Player_Weaps.size(); i++)
			{
				Hash MyWeap = MyHashKey(Player_Weaps[i].MyWeapon);
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), MyWeap, 0, false, true);
				WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), MyWeap, true);
				for (int j = 0; j < (int)Player_Weaps[i].MyAddons.size(); j++)
				{
					Hash MyAdon = MyHashKey(Player_Weaps[i].MyAddons[j]);
					if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT, MyWeap, MyAdon)
						WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MyWeap, MyAdon);

				}
				if (WeaponIsMk2(MyWeap))
					WAIT(500);
				//int Yourammo;
				//WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), MyHashKey(Player_Weaps[i].MyWeapon), &Yourammo);
				WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), MyWeap, Player_Weaps[i].Ammo);
				WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), MyWeap, WEAPON::GET_MAX_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), MyWeap, true));
			}
			//WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE(PLAYER::PLAYER_PED_ID(), false, true, true, true);
			WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), -1569615261, true);
		}
	}

	const std::vector<Mod_Class::AnimatedActions> MaleDance01 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_male^5"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_male^6"),
	};
	const std::vector<Mod_Class::AnimatedActions> MaleDance02 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_male^6")
	};
	const std::vector<Mod_Class::AnimatedActions> MaleDance03 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_male^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_male^6")
	};

	const std::vector<Mod_Class::AnimatedActions> FemaleDance01 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_09_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_11_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_13_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_15_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@low_intesnsity", "li_dance_facedj_17_v2_female^6")
	};
	const std::vector<Mod_Class::AnimatedActions> FemaleDance02 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_09_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_11_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_13_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_15_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@med_intensity", "mi_dance_facedj_17_v1_female^6")
	};
	const std::vector<Mod_Class::AnimatedActions> FemaleDance03 = {
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_09_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_11_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_13_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_15_v2_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v1_female^6"),

		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^1"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^2"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^3"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^4"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^5"),
		Mod_Class::AnimatedActions("anim@amb@nightclub@dancers@crowddance_facedj@hi_intensity", "hi_dance_facedj_17_v2_female^6")
	};

	bool VehicleEnter = false;
	int iFindingTime;
	void GetInVehicle(Ped Peddy, Vehicle Vhick, int Seat, bool clearSeat)
	{
		LoggerLight("PlayerEnterVeh");

		iFindingTime = InGameTime() + 30000;

		if (clearSeat)
			GetOutVehicle(VEHICLE::GET_PED_IN_VEHICLE_SEAT(Vhick, Seat));

		AI::TASK_ENTER_VEHICLE(Peddy, Vhick, -1, Seat, 1.0f, 1, 0);
		while (!(bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
		{
			WAIT(1000);
			if (iFindingTime < InGameTime())
			{
				WarptoAnyVeh(Vhick, Peddy, Seat);
				break;
			}
		}
	}
	void PlayerEnterVeh(Vehicle Vhick)
	{
		VehicleEnter = true;
		int iSeats = FindUSeat(Vhick);
		GetInVehicle(PLAYER::PLAYER_PED_ID(), Vhick, iSeats, false);
		VehicleEnter = false;
	}
	
	void WalkingStyle(Ped myPEd, const std::string& Anim)
	{
		PED::SET_PED_MOVEMENT_CLIPSET(myPEd, (LPSTR)Anim.c_str(), 1.0f);
	}
	void ForceAnim(Ped peddy, const std::string& sAnimDict, const std::string& sAnimName, Vector3 AnPos, Vector3 AnRot)
	{
		AI::CLEAR_PED_TASKS(peddy);
		STREAMING::REQUEST_ANIM_DICT((LPSTR)sAnimDict.c_str());
		int iFailed = InGameTime() + 5000;
		bool bFine = true;
		while (!STREAMING::HAS_ANIM_DICT_LOADED((LPSTR)sAnimDict.c_str()))
		{
			if (iFailed < InGameTime())
			{
				bFine = false;
				break;
			}
			WAIT(1);
		}

		if (bFine)
			AI::TASK_PLAY_ANIM_ADVANCED(peddy, (LPSTR)sAnimDict.c_str(), (LPSTR)sAnimName.c_str(), AnPos.x, AnPos.y, AnPos.z, AnRot.x, AnRot.y, AnRot.z, 8.0f, 0.0f, -1, 0, 0.01f, 0, 0);
		STREAMING::REMOVE_ANIM_DICT((LPSTR)sAnimDict.c_str());
	}
	void ForceAnim(Ped peddy, const std::string& sAnimDict, const std::string& sAnimName, Mod_Class::Vector4 AnPos)
	{
		ForceAnim(peddy, sAnimDict, sAnimName, Mod_Maths::NewVector3(AnPos.X, AnPos.Y, AnPos.Z), Mod_Maths::NewVector3(0.0f, 0.0f, AnPos.R));
	}
	void ForceAnim(Ped peddy, Mod_Class::AnimatedActions sAnim, Mod_Class::Vector4 AnPos)
	{
		ForceAnim(peddy, sAnim.Libary, sAnim.Action, Mod_Maths::NewVector3(AnPos.X, AnPos.Y, AnPos.Z), Mod_Maths::NewVector3(0.0f, 0.0f, AnPos.R));
	}
	void ForceSenario(const std::string& senareo, Mod_Class::Vector4 vpos, bool sitting)
	{
		Ped peddy = PLAYER::PLAYER_PED_ID();
		AI::TASK_START_SCENARIO_AT_POSITION(peddy, (LPSTR)senareo.c_str(), vpos.X, vpos.Y, vpos.Z, vpos.R, -1, sitting, true);
		while (true)
		{
			Mod_Ui::TopLeft(RSLangMenu[188]);
			if ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;
			else if (WhileButtonDown(75, true))
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(peddy);
				AI::CLEAR_PED_TASKS(peddy);
				AI::STOP_ANIM_PLAYBACK(peddy, 0, 0);
				break;
			}
			WAIT(1);
		}
	}
	void AddSenario(Ped Peddy, const std::string& senareo, Mod_Class::Vector4 vpos)
	{
		AI::TASK_START_SCENARIO_AT_POSITION(Peddy, (LPSTR)senareo.c_str(), vpos.X, vpos.Y, vpos.Z, vpos.R, -1, true, true);
	}
	void RunAnimSeq(Mod_Class::AnimList myAnim, Mod_Class::Vector4 pos)
	{
		int iPause = 0;
		Ped peddy = PLAYER::PLAYER_PED_ID();
		ForceAnim(peddy, myAnim.Start.Libary, myAnim.Start.Action, pos);
		CAM::DO_SCREEN_FADE_IN(1000);
		while (true)
		{
			if ((int)myAnim.Middle.size() > 0)
				Mod_Ui::TopLeft(RSLangMenu[212]);
			else
				Mod_Ui::TopLeft(RSLangMenu[188]);

			if (Mod_Systems::WhileButtonDown(75, false) || (bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;
			else if (!AI::GET_IS_TASK_ACTIVE(peddy, 134) || Mod_Systems::ButtonDown(46, false))
			{
				if (iPause < InGameTime())
				{
					iPause = InGameTime() + 2000;
					if ((int)myAnim.Middle.size() > 0)
					{
						int iBe = LessRandomInt("RN_" + myAnim.Start.Libary, 0, (int)myAnim.Middle.size() - 1);
						ForceAnim(peddy, myAnim.Middle[iBe].Libary, myAnim.Middle[iBe].Action, pos);
					}
					else
						ForceAnim(peddy, myAnim.Start.Libary, myAnim.Start.Action, pos);
				}
			}
			WAIT(1);
		}
		ForceAnim(peddy, myAnim.End.Libary, myAnim.End.Action, pos);

		iPause = InGameTime() + 6000;
		while (AI::GET_IS_TASK_ACTIVE(peddy, 134))
		{
			if (iPause < InGameTime())
				break;
			WAIT(1);
		}
		WAIT(2500);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(peddy);
		AI::CLEAR_PED_TASKS(peddy);
		AI::STOP_ANIM_PLAYBACK(peddy, 0, 0);
	}
	void DanceDanceDance(Ped Dancer)
	{
		Mod_Class::Vector4 DanceHere = Mod_Maths::GetPosV4(Dancer);
		int iRanSpeed = LessRandomInt("DanceDanceDance01", 1, 3);
		if (PED::IS_PED_MALE(Dancer))
		{
			if (iRanSpeed == 1)
				ForceAnim(Dancer, MaleDance01[LessRandomInt("DanceDanceM01", 0, (int)MaleDance01.size() - 1)], DanceHere);
			else if (iRanSpeed == 2)
				ForceAnim(Dancer, MaleDance02[LessRandomInt("DanceDanceM02", 0, (int)MaleDance02.size() - 1)], DanceHere);
			else
				ForceAnim(Dancer, MaleDance03[LessRandomInt("DanceDanceM03", 0, (int)MaleDance03.size() - 1)], DanceHere);
		}
		else
		{
			if (iRanSpeed == 1)
				ForceAnim(Dancer, FemaleDance01[LessRandomInt("DanceDanceF01", 0, (int)FemaleDance01.size() - 1)], DanceHere);
			else if (iRanSpeed == 2)
				ForceAnim(Dancer, FemaleDance02[LessRandomInt("DanceDanceF02", 0, (int)FemaleDance02.size() - 1)], DanceHere);
			else
				ForceAnim(Dancer, FemaleDance03[LessRandomInt("DanceDanceF03", 0, (int)FemaleDance03.size() - 1)], DanceHere);
		}
	}
	void TakeAChair(Ped Sitter, Mod_Class::Vector4 ChairPos)
	{
		ChairPos.R -= 180.0f;
		AddSenario(Sitter, "PROP_HUMAN_SEAT_CHAIR", ChairPos);
	}
	void SunningIt(Ped Sitter, Mod_Class::Vector4 ChairPos)
	{
		int iTurn = LessRandomInt("SunningIt", 1, 5);
		if (iTurn < 3)
		{
			if (PED::IS_PED_MALE(Sitter))
				ForceAnim(Sitter, SunbathefrontM.Middle[0].Libary, SunbathefrontM.Middle[0].Action, ChairPos);
			else
				ForceAnim(Sitter, SunbathefrontF.Middle[0].Libary, SunbathefrontF.Middle[0].Action, ChairPos);
		}
		else
		{
			if (PED::IS_PED_MALE(Sitter))
				ForceAnim(Sitter, SunbathebackM.Middle[0].Libary, SunbathebackM.Middle[0].Action, ChairPos);
			else
				ForceAnim(Sitter, SunbathebackF.Middle[0].Libary, SunbathebackF.Middle[0].Action, ChairPos);
		}
	}

	void PlayHorn(Vehicle Vic, int duration)
	{
		VEHICLE::START_VEHICLE_HORN(Vic, duration, MyHashKey("HELDDOWN"), 0);
	}
	int LandingGear(Vehicle Vic)
	{
		//	0: Deployed
		//	1 : Closing
		//	2 : Opening
		//	3 : Retracted
		return VEHICLE::_GET_VEHICLE_LANDING_GEAR(Vic);
	}
	void LandNearHeli(Ped Peddy, Vehicle vHick, Vector3 vTarget)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		float HeliDesX = vTarget.x;
		float HeliDesY = vTarget.y;
		float HeliDesZ = vTarget.z;
		float HeliSpeed = 35;
		float HeliLandArea = 10;
		Vector3 VHickPos = ENTITY::GET_ENTITY_COORDS(vHick, true);
		float dx = VHickPos.x - HeliDesX;
		float dy = VHickPos.y - HeliDesY;

		float HeliDirect = GAMEPLAY::GET_HEADING_FROM_VECTOR_2D(dx, dy) - 180.00f;


		AI::TASK_HELI_MISSION(Peddy, vHick, 0, 0, HeliDesX, HeliDesY, HeliDesZ, 20, HeliSpeed, HeliLandArea, HeliDirect, -1, -1, -1, 32);

		PED::SET_PED_FIRING_PATTERN(Peddy, MyHashKey("FIRING_PATTERN_BURST_FIRE_HELI"));

		PED::SET_PED_KEEP_TASK(Peddy, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Peddy, true);
	}
	void LandNearPlane(Ped Peddy, Vehicle vHick, Vector3 vStart, Vector3 vFinish)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		AI::TASK_PLANE_LAND(Peddy, vHick, vStart.x, vStart.y, vStart.z, vFinish.x, vFinish.y, vFinish.z);
		PED::SET_PED_KEEP_TASK(Peddy, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Peddy, true);
	}

	void WalkHere(Ped Peddy, Mod_Class::Vector4 Dest)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		AI::TASK_FOLLOW_NAV_MESH_TO_COORD(Peddy, Dest.X, Dest.Y, Dest.Z, 1.0, -1, 0.0, false, 0.0);
		PED::SET_PED_KEEP_TASK(Peddy, true);
	}
	void RunHere(Ped Peddy, Vector3 Dest)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		AI::TASK_FOLLOW_NAV_MESH_TO_COORD(Peddy, Dest.x, Dest.y, Dest.z, 2.0, -1, 0.0, false, 0.0);
		PED::SET_PED_KEEP_TASK(Peddy, true);
	}
	void DriveAround(Ped Peddy)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
		{
			if (Peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(Peddy), -1))
			{
				Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(Peddy, false);

				AI::TASK_VEHICLE_DRIVE_WANDER(Peddy, Vick, 25, 262972);
				PED::SET_PED_KEEP_TASK(Peddy, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Peddy, true);
			}
		}

	}
	void DriveToooPed(Ped Peddy, Ped Target, bool bRunOver)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
		{
			if (Peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(Peddy), -1))
			{
				Vector3 PlayerPos = ENTITY::GET_ENTITY_COORDS(Target, true);
				Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(Peddy, false);
				if (bRunOver)
					AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Peddy, Vick, PlayerPos.x, PlayerPos.y, PlayerPos.z, 45, 262972, 0);
				else
					AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Peddy, Vick, PlayerPos.x, PlayerPos.y, PlayerPos.z, 25, 262972, 0);

				//PED::SET_PED_KEEP_TASK(Peddy, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Peddy, true);
			}
		}
	}
	void DriveBye(Ped Peddy, Ped Target, int iVeh)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
		{
			if (Peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(Peddy), -1))
			{
				if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Target, 0))
					AI::TASK_VEHICLE_CHASE(Peddy, Target);
				else
					DriveToooPed(Peddy, Target, true);
			}

			AI::TASK_VEHICLE_SHOOT_AT_PED(Peddy, Target, 5);
			//PED::SET_PED_KEEP_TASK(Peddy, true);
			bool blocking = false;
			if (iVeh == 6)
				blocking = true;
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Peddy, blocking);
		}
	}
	void FlyHeli(Ped Pedd, Vehicle Vhick, Vector3 vHeliDest, float fSpeed, float flanding)
	{
		ENTITY::FREEZE_ENTITY_POSITION(Vhick, false);
		AI::CLEAR_PED_TASKS(Pedd);
		float HeliDesX = vHeliDest.x;
		float HeliDesY = vHeliDest.y;
		float HeliDesZ = vHeliDest.z;
		float HeliSpeed = fSpeed;
		float HeliLandArea = flanding;

		Vector3 VHickPos = Mod_Maths::EntPosition(Vhick);

		float dx = VHickPos.x - HeliDesX;
		float dy = VHickPos.y - HeliDesY;
		float HeliDirect = GAMEPLAY::GET_HEADING_FROM_VECTOR_2D(dx, dy) - 180.00f;

		AI::TASK_HELI_MISSION(Pedd, Vhick, 0, 0, HeliDesX, HeliDesY, HeliDesZ, 9, HeliSpeed, HeliLandArea, HeliDirect, -1, -1, -1, 0);
		PED::SET_PED_FIRING_PATTERN(Pedd, MyHashKey("FIRING_PATTERN_BURST_FIRE_HELI"));
		PED::SET_PED_KEEP_TASK(Pedd, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Pedd, true);
	}
	void FlyPlane(Ped Pedd, Vehicle Vhick, Vector3 vPlaneDest)
	{
		float fAngle = Mod_Maths::GetAngle(ENTITY::GET_ENTITY_COORDS(Vhick, true), vPlaneDest);
		AI::CLEAR_PED_TASKS(Pedd);

		AI::TASK_PLANE_MISSION(Pedd, Vhick, 0, 0, vPlaneDest.x, vPlaneDest.y, vPlaneDest.z, 6, 20, 50, fAngle, 50, 1);

		PED::SET_PED_KEEP_TASK(Pedd, true);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Pedd, true);
	}
	void DriveToooDest(Ped Peddy, Vector3 Vme, float fSpeed)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
		{
			Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(Peddy, false);
			if (Peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(Peddy), -1))
			{
				AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Peddy, Vick, Vme.x, Vme.y, Vme.z, fSpeed, 262972, 1);
				PED::SET_PED_KEEP_TASK(Peddy, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Peddy, true);
			}
		}
	}
	void DriveDirect(Ped Peddy, Vector3 Vme, float fSpeed)
	{
		AI::CLEAR_PED_TASKS(Peddy);
		if ((bool)PED::IS_PED_IN_ANY_VEHICLE(Peddy, 0))
		{
			Vehicle Vick = PED::GET_VEHICLE_PED_IS_IN(Peddy, false);
			if (Peddy == VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_USING(Peddy), -1))
			{
				AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Peddy, Vick, Vme.x, Vme.y, Vme.z, fSpeed, 16777216, 1);
				PED::SET_PED_KEEP_TASK(Peddy, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Peddy, true);
			}
		}
	}
	void PedDoGetIn(Vehicle GetV, Ped Peddy, const std::string& sId)
	{
		int iSeats = FindUSeat(GetV);
		Vector3 PedPos = ENTITY::GET_ENTITY_COORDS(Peddy, true);
		Vector3 VehPos = ENTITY::GET_ENTITY_COORDS(GetV, true);

		if (iSeats > -1)
		{
			if (Mod_Maths::DistanceTo(PedPos, VehPos) < 65.00)
			{
				GetInVehicle(Peddy, GetV, iSeats, false);
			}
			else
				WarptoAnyVeh(GetV, Peddy, iSeats);
		}
	}
	void FightPlayer(Ped Peddy, bool bInVeh, int PrefVeh)
	{
		Ped Player = PLAYER::PLAYER_PED_ID();
		PED::REMOVE_PED_FROM_GROUP(Peddy);
		PED::SET_PED_RELATIONSHIP_GROUP_HASH(Peddy, GP_Attack);
		//AI::CLEAR_PED_TASKS_IMMEDIATELY(Peddy);
		PED::SET_PED_FLEE_ATTRIBUTES(Peddy, 0, 1);
		PED::SET_PED_COMBAT_ATTRIBUTES(Peddy, 46, 1);
		if (!bInVeh)
			AI::TASK_COMBAT_PED(Peddy, Player, 0, 16);
		else
			DriveBye(Peddy, Player, PrefVeh);
	}
	void GreefWar(Ped Peddy, Ped Victim)
	{
		if (Victim != NULL)
		{
			AI::CLEAR_PED_TASKS(Peddy);
			PED::SET_PED_FLEE_ATTRIBUTES(Peddy, 0, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(Peddy, 46, true);

			AI::TASK_COMBAT_PED(Peddy, Victim, 0, 16);
		}
	}
	void JogOn(std::vector<Mod_Class::Vector4>& Route, int start)
	{
		MoveEntity(PLAYER::PLAYER_PED_ID(), Route[start]);
		while (true)
		{
			Mod_Ui::TopLeft(RSLangMenu[188]);
			if (Mod_Systems::WhileButtonDown(75, true) || (bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
				break;
			else if (Mod_Maths::DistanceTo(PLAYER::PLAYER_PED_ID(), Route[start]) < 3.0f)
			{
				if (start < Route.size())
					start++;
				else
					start = 0;

				RunHere(PLAYER::PLAYER_PED_ID(), Mod_Maths::NewVector3(Route[start].X, Route[start].Y, Route[start].Z));
			}
			WAIT(1);
		}
		ForceSenario("WORLD_HUMAN_JOG_STANDING", Mod_Maths::PlayerV4(), false);
		WAIT(4000);
		AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
	}
	void Drive_Fly_On(Ped peddy, Vehicle vic, std::vector<Mod_Class::Vector4>& Route, bool plane, bool heli, bool playerDrives, int start)
	{
		if (plane)
			FlyPlane(peddy, vic, Mod_Maths::NewVector3(Route[start].X, Route[start].Y, Route[start].Z));
		else if (heli)
			FlyHeli(peddy, vic, Mod_Maths::NewVector3(Route[start].X, Route[start].Y, Route[start].Z), 45.0f, 5.0f);
		else
			DriveToooDest(peddy, Mod_Maths::NewVector3(Route[start].X, Route[start].Y, Route[start].Z), 25.0f);

		while (true)
		{
			if (playerDrives)
			{
				Mod_Ui::TopLeft(RSLangMenu[188]);
				if (WhileButtonDown(75, true) || (bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), true))
					break;
			}

			if (Mod_Maths::DistanceTo(PLAYER::PLAYER_PED_ID(), vic) > 50.0f)
				break;

			if (Mod_Maths::DistanceTo(vic, Route[start]) < 3.0f)
			{
				start++;
				if (start >= Route.size())
					start = 0;

				if (plane)
					FlyPlane(peddy, vic, Mod_Maths::NewVector3(Route[start].X, Route[start].Y, Route[start].Z));
				else if (heli)
					FlyHeli(peddy, vic, Mod_Maths::NewVector3(Route[start].X, Route[start].Y, Route[start].Z), 45.0f, 5.0f);
				else
					DriveToooDest(peddy, Mod_Maths::NewVector3(Route[start].X, Route[start].Y, Route[start].Z), 25.0f);
			}
			WAIT(1);
		}

		if (playerDrives)
			AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
	}
	void MethEdd(bool Act)
	{
		if (Act)
		{
			int iTenPass = 10;
			GRAPHICS::SET_TIMECYCLE_MODIFIER("DRUG_gas_huffin");
			while (!STREAMING::HAS_ANIM_SET_LOADED("move_m@drunk@moderatedrunk") || iTenPass < 0)
			{
				iTenPass -= 1;
				STREAMING::REQUEST_ANIM_SET("move_m@drunk@moderatedrunk");
				WAIT(100);
			}
			PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_m@drunk@moderatedrunk", 1.00f);
		}
		else
		{
			GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
			PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 0.0f);
		}
	}

	void GunningIt(Ped Peddy, int iGun)
	{
		LoggerLight("GunningIt Gun == " + std::to_string(iGun));

		std::vector<std::string> sWeapList = {};

		if (iGun == 1)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt01", 1, 17)]);//Meelee
		}
		else if (iGun == 2)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt02", 18, 37)]);//HandGuns
		}
		else if (iGun == 3)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt01", 1, 17)]);//Meelee
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt02", 18, 37)]);//HandGuns
		}
		else if (iGun == 4)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt04", 46, 55)]);//ShotGun
		}
		else if (iGun == 5)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt01", 1, 17)]);//Meelee
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt02", 18, 37)]);//HandGuns
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt07", 73, 78)]);//sniper
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt08", 79, 87)]);//Heavey
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt09", 88, 94)]);//throw
		}
		else if (iGun == 6)
		{
			sWeapList.push_back("WEAPON_golfclub");//golf
		}
		else if (iGun == 7)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt01", 1, 17)]);//Meelee
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt03", 38, 45)]);//Smg
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt05", 56, 68)]);//riflles
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt06", 69, 72)]);//Mg
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt07", 73, 78)]);//sniper
		}
		else if (iGun == 8)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt07", 73, 78)]);//sniper
		}
		else if (iGun == 9)
		{
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt01", 1, 17)]);//Meelee
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt02", 18, 37)]);//HandGuns
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt03", 38, 45)]);//Smg
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt04", 46, 55)]);//ShotGun
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt05", 56, 68)]);//riflles
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt06", 69, 72)]);//Mg
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt07", 73, 78)]);//sniper
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt08", 79, 87)]);//Heavey
			sWeapList.push_back(Weapons_List[LessRandomInt("GunIt09", 88, 94)]);//throw
		}
		else if (iGun == 10)
		{
			sWeapList.push_back("WEAPON_raypistol");  //0xAF3696A1",--36
			sWeapList.push_back("WEAPON_raycarbine");  //0x476BF155"--44
			sWeapList.push_back("weapon_rayminigun");
		}
		else if (iGun == 50)
			ReturnPlayerWeapons();

		for (int i = 0; i < sWeapList.size(); i++)
			WEAPON::GIVE_WEAPON_TO_PED(Peddy, MyHashKey(sWeapList[i]), 9999, false, true);
	}
	void MaxOutAllModsNoWheels(Vehicle Vehic, int cT)
	{
		LoggerLight("MaxOutAllModsNoWheels");

		VEHICLE::SET_VEHICLE_MOD_KIT(Vehic, 0);
		for (int i = 0; i < 50; i++)
		{
			int iSpoilher = VEHICLE::GET_NUM_VEHICLE_MODS(Vehic, i);

			if (i == 18 || i == 22 || i == 23 || i == 24)
			{

			}
			else
			{
				iSpoilher -= 1;
				VEHICLE::SET_VEHICLE_MOD(Vehic, i, iSpoilher, true);
			}
		}

		if (cT != 13 && cT != 14 && cT != 15 && cT != 16)
		{
			VEHICLE::TOGGLE_VEHICLE_MOD(Vehic, 18, true);
			VEHICLE::TOGGLE_VEHICLE_MOD(Vehic, 22, true);
		}
		else if (cT == 15 || cT == 16)
			VEHICLE::_SET_VEHICLE_LANDING_GEAR(Vehic, 3);
	}
	void MakeModsNotWar(Vehicle Vehic, std::vector<int>& MyMods)
	{
		LoggerLight("MakeModsNotWar");

		VEHICLE::SET_VEHICLE_MOD_KIT(Vehic, 0);

		for (int i = 0; i < MyMods.size(); i++)
		{
			if (MyMods[i] == -10)
			{

			}
			else if (i == 48)
			{
				int iSpoilher = -1;
				if (MyMods[i] == -1)
				{
					iSpoilher = VEHICLE::GET_NUM_VEHICLE_MODS(Vehic, i) - 1;
					if (iSpoilher < 1)
						iSpoilher = VEHICLE::GET_VEHICLE_LIVERY_COUNT(Vehic) - 1;

					if (iSpoilher > 0)
					{
						MyMods[i] = RandomInt(0, iSpoilher);
					}
				}

				if (iSpoilher > -1 || MyMods[i] > -1)
				{
					VEHICLE::SET_VEHICLE_LIVERY(Vehic, MyMods[i]);
					VEHICLE::SET_VEHICLE_MOD(Vehic, i, MyMods[i], true);
				}
			}
			else if (i == 66)
			{
				if (MyMods[i] == -1)
				{
					int iCheckHere = RandomInt(0, 159);
					MyMods[i] = iCheckHere;
				}
			}
			else if (i == 67)
			{
				if (MyMods[i] == -1)
				{
					int iCheckHere = RandomInt(0, 159);
					VEHICLE::SET_VEHICLE_COLOURS(Vehic, MyMods[i - 1], iCheckHere);
				}
				else
				{
					VEHICLE::SET_VEHICLE_COLOURS(Vehic, MyMods[i - 1], MyMods[i]);
				}
			}
			else if (MyMods[i] == -1)
			{
				int iSpoilher = VEHICLE::GET_NUM_VEHICLE_MODS(Vehic, i) - 1;
				if (iSpoilher > 0)
				{
					int iCheckHere = RandomInt(0, iSpoilher);
					VEHICLE::SET_VEHICLE_MOD(Vehic, i, iCheckHere, true);
				}
			}
			else
			{
				VEHICLE::SET_VEHICLE_MOD(Vehic, i, MyMods[i], true);
			}
		}
	}

	void PoliceAcadamy(bool togg)
	{
		if (togg)
		{
			PED::SET_PED_AS_COP(PLAYER::PLAYER_PED_ID(), togg);
			//PLAYER::_0xDC64D2C53493ED12(PLAYER::PLAYER_ID());
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(PLAYER::PLAYER_PED_ID(), MyHashKey("COP"));
		}
		else if (!Mod_Settings.Saved_Ped && !Mod_Settings.Random_Ped)
			SavedPlayer(&SavedPeds[0], 50);
		PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), togg);
	}

	const std::vector<Mod_Class::HairSets> MHairsets = {
		Mod_Class::HairSets(1, 0, "H_FMM_1_0", "Buzzcut Dark Brown", -1, -1),
		Mod_Class::HairSets(1, 1, "H_FMM_1_1", "Buzzcut Light Brown", -1, -1),
		Mod_Class::HairSets(1, 2, "H_FMM_1_2", "Buzzcut Auburn", -1, -1),
		Mod_Class::HairSets(1, 3, "H_FMM_1_3", "Buzzcut Blond", -1, -1),
		Mod_Class::HairSets(1, 4, "H_FMM_1_4", "Buzzcut Black", -1, -1),
		Mod_Class::HairSets(2, 0, "H_FMM_2_0", "Faux Hawk Dark Brown", -1, -1),
		Mod_Class::HairSets(2, 1, "H_FMM_2_1", "Faux Hawk Light Brown", -1, -1),
		Mod_Class::HairSets(2, 2, "H_FMM_2_2", "Faux Hawk Auburn", -1, -1),
		Mod_Class::HairSets(2, 3, "H_FMM_2_3", "Faux Hawk Blond", -1, -1),
		Mod_Class::HairSets(2, 4, "H_FMM_2_4", "Faux Hawk Black", -1, -1),
		Mod_Class::HairSets(2, 5, "H_FMM_2_5", "Faux Hawk Purple", -1, -1),
		Mod_Class::HairSets(3, 0, "H_FMM_3_0", "Hipster Shaved Dark Brown", -1, -1),
		Mod_Class::HairSets(3, 1, "H_FMM_3_1", "Hipster Shaved Light Brown", -1, -1),
		Mod_Class::HairSets(3, 2, "H_FMM_3_2", "Hipster Shaved Auburn", -1, -1),
		Mod_Class::HairSets(3, 3, "H_FMM_3_3", "Hipster Shaved Blond", -1, -1),
		Mod_Class::HairSets(3, 4, "H_FMM_3_4", "Hipster Shaved Black", -1, -1),
		Mod_Class::HairSets(3, 5, "H_FMM_3_5", "Hipster Shaved Red", -1, -1),
		Mod_Class::HairSets(4, 0, "H_FMM_4_0", "Side Parting Spiked Dark Brown", -1, -1),
		Mod_Class::HairSets(4, 1, "H_FMM_4_1", "Side Parting Spiked Light Brown", -1, -1),
		Mod_Class::HairSets(4, 2, "H_FMM_4_2", "Side Parting Spiked Auburn", -1, -1),
		Mod_Class::HairSets(4, 3, "H_FMM_4_3", "Side Parting Spiked Blond", -1, -1),
		Mod_Class::HairSets(4, 4, "H_FMM_4_4", "Side Parting Spiked Black", -1, -1),
		Mod_Class::HairSets(4, 6, "H_FMM_4_6", "Side Parting Spiked Blue", -1, -1),
		Mod_Class::HairSets(5, 0, "H_FMM_5_0", "Shorter Cut Dark Brown", -1, -1),
		Mod_Class::HairSets(5, 1, "H_FMM_5_1", "Shorter Cut Light Brown", -1, -1),
		Mod_Class::HairSets(5, 2, "H_FMM_5_2", "Shorter Cut Auburn", -1, -1),
		Mod_Class::HairSets(5, 3, "H_FMM_5_3", "Shorter Cut Blond", -1, -1),
		Mod_Class::HairSets(5, 4, "H_FMM_5_4", "Shorter Cut Black", -1, -1),
		Mod_Class::HairSets(5, 5, "H_FMM_5_5", "Shorter Cut Green", -1, -1),
		Mod_Class::HairSets(6, 0, "H_FMM_6_0", "Biker Dark Brown", -1, -1),
		Mod_Class::HairSets(6, 1, "H_FMM_6_1", "Biker Light Brown", -1, -1),
		Mod_Class::HairSets(6, 2, "H_FMM_6_2", "Biker Auburn", -1, -1),
		Mod_Class::HairSets(6, 3, "H_FMM_6_3", "Biker Blond", -1, -1),
		Mod_Class::HairSets(6, 4, "H_FMM_6_4", "Biker Black", -1, -1),
		Mod_Class::HairSets(6, 5, "H_FMM_6_5", "Biker Purple Fade", -1, -1),
		Mod_Class::HairSets(7, 0, "H_FMM_7_0", "Ponytail Dark Brown", -1, -1),
		Mod_Class::HairSets(7, 1, "H_FMM_7_1", "Ponytail Light Brown", -1, -1),
		Mod_Class::HairSets(7, 2, "H_FMM_7_2", "Ponytail Auburn", -1, -1),
		Mod_Class::HairSets(7, 3, "H_FMM_7_3", "Ponytail Blond", -1, -1),
		Mod_Class::HairSets(7, 4, "H_FMM_7_4", "Ponytail Black", -1, -1),
		Mod_Class::HairSets(7, 6, "H_FMM_7_6", "Ponytail Purple", -1, -1),
		Mod_Class::HairSets(8, 0, "H_FMM_8_0", "Cornrows Dark Brown", -1, -1),
		Mod_Class::HairSets(8, 1, "H_FMM_8_1", "Cornrows Light Brown", -1, -1),
		Mod_Class::HairSets(8, 2, "H_FMM_8_2", "Cornrows Auburn", -1, -1),
		Mod_Class::HairSets(8, 3, "H_FMM_8_3", "Cornrows Blond", -1, -1),
		Mod_Class::HairSets(8, 4, "H_FMM_8_4", "Cornrows Black", -1, -1),
		Mod_Class::HairSets(9, 0, "H_FMM_9_0", "Slicked Dark Brown", -1, -1),
		Mod_Class::HairSets(9, 1, "H_FMM_9_1", "Slicked Light Brown", -1, -1),
		Mod_Class::HairSets(9, 2, "H_FMM_9_2", "Slicked Auburn", -1, -1),
		Mod_Class::HairSets(9, 3, "H_FMM_9_3", "Slicked Blond", -1, -1),
		Mod_Class::HairSets(9, 4, "H_FMM_9_4", "Slicked Black", -1, -1),
		Mod_Class::HairSets(9, 6, "H_FMM_9_6", "Slicked Red", -1, -1),
		Mod_Class::HairSets(10, 0, "H_FMM_10_0", "Short Brushed Dark Brown", -1, -1),
		Mod_Class::HairSets(10, 1, "H_FMM_10_1", "Short Brushed Light Brown", -1, -1),
		Mod_Class::HairSets(10, 2, "H_FMM_10_2", "Short Brushed Auburn", -1, -1),
		Mod_Class::HairSets(10, 3, "H_FMM_10_3", "Short Brushed Blond", -1, -1),
		Mod_Class::HairSets(10, 4, "H_FMM_10_4", "Short Brushed Black", -1, -1),
		Mod_Class::HairSets(11, 0, "H_FMM_11_0", "Spikey Dark Brown", -1, -1),
		Mod_Class::HairSets(11, 1, "H_FMM_11_1", "Spikey Light Brown", -1, -1),
		Mod_Class::HairSets(11, 2, "H_FMM_11_2", "Spikey Auburn", -1, -1),
		Mod_Class::HairSets(11, 3, "H_FMM_11_3", "Spikey Blond", -1, -1),
		Mod_Class::HairSets(11, 4, "H_FMM_11_4", "Spikey Black", -1, -1),
		Mod_Class::HairSets(11, 5, "H_FMM_11_5", "Spikey Blue", -1, -1),
		Mod_Class::HairSets(12, 0, "H_FMM_12_0", "Caesar Dark Brown", -1, -1),
		Mod_Class::HairSets(12, 1, "H_FMM_12_1", "Caesar Light Brown", -1, -1),
		Mod_Class::HairSets(12, 2, "H_FMM_12_2", "Caesar Auburn", -1, -1),
		Mod_Class::HairSets(12, 3, "H_FMM_12_3", "Caesar Blond", -1, -1),
		Mod_Class::HairSets(12, 4, "H_FMM_12_4", "Caesar Black", -1, -1),
		Mod_Class::HairSets(13, 0, "H_FMM_13_0", "Chopped Dark Brown", -1, -1),
		Mod_Class::HairSets(13, 1, "H_FMM_13_1", "Chopped Light Brown", -1, -1),
		Mod_Class::HairSets(13, 2, "H_FMM_13_2", "Chopped Auburn", -1, -1),
		Mod_Class::HairSets(13, 3, "H_FMM_13_3", "Chopped Blond", -1, -1),
		Mod_Class::HairSets(13, 4, "H_FMM_13_4", "Chopped Black", -1, -1),
		Mod_Class::HairSets(13, 5, "H_FMM_13_5", "Chopped Green", -1, -1),
		Mod_Class::HairSets(14, 0, "H_FMM_14_0", "Dreads Dark Brown", -1, -1),
		Mod_Class::HairSets(14, 1, "H_FMM_14_1", "Dreads Light Brown", -1, -1),
		Mod_Class::HairSets(14, 2, "H_FMM_14_2", "Dreads Auburn", -1, -1),
		Mod_Class::HairSets(14, 3, "H_FMM_14_3", "Dreads Blond", -1, -1),
		Mod_Class::HairSets(14, 4, "H_FMM_14_4", "Dreads Black", -1, -1),
		Mod_Class::HairSets(15, 0, "H_FMM_15_0", "Long Hair Dark Brown", -1, -1),
		Mod_Class::HairSets(15, 1, "H_FMM_15_1", "Long Hair Light Brown", -1, -1),
		Mod_Class::HairSets(15, 2, "H_FMM_15_2", "Long Hair Auburn", -1, -1),
		Mod_Class::HairSets(15, 3, "H_FMM_15_3", "Long Hair Blond", -1, -1),
		Mod_Class::HairSets(15, 4, "H_FMM_15_4", "Long Hair Black", -1, -1),
		Mod_Class::HairSets(15, 5, "H_FMM_15_5", "Long Hair Purple Fade", -1, -1),
		Mod_Class::HairSets(16, 0, "CLO_BBM_H_00", "Shaggy Curls Dark Brown", -1, -1),
		Mod_Class::HairSets(16, 1, "CLO_BBM_H_01", "Shaggy Curls Light Brown", -1, -1),
		Mod_Class::HairSets(16, 2, "CLO_BBM_H_02", "Shaggy Curls Auburn", -1, -1),
		Mod_Class::HairSets(16, 3, "CLO_BBM_H_03", "Shaggy Curls Blonde", -1, -1),
		Mod_Class::HairSets(16, 4, "CLO_BBM_H_04", "Shaggy Curls Black", -1, -1),
		Mod_Class::HairSets(17, 0, "CLO_BBM_H_05", "Surfer Dude Dark Brown", -1, -1),
		Mod_Class::HairSets(17, 1, "CLO_BBM_H_06", "Surfer Dude Light Brown", -1, -1),
		Mod_Class::HairSets(17, 2, "CLO_BBM_H_07", "Surfer Dude Auburn", -1, -1),
		Mod_Class::HairSets(17, 3, "CLO_BBM_H_08", "Surfer Dude Blonde", -1, -1),
		Mod_Class::HairSets(17, 4, "CLO_BBM_H_09", "Surfer Dude Black", -1, -1),
		Mod_Class::HairSets(18, 0, "CLO_BUS_H_0_0", "Short Side Part Dark Brown", -2086773, 224730392),
		Mod_Class::HairSets(18, 1, "CLO_BUS_H_0_1", "Short Side Part Light Brown", -2086773, 1988816738),
		Mod_Class::HairSets(18, 2, "CLO_BUS_H_0_2", "Short Side Part Auburn", -2086773, 736778786),
		Mod_Class::HairSets(18, 3, "CLO_BUS_H_0_3", "Short Side Part Blonde", -2086773, 439629494),
		Mod_Class::HairSets(18, 4, "CLO_BUS_H_0_4", "Short Side Part Black", -2086773, 1048444745),
		Mod_Class::HairSets(19, 0, "CLO_BUS_H_1_0", "High Slicked Sides Dark Brown", -2086773, 2140603469),
		Mod_Class::HairSets(19, 1, "CLO_BUS_H_1_1", "High Slicked Sides Light Brown", -2086773, -681528353),
		Mod_Class::HairSets(19, 2, "CLO_BUS_H_1_2", "High Slicked Sides Auburn", -2086773, 1006238992),
		Mod_Class::HairSets(19, 3, "CLO_BUS_H_1_3", "High Slicked Sides Blonde", -2086773, 214245031),
		Mod_Class::HairSets(19, 4, "CLO_BUS_H_1_4", "High Slicked Sides Black", -2086773, 689952604),
		Mod_Class::HairSets(20, 0, "CLO_HP_HR_0_0", "Long Slicked Dark Brown", -1398869298, 965649655),
		Mod_Class::HairSets(20, 1, "CLO_HP_HR_0_1", "Long Slicked Light Brown", -1398869298, 718800778),
		Mod_Class::HairSets(20, 2, "CLO_HP_HR_0_2", "Long Slicked Auburn", -1398869298, 1959959422),
		Mod_Class::HairSets(20, 3, "CLO_HP_HR_0_3", "Long Slicked Blonde", -1398869298, 1200177388),
		Mod_Class::HairSets(20, 4, "CLO_HP_HR_0_4", "Long Slicked Black", -1398869298, -1874439579),
		Mod_Class::HairSets(21, 0, "CLO_HP_HR_1_0", "Hipster Youth Dark Brown", -1398869298, -1679505893),
		Mod_Class::HairSets(21, 1, "CLO_HP_HR_1_1", "Hipster Youth Blonde", -1398869298, -1976229188),
		Mod_Class::HairSets(21, 2, "CLO_HP_HR_1_2", "Hipster Youth Auburn", -1398869298, 2037875009),
		Mod_Class::HairSets(21, 3, "CLO_HP_HR_1_3", "Hipster Youth Light Brown", -1398869298, -235146664),
		Mod_Class::HairSets(21, 4, "CLO_HP_HR_1_4", "Hipster Youth Black", -1398869298, -441853516),
		Mod_Class::HairSets(22, 0, "CLO_IND_H_0_0", "Mullet Dark Brown", -1, -1),
		Mod_Class::HairSets(22, 1, "CLO_IND_H_0_1", "Mullet Light Brown", -1, -1),
		Mod_Class::HairSets(22, 2, "CLO_IND_H_0_2", "Mullet Auburn", -1, -1),
		Mod_Class::HairSets(22, 3, "CLO_IND_H_0_3", "Mullet Blonde", -1, -1),
		Mod_Class::HairSets(22, 4, "CLO_IND_H_0_4", "Mullet Black", -1, -1),
		Mod_Class::HairSets(24, 0, "CLO_S1M_H_0_0", "Classic Cornrows", 62137527, 534771589),
		Mod_Class::HairSets(25, 0, "CLO_S1M_H_1_0", "Palm Cornrows", 62137527, -1340139519),
		Mod_Class::HairSets(26, 0, "CLO_S1M_H_2_0", "Lightning Cornrows", 62137527, -849980761),
		Mod_Class::HairSets(27, 0, "CLO_S1M_H_3_0", "Whipped Cornrows", 62137527, -551553478),
		Mod_Class::HairSets(28, 0, "CLO_S2M_H_0_0", "Zig Zag Cornrows", 1529191571, -1431204514),
		Mod_Class::HairSets(29, 0, "CLO_S2M_H_1_0", "Snail Cornrows", 1529191571, -1133334304),
		Mod_Class::HairSets(30, 0, "CLO_S2M_H_2_0", "Hightop", 1529191571, -1809784771),
		Mod_Class::HairSets(31, 0, "CLO_BIM_H_0_0", "Loose Swept Back", -240234547, 1431846777),
		Mod_Class::HairSets(32, 0, "CLO_BIM_H_1_0", "Undercut Swept Back", -240234547, -460168116),
		Mod_Class::HairSets(33, 0, "CLO_BIM_H_2_0", "Undercut Swept Side", -240234547, -311245907),
		Mod_Class::HairSets(34, 0, "CLO_BIM_H_3_0", "Spiked Mohawk", -240234547, -942031335),
		Mod_Class::HairSets(35, 0, "CLO_BIM_H_4_0", "Mod", -240234547, -644503216),
		Mod_Class::HairSets(36, 0, "CLO_BIM_H_5_0", "Layered Mod", -240234547, 211198653),
		Mod_Class::HairSets(37, 0, "CC_M_HS_1", "Buzzcut", 598190139, 739308497),
		Mod_Class::HairSets(38, 0, "CC_M_HS_2", "Faux Hawk", 598190139, 495343292),
		Mod_Class::HairSets(39, 0, "CC_M_HS_3", "Hipster", 598190139, -1686711653),
		Mod_Class::HairSets(40, 0, "CC_M_HS_4", "Side Parting", 598190139, 1187457341),
		Mod_Class::HairSets(41, 0, "CC_M_HS_5", "Shorter Cut", 598190139, 956403122),
		Mod_Class::HairSets(42, 0, "CC_M_HS_6", "Biker", 598190139, 1647042566),
		Mod_Class::HairSets(43, 0, "CC_M_HS_7", "Ponytail", 598190139, -461478743),
		Mod_Class::HairSets(44, 0, "CC_M_HS_8", "Cornrows", 598190139, -1883325653),
		Mod_Class::HairSets(45, 0, "CC_M_HS_9", "Slicked", 598190139, -2114248796),
		Mod_Class::HairSets(46, 0, "CC_M_HS_10", "Short Brushed", 598190139, 314228205),
		Mod_Class::HairSets(47, 0, "CC_M_HS_11", "Spikey", 598190139, 1503775674),
		Mod_Class::HairSets(48, 0, "CC_M_HS_12", "Caesar", 598190139, 1862399610),
		Mod_Class::HairSets(49, 0, "CC_M_HS_13", "Chopped", 598190139, 708472048),
		Mod_Class::HairSets(50, 0, "CC_M_HS_14", "Dreads", 598190139, -1207367545),
		Mod_Class::HairSets(51, 0, "CC_M_HS_15", "Long Hair", 598190139, 111650251),
		Mod_Class::HairSets(52, 0, "CLO_BBM_H_00", "Shaggy Curls Dark Brown", -1, -1),
		Mod_Class::HairSets(53, 0, "CLO_BBM_H_05", "Surfer Dude Dark Brown", -1, -1),
		Mod_Class::HairSets(54, 0, "CLO_BUS_H_0_0", "Short Side Part Dark Brown", -2086773, 224730392),
		Mod_Class::HairSets(55, 0, "CLO_BUS_H_1_0", "High Slicked Sides Dark Brown", -2086773, 2140603469),
		Mod_Class::HairSets(56, 0, "CLO_HP_HR_0_0", "Long Slicked Dark Brown", -1398869298, 965649655),
		Mod_Class::HairSets(57, 0, "CLO_HP_HR_1_0", "Hipster Youth Dark Brown", -1398869298, -1679505893),
		Mod_Class::HairSets(58, 0, "CLO_IND_H_0_0", "Mullet Dark Brown", -1, -1),
		Mod_Class::HairSets(59, 0, "CLO_S1M_H_0_0", "Classic Cornrows", 62137527, 534771589),
		Mod_Class::HairSets(60, 0, "CLO_S1M_H_1_0", "Palm Cornrows", 62137527, -1340139519),
		Mod_Class::HairSets(61, 0, "CLO_S1M_H_2_0", "Lightning Cornrows", 62137527, -849980761),
		Mod_Class::HairSets(62, 0, "CLO_S1M_H_3_0", "Whipped Cornrows", 62137527, -551553478),
		Mod_Class::HairSets(63, 0, "CLO_S2M_H_0_0", "Zig Zag Cornrows", 1529191571, -1431204514),
		Mod_Class::HairSets(64, 0, "CLO_S2M_H_1_0", "Snail Cornrows", 1529191571, -1133334304),
		Mod_Class::HairSets(65, 0, "CLO_S2M_H_2_0", "Hightop", 1529191571, -1809784771),
		Mod_Class::HairSets(66, 0, "CLO_BIM_H_0_0", "Loose Swept Back", -240234547, 1431846777),
		Mod_Class::HairSets(67, 0, "CLO_BIM_H_1_0", "Undercut Swept Back", -240234547, -460168116),
		Mod_Class::HairSets(68, 0, "CLO_BIM_H_2_0", "Undercut Swept Side", -240234547, -311245907),
		Mod_Class::HairSets(69, 0, "CLO_BIM_H_3_0", "Spiked Mohawk", -240234547, -942031335),
		Mod_Class::HairSets(70, 0, "CLO_BIM_H_4_0", "Mod", -240234547, -644503216),
		Mod_Class::HairSets(71, 0, "CLO_BIM_H_5_0", "Layered Mod", -240234547, 211198653),
		Mod_Class::HairSets(72, 0, "CLO_GRM_H_0_0", "Flattop", 1616273011, -1119221482),
		Mod_Class::HairSets(73, 0, "CLO_GRM_H_1_0", "Military Buzzcut", 1616273011, -1642199958),
		Mod_Class::HairSets(74, 0, "CLO_VWM_H_0_0", "Impotent Rage", 1347816957, -599666460),
		Mod_Class::HairSets(75, 0, "CLO_TRM_H_0_0", "Afro Faded", -1970774728, -416636904),
		Mod_Class::HairSets(76, 0, "CLO_FXM_H_0_0", "Top Knot", 601646824, 1334100948),
		Mod_Class::HairSets(77, 0, "CLO_SBM_H_0_0", "Two Block", 987639353, -1927370417),
		Mod_Class::HairSets(78, 0, "CLO_SBM_H_1_0", "Shaggy Mullet", 987639353, -1088161005)
	};
	const std::vector<Mod_Class::HairSets> FHairsets = {
		Mod_Class::HairSets(1, 0, "H_FMF_1_0","Short Chestnut", -1, -1),
		Mod_Class::HairSets(1, 1, "H_FMF_1_1","Short Blonde", -1, -1),
		Mod_Class::HairSets(1, 2, "H_FMF_1_2","Short Auburn", -1, -1),
		Mod_Class::HairSets(1, 3, "H_FMF_1_3","Short Black", -1, -1),
		Mod_Class::HairSets(1, 4, "H_FMF_1_4","Short Brown", -1, -1),
		Mod_Class::HairSets(1, 5, "H_FMF_1_5","Short Purple", -1, -1),

		Mod_Class::HairSets(2, 0, "H_FMF_2_0","Layered Bob Chestnut", -1, -1),
		Mod_Class::HairSets(2, 1, "H_FMF_2_1","Layered Bob Blonde", -1, -1),
		Mod_Class::HairSets(2, 2, "H_FMF_2_2","Layered Bob Auburn", -1, -1),
		Mod_Class::HairSets(2, 3, "H_FMF_2_3","Layered Bob Black", -1, -1),
		Mod_Class::HairSets(2, 4, "H_FMF_2_4","Layered Bob Brown", -1, -1),
		Mod_Class::HairSets(2, 5, "H_FMF_2_5","Layered Bob Green", -1, -1),

		Mod_Class::HairSets(3, 0, "H_FMF_3_0","Pigtails Chestnut", -1, -1),
		Mod_Class::HairSets(3, 1, "H_FMF_3_1","Pigtails Blonde", -1, -1),
		Mod_Class::HairSets(3, 2, "H_FMF_3_2","Pigtails Auburn", -1, -1),
		Mod_Class::HairSets(3, 3, "H_FMF_3_3","Pigtails Black", -1, -1),
		Mod_Class::HairSets(3, 4, "H_FMF_3_4","Pigtails Brown", -1, -1),

		Mod_Class::HairSets(4, 0, "H_FMF_4_0","Ponytail Chestnut", -1, -1),
		Mod_Class::HairSets(4, 1, "H_FMF_4_1","Ponytail Blonde", -1, -1),
		Mod_Class::HairSets(4, 2, "H_FMF_4_2","Ponytail Auburn", -1, -1),
		Mod_Class::HairSets(4, 3, "H_FMF_4_3","Ponytail Black", -1, -1),
		Mod_Class::HairSets(4, 4, "H_FMF_4_4","Ponytail Brown", -1, -1),
		Mod_Class::HairSets(4, 5, "H_FMF_4_5","Ponytail Blue", -1, -1),

		Mod_Class::HairSets(5, 0, "H_FMF_5_0","Braided Mohawk Chestnut", -1, -1),
		Mod_Class::HairSets(5, 1, "H_FMF_5_1","Braided Mohawk Blonde", -1, -1),
		Mod_Class::HairSets(5, 2, "H_FMF_5_2","Braided Mohawk Auburn", -1, -1),
		Mod_Class::HairSets(5, 3, "H_FMF_5_3","Braided Mohawk Black", -1, -1),
		Mod_Class::HairSets(5, 4, "H_FMF_5_4","Braided Mohawk Brown", -1, -1),
		Mod_Class::HairSets(5, 5, "H_FMF_5_5","Braided Mohawk Pink", -1, -1),

		Mod_Class::HairSets(6, 0, "H_FMF_6_0","Braids Chestnut", -1, -1),
		Mod_Class::HairSets(6, 1, "H_FMF_6_1","Braids Blonde", -1, -1),
		Mod_Class::HairSets(6, 2, "H_FMF_6_2","Braids Auburn", -1, -1),
		Mod_Class::HairSets(6, 3, "H_FMF_6_3","Braids Black", -1, -1),
		Mod_Class::HairSets(6, 4, "H_FMF_6_4","Braids Brown", -1, -1),

		Mod_Class::HairSets(7, 0, "H_FMF_7_0","Bob Chestnut", -1, -1),
		Mod_Class::HairSets(7, 1, "H_FMF_7_1","Bob Blonde", -1, -1),
		Mod_Class::HairSets(7, 2, "H_FMF_7_2","Bob Auburn", -1, -1),
		Mod_Class::HairSets(7, 3, "H_FMF_7_3","Bob Black", -1, -1),
		Mod_Class::HairSets(7, 4, "H_FMF_7_4","Bob Brown", -1, -1),
		Mod_Class::HairSets(7, 5, "H_FMF_7_5","Bob Purple Fade", -1, -1),

		Mod_Class::HairSets(8, 0, "H_FMF_8_0","Faux Hawk Chestnut", -1, -1),
		Mod_Class::HairSets(8, 1, "H_FMF_8_1","Faux Hawk Blonde", -1, -1),
		Mod_Class::HairSets(8, 2, "H_FMF_8_2","Faux Hawk Auburn", -1, -1),
		Mod_Class::HairSets(8, 3, "H_FMF_8_3","Faux Hawk Black", -1, -1),
		Mod_Class::HairSets(8, 4, "H_FMF_8_4","Faux Hawk Brown", -1, -1),
		Mod_Class::HairSets(8, 5, "H_FMF_8_5","Faux Hawk Pink", -1, -1),

		Mod_Class::HairSets(9, 0, "H_FMF_9_0","French Twist Chestnut", -1, -1),
		Mod_Class::HairSets(9, 1, "H_FMF_9_1","French Twist Blonde", -1, -1),
		Mod_Class::HairSets(9, 2, "H_FMF_9_2","French Twist Auburn", -1, -1),
		Mod_Class::HairSets(9, 3, "H_FMF_9_3","French Twist Black", -1, -1),
		Mod_Class::HairSets(9, 4, "H_FMF_9_4","French Twist Brown", -1, -1),

		Mod_Class::HairSets(10, 0, "H_FMF_10_0","Long Bob Chestnut", -1, -1),
		Mod_Class::HairSets(10, 1, "H_FMF_10_1","Long Bob Blonde", -1, -1),
		Mod_Class::HairSets(10, 2, "H_FMF_10_2","Long Bob Auburn", -1, -1),
		Mod_Class::HairSets(10, 3, "H_FMF_10_3","Long Bob Black", -1, -1),
		Mod_Class::HairSets(10, 4, "H_FMF_10_4","Long Bob Brown", -1, -1),
		Mod_Class::HairSets(10, 6, "H_FMF_10_6","Long Bob Purple Fade", -1, -1),

		Mod_Class::HairSets(11, 0, "H_FMF_11_0","Loose Tied Chestnut", -1, -1),
		Mod_Class::HairSets(11, 1, "H_FMF_11_1","Loose Tied Blonde", -1, -1),
		Mod_Class::HairSets(11, 2, "H_FMF_11_2","Loose Tied Auburn", -1, -1),
		Mod_Class::HairSets(11, 3, "H_FMF_11_3","Loose Tied Black", -1, -1),
		Mod_Class::HairSets(11, 4, "H_FMF_11_4","Loose Tied Brown", -1, -1),
		Mod_Class::HairSets(11, 6, "H_FMF_11_6","Loose Tied Green", -1, -1),

		Mod_Class::HairSets(12, 0, "H_FMF_12_0","Pixie Chestnut", -1, -1),
		Mod_Class::HairSets(12, 1, "H_FMF_12_1","Pixie Blonde", -1, -1),
		Mod_Class::HairSets(12, 2, "H_FMF_12_2","Pixie Auburn", -1, -1),
		Mod_Class::HairSets(12, 3, "H_FMF_12_3","Pixie Black", -1, -1),
		Mod_Class::HairSets(12, 4, "H_FMF_12_4","Pixie Brown", -1, -1),
		Mod_Class::HairSets(12, 5, "H_FMF_12_5","Pixie Blue", -1, -1),

		Mod_Class::HairSets(13, 0, "H_FMF_13_0","Shaved Bangs Chestnut", -1, -1),
		Mod_Class::HairSets(13, 1, "H_FMF_13_1","Shaved Bangs Blonde", -1, -1),
		Mod_Class::HairSets(13, 2, "H_FMF_13_2","Shaved Bangs Auburn", -1, -1),
		Mod_Class::HairSets(13, 3, "H_FMF_13_3","Shaved Bangs Black", -1, -1),
		Mod_Class::HairSets(13, 4, "H_FMF_13_4","Shaved Bangs Brown", -1, -1),
		Mod_Class::HairSets(13, 5, "H_FMF_13_5","Shaved Bangs Blue Fade", -1, -1),

		Mod_Class::HairSets(14, 0, "H_FMF_14_0","Top Knot Chestnut", -1, -1),
		Mod_Class::HairSets(14, 1, "H_FMF_14_1","Top Knot Blonde", -1, -1),
		Mod_Class::HairSets(14, 2, "H_FMF_14_2","Top Knot Auburn", -1, -1),
		Mod_Class::HairSets(14, 3, "H_FMF_14_3","Top Knot Black", -1, -1),
		Mod_Class::HairSets(14, 4, "H_FMF_14_4","Top Knot Brown", -1, -1),

		Mod_Class::HairSets(15, 0, "H_FMF_15_0","Wavy Bob Chestnut", -1, -1),
		Mod_Class::HairSets(15, 1, "H_FMF_15_1","Wavy Bob Blonde", -1, -1),
		Mod_Class::HairSets(15, 2, "H_FMF_15_2","Wavy Bob Auburn", -1, -1),
		Mod_Class::HairSets(15, 3, "H_FMF_15_3","Wavy Bob Black", -1, -1),
		Mod_Class::HairSets(15, 4, "H_FMF_15_4","Wavy Bob Brown", -1, -1),
		Mod_Class::HairSets(15, 6, "H_FMF_15_6","Wavy Bob Red Fade", -1, -1),

		Mod_Class::HairSets(16, 0, "CLO_BBF_H_00","Pin Up Girl Chestnut", -1, -1),
		Mod_Class::HairSets(16, 1, "CLO_BBF_H_01","Pin Up Girl Blonde", -1, -1),
		Mod_Class::HairSets(16, 2, "CLO_BBF_H_02","Pin Up Girl Auburn", -1, -1),
		Mod_Class::HairSets(16, 3, "CLO_BBF_H_03","Pin Up Girl Black", -1, -1),
		Mod_Class::HairSets(16, 4, "CLO_BBF_H_04","Pin Up Girl Brown", -1, -1),

		Mod_Class::HairSets(17, 0, "CLO_BBF_H_05","Messy Bun Chestnut", -1398869298, -811206225),
		Mod_Class::HairSets(17, 1, "CLO_BBF_H_06","Messy Bun Blonde", -1398869298, -1586815686),
		Mod_Class::HairSets(17, 2, "CLO_BBF_H_07","Messy Bun Auburn", -1398869298, -1423429452),
		Mod_Class::HairSets(17, 3, "CLO_BBF_H_08","Messy Bun Black", -1398869298, -1697869815),
		Mod_Class::HairSets(17, 4, "CLO_BBF_H_09","Messy Bun Brown", -1398869298, -1470846183),

		Mod_Class::HairSets(18, 0, "CLO_VALF_H_0_0","Flapper Bob Chestnut", -1, -1),
		Mod_Class::HairSets(18, 1, "CLO_VALF_H_0_1","Flapper Bob Blonde", -1, -1),
		Mod_Class::HairSets(18, 2, "CLO_VALF_H_0_2","Flapper Bob Auburn", -1, -1),
		Mod_Class::HairSets(18, 3, "CLO_VALF_H_0_3","Flapper Bob Black", -1, -1),
		Mod_Class::HairSets(18, 4, "CLO_VALF_H_0_4","Flapper Bob Brown", -1, -1),
		Mod_Class::HairSets(18, 5, "CLO_VALF_H_0_5","Flapper Bob Blue", -1, -1),

		Mod_Class::HairSets(19, 0, "CLO_BUS_F_H_0_0","Tight Bun Black", -2086773, -1816086813),
		Mod_Class::HairSets(19, 1, "CLO_BUS_F_H_0_1","Tight Bun Brown", -2086773, -2113006722),
		Mod_Class::HairSets(19, 2, "CLO_BUS_F_H_0_2","Tight Bun Auburn", -2086773, -1398740829),
		Mod_Class::HairSets(19, 3, "CLO_BUS_F_H_0_3","Tight Bun Chestnut", -2086773, -131530830),
		Mod_Class::HairSets(19, 4, "CLO_BUS_F_H_0_4","Tight Bun Blonde", -2086773, -1101886458),

		Mod_Class::HairSets(20, 0, "CLO_BUS_F_H_1_0","Twisted Bob Chestnut", -1398869298, 558694786),
		Mod_Class::HairSets(20, 1, "CLO_BUS_F_H_1_1","Twisted Bob Black", -1398869298, 569279177),
		Mod_Class::HairSets(20, 2, "CLO_BUS_F_H_1_2","Twisted Bob Auburn", -1398869298, 544309199),
		Mod_Class::HairSets(20, 3, "CLO_BUS_F_H_1_3","Twisted Bob Brown", -1398869298, 1190448341),
		Mod_Class::HairSets(20, 4, "CLO_BUS_F_H_1_4","Twisted Bob Blonde", -1398869298, 885139568),

		Mod_Class::HairSets(21, 0, "CLO_HP_F_HR_0_0","Big Bangs Chestnut", -1, -1),
		Mod_Class::HairSets(21, 1, "CLO_HP_F_HR_0_1","Big Bangs Blonde", -1, -1),
		Mod_Class::HairSets(21, 2, "CLO_HP_F_HR_0_2","Big Bangs Auburn", -1, -1),
		Mod_Class::HairSets(21, 3, "CLO_HP_F_HR_0_3","Big Bangs Black", -1, -1),
		Mod_Class::HairSets(21, 4, "CLO_HP_F_HR_0_4","Big Bangs Brown", -1, -1),

		Mod_Class::HairSets(22, 0, "CLO_HP_F_HR_1_0","Braided Top Knot Chestnut", -1398869298, -1845683606),
		Mod_Class::HairSets(22, 1, "CLO_HP_F_HR_1_1","Braided Top Knot Blonde", -1398869298, -1555317497),
		Mod_Class::HairSets(22, 2, "CLO_HP_F_HR_1_2","Braided Top Knot Auburn", -1398869298, 1704673699),
		Mod_Class::HairSets(22, 3, "CLO_HP_F_HR_1_3","Braided Top Knot Black", -1398869298, 1993401358),
		Mod_Class::HairSets(22, 4, "CLO_HP_F_HR_1_4","Braided Top Knot Brown", -1398869298, 1227065524),

		Mod_Class::HairSets(23, 0, "CLO_INDF_H_0_0","Mullet Chestnut", -1, -1),
		Mod_Class::HairSets(23, 1, "CLO_INDF_H_0_1","Mullet Blonde", -1, -1),
		Mod_Class::HairSets(23, 2, "CLO_INDF_H_0_2","Mullet Auburn", -1, -1),
		Mod_Class::HairSets(23, 3, "CLO_INDF_H_0_3","Mullet Black", -1, -1),
		Mod_Class::HairSets(23, 4, "CLO_INDF_H_0_4","Mullet Brown", -1, -1),

		Mod_Class::HairSets(25, 0, "CLO_S1F_H_0_0","Pinched Cornrows", 62137527, -1325458477),
		Mod_Class::HairSets(26, 0, "CLO_S1F_H_1_0","Leaf Cornrows", 62137527, -566725051),
		Mod_Class::HairSets(27, 0, "CLO_S1F_H_2_0","Zig Zag Cornrows", 62137527, -787850263),
		Mod_Class::HairSets(28, 0, "CLO_S1F_H_3_0","Pigtail Bangs", 1529191571, 2039295216),
		Mod_Class::HairSets(29, 0, "CLO_S2F_H_0_0","Wave Braids", 1529191571, 2039295216),
		Mod_Class::HairSets(30, 0, "CLO_S2F_H_1_0","Coil Braids", 1529191571, 1800147054),
		Mod_Class::HairSets(31, 0, "CLO_S2F_H_2_0","Rolled Quiff", 1529191571, -2019505897),
		Mod_Class::HairSets(32, 0, "CLO_BIF_H_0_0","Loose Swept Back", -240234547, -328340062),
		Mod_Class::HairSets(33, 0, "CLO_BIF_H_1_0","Undercut Swept Back", -240234547, 1657725123),
		Mod_Class::HairSets(34, 0, "CLO_BIF_H_2_0","Undercut Swept Side", -240234547, -1517964336),
		Mod_Class::HairSets(35, 0, "CLO_BIF_H_3_0","Spiked Mohawk", -240234547, 1677522529),
		Mod_Class::HairSets(36, 0, "CLO_BIF_H_4_0","Bandana and Braid", 598190139, -1362677538),
		Mod_Class::HairSets(37, 0, "CLO_BIF_H_6_0","Skinbyrd", -240234547, 1841934566),
		Mod_Class::HairSets(38, 0, "CLO_BIF_H_5_0","Layered Mod", -240234547, 1742494019),
		Mod_Class::HairSets(39, 0, "CC_F_HS_1","Short", 598190139, 104062694),
		Mod_Class::HairSets(40, 0, "CC_F_HS_2","Layered Bob", 598190139, 869579299),
		Mod_Class::HairSets(41, 0, "CC_F_HS_3","Pigtails", 598190139, 1201332655),
		Mod_Class::HairSets(42, 0, "CC_F_HS_4","Ponytail", 598190139, 1028967715),
		Mod_Class::HairSets(43, 0, "CC_F_HS_5","Braided Mohawk", 598190139, -1651634800),
		Mod_Class::HairSets(44, 0, "CC_F_HS_6","Braids", 598190139, -892278763),
		Mod_Class::HairSets(45, 0, "CC_F_HS_7","Bob", 598190139, -1032005779),
		Mod_Class::HairSets(46, 0, "CC_F_HS_8","Faux Hawk", 598190139, -255675400),
		Mod_Class::HairSets(47, 0, "CC_F_HS_9","French Twist", 598190139, 1890137027),
		Mod_Class::HairSets(48, 0, "CC_F_HS_10","Long Bob", 598190139, -406805808),
		Mod_Class::HairSets(49, 0, "CC_F_HS_11","Loose Tied", 598190139, -592540500),
		Mod_Class::HairSets(50, 0, "CC_F_HS_12","Pixie", 598190139, 205417419),
		Mod_Class::HairSets(51, 0, "CC_F_HS_13","Shaved Bangs", 598190139, -2127276619),
		Mod_Class::HairSets(52, 0, "CC_F_HS_14","Top Knot", 598190139, -1362677538),
		Mod_Class::HairSets(53, 0, "CC_F_HS_15","Wavy Bob", 598190139, -1549722990),
		Mod_Class::HairSets(54, 0, "CLO_BBF_H_05","Messy Bun Chestnut", -1398869298, -811206225),
		Mod_Class::HairSets(55, 0, "CLO_BBF_H_00","Pin Up Girl Chestnut", -1, -1),
		Mod_Class::HairSets(56, 0, "CLO_BUS_F_H_0_0","Tight Bun Black", -2086773, -1816086813),
		Mod_Class::HairSets(57, 0, "CLO_BUS_F_H_1_0","Twisted Bob Chestnut", -1398869298, 558694786),
		Mod_Class::HairSets(58, 0, "CLO_VALF_H_0_0","Flapper Bob Chestnut", -1, -1),
		Mod_Class::HairSets(59, 0, "CLO_HP_F_HR_0_0","Big Bangs Chestnut", -1, -1),
		Mod_Class::HairSets(60, 0, "CLO_HP_F_HR_1_0","Braided Top Knot Chestnut", -1398869298, -1845683606),
		Mod_Class::HairSets(61, 0, "CLO_INDF_H_0_0","Mullet Chestnut", -1, -1),
		Mod_Class::HairSets(62, 0, "CLO_S1F_H_0_0","Pinched Cornrows", 62137527, -1325458477),
		Mod_Class::HairSets(63, 0, "CLO_S1F_H_1_0","Leaf Cornrows", 62137527, -566725051),
		Mod_Class::HairSets(64, 0, "CLO_S1F_H_2_0","Zig Zag Cornrows", 62137527, -787850263),
		Mod_Class::HairSets(65, 0, "CLO_S1F_H_3_0","Pigtail Bangs", 1529191571, 2039295216),
		Mod_Class::HairSets(66, 0, "CLO_S2F_H_0_0","Wave Braids", 1529191571, 2039295216),
		Mod_Class::HairSets(67, 0, "CLO_S2F_H_1_0","Coil Braids", 1529191571, 1800147054),
		Mod_Class::HairSets(68, 0, "CLO_S2F_H_2_0","Rolled Quiff", 1529191571, -2019505897),
		Mod_Class::HairSets(69, 0, "CLO_BIF_H_0_0","Loose Swept Back", -240234547, -328340062),
		Mod_Class::HairSets(70, 0, "CLO_BIF_H_1_0","Undercut Swept Back", -240234547, 1657725123),
		Mod_Class::HairSets(71, 0, "CLO_BIF_H_2_0","Undercut Swept Side", -240234547, -1517964336),
		Mod_Class::HairSets(72, 0, "CLO_BIF_H_3_0","Spiked Mohawk", -240234547, 1677522529),
		Mod_Class::HairSets(73, 0, "CLO_BIF_H_4_0","Bandana and Braid", 598190139, -1362677538),
		Mod_Class::HairSets(74, 0, "CLO_BIF_H_5_0","Layered Mod", -240234547, 1742494019),
		Mod_Class::HairSets(75, 0, "CLO_BIF_H_6_0","Skinbyrd", -240234547, 1841934566),
		Mod_Class::HairSets(76, 0, "CLO_GRF_H_0_0","Neat Bun", 1616273011, 687338866),
		Mod_Class::HairSets(77, 0, "CLO_GRF_H_1_0","Short Bob", 1616273011, 1827923343),
		Mod_Class::HairSets(78, 0, "CLO_VWF_H_0_0","Impotent Rage", 1347816957, 987747946),
		Mod_Class::HairSets(79, 0, "CLO_TRF_H_0_0","Afro", -1970774728, -2025496493),
		Mod_Class::HairSets(80, 0, "CLO_FXF_H_0_0","Pixie Wavy", 601646824, -974054285),
		Mod_Class::HairSets(81, 0, "CLO_SBF_H_0_0","Short Tucked Bob", 987639353, -606892013),
		Mod_Class::HairSets(82, 0, "CLO_SBF_H_1_0","Shaggy Mullet", 987639353, -1514684318),
		Mod_Class::HairSets(83, 0, "CLO_X6F_H_0_0","Buzzcut", 1841427399, 606012624)
	};

	Mod_Class::ClothX MaleDefault = Mod_Class::ClothX("AAA_M_Epslon_0", { 0, 0, 0, 8, 104, 0, 20, 129, 15, 0, 0, 272 }, { 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0 }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });
	Mod_Class::ClothX FemaleDefault = Mod_Class::ClothX("AAA_F_Epsilon_0", { 21, 0, 0, 3, 111, 0, 29, 99, 6, 0, 0, 285 }, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });

	std::vector<Mod_Class::ClothX> XmasOut_M = {
		Mod_Class::ClothX("MaleFestiveWinter Pajamas", { 0, 0, -1, 1, 32, 0, 4, 0, 15, 0, 0, 52}, { 0, 0, -1, 0, 2, 0, 1, 0, 0, 0, 0, 2}, { 44, -1, -1, -1, -1}, { 1, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveThe Pudding", { 0, 0, -1, 1, 26, 0, 12, 0, 15, 0, 0, 51}, { 0, 0, -1, 0, 3, 0, 8, 0, 0, 0, 0, 2}, { 41, -1, -1, -1, -1}, {0,-1,-1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveThe Elf", {0, 0, -1, 1, 26, 0, 17, 34, 15, 0, 0, 51}, { 0, 0, -1, 0, 3, 0, 0, 0, 0, 0, 0, 1}, { 42, -1, -1, -1, -1}, { 2, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveThe Claus", {0, 0, -1, 1, 3, 0, 4, 0, 15, 0, 0, 51}, { 0, 0, -1, 0, 0, 0, 4, 0, 0, 0, 0, 0}, { 40, -1, -1, -1, -1}, { 6, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveStripy Pajamas", {0, 0, -1, 1, 32, 0, 17, 0, 15, 0, 0, 52}, { 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, { 42, -1, -1, -1, -1}, { 0, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveRed Pajamas", {0, 0, -1, 1, 32, 0, 4, 34, 15, 0, 0, 52}, { 0, 0, -1, 0, 0, 0, 2, 0, 0, 0, 0, 0}, { 40, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleFestiveFestive Pajamas", {0, 0, -1, 1, 32, 0, 4, 34, 15, 0, 0, 52}, { 0, 0, -1, 0, 3, 0, 0, 3, 0, 0, 0, 3}, { 43, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleSanta CostumesFilthy Santa Costume", { 0, 0, -1, 61, 57, 0, 39, 0, 15, 0, 0, 116}, { 0, 0, -1, 0, 2, 0, 0, 0, 0, 0, 0, 2}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleSanta CostumesDirty Santa Costume", { 0, 0, -1, 50, 57, 0, 39, 0, 15, 0, 0, 116}, { 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("MaleSanta CostumesBad Santa Costume", { 0, 0, -1, 50, 57, 0, 39, 0, 15, 0, 0, 116}, { 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1})
	};
	std::vector<Mod_Class::ClothX> XmasOut_F = {
		Mod_Class::ClothX("FemaleFestiveWinter Pajamas", {0, 0, -1, 3, 31, 0, 2, 0, 3, 0, 0, 45}, { 0, 0, -1, 0, 2, 0, 5, 0, 0, 0, 0, 2}, { 43, -1, -1, -1, -1}, { 1, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveThe Pudding", {0, 0, -1, 3, 0, 0, 22, 0, 3, 0, 0, 44}, { 0, 0, -1, 0, 7, 0, 0, 0, 0, 0, 0, 2}, { 40, -1, -1, -1, -1}, { 0, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveThe Elf", {0, 0, -1, 3, 27, 0, 17, 17, 3, 0, 0, 44}, { 0, 0, -1, 0, 2, 0, 0, 0, 0, 0, 0, 1}, { 41, -1, -1, -1, -1}, { 2, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveThe Claus", {0, 0, -1, 3, 2, 0, 2, 0, 3, 0, 0, 44}, { 0, 0, -1, 0, 0, 0, 13, 0, 0, 0, 0, 0}, { 39, -1, -1, -1, -1}, { 6, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveStripy Pajamas", {0, 0, -1, 3, 31, 0, 17, 0, 3, 0, 0, 45}, { 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, { 41, -1, -1, -1, -1}, { 0, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveRed Pajamas", {0, 0, -1, 3, 31, 0, 2, 17, 3, 0, 0, 45}, { 0, 0, -1, 0, 0, 0, 13, 0, 0, 0, 0, 0}, { 39, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleFestiveFestive Pajamas",{ 0, 0, -1, 3, 31, 0, 2, 17, 3, 0, 0, 45}, { 0, 0, -1, 0, 3, 0, 13, 2, 0, 0, 0, 3}, { 42, -1, -1, -1, -1}, { 3, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleSanta CostumesFilthy Santa Costume", { 0, 0, -1, 65, 59, 0, 40, 0, 1, 0, 0, 108}, { 0, 0, -1, 0, 2, 0, 0, 0, 2, 0, 0, 2}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleSanta CostumesDirty Santa Costume", { 0, 0, -1, 52, 59, 0, 40, 0, 1, 0, 0, 108}, { 0, 0, -1, 0, 1, 0, 0, 0, 2, 0, 0, 1}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1}),
		Mod_Class::ClothX("FemaleSanta CostumesBad Santa Costume", { 0, 0, -1, 52, 59, 0, 40, 0, 1, 0, 0, 108}, { 0, 0, -1, 0, 0, 0, 0, 0, 2, 0, 0, 0}, { -1, -1, -1, -1, -1}, { -1, -1, -1, -1, -1})
	};
	std::vector<std::string> FindCloths(bool male)
	{
		LoggerLight("-FindCloths-");
		std::vector<std::string> Files = {};
		std::string OutputFolder = GetDir() + "/Outfits";

		if (CreateDirectoryA((LPSTR)OutputFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{

		}
		if (male)
		{
			OutputFolder = GetDir() + "/Outfits/Male";
			if (CreateDirectoryA((LPSTR)OutputFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			{

			}
		}
		else
		{
			OutputFolder = GetDir() + "/Outfits/Female";
			if (CreateDirectoryA((LPSTR)OutputFolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			{

			}
		}

		for (const auto& entry : std::filesystem::directory_iterator(OutputFolder))
			Files.push_back(entry.path().string());

		return Files;
	}

	Mod_Class::ClothX LoadCloths(const std::string& file)
	{
		LoggerLight("-LoadCloths-");
		std::string Cloths = "";
		std::vector<int> ClothA = {}, ClothB = {}, ExtraA = {}, ExtraB = {};
		int intList = 0;

		std::vector<std::string> MyColect = ReadSetFile(file);

		for (int i = 0; i < MyColect.size(); i++)
		{
			std::string line = MyColect[i];
			if (StringContains("Title", line))
			{
				Cloths = AfterEqual(line);
			}
			else if (StringContains("[ClothA]", line))
			{
				intList = 1;
			}
			else if (StringContains("[ClothB]", line))
			{
				intList = 2;
			}
			else if (StringContains("[ExtraA]", line))
			{
				intList = 3;
			}
			else if (StringContains("[ExtraB]", line))
			{
				intList = 4;
			}
			else if (intList == 1)
			{
				ClothA.push_back(StingNumbersInt(line));
			}
			else if (intList == 2)
			{
				int iSpot = StingNumbersInt(line);
				if (iSpot < 0)
					iSpot = 0;
				ClothB.push_back(iSpot);
			}
			else if (intList == 3)
			{
				ExtraA.push_back(StingNumbersInt(line));
			}
			else if (intList == 4)
			{
				int iSpot = StingNumbersInt(line);
				if (iSpot < 0)
					iSpot = 0;
				ExtraB.push_back(iSpot);
			}
		}

		return Mod_Class::ClothX(Cloths, ClothA, ClothB, ExtraA, ExtraB);
	}
	Mod_Class::ClothX GetCloths(bool male)
	{
		LoggerLight("-GetCloths-");

		Mod_Class::ClothX cothing = FemaleDefault;
		if (male)
			cothing = MaleDefault;

		std::vector<std::string> Files = FindCloths(male);

		if ((int)Files.size() > 0)
		{
			int iRando = 0;
			if (male)
				iRando = LessRandomInt("Outfits_01", 0, (int)Files.size() - 1);
			else
				iRando = LessRandomInt("Outfits_02", 0, (int)Files.size() - 1);

			cothing = LoadCloths(Files[iRando]);
		}

		return cothing;
	}

	int SizeUpHairList(bool bMale)
	{
		if (bMale)
			return (int)MHairsets.size() - 1;
		else
			return (int)FHairsets.size() - 1;
	}
	Mod_Class::HairSets PickAStyle(int Style, bool bMale)
	{
		if (bMale)
			return MHairsets[Style];
		else
			return FHairsets[Style];
	}
	Mod_Class::HairSets PickAStyle(bool bMale)
	{
		return PickAStyle(bMale, LessRandomInt("PickAStyle0" + std::to_string(bMale), 0, SizeUpHairList(bMale)));
	}
	Mod_Class::FaceBank AddFace(bool male)
	{
		int ShapeFirstID;
		int ShapeSecondID;
		if (male)
		{
			ShapeFirstID = LessRandomInt("AddFaceM01", 0, 20);
			ShapeSecondID = LessRandomInt("AddFaceM01", 0, 20);
		}
		else
		{
			ShapeFirstID = LessRandomInt("AddFaceF01", 21, 41);
			ShapeSecondID = LessRandomInt("AddFaceF01", 21, 41);
		}

		float ShapeMix = RandomFloat(-0.9, 0.9);
		float SkinMix = RandomFloat(0.9, 0.99);
		float ThirdMix = RandomFloat(-0.9, 0.9);

		return Mod_Class::FaceBank(ShapeFirstID, ShapeSecondID, ShapeMix, SkinMix, ThirdMix);
	}
	std::vector<Mod_Class::FreeOverLay> AddOverLay(bool male, bool freemode)
	{
		LoggerLight("AddOverLay");

		std::vector<Mod_Class::FreeOverLay> YourOver = {};
		if (freemode)
		{
			for (int i = 0; i < 12; i++)
			{
				int iColour = 0;
				int iChange = RandomInt(0, PED::_GET_NUM_HEAD_OVERLAY_VALUES(i));
				float fVar = RandomFloat(0.45, 0.99);

				if (i == 0)
				{
					iChange = RandomInt(0, iChange);
				}//Blemishes
				else if (i == 1)
				{
					if (male)
						iChange = RandomInt(0, iChange);
					else
						iChange = 255;
					iColour = 1;
				}//Facial Hair
				else if (i == 2)
				{
					iChange = RandomInt(0, iChange);
					iColour = 1;
				}//Eyebrows
				else if (i == 3)
				{
					iChange = 255;
				}//Ageing
				else if (i == 4)
				{
					int iFace = RandomInt(0, 50);
					if (iFace < 30)
					{
						iChange = RandomInt(0, 15);
					}
					else if (iFace < 45)
					{
						iChange = RandomInt(0, iChange);
						fVar = RandomFloat(0.85f, 0.99f);
					}
					else
						iChange = 255;
				}//Makeup
				else if (i == 5)
				{
					if (!male)
					{
						iChange = RandomInt(0, iChange);
						fVar = RandomFloat(0.15f, 0.39f);
					}
					else
						iChange = 255;
					iColour = 2;
				}//Blush
				else if (i == 6)
				{
					iChange = RandomInt(0, iChange);
				}//Complexion
				else if (i == 7)
				{
					iChange = 255;
				}//Sun Damage
				else if (i == 8)
				{
					if (!male)
						iChange = RandomInt(0, iChange);
					else
						iChange = 255;
					iColour = 2;
				}//Lipstick
				else if (i == 9)
				{
					iChange = RandomInt(0, iChange);
				}//Moles/Freckles
				else if (i == 10)
				{
					if (male)
						iChange = RandomInt(0, iChange);
					else
						iChange = 255;
					iColour = 1;
				}//Chest Hair
				else if (i == 11)
				{
					iChange = RandomInt(0, iChange);
				}//Body Blemishes

				int AddColour = -1;

				if (iColour > 0)
					AddColour = RandomInt(0, 64);

				YourOver.push_back(Mod_Class::FreeOverLay(iChange, AddColour, fVar));
			}

		}

		return YourOver;
	}
	std::vector<Mod_Class::Tattoo> AddRandTats(bool male)
	{
		LoggerLight("AddRandTats");
		std::vector<Mod_Class::Tattoo> Tatlist = {};

		if (male)
		{
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats01[RandomInt(0, (int)maleTats01.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats02[RandomInt(0, (int)maleTats02.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats03[RandomInt(0, (int)maleTats03.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats04[RandomInt(0, (int)maleTats04.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats05[RandomInt(0, (int)maleTats05.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats06[RandomInt(0, (int)maleTats06.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats07[RandomInt(0, (int)maleTats07.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = maleTats08[RandomInt(0, (int)maleTats08.size() - 1)];
				Tatlist.push_back(T);
			}
		}
		else
		{
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats01[RandomInt(0, (int)femaleTats01.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats02[RandomInt(0, (int)femaleTats02.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats03[RandomInt(0, (int)femaleTats03.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats04[RandomInt(0, (int)femaleTats04.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats05[RandomInt(0, (int)femaleTats05.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats06[RandomInt(0, (int)femaleTats06.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats07[RandomInt(0, (int)femaleTats07.size() - 1)];
				Tatlist.push_back(T);
			}
			if (RandomInt(0, 10) < 5)
			{
				Mod_Class::Tattoo T = femaleTats08[RandomInt(0, (int)femaleTats08.size() - 1)];
				Tatlist.push_back(T);
			}
		}

		return Tatlist;
	}
	Mod_Class::ClothBank NewFreeModePed()
	{
		if (LessRandomInt("GotMale", 0, 10) < 5)
		{
			bool Male = true;
			std::string Model = "mp_m_freemode_01";
			Mod_Class::ClothX Cothing = GetCloths(true);
			Mod_Class::HairSets MyHair = PickAStyle(Male);
			return Mod_Class::ClothBank("", Model, 0, true, AddFace(Male), Male, false, MyHair, RandomInt(1, 61), RandomInt(1, 61), RandomInt(0, 10), 0, AddOverLay(Male, true), AddRandTats(Male), std::vector<Mod_Class::ClothX>{ Cothing }, {}, "", "", "");
		}
		else
		{
			bool Male = false;
			std::string Model = "mp_f_freemode_01";
			Mod_Class::ClothX Cothing = GetCloths(false);
			Mod_Class::HairSets MyHair = PickAStyle(Male);
			return Mod_Class::ClothBank("", Model, 0, true, AddFace(Male), Male, false, MyHair, RandomInt(1, 61), RandomInt(1, 61), RandomInt(0, 10), 0, AddOverLay(Male, true), AddRandTats(Male), std::vector<Mod_Class::ClothX>{ Cothing }, {}, "", "", "");
		}
	}

	bool ItsChristmas;
	bool ItHalloween;

	void ThemVoices(const std::string& voip)
	{
		AUDIO::SET_AMBIENT_VOICE_NAME(PLAYER::PLAYER_PED_ID(), (LPSTR)voip.c_str());
		invoke <Void>(0x4ADA3F19BE4A6047, PLAYER::PLAYER_PED_ID());
	}
	void PullingFaces(const std::string& aniName)
	{
		PED::SET_FACIAL_IDLE_ANIM_OVERRIDE(PLAYER::PLAYER_PED_ID(), (LPSTR)aniName.c_str(), 0);
	}

	const std::vector<std::string> LsGstars = {
		"g_f_importexport_01",//"Gang Female (Import-Export)", 
		"a_f_y_eastsa_03",//"East SA Young Female 3", 
		"g_f_importexport_01",//"Import Export Female", 
		"g_m_importexport_01",//"Gang Male (Import-Export)",
		"g_m_m_armboss_01",//"Armenian Boss",  Rogers Salvage and Scrap in La Puerta.-- NON -- 
		"g_m_m_armgoon_01",//"Armenian Goon",  
		"g_m_y_armgoon_02",//"Armenian Goon 2",  
		"g_m_m_armlieut_01",//"Armenian Lieutenant",  
		"g_f_y_ballas_01",//"Ballas Female", Davis,--Families--Vagos
		"g_m_y_ballaeast_01",//"Ballas East Male",  
		"g_m_y_ballaorig_01",//"Ballas Original Male",  
		"g_m_y_ballasout_01",//"Ballas South Male", 
		"g_m_m_chiboss_01",//"Chinese Boss",   textstyle-- korean
		"g_m_m_chigoon_01",//"Chinese Goon",  
		"g_m_m_chigoon_02",//"Chinese Goon 2",  
		"g_m_m_chicold_01",//"Chinese Goon Older", 
		"g_f_y_families_01",//"Families Female",
		"g_m_y_famca_01",//"Families CA Male",  
		"g_m_y_famdnf_01",//"Families DNF Male",  
		"g_m_y_famfor_01",//"Families FOR Male", 
		"g_m_m_korboss_01",//"Korean Boss",  K-town-- Chinesse
		"g_m_y_korlieut_01",//"Korean Lieutenant",  
		"g_m_y_korean_01",//"Korean Young Male",  
		"g_m_y_korean_02",//"Korean Young Male 2", 
		"g_m_y_azteca_01",//"Azteca", 
		"g_f_y_vagos_01",//"Vagos Female",
		"a_m_y_mexthug_01",//"Mexican Thug", 
		"g_m_m_mexboss_01",//"Mexican Boss",  
		"g_m_m_mexboss_02",//"Mexican Boss 2",  
		"g_m_y_mexgang_01",//"Mexican Gang Member",  
		"g_m_y_mexgoon_01",//"Mexican Goon",  
		"g_m_y_mexgoon_02",//"Mexican Goon 2",  
		"g_m_y_mexgoon_03",//"Mexican Goon 3",  
		"g_m_y_pologoon_01",//"Polynesian Goon",  
		"g_m_y_pologoon_02",//"Polynesian Goon 2", 
		"g_m_y_salvaboss_01",//"Salvadoran Boss",  
		"g_m_y_salvagoon_01",//"Salvadoran Goon",  
		"g_m_y_salvagoon_02",//"Salvadoran Goon 2",  
		"g_m_y_salvagoon_03",//"Salvadoran Goon 3",  
		"g_f_y_lost_01",//"The Lost MC Female",  
		"g_m_y_lost_01",//"The Lost MC Male",  
		"g_m_y_lost_02",//"The Lost MC Male 2",  
		"g_m_y_lost_03",//"The Lost MC Male 3",
		"A_F_M_GenBiker_01",//
		"A_M_M_GenBiker_01",//
		"g_m_y_strpunk_01",//"Street Punk",  
		"g_m_y_strpunk_02",//"Street Punk 2",  
		"G_M_M_GenThug_01",
		"G_M_M_Goons_01"
	};
	const std::vector<std::string> Eplomes = {
		"a_f_y_epsilon_01",//"Epsilon Female",  
		"a_m_y_epsilon_01",//"Epsilon Male",  
		"a_m_y_epsilon_02",//"Epsilon Male 2", 
	};
	const std::vector<std::string> WorkinClass = { 
		"mp_f_bennymech_01",//"Benny Mechanic (Female)",	0
		"s_m_m_autoshop_01",//"Autoshop Worker",			1
		"s_m_m_autoshop_02",//"Autoshop Worker 2",			2
		"s_f_y_bartender_01",//"Bartender",					3
		"s_f_y_clubbar_01",//"Club Bartender Female",		4
		"s_m_y_barman_01",//"Barman",						5
		"s_m_y_waiter_01",//"Waiter",						6
		"s_f_y_factory_01",//"Factory Worker Female",		7
		"s_f_m_sweatshop_01",//"Sweatshop Worker",			8
		"s_f_y_sweatshop_01",//"Sweatshop Worker Young",	9
		"S_F_M_Warehouse_01",	//							10
		"S_M_M_Warehouse_01",	//							11
		"mp_m_shopkeep_01",//"Shopkeeper (Male)",			12
		"s_f_y_scrubs_01",//"Hospital Scrubs Female",		13
		"s_m_m_doctor_01",//"Doctor",						14
		"s_f_m_maid_01",//"Maid",							15
		"s_f_y_migrant_01",//"Migrant Female--cleaner",		16
		"s_m_m_migrant_01",//"Migrant Male",				17
		"mp_s_m_armoured_01",//"Armoured Van Security Male",18
		"s_m_m_armoured_01",//"Armoured Van Security",		19
		"s_m_m_armoured_02",//"Armoured Van Security 2",	20	
		"s_m_m_chemsec_01",//"Chemical Plant Security",		21
		"mp_m_securoguard_01",//"Securoserve Guard (Male)", 22
		"s_m_m_security_01",//"Security Guard",				23
		"s_m_y_autopsy_01",//"Autopsy Tech",				24			
		"s_m_m_scientist_01",//"Scientist",					25
		"g_m_m_chemwork_01",//"Chemical Plant Worker",		26
		"s_m_y_construct_01",//"construction Worker",		27
		"s_m_y_construct_02",//"construction Worker 2",		28
		"s_m_m_dockwork_01",//"Dock Worker",				29
		"s_m_y_dockwork_01",//"Dock Worker",				30
		"s_m_y_airworker",//"Air Worker Male",				31
		"s_m_y_dwservice_01",//"DW Airport Worker",			32
		"s_m_y_dwservice_02",//"DW Airport Worker 2",		33
		"s_m_y_garbage",//"Garbage Worker",					34		
		"s_m_m_gardener_01",//"Gardener",					35
		"s_m_m_lathandy_01",//"Latino Handyman Male",		36
		"s_m_m_lsmetro_01",//"LS Metro Worker Male",		37
		"s_m_m_gentransport",//"Transport Worker Male",		38
		"s_m_y_pestcont_01",//"Pest Control",				39
		"s_m_m_postal_01",//"Postal Worker Male",			40
		"s_m_m_postal_02",//"Postal Worker Male 2",			41
		"s_m_m_ups_01",//"UPS Driver",						42
		"s_m_m_ups_02",//"UPS Driver 2",					43
		"s_m_m_strvend_01",//"Street Vendor",				44
		"s_m_y_strvend_01",//"Street Vendor Young",			45
		"s_m_y_valet_01",//"Valet",							46
		"s_m_y_winclean_01"//"Window Cleaner",				47
	};

	const std::vector<std::string> MotoCrossPeds = {
		"a_m_y_motox_01",//"Motocross Biker",  
		"a_m_y_motox_02",//"Motocross Biker 2",
	};
	const std::vector<std::string> ServicePeds = {
		"s_f_y_baywatch_01",//"Baywatch Female",	0
		"s_m_y_baywatch_01",//"Baywatch Male",		1
		"s_m_y_uscg_01",//"US Coastguard",			2
		"s_m_y_cop_01",//"Cop Male",				3
		"s_f_y_cop_01",//"Cop Female",				4
		"s_m_y_hwaycop_01",//"Highway Cop",			5
		"s_f_y_ranger_01",//"Ranger Female",		6
		"s_m_y_ranger_01",//"Ranger Male",			7
		"s_f_y_sheriff_01",//"Sheriff Female",		8
		"s_m_y_sheriff_01",//"Sheriff Male",		9
		"s_m_m_fibsec_01",//"FIB Security",			10
		"s_m_y_swat_01",//"SWAT",					11
		"s_m_y_armymech_01",//"Army Mechanic",		12
		"s_m_m_ccrew_01",//"Crew Member",			13
		"s_m_y_blackops_01",//"Black Ops Soldier",	14
		"s_m_y_blackops_02",//"Black Ops Soldier 2",15
		"s_m_y_blackops_03",//"Black Ops Soldier 3",16
		"s_m_m_marine_01",//"Marine",				17
		"s_m_m_marine_02",//"Marine 2",				18
		"s_m_y_marine_01",//"Marine Young",			19	
		"s_m_y_marine_02",//"Marine Young 2",		20
		"s_m_y_marine_03",//"Marine Young 3",		21
		"s_m_m_paramedic_01",//"Paramedic",			22
		"s_m_y_fireman_01"//"Fireman Male",			23
	};
	const std::vector<std::string> PilotPeds = {
		"s_m_y_pilot_01",//"Pilot",  
		"s_m_m_pilot_02",//"Pilot 2", 
		"s_m_m_pilot_01"//"Pilot",  
	};
	const std::vector<std::string> AnimalsPeds = {
		"a_c_boar",//"a_c_boar",		0
		"a_c_cat_01",//					1
		"a_c_husky",//					2
		"a_c_poodle",//					3
		"a_c_pug",//					4
		"a_c_retriever",//				5
		"a_c_rottweiler",//				6
		"a_c_shepherd",//				7
		"a_c_westy",//					8
		"a_c_pigeon",//"a_c_pigeon" />	9
		"a_c_rat",//"a_c_rat" />		10
		"a_c_cow",//"a_c_cow" />		11
		"a_c_coyote",//"a_c_coyote" />	12
		"a_c_crow",//"a_c_crow" />		13
		"a_c_rabbit_01",//"a_c_rabbit_01" />14
		"a_c_deer",//"a_c_deer" />			15
		"a_c_hen",//"a_c_hen" />		16
		"a_c_mtlion",//"mountain lion" />17
		"a_c_pig",//"a_c_pig" />		18
		"a_c_dolphin",//"fish/sharks" />19
		"a_c_fish",//					20
		"a_c_sharkhammer",//			21
		"a_c_humpback",//				22
		"a_c_killerwhale",//			23
		"a_c_stingray",//				24
		"a_c_sharktiger",//				25
		"a_c_chickenhawk",//"a_c_chickenhawk",  26
		"a_c_cormorant",//"a_c_cormorant" />	27
		"a_c_seagull"//					28
	};
	const std::vector<std::string> YankoPPeds = {
		"csb_prologuedriver",
		"csb_prolsec",
		"cs_prolsec_02",
		"ig_prolsec_02",
		"u_f_o_prolhost_01",
		"u_f_m_promourn_01"
	};
	const std::vector<std::string> CayoPercPeds = {
		"A_C_Panther",
		"G_M_M_CartelGuards_01",
		"G_M_M_CartelGuards_02",
		"S_M_M_HighSec_04",
		"S_F_Y_BeachBarStaff_01",
		"S_M_M_DrugProcess_01",
		"S_M_M_FieldWorker_01",
		"IG_Pilot",
		"CSB_JIO",
		"CSB_JuanStrickler",
		"CSB_MJO",
		"CSB_SSS",
		"IG_ARY",
		"IG_JIO",
		"IG_MJO",
		"IG_OldRichGuy",
		"IG_SSS"
	};

	std::string RandomPed(int iPedtype, int iSubType)
	{
		std::string YourPed = "s_m_y_clown_01";
		if (iPedtype == 1)
			YourPed = PrePed_01[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_01.size() - 1)];		//Beach Peds
		else if (iPedtype == 2)
			YourPed = PrePed_02[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_02.size() - 1)];		//Tramps
		else if (iPedtype == 3)
			YourPed = PrePed_03[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_03.size() - 1)];		//High class
		else if (iPedtype == 4)
			YourPed = PrePed_04[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_04.size() - 1)];		//Mid class
		else if (iPedtype == 5)
			YourPed = PrePed_05[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_05.size() - 1)];		//Low class 
		else if (iPedtype == 6)
			YourPed = PrePed_06[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_06.size() - 1)];		//Buisness
		else if (iPedtype == 7)
			YourPed = PrePed_07[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_07.size() - 1)];		//Body builder
		else if (iPedtype == 8)
		{
			if (iSubType == 1)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 0, 3)];
			else if (iSubType == 2)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 4, 7)];
			else if (iSubType == 3)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 8, 11)];
			else if (iSubType == 4)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 12, 15)];
			else if (iSubType == 5)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 16, 19)];
			else if (iSubType == 6)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 20, 23)];
			else if (iSubType == 7)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 24, 32)];
			else if (iSubType == 8)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 33, 34)];
			else if (iSubType == 9)
				YourPed = LsGstars[LessRandomInt("RandGsPed_0" + std::to_string(iSubType), 35, 38)];
			else if (iSubType == 10)
				YourPed = LsGstars[LessRandomInt("RandGsPed_" + std::to_string(iSubType), 39, 44)];
			else
				YourPed = LsGstars[LessRandomInt("RandGsPed_" + std::to_string(iSubType), 45, (int)LsGstars.size() - 1)];
		}       //GangStars--Subset
		else if (iPedtype == 9)
			YourPed = Eplomes[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)Eplomes.size() - 1)];			//Epslon 
		else if (iPedtype == 10)
			YourPed = PrePed_08[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_08.size() - 1)];		//Jogger
		else if (iPedtype == 11)
			YourPed = PrePed_09[LessRandomInt("RandPed_0" + std::to_string(iPedtype), 0, (int)PrePed_09.size() - 1)];		//Golfer
		else if (iPedtype == 12)
			YourPed = PrePed_10[LessRandomInt("RandPed_" + std::to_string(iPedtype), 0, (int)PrePed_10.size() - 1)];		//Hiker
		else if (iPedtype == 13)
			YourPed = PrePed_11[LessRandomInt("RandPed_" + std::to_string(iPedtype), 0, (int)PrePed_11.size() - 1)];		//Meth
		else if (iPedtype == 14)
			YourPed = PrePed_12[LessRandomInt("RandPed_" + std::to_string(iPedtype), 0, (int)PrePed_12.size() - 1)];		//Rural 
		else if (iPedtype == 15)
			YourPed = PrePed_13[LessRandomInt("RandPed_" + std::to_string(iPedtype), 0, (int)PrePed_13.size() - 1)];		//Cycles
		else if (iPedtype == 16)
			YourPed = PrePed_14[LessRandomInt("RandPed_" + std::to_string(iPedtype), 0, (int)PrePed_14.size() - 1)];		//LGBTQWSTRVX
		else if (iPedtype == 17)
			YourPed = PrePed_01[LessRandomInt("RandPed_" + std::to_string(iPedtype), 0, (int)PrePed_01.size() - 1)];		//Pool Peds
		else if (iPedtype == 18)
		{
			if (iSubType == 1)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 0, 2)];
			else if (iSubType == 2)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 3, 6)];
			else if (iSubType == 3)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 7, 11)];
			else if (iSubType == 4)
				YourPed = WorkinClass[12];
			else if (iSubType == 5)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 13, 14)];
			else if (iSubType == 6)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 15, 17)];
			else if (iSubType == 7)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 18, 20)];
			else if (iSubType == 8)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 21, 23)];
			else if (iSubType == 9)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_0" + std::to_string(iSubType), 24, 25)];
			else if (iSubType == 10)
				YourPed = WorkinClass[26];
			else if (iSubType == 11)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_" + std::to_string(iSubType), 27, 28)];
			else if (iSubType == 12)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_" + std::to_string(iSubType), 29, 30)];
			else if (iSubType == 13)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_" + std::to_string(iSubType), 31, 33)];
			else if (iSubType == 14)
				YourPed = WorkinClass[34];
			else if (iSubType == 15)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_" + std::to_string(iSubType), 35, 36)];
			else if (iSubType == 16)
				YourPed = WorkinClass[37];
			else if (iSubType == 17)
				YourPed = WorkinClass[38];
			else if (iSubType == 18)
				YourPed = WorkinClass[39];
			else if (iSubType == 19)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_" + std::to_string(iSubType), 40, 41)];
			else if (iSubType == 20)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_" + std::to_string(iSubType), 42, 43)];
			else if (iSubType == 21)
				YourPed = WorkinClass[LessRandomInt("RandWkPed_" + std::to_string(iSubType), 44, 45)];
			else if (iSubType == 22)
				YourPed = WorkinClass[46];
			else
				YourPed = WorkinClass[(int)WorkinClass.size() - 1];
		}       //Workers--Subset
		else if (iPedtype == 19)
			YourPed = "a_m_y_jetski_01";		//jet ski
		else if (iPedtype == 20)
			YourPed = MotoCrossPeds[LessRandomInt("RandMcPed_" + std::to_string(iPedtype), 0, 1)];		//Bike/ATV Male
		else if (iPedtype == 21)
		{
			if (iSubType == 1)
				YourPed = ServicePeds[LessRandomInt("RandSvPed_0" + std::to_string(iSubType), 0, 1)];		//"Baywatch 
			else if (iSubType == 2)
				YourPed = ServicePeds[2];																	//"US Coastguard
			else if (iSubType == 3)
				YourPed = ServicePeds[LessRandomInt("RandSvPed_0" + std::to_string(iSubType), 3, 4)];		//><!--Cops
			else if (iSubType == 4)
				YourPed = ServicePeds[5];																	//><!-- PoliceBike
			else if (iSubType == 5)
				YourPed = ServicePeds[LessRandomInt("RandSvPed_0" + std::to_string(iSubType), 6, 7)];		//><!-- Ranger
			else if (iSubType == 6)
				YourPed = ServicePeds[LessRandomInt("RandSvPed_0" + std::to_string(iSubType), 8, 9)];		//><!-- Sherif
			else if (iSubType == 7)
				YourPed = ServicePeds[10];																	//><!-- fib
			else if (iSubType == 8)
				YourPed = ServicePeds[11];																	//><!-- swat
			else if (iSubType == 9)
				YourPed = ServicePeds[LessRandomInt("RandSvPed_0" + std::to_string(iSubType), 12, 21)];		//military
			else if (iSubType == 10)
				YourPed = ServicePeds[22];																	//medic
			else
				YourPed = ServicePeds[(int)ServicePeds.size() - 1];											//fireman
		}       //Services
		else if (iPedtype == 22)
		{
			if (iSubType == 2)
				YourPed = "mp_f_helistaff_01";
			else
				YourPed = PilotPeds[LessRandomInt("RandPiPed", 0, (int)PilotPeds.size() - 1)];
		}       //Pilot
		else if (iPedtype == 23)
		{
			if (iSubType == 1)
				YourPed = AnimalsPeds[0];
			else if (iSubType == 2)
				YourPed = AnimalsPeds[LessRandomInt("RandAnPed_0" + std::to_string(iSubType), 1, 8)];		//"Cats/dogs", 
			else if (iSubType == 3)
				YourPed = AnimalsPeds[9];
			else if (iSubType == 4)
				YourPed = AnimalsPeds[10];
			else if (iSubType == 5)
				YourPed = AnimalsPeds[11];
			else if (iSubType == 6)
				YourPed = AnimalsPeds[12];
			else if (iSubType == 7)
				YourPed = AnimalsPeds[13];
			else if (iSubType == 8)
				YourPed = AnimalsPeds[LessRandomInt("RandAnPed_0" + std::to_string(iSubType), 14, 15)];		//"dearRabbit", 
			else if (iSubType == 9)
				YourPed = AnimalsPeds[16];
			else if (iSubType == 10)
				YourPed = AnimalsPeds[17];
			else if (iSubType == 11)
				YourPed = AnimalsPeds[18];
			else if (iSubType == 12)
				YourPed = AnimalsPeds[LessRandomInt("RandAnPed_" + std::to_string(iSubType), 19, 25)];
			else if (iSubType == 13)
				YourPed = AnimalsPeds[26];
			else
				YourPed = AnimalsPeds[LessRandomInt("RandAnPed_" + std::to_string(iSubType), 27, (int)AnimalsPeds.size() - 1)];
		}       //animals
		else if (iPedtype == 24)
			YourPed = YankoPPeds[LessRandomInt("RandPed_" + std::to_string(iPedtype), 0, (int)YankoPPeds.size() - 1)];		//Yankton
		else
		{
			if (iSubType == 1)
				YourPed = CayoPercPeds[0]; //A_C_Panther  
			else if (iSubType == 2)
				YourPed = PrePed_01[LessRandomInt("RandCpPed_0" + std::to_string(iSubType), 0, (int)PrePed_01.size() - 1)];		 //A_F_Y_Beach_02
			else if (iSubType == 3)
				YourPed = CayoPercPeds[LessRandomInt("RandCpPed_0" + std::to_string(iSubType), 1, 3)]; //Guard
			else if (iSubType == 4)
				YourPed = CayoPercPeds[4];  //Bar
			else if (iSubType == 5)
				YourPed = CayoPercPeds[LessRandomInt("RandCpPed_0" + std::to_string(iSubType), 5, 6)]; //worker
			else if (iSubType == 6)
				YourPed = CayoPercPeds[LessRandomInt("RandCpPed_0" + std::to_string(iSubType), 7, (int)CayoPercPeds.size() - 2)];  //pilot
			else
				YourPed = CayoPercPeds[(int)CayoPercPeds.size() - 1];

		}     //Cayo Perico


		return YourPed;
	}
	Mod_Class::ClothBank NewClothBank(const std::string& PedTitle)
	{
		bool Male = true;
		std::string Model = PedTitle;
		Mod_Class::HairSets MyHair = MHairsets[0];
		return Mod_Class::ClothBank("", Model, 0, false, AddFace(Male), Male, false, MyHair, 0, 0, 0, 0, {}, {}, {}, {}, "", "", "");
	}
	Mod_Class::ClothBank NewClothBank(int iPedtype, int iSubType)
	{
		return NewClothBank(RandomPed(iPedtype, iSubType));
	}

	void ApplyTats(Ped Pedx, Mod_Class::ClothBank* GetTats)
	{
		if (GetTats != nullptr)
		{
			for (int i = 0; i < GetTats->MyTattoo.size(); i++)
				PED::_APPLY_PED_OVERLAY(Pedx, MyHashKey(GetTats->MyTattoo[i].BaseName), MyHashKey(GetTats->MyTattoo[i].TatName));
		}
	}
	void OnlineDress(Ped Pedx, Mod_Class::ClothX* MyCloths)
	{
		PED::CLEAR_ALL_PED_PROPS(Pedx);
		if (MyCloths != nullptr)
		{

			for (int i = 0; i < MyCloths->ClothA.size(); i++)
			{
				if (MyCloths->ClothA[i] != -10)
					PED::SET_PED_COMPONENT_VARIATION(Pedx, i, MyCloths->ClothA[i], MyCloths->ClothB[i], 2);
			}

			for (int i = 0; i < MyCloths->ExtraA.size(); i++)
			{
				if (MyCloths->ExtraA[i] != -10)
					PED::SET_PED_PROP_INDEX(Pedx, i, MyCloths->ExtraA[i], MyCloths->ExtraB[i], false);
			}
		}

	}
	void SetingtheHair(Ped Pedx, Mod_Class::HairSets* Hair)
	{
		if (Hair != nullptr)
		{

			PED::SET_PED_COMPONENT_VARIATION(Pedx, 2, Hair->Comp, Hair->Text, 2);

			if (Hair->Over != -1)
				PED::_APPLY_PED_OVERLAY(Pedx, Hair->OverLib, Hair->Over);
		}

	}
	void OnlineFaces(Ped Pedx, Mod_Class::ClothBank* pFixtures)
	{
		//****************FaceShape/Colour****************
		PED::SET_PED_HEAD_BLEND_DATA(Pedx, pFixtures->MyFaces.ShapeFirstID, pFixtures->MyFaces.ShapeSecondID, pFixtures->MyFaces.ShapeThirdID, pFixtures->MyFaces.SkinFirstID, pFixtures->MyFaces.SkinSecondID, pFixtures->MyFaces.SkinThirdID, pFixtures->MyFaces.ShapeMix, pFixtures->MyFaces.SkinMix, pFixtures->MyFaces.ThirdMix, 0);

		if (ItsChristmas)
		{
			if (pFixtures->Male)
				OnlineDress(Pedx, &XmasOut_M[LessRandomInt("Crimb01", 0, (int)XmasOut_M.size() - 1)]);
			else
				OnlineDress(Pedx, &XmasOut_F[LessRandomInt("Crimb01", 0, (int)XmasOut_F.size() - 1)]);
		}
		else if (ItHalloween)
		{
			if (pFixtures->Male)
			{
				int iRan = LessRandomInt("Hallow01", 0, 11);
				Mod_Class::ClothX Cloths = Mod_Class::ClothX("MaleArena WarSpace_Horror", { 0, 141, 0, 164, 108, 0, 33, 0, 15, 0, 0, 277 }, { 0, iRan, 0, iRan, iRan, 0, 0, 0, 0, 0, 0, iRan }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });
				OnlineDress(Pedx, &Cloths);
			}
			else
			{
				int iRan = LessRandomInt("Hallow01", 0, 11);
				Mod_Class::ClothX Cloths = Mod_Class::ClothX("FemaleArena WarSpace_Horror", { 21, 141, 0, 205, 115, 0, 34, 0, 6, 0, 0, 290 }, { 0, iRan, 0, iRan, iRan, 0, 0, 0, 0, 0, 0, iRan }, { -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 });
				OnlineDress(Pedx, &Cloths);
			}
		}
		else
		{
			if ((int)pFixtures->Cothing.size() > 0 && pFixtures->Cloth_Pick < (int)pFixtures->Cothing.size())
			{
				Mod_Class::ClothX Cloths = pFixtures->Cothing[pFixtures->Cloth_Pick];
				OnlineDress(Pedx, &Cloths);
			}
			else
			{
				if (pFixtures->Male)
					OnlineDress(Pedx, &MaleDefault);
				else
					OnlineDress(Pedx, &FemaleDefault);
			}
		}

		Mod_Class::HairSets Hairs = pFixtures->MyHair;
		SetingtheHair(Pedx, &Hairs);

		PED::_SET_PED_HAIR_COLOR(Pedx, pFixtures->HairColour, pFixtures->HairStreaks);
		//****************Face****************
		for (int i = 0; i < pFixtures->MyOverlay.size(); i++)
		{
			int iColour = 0;

			if (i == 1)
			{
				iColour = 1;
			}//Facial Hair
			else if (i == 2)
			{
				iColour = 1;
			}//Eyebrows
			else if (i == 5)
			{
				iColour = 2;
			}//Blush
			else if (i == 8)
			{
				iColour = 2;
			}//Lipstick
			else if (i == 10)
			{
				iColour = 1;
			}//Chest Hair

			int iChange = pFixtures->MyOverlay[i].Overlay;
			int AddColour = pFixtures->MyOverlay[i].OverCol;
			float fVar = pFixtures->MyOverlay[i].OverOpc;

			PED::SET_PED_HEAD_OVERLAY(Pedx, i, iChange, fVar);

			if (iColour > 0)
				PED::_SET_PED_HEAD_OVERLAY_COLOR(Pedx, i, iColour, AddColour, 0);
		}

		if ((int)pFixtures->FaceScale.size() > 0)
		{
			for (int i = 0; i < (int)pFixtures->FaceScale.size(); i++)
				PED::_SET_PED_FACE_FEATURE(PLAYER::PLAYER_PED_ID(), i, pFixtures->FaceScale[i]);
		}
	}
	Ped PlayerPedGen(Mod_Class::Vector4 vLocal, Mod_Class::ClothBank* thisBrain, bool onFoot, bool bfriend)
	{
		if (thisBrain != nullptr)
		{
			WAIT(100);//Can overload and cause CTD if run multiple times.

			LoggerLight("PlayerPedGen == " + thisBrain->Model);

			Ped thisPed = NULL;
			Hash model = MyHashKey(thisBrain->Model);

			if (thisBrain->Model == "mp_m_freemode_01" || thisBrain->Model == "mp_f_freemode_01")
				thisBrain->FreeMode = true;
			else
				thisBrain->FreeMode = false;

			if (!STREAMING::IS_MODEL_VALID(model))
				model = MyHashKey("cs_chrisformage");

			STREAMING::REQUEST_MODEL(model);// Check if the model is valid
			if ((bool)STREAMING::IS_MODEL_IN_CDIMAGE(model) && (bool)STREAMING::IS_MODEL_VALID(model))
			{
				while (!STREAMING::HAS_MODEL_LOADED(model))
					WAIT(10);

				thisPed = PED::CREATE_PED(4, model, vLocal.X, vLocal.Y, vLocal.Z, vLocal.R, true, false);

				int iAccuracy = RandomInt(50, 75);
				PED::SET_PED_ACCURACY(thisPed, iAccuracy);
				PED::SET_PED_MAX_HEALTH(thisPed, 200);
				ENTITY::SET_ENTITY_HEALTH(thisPed, 200);

				AI::SET_PED_PATH_PREFER_TO_AVOID_WATER(thisPed, false);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(thisPed, 1, 1);

				PED::SET_PED_COMBAT_ABILITY(thisPed, 100);
				if (onFoot)
				{
					PED::SET_PED_CAN_SWITCH_WEAPON(thisPed, true);
					PED::SET_PED_COMBAT_MOVEMENT(thisPed, 2);
					AI::SET_PED_PATH_CAN_USE_CLIMBOVERS(thisPed, true);
					AI::SET_PED_PATH_CAN_USE_LADDERS(thisPed, true);
					AI::SET_PED_PATH_CAN_DROP_FROM_HEIGHT(thisPed, true);
					AI::SET_PED_PATH_PREFER_TO_AVOID_WATER(thisPed, false);
					PED::SET_PED_COMBAT_ATTRIBUTES(thisPed, 0, true);
					PED::SET_PED_COMBAT_ATTRIBUTES(thisPed, 1, true);
					PED::SET_PED_COMBAT_ATTRIBUTES(thisPed, 2, true);
					PED::SET_PED_COMBAT_ATTRIBUTES(thisPed, 3, true);
				}

				if (bfriend)
					RelGroupMember(thisPed, Gp_Follow);
				else
					RelGroupMember(thisPed, GP_Attack);

				if (thisBrain->FreeMode)
					OnlineFaces(thisPed, thisBrain);

				GunningIt(thisPed, -1);

				Ped_List.push_back(thisPed);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			}
			else
				thisPed = NULL;

			return thisPed;
		}
		else
			return NULL;
	}
	Ped PlayerPedGen(Mod_Class::Vector4 vLocal, int Set, int Subset, bool onFoot, bool bfriend)
	{
		Mod_Class::ClothBank PedBank = NewClothBank(Set, Subset);
		return PlayerPedGen(vLocal, &PedBank, onFoot, bfriend);;
	}
	Ped PlayerPedGen(Mod_Class::Vector4 vLocal, const std::string& sPed, bool onFoot, bool bfriend)
	{
		Mod_Class::ClothBank PedBank = NewClothBank(sPed);
		return PlayerPedGen(vLocal, &PedBank, onFoot, bfriend);;
	}
	void RepoPedPlayer(Ped Victim)
	{
		Ped YoPlaya = PLAYER::PLAYER_PED_ID();
		PLAYER::CHANGE_PLAYER_PED(PLAYER::PLAYER_ID(), Victim, true, true);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Victim);

		if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) != 28)
		{
			if (Mod_Settings.Random_Weapons)
				GunningIt(PLAYER::PLAYER_PED_ID(), 0);
			else
				ReturnPlayerWeapons();
		}
	}
	void ChangePlayer(Hash modelHash, int iWeap)
	{
		LoggerLight("ChangePlayer == " + std::to_string(modelHash));

		if (!STREAMING::IS_MODEL_VALID(modelHash))
			modelHash = MyHashKey("cs_chrisformage");

		if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash) && STREAMING::IS_MODEL_VALID(modelHash))
		{
			STREAMING::REQUEST_MODEL(modelHash);
			while (!STREAMING::HAS_MODEL_LOADED(modelHash))
				WAIT(1);

			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), modelHash);

			WAIT(1000);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(modelHash);
		}

		if (iWeap == -1)
			iWeap = RandomInt(2, 10);

		if (PED::GET_PED_TYPE(PLAYER::PLAYER_PED_ID()) != 28)
		{
			if (Mod_Settings.Random_Weapons)
				GunningIt(PLAYER::PLAYER_PED_ID(), iWeap);
			else
				ReturnPlayerWeapons();
		}
	}
	void ChangePlayer(int iSelect, int iSubset, int iWeap)
	{
		WAIT(1000);
		ChangePlayer(MyHashKey(RandomPed(iSelect, iSubset)), iWeap);
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), false);
	}
	void SavedPlayer(Mod_Class::ClothBank* MyBank, int iWeap)
	{
		if (MyBank != nullptr)
		{
			LoggerLight("SavedPlayer == " + MyBank->CharName);

			if (MyBank->ModelHash == 0)
				MyBank->ModelHash = MyHashKey(MyBank->Model);

			ChangePlayer(MyBank->ModelHash, iWeap);

			if (MyBank->FreeMode)
				OnlineFaces(PLAYER::PLAYER_PED_ID(), MyBank);
			else
				OnlineDress(PLAYER::PLAYER_PED_ID(), &MyBank->Cothing[MyBank->Cloth_Pick]);

			if (MyBank->Cothing[MyBank->Cloth_Pick].Badge.TatName != "")
				PED::_APPLY_PED_OVERLAY(PLAYER::PLAYER_PED_ID(), MyHashKey(MyBank->Cothing[MyBank->Cloth_Pick].Badge.BaseName), MyHashKey(MyBank->Cothing[MyBank->Cloth_Pick].Badge.TatName));

			if (MyBank->Voice != "")
				ThemVoices(MyBank->Voice);

			if (MyBank->Walkies != "")
				WalkingStyle(PLAYER::PLAYER_PED_ID(), MyBank->Walkies);

			if (MyBank->Moods != "")
				PullingFaces(MyBank->Moods);

			//****************Tattoos****************
			ApplyTats(PLAYER::PLAYER_PED_ID(), MyBank);
		}
	}

	std::string RandVeh(int iVechList, int iSubSet)
	{
		LoggerLight("RandVeh, iVechList == " + std::to_string(iVechList));

		std::string sVeh = "ZENTORNO";

		if (iVechList == 1)
			sVeh = PreVeh_01[LessRandomInt("RandVeh01", 0, (int)PreVeh_01.size() - 1)];//Boats
		else if (iVechList == 3)
			sVeh = PreVeh_02[LessRandomInt("RandVeh02", 0, (int)PreVeh_02.size() - 1)];//Posh
		else if (iVechList == 4)
			sVeh = PreVeh_03[LessRandomInt("RandVeh03", 0, (int)PreVeh_03.size() - 1)];//Mid
		else if (iVechList == 5)
			sVeh = PreVeh_04[LessRandomInt("RandVeh04", 0, (int)PreVeh_04.size() - 1)];//low
		else if (iVechList == 6)
			sVeh = "VOLATUS";
		else if (iVechList == 11)
			sVeh = "CADDY";
		else if (iVechList == 14)
			sVeh = "TRACTOR2";
		else if (iVechList == 15)
		{
			if (iSubSet == 1)
				sVeh = "TRIBIKE";      //Racer
			else if (iSubSet == 2)
				sVeh = "SCORCHER";     //Mountain
			else if (iSubSet == 3)
				sVeh = "BMX";      //BMX
			else
				sVeh = "CRUISER";      //Cruser
		}
		else if (iVechList == 18)
		{
			if (iSubSet == 7)
				sVeh = "STOCKADE";  //"Armoured Van Security 2"); 
			else if (iSubSet == 8)
				sVeh = "DILETTANTE2"; //"Security Guard"); 
			else if (iSubSet == 11)
				sVeh = PreVeh_05[LessRandomInt("RandVeh05", 0, (int)PreVeh_05.size() - 1)];//low//"construction Worker 2"); 
			else if (iSubSet == 12)
				sVeh = "HANDLER"; //"Dock Worker");  
			else if (iSubSet == 13)
				sVeh = "AIRTUG";  //Airport
			else if (iSubSet == 14)
				sVeh = "TRASH2";  //"Garbage Worker");  
			else if (iSubSet == 17)
				sVeh = PreVeh_06[LessRandomInt("RandVeh06", 0, (int)PreVeh_06.size() - 1)]; //"Transport Worker Male");  
			else if (iSubSet == 19)
				sVeh = "BOXVILLE2";  //"Postal Worker Male 2");  
			else if (iSubSet == 20)
				sVeh = PreVeh_06[LessRandomInt("RandVeh06", 0, (int)PreVeh_06.size() - 1)]; //"Transport Worker Male");  
			else if (iSubSet == 21)
				sVeh = "BOXVILLE2";  //"Postal Worker Male 2");  
		}
		else if (iVechList == 19)
			sVeh = "SEASHARK";
		else if (iVechList == 20)
			sVeh = PreVeh_07[LessRandomInt("RandVeh07", 0, (int)PreVeh_07.size() - 1)];//bikeAtv
		else if (iVechList == 21)
		{
			if (iSubSet == 1)
				sVeh = "BLAZER2"; //"Baywatch 
			else if (iSubSet == 2)
				sVeh = "PREDATOR";  //"US Coastguard
			else if (iSubSet == 3)
				sVeh = PreVeh_08[LessRandomInt("RandVeh08a", 8, (int)PreVeh_08.size() - 2)]; //><!--Cops
			else if (iSubSet == 4)
				sVeh = PreVeh_08[4]; //><!-- PoliceBike
			else if (iSubSet == 5)
				sVeh = PreVeh_08[5];//><!-- Ranger
			else if (iSubSet == 6)
				sVeh = PreVeh_08[LessRandomInt("RandVeh08b", 6, 7)]; //><!-- Sherif
			else if (iSubSet == 7)
				sVeh = PreVeh_08[LessRandomInt("RandVeh08b", 0, 2)];  //><!-- fib
			else if (iSubSet == 8)
				sVeh = PreVeh_08[(int)PreVeh_08.size() - 1]; //><!-- swat
			else if (iSubSet == 9)
				sVeh = PreVeh_09[LessRandomInt("RandVeh09", 0, (int)PreVeh_09.size() - 1)]; //military
			else if (iSubSet == 10)
				sVeh = "AMBULANCE"; //medic
			else
				sVeh = "FIRETRUK";  //fireman
		}
		else if (iVechList == 22)
		{
			if (iSubSet == 1)
				sVeh = PreVeh_10[LessRandomInt("RandVeh10a", 17, (int)PreVeh_10.size() - 1)];  //civilian
			else if (iSubSet == 2)
				sVeh = PreVeh_10[LessRandomInt("RandVeh10b", 0, 18)];    //milatary
			else
				sVeh = PreVeh_11[LessRandomInt("RandVeh11", 0, (int)PreVeh_11.size() - 1)];   //helitours
		}
		else if (iVechList == 24)
			sVeh = PreVeh_12[LessRandomInt("RandVeh12", 0, (int)PreVeh_12.size() - 1)];
		else if (iVechList == 50)
			sVeh = "Mule";
		else //if (iVechList == 25)
			sVeh = PreVeh_13[LessRandomInt("RandVeh13", 0, (int)PreVeh_13.size() - 1)];

		return sVeh;
	}
	bool IsItARealVehicle(const std::string& sVehName)
	{
		LoggerLight("IsItARealVehicle, sVehName == " + sVehName);

		bool bIsReal = false;
		if ((bool)STREAMING::IS_MODEL_A_VEHICLE(MyHashKey(sVehName)))
			bIsReal = true;

		return bIsReal;
	}
	bool HasASeat(Vehicle vMe)
	{
		bool bIn = false;
		if (vMe != NULL)
		{
			if (FindUSeat(vMe) > -1)
				bIn = true;
		}
		return bIn;
	}

	Vehicle VehicleSpawn(Mod_Class::Veh_Set vehSet)
	{//Fix the player to drive till press buutton and fly and other stuuff
		LoggerLight("SpawnVehicle");

		Vehicle thisVeh = NULL;
		WAIT(100);
		std::string sVehModel = vehSet.Model;

		if (!IsItARealVehicle(sVehModel))
			sVehModel = "MAMBA";

		vehSet.ModelHash = MyHashKey(sVehModel);

		if ((bool)STREAMING::IS_MODEL_IN_CDIMAGE(vehSet.ModelHash) && (bool)STREAMING::IS_MODEL_A_VEHICLE(vehSet.ModelHash))
		{
			STREAMING::REQUEST_MODEL(vehSet.ModelHash);
			while (!(bool)STREAMING::HAS_MODEL_LOADED(vehSet.ModelHash))
				WAIT(1);

			thisVeh = VEHICLE::CREATE_VEHICLE(vehSet.ModelHash, vehSet.SpawnPoint.X, vehSet.SpawnPoint.Y, vehSet.SpawnPoint.Z, vehSet.SpawnPoint.R, true, true);

			if (vehSet.IsHeli || vehSet.IsPlane)
			{
				int iClass = VEHICLE::GET_VEHICLE_CLASS(thisVeh);
				MaxOutAllModsNoWheels(thisVeh, iClass);
			}
			else
				MakeModsNotWar(thisVeh, RandVehModsist());

			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(thisVeh, 1, 1);

			Ped DesDriver = NULL;

			int iSeating = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(thisVeh);

			if (!vehSet.PlayerDriver && vehSet.PlayerInVeh && iSeating == 0)
			{
				vehSet.PlayerDriver = true;
				vehSet.FillVeh = false;
			}

			if (vehSet.PlayerDriver)
			{
				MoveEntity(PLAYER::PLAYER_PED_ID(), vehSet.SpawnPoint);
				DesDriver = PLAYER::PLAYER_PED_ID();
				WarptoAnyVeh(thisVeh, DesDriver, -1);
			}

			if (vehSet.FillVeh)
			{
				int iStart = 0;

				if (!vehSet.PlayerDriver)
				{
					DesDriver = PlayerPedGen(vehSet.SpawnPoint, vehSet.Select, vehSet.SubSet, false, vehSet.bFriend);
					WarptoAnyVeh(thisVeh, DesDriver, -1);

					if (vehSet.PlayerInVeh)
					{
						MoveEntity(PLAYER::PLAYER_PED_ID(), vehSet.SpawnPoint);
						WarptoAnyVeh(thisVeh, PLAYER::PLAYER_PED_ID(), 0);
						iStart++;
					}
				}

				for (int i = iStart; i < iSeating; i++)
				{
					LoggerLight("Fill Vehicle with peds");
					Ped CarPed = PlayerPedGen(vehSet.SpawnPoint, vehSet.Select, vehSet.SubSet, false, vehSet.bFriend);
					WarptoAnyVeh(thisVeh, CarPed, i);
				}
			}

			if (vehSet.DriveTo.size() > 1)
			{
				Drive_Fly_On(DesDriver, thisVeh, vehSet.DriveTo, vehSet.IsPlane, vehSet.IsHeli, vehSet.PlayerDriver, vehSet.RanDriveTo);
			}

			Vehicle_List.push_back(thisVeh);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehSet.ModelHash);
		}
		else
			thisVeh = NULL;

		return thisVeh;
	}

	std::vector<Ped> CollectPeds()
	{
		const int PED_ARR_SIZE = 1024;
		Ped Pedds[PED_ARR_SIZE];
		int Pedcount = worldGetAllPeds(Pedds, PED_ARR_SIZE);
		std::vector<Ped> NpcList = {};

		for (int i = 0; i < Pedcount; i++)
		{
			Ped Pent = Pedds[i];
			if (Pent != NULL && ENTITY::DOES_ENTITY_EXIST(Pent))
			{
				if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(Pent))
					NpcList.push_back(Pent);
			}
		}
		return NpcList;
	}
	Ped NearByPed(Mod_Class::Vector4 vArea, float areaMin, float areaMax)
	{
		Ped Pedlass = NULL;

		Ped PlayerPed = PLAYER::PLAYER_PED_ID();

		const int PED_ARR_SIZE = 1024;
		Ped Pedds[PED_ARR_SIZE];
		int Pedcount = worldGetAllPeds(Pedds, PED_ARR_SIZE);
		std::vector<Ped> NpcList = {};
		std::vector<Ped> AnimalList = {};

		for (int i = 0; i < Pedcount; i++)
		{
			Ped Pent = Pedds[i];
			if (Pent != NULL && ENTITY::DOES_ENTITY_EXIST(Pent))
			{
				if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(Pent) && Mod_Maths::DistanceTo(vArea, Mod_Maths::EntPosition(Pent)) > areaMin && Mod_Maths::DistanceTo(vArea, Mod_Maths::EntPosition(Pent)) < areaMax)
				{
					if (PED::GET_PED_TYPE(Pent) == 28)
						AnimalList.push_back(Pent);
					else
						NpcList.push_back(Pent);
				}
			}
		}

		for (int i = 0; i < (int)NpcList.size(); i++)
		{
			Ped MadP = NpcList[i];

			if (ENTITY::DOES_ENTITY_EXIST(MadP))
			{
				if (MadP != PlayerPed && !(bool)ENTITY::IS_ENTITY_DEAD(MadP) && Mod_Maths::EntPosition(MadP).z > -10)
				{
					Pedlass = MadP;
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Pedlass, 1, 1);
					break;
				}
			}
		}

		if (Pedlass == NULL)
		{
			for (int i = 0; i < (int)AnimalList.size(); i++)
			{
				Ped MadP = AnimalList[i];

				if (ENTITY::DOES_ENTITY_EXIST(MadP))
				{
					if (MadP != PlayerPed && !(bool)ENTITY::IS_ENTITY_DEAD(MadP))
					{
						Pedlass = MadP;
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Pedlass, 1, 1);
						break;
					}
				}
			}
		}
		return Pedlass;
	}

	void SideAdviceNote()
	{
		Side_Add_Time = InGameTime() + 7000;
		Disp_Pick = Space38(RSLangMenu[LessRandomInt("BadAdvice", 194, 208)]);
		Disp_Advice = true;
	}
	void Reicarnations()
	{
		LoggerLight("Reicarnations");

		Mod_Maths::AnyPreActives(0, false);
		Mod_Class::Vector4 DeathPlace = Mod_Maths::FindPedSpPoint(Mod_Maths::PlayerPosi());
		Ped Bob = NULL;

		if (!Mod_Settings.ReCurr || !Mod_Settings.Saved_Ped)
			Bob = NearByPed(DeathPlace, 35.0f, 500.0f);

		while ((bool)ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
			WAIT(1);

		WAIT(1000);

		if (Mod_Settings.ReCurr)
			MoveEntity(PLAYER::PLAYER_PED_ID(), DeathPlace);
		else if (Mod_Settings.Saved_Ped)
		{
			MoveEntity(PLAYER::PLAYER_PED_ID(), DeathPlace);
			Mod_Class::ClothBank bank = SavedPeds[LessRandomInt("SavedPedFind", 1, (int)SavedPeds.size() - 1)];
			SavedPlayer(&bank, -1);
		}
		else
		{
			if (Bob != NULL && !Yankton_Loaded)
				RepoPedPlayer(Bob);
			else 
			{
				if (Yankton_Loaded)
					ChangePlayer(24, 0, 5);
				else if (Cayo_Loaded)
					ChangePlayer(25, 3, 4);
				else
					ChangePlayer(4, 0, 1);

				MoveEntity(PLAYER::PLAYER_PED_ID(), DeathPlace);
			}
		}

		RandomWeatherTime();
		Play_Wav(Ahhhh);
		CAM::DO_SCREEN_FADE_IN(1500);
		SideAdviceNote();

		Vector3 Campo = Mod_Maths::PlayerPosi();
		Vector3 Camro = Mod_Maths::NewVector3(-90.00f, 0.00f, 0.00f);
		UI::DISPLAY_RADAR(false);
		Campo.z += 155.00f;
		char* Cams = "DEFAULT_SCRIPTED_CAMERA";
		Camera cCams = CAM::CREATE_CAM_WITH_PARAMS(Cams, Campo.x, Campo.y, Campo.z, Camro.x, Camro.y, Camro.z, 150.00f, true, 2);
		CAM::RENDER_SCRIPT_CAMS(1, 1, cCams, 0, 0);
		WAIT(3000);
		while (CAM::GET_CAM_COORD(cCams).z > Mod_Maths::PlayerPosi().z + 2.00f)
		{
			Campo.z -= 1.00f;
			CAM::SET_CAM_COORD((Any)cCams, Campo.x, Campo.y, Campo.z);
			WAIT(1);
		}
		CAM::RENDER_SCRIPT_CAMS(0, 1, 0, 0, 0);
		CAM::DESTROY_CAM(cCams, true);
		UI::DISPLAY_RADAR(true);
	}//ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
	const std::vector<std::string> fluids = {
		"scr_solomon3",
		"scr_trev4_747_blood_splash",
		"cut_trevor1",
		"cs_trev1_blood_pool",
	};
	void EasyWayOut(Ped Vic)
	{
		WEAPON::GIVE_WEAPON_TO_PED(Vic, MyHashKey("WEAPON_pistol"), 100, false, true);
		WEAPON::SET_CURRENT_PED_WEAPON(Vic, MyHashKey("WEAPON_pistol"), true);
		WAIT(450);
		ForceAnim(Vic, "mp_suicide", "pistol", Mod_Maths::GetPosV4(Vic));
		AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "GENERIC_CURSE_HIGH", Vic, 0, 0, 0);
		WAIT(700);
		int WaitHere = InGameTime() + 200;
		while (true)
		{
			if (WaitHere < InGameTime())
				break;
			if ((bool)STREAMING::HAS_NAMED_PTFX_ASSET_LOADED((LPSTR)fluids[0].c_str()))
			{
				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL((LPSTR)fluids[0].c_str());
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY((LPSTR)fluids[1].c_str(), Vic, 0.0f, 0.15f, 0.75f, 0.0f, 0.0f, 90.0f, 1.0f, false, false, false);
			}
			else
				STREAMING::REQUEST_NAMED_PTFX_ASSET((LPSTR)fluids[0].c_str());

			if ((bool)STREAMING::HAS_NAMED_PTFX_ASSET_LOADED((LPSTR)fluids[2].c_str()))
			{
				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL((LPSTR)fluids[2].c_str());
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY((LPSTR)fluids[3].c_str(), Vic, 0.0f, 0.15f, 0.75f, 0.0f, 0.0f, 90.0f, 0.5f, false, false, false);
			}
			else
				STREAMING::REQUEST_NAMED_PTFX_ASSET((LPSTR)fluids[2].c_str());

			WAIT(1);
		}
		//AddDecals(Mod_Maths::FowardOf(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Vic), 0.01, true), 1017, 10.00f, 10.0f);
		ENTITY::SET_ENTITY_HEALTH(Vic, 1);
	}
	void CayoAudio()
	{
		if (Cayo_Loaded)
		{
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_01_left", true);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_02_right", true);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_03_reverb", true);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_04_reverb", true);
		}
		else
		{
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_01_left", false);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_02_right", false);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_03_reverb", false);
			AUDIO::SET_STATIC_EMITTER_ENABLED("se_dlc_hei4_island_beach_party_music_new_04_reverb", false);
		}
	}
	void CayoPartay()
	{
		const std::vector<Mod_Class::Vector4> CayoPartays = {
			Mod_Class::Vector4(4894.263f, -4913.141f, 3.36446f, 0.0f),     //Dance Rad == 5    00
			Mod_Class::Vector4(4890.318f, -4923.923f, 3.368097f, 0.0f),    //Dance Rad == 8    01
			Mod_Class::Vector4(4900.574f, -4923.098f, 3.36113f, 0.0f),     //Sit  Rad == 3     02
			Mod_Class::Vector4(4883.7f, -4916.323f, 3.368711f, 0.0f),      //Sit  Rad == 3     03
			Mod_Class::Vector4(4888.34f, -4933.511f, 3.367885f, 0.0f),     //Sit  Rad == 3     04
			Mod_Class::Vector4(4882.221f, -4933.872f, 3.37767f, 0.0f),     //Sit  Rad == 3     05
			Mod_Class::Vector4(4897.382f, -4938.688f, 3.362702f, 0.0f),    //Sit  Rad == 3     06
			Mod_Class::Vector4(4901.941f, -4935.71f, 3.363577f, 0.0f),     //Sit  Rad == 3     07
			Mod_Class::Vector4(4908.562f, -4934.384f, 3.367695f, 0.0f)     //Sit  Rad == 3	   08
		};

		const std::vector<Mod_Class::Vector4> CayoLay = {
			Mod_Class::Vector4(4878.054f, -4948.04f, 3.556281f, 91.67182f),
			Mod_Class::Vector4(4875.837f, -4950.161f, 3.629188f, 351.4073f),
			Mod_Class::Vector4(4874.032f, -4947.307f, 3.575044f, 242.7412f),
			Mod_Class::Vector4(4876.772f, -4946.251f, 3.520398f, 146.6341f),
			Mod_Class::Vector4(4872.481f, -4911.394f, 3.003824f, 294.576f),
			Mod_Class::Vector4(4872.82f, -4917.226f, 2.915241f,271.9123f),
			Mod_Class::Vector4(4871.187f, -4917.283f, 2.847157f,341.5042f),
			Mod_Class::Vector4(4871.44f, -4910.393f, 2.946956f, 288.3906f),
			Mod_Class::Vector4(4872.479f, -4911.321f, 3.003426f ,119.555f),
			Mod_Class::Vector4(4866.439f, -4906.744f, 2.577915f,106.9248f),
			Mod_Class::Vector4(4867.695f, -4910.954f, 2.650635f, 110.5905f),
			Mod_Class::Vector4(4867.171f, -4909.43f, 2.605493f ,101.497f),
			Mod_Class::Vector4(4868.493f, -4913.752f, 2.716372f, 283.9765f),
			Mod_Class::Vector4(4869.915f, -4921.263f, 2.879118f ,278.9364f),
			Mod_Class::Vector4(4868.144f, -4943.559f, 2.709443f,246.9356f),
			Mod_Class::Vector4(4862.854f, -4956.314f, 2.491656f, 64.97399f),
			Mod_Class::Vector4(4863.502f, -4955.183f, 2.544171f,78.42456f)
		};

		int iRan = RandomInt(4, 7);
		for (int i = 0; i < iRan; i++)
		{
			Mod_Class::Vector4 vDance = Mod_Maths::InAreaOf(CayoPartays[0], 2.0f, 5.0f);
			Ped Dancer = PlayerPedGen(vDance, 1, 0, true, true);
			CayDancers.push_back(Dancer);
			DanceDanceDance(Dancer);
		}

		iRan = RandomInt(7, 13);

		for (int i = 0; i < iRan; i++)
		{
			Mod_Class::Vector4 vDance = Mod_Maths::InAreaOf(CayoPartays[1], 2.0f, 8.0f);
			Ped Dancer = PlayerPedGen(vDance, 1, 0, true, true);
			CayDancers.push_back(Dancer);
			DanceDanceDance(Dancer);
		}

		for (int i = 2; i < CayoPartays.size(); i++)
		{
			Entity Chair = NULL;
			Chair = FindingProps(CayoPartays[i], 3.0f, "h4_prop_h4_couch_01a");

			if (Chair == NULL)
				Chair = FindingProps(CayoPartays[i], 3.0f, "h4_prop_h4_chair_01a");

			if (Chair != NULL)
			{
				ENTITY::FREEZE_ENTITY_POSITION(Chair, true);
				Mod_Class::Vector4 SunPos = Mod_Maths::GetPosV4(Chair);
				Ped Sitter = PlayerPedGen(SunPos, 1, 0, true, true);
				TakeAChair(Sitter, SunPos);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			Ped SunS = PlayerPedGen(CayoLay[i], 1, 0, true, true);
			SunningIt(SunS, CayoLay[i]);
		}

		for (int i = 4; i < CayoLay.size(); i++)
		{
			if (RandomInt(0, 20) < 10)
			{
				Ped SunS = PlayerPedGen(CayoLay[i], 1, 0, true, true);
				SunningIt(SunS, CayoLay[i]);
			}
		}

		Ped Dj = PlayerPedGen(Mod_Class::Vector4(4893.571f, -4905.296f, 3.481121f, 192.4766f), "IG_SSS", true, true);
		DanceDanceDance(Dj);
		Ped Bar = PlayerPedGen(Mod_Class::Vector4(4902.647f, -4943.707f, 3.392626f, 46.24336f), "S_F_Y_BeachBarStaff_01", true, true);
		DanceDanceDance(Bar);

		CayoAudio();
	}
}

namespace Mod_Ui
{
	int AddScreenText(int font, const std::string& caption, float textLeftScaled, float lineTopScaled, float lineHeightScaled, float text_scale, int text_col[4])
	{
		// text upper part
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_CENTRE(0);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
		UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

		// text lower part
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_CENTRE(0);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::_SET_TEXT_GXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
		return UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	}
	void AddSprite(const std::string& spriteLocation, const std::string& spriteName, float posX, float posY, float sizeX, float sizeY, float heading)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((LPSTR)spriteLocation.c_str()))
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((LPSTR)spriteLocation.c_str(), true);

		int red = 255;
		int blue = 255;
		int green = 255;
		int alpha = 255;

		int iWidth, iHeight;
		GRAPHICS::GET_SCREEN_RESOLUTION(&iWidth, &iHeight);

		float num = (float)iWidth / (float)iHeight;
		float num2 = (float)1080.0 * num;
		float width = posX / num2;
		float height = posY / 1080;
		float screenX = sizeX / num2 + width * 0.5f;
		float screenY = sizeY / 1080 + height * 0.5f;
		GRAPHICS::DRAW_SPRITE((LPSTR)spriteLocation.c_str(), (LPSTR)spriteName.c_str(), screenX, screenY, width, height, heading, red, green, blue, alpha);
	}
	void Draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7)
	{
		GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
	}
	void DrawSessionList(const std::string& caption, const std::string& level, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, float textLeft2, bool active, bool title, int position)
	{
		// default values
		int text_col[4] = { 255, 255, 255, 255 },
			rect_col[4] = { 0, 0, 0, 120 };
		float text_scale = 0.50;
		int font = 4;

		// correcting values for active line
		if (title)
		{
			rect_col[0] = 0;
			rect_col[1] = 0;
			rect_col[2] = 0;
			rect_col[3] = 250;
		}

		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

		textLeft += lineLeft;
		textLeft2 += lineLeft;

		float lineWidthScaled = lineWidth / (float)screen_w; // line width
		float lineTopScaled = lineTop / (float)screen_h; // line top offset
		float textLeftScaled = textLeft / (float)screen_w; // text left offset
		float textLeftScaled2 = textLeft2 / (float)screen_w; // text left offset
		float lineHeightScaled = lineHeight / (float)screen_h; // line height

		float lineLeftScaled = lineLeft / (float)screen_w;

		// this is how it's done in original scripts

		// text upper part
		int num25 = AddScreenText(font, caption, textLeftScaled, lineTopScaled, lineHeightScaled, text_scale, text_col);
		int num26 = AddScreenText(font, level, textLeftScaled2, lineTopScaled, lineHeightScaled, text_scale, text_col);
		// rect
		Draw_rect(lineLeftScaled, lineTopScaled + (0.00278f), lineWidthScaled, ((((float)(num25)*UI::_0xDB88A37483346780(text_scale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f), rect_col[0], rect_col[1], rect_col[2], rect_col[3]);

		if (active)
		{
			float PosX = 55.5;
			float PosY = 62.0;
			float sizeX = 352.0;
			float sizeY = 51.0;
			float Heading = 0.0;

			float iTimes1 = 1.0;
			float iTimes2 = 33.0;

			AddSprite("mpleaderboard", "leaderboard_globe_icon", PosX, PosY + (float)position * iTimes1, sizeX, sizeY + (float)position * iTimes2, 0.0);
		}
	}
	void Draw_menu_line(const std::string& caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText)
	{
		// default values
		int text_col[4] = { 255, 255, 255, 245 },
			rect_col[4] = { 0, 0, 0, 200 };
		float text_scale = 0.35;
		int font = 0;

		// correcting values for active line
		if (active)
		{
			text_col[0] = 0;
			text_col[1] = 0;
			text_col[2] = 0;

			rect_col[0] = 255;
			rect_col[1] = 255;
			rect_col[2] = 255;

			if (rescaleText) text_scale = 0.40;
		}

		if (title)
		{
			rect_col[0] = 112;
			rect_col[1] = 44;
			rect_col[2] = 20;

			if (rescaleText) text_scale = 0.50;
			font = 1;
		}

		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

		textLeft += lineLeft;

		float lineWidthScaled = lineWidth / (float)screen_w; // line width
		float lineTopScaled = lineTop / (float)screen_h; // line top offset
		float textLeftScaled = textLeft / (float)screen_w; // text left offset
		float lineHeightScaled = lineHeight / (float)screen_h; // line height

		float lineLeftScaled = lineLeft / (float)screen_w;

		// this is how it's done in original scripts
		int num25 = AddScreenText(font, caption, textLeftScaled, lineTopScaled, lineHeightScaled, text_scale, text_col);

		// rect
		Draw_rect(lineLeftScaled, lineTopScaled + (0.00278f), lineWidthScaled, ((((float)(num25)*UI::_0xDB88A37483346780(text_scale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f),
			rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
	}
	void Draw_menu_line_Numbers(const std::string& caption, int number, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, float textLeft2, bool active, bool title, bool rescaleText)
	{
		// default values
		int text_col[4] = { 255, 255, 255, 245 },
			rect_col[4] = { 0, 0, 0, 200 };
		float text_scale = 0.35;
		int font = 0;

		if (rescaleText)
			text_scale = 0.20;
		// correcting values for active line
		if (active)
		{
			text_col[0] = 0;
			text_col[1] = 0;
			text_col[2] = 0;

			rect_col[0] = 255;
			rect_col[1] = 255;
			rect_col[2] = 255;

		}

		if (title)
		{
			rect_col[0] = 112;
			rect_col[1] = 44;
			rect_col[2] = 20;

			if (rescaleText) text_scale = 0.50;
			font = 1;
		}

		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

		textLeft += lineLeft;

		float lineWidthScaled = lineWidth / (float)screen_w; // line width
		float lineTopScaled = lineTop / (float)screen_h; // line top offset
		float textLeftScaled = textLeft / (float)screen_w; // text left offset
		float lineHeightScaled = lineHeight / (float)screen_h; // line height

		float textLeftScaled2 = textLeft2 / (float)screen_w; // text left offset

		float lineLeftScaled = lineLeft / (float)screen_w;

		// this is how it's done in original scripts
		int num25 = AddScreenText(font, caption, textLeftScaled, lineTopScaled, lineHeightScaled, text_scale, text_col);

		int num26 = AddScreenText(font, std::to_string(number), textLeftScaled2, lineTopScaled, lineHeightScaled, text_scale, text_col);
		// rect
		Draw_rect(lineLeftScaled, lineTopScaled + (0.00278f), lineWidthScaled, ((((float)(num25)*UI::_0xDB88A37483346780(text_scale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f),
			rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
	}
	int BottomRight(std::vector<int>& iButtons, std::vector<std::string>& sInstuctions)
	{
		std::string CharCon = "instructional_buttons";
		int iScale = GRAPHICS::REQUEST_SCALEFORM_MOVIE((LPSTR)CharCon.c_str());

		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(iScale))
			WAIT(1);

		CharCon = "CLEAR_ALL";
		GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(iScale, (LPSTR)CharCon.c_str());
		CharCon = "TOGGLE_MOUSE_BUTTONS";
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(iScale, (LPSTR)CharCon.c_str());
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(0);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();

		CharCon = "CREATE_CONTAINER";
		GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(iScale, (LPSTR)CharCon.c_str());//Was---_CALL_SCALEFORM_MOVIE_FUNCTION_VOID

		int iAddOns = 0;

		for (int i = 0; i < (int)iButtons.size(); i++)
		{
			CharCon = "SET_DATA_SLOT";
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(iScale, (LPSTR)CharCon.c_str());
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(iAddOns);
			GRAPHICS::_0xE83A3E3557A56640(CONTROLS::_GET_CONTROL_ACTION_NAME(2, iButtons[i], 1));
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING((LPSTR)sInstuctions[i].c_str());
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
			iAddOns++;
		}
		CharCon = "DRAW_INSTRUCTIONAL_BUTTONS";
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(iScale, (LPSTR)CharCon.c_str());
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(-1);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();

		return iScale;
	}
	void CloseBaseHelpBar(int CloseMe)
	{
		int SF = CloseMe;
		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&SF);
	}
	int Get_Int_Length(int iLeg)
	{
		int iDis = 0;
		if (iLeg < -1000)
			iDis = 5;
		else if (iLeg < -100)
			iDis = 4;
		else if (iLeg < -10)
			iDis = 3;
		else if (iLeg < 0)
			iDis = 2;
		else if (iLeg < 10)
			iDis = 1;
		else if (iLeg < 100)
			iDis = 2;
		else if (iLeg < 1000)
			iDis = 3;
		else
			iDis = 4;

		return iDis;
	}
	bool CloseAll = false;

	void ShowText(float x, float y, float scale, const std::string& text, int font, Mod_Class::RGBA rgba, bool outline)
	{
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scale, scale);
		UI::SET_TEXT_COLOUR(rgba.R, rgba.G, rgba.B, rgba.A);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(0);
		if (outline)
			UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)text.c_str());
		UI::_DRAW_TEXT(x, y);
	}
	void ShowPlayerLabel(Vector3 location, float baseSize, const std::vector<std::string>& textLines)
	{
		Vector3 cameraPos = CAM::GET_GAMEPLAY_CAM_COORD();
		float distance = Mod_Maths::DistanceTo(cameraPos, location);
		float totalMult = baseSize / (distance * (CAM::GET_GAMEPLAY_CAM_FOV() / 60.0f));

		float height = 0.0125f * totalMult;
		Mod_Class::RGBA fontColor = Mod_Class::RGBA(255, 255, 255, 255);
		GRAPHICS::SET_DRAW_ORIGIN(location.x, location.y, location.z, 0);
		int i = 0;

		for (auto line : textLines) {

			ShowText(0.0f, 0.0f + height * i, 0.2f * totalMult, line, 0, fontColor, true);
			i++;
		}

		GRAPHICS::CLEAR_DRAW_ORIGIN();
	}
	void BigMessage(const std::string& message, const std::string& message2, int colour)
	{
		int iScale = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MIDSIZED_MESSAGE");

		WAIT(1500);
		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(iScale))
			WAIT(1);

		GRAPHICS::_START_SCREEN_EFFECT("SuccessNeutral", 8500, false);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(iScale, "SHOW_SHARD_MIDSIZED_MESSAGE");
		GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)message.c_str());
		GRAPHICS::_END_TEXT_COMPONENT();
		GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)message2.c_str());
		GRAPHICS::_END_TEXT_COMPONENT();
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(colour);// color 0,1=white 2=black 3=grey 6,7,8=red 9,10,11=blue 12,13,14=yellow 15,16,17=orange 18,19,20=green 21,22,23=purple 
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();

		int iWait4 = InGameTime() + 8000;

		while (iWait4 > InGameTime())
		{
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(iScale, 255, 255, 255, 255, 2);
			WAIT(1);
		}

		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&iScale);
	}
	void TopLeft(const std::string& sText)
	{
		UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)sText.c_str());
		UI::_DISPLAY_HELP_TEXT_FROM_STRING_LABEL(0, 0, 1, 5000);
	}
	int BottomLeft(const std::string& sText)
	{
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)sText.c_str());
		return UI::_DRAW_NOTIFICATION(1, 1);
	}
	int BottomLeftIcon(const std::string& sText1, const std::string& sText2, const std::string& subject, const std::string& badge, const std::string& clanTag)
	{
		//badge = "CHAR_SOCIAL_CLUB";
		// clanTag = "__EXAMPLE"

		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)sText1.c_str());
		///char* picName1, char* picName2, BOOL flash, int iconType1, char* sender, char* subject, float duration, char* clanTag, int iconType2, int p9
		UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2((LPSTR)badge.c_str(), (LPSTR)badge.c_str(), 0, 7, (LPSTR)sText2.c_str(), (LPSTR)subject.c_str(), 3.0, (LPSTR)clanTag.c_str(), 7, 0);
		return UI::_DRAW_NOTIFICATION(1, 1);
	}
	std::vector<std::string> LastMessage = {};
	void RightSide(const std::string& caption, int iPos)
	{
		int text_col[4] = { 255, 255, 255, 255 },
			rect_col[4] = { 0, 0, 0, 120 };
		float text_scale = 0.5;
		int font = 4;

		float lineTop = 251.0f + iPos * 22.5f;
		float lineHeight = 49.5;
		float lineLeft = 1000.0;
		float textLeft = -10.0;

		// correcting values for active line
		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

		textLeft += lineLeft;

		float lineTopScaled = lineTop / (float)screen_h; // line top offset
		float textLeftScaled = textLeft / (float)screen_w; // text left offset
		float lineHeightScaled = lineHeight / (float)screen_h; // line height

		float lineLeftScaled = lineLeft / (float)screen_w;

		// this is how it's done in original scripts

		// text upper part
		int num25 = AddScreenText(font, caption, textLeftScaled, lineTopScaled, lineHeightScaled, text_scale, text_col);
	}
	void AddGraphics(const std::string& graphics)
	{
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_xm_orbital");
	}

	int Menu_interval = 150;
	void MeunDescrition(Mod_Class::MeunSystem* myMenu, std::vector<std::string>& Descrip, bool reSize)
	{
		if (myMenu != nullptr)
		{
			for (int i = 0; i < (int)Descrip.size(); i++)
				Draw_menu_line(Descrip[i], myMenu->_Screen.lineWidth, myMenu->_Screen.lineHeight, myMenu->_Screen.lineTop + (i + myMenu->High - myMenu->Low + 0.1f) * myMenu->_Screen.lineTobSpace, myMenu->_Screen.lineLeft, myMenu->_Screen.textLeft, false, false, reSize);
		}
	}
	void MenuDisplay(Mod_Class::MeunSystem* myMenu, float screenHeightScaleFactor)
	{
		if (myMenu != nullptr)
		{
			myMenu->_Exit = false;
			myMenu->_Activate = false;
			myMenu->_Left = false;
			myMenu->_Right = false;
			std::vector<std::string> Descrip = Space38(myMenu->Menu_Form[myMenu->Index].Description);

			if (myMenu->Menu_Form.size() > 0)
			{
				drawTexture(MyBannerPng, 1, 10, 100, myMenu->_Screen.sizeX, myMenu->_Screen.sizeY, myMenu->_Screen.centerX, myMenu->_Screen.centerY, myMenu->_Screen.posX, myMenu->_Screen.posY, myMenu->_Screen.rotation, screenHeightScaleFactor, myMenu->_Screen.red, myMenu->_Screen.green, myMenu->_Screen.blue, myMenu->_Screen.alfa);
				for (int i = myMenu->Low; i < myMenu->High; i++)
				{
					if (i != myMenu->Index)
					{
						if (myMenu->Menu_Form[i].TickBox)
						{
							Draw_menu_line(myMenu->Menu_Form[i].Title, myMenu->_Screen.lineWidth, myMenu->_Screen.lineHeight, myMenu->_Screen.lineTop + (i - myMenu->Low) * myMenu->_Screen.lineTobSpace, myMenu->_Screen.lineLeft, myMenu->_Screen.textLeft, false, false, false);
							if (myMenu->Menu_Form[i].Current == 1)
								AddSprite("commonmenu", "shop_box_tick", myMenu->_Screen.tickSizeX, myMenu->_Screen.tickSizeY, myMenu->_Screen.tickX, (myMenu->_Screen.tickY + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
							else
								AddSprite("commonmenu", "shop_box_blank", myMenu->_Screen.tickSizeX, myMenu->_Screen.tickSizeY, myMenu->_Screen.tickX, (myMenu->_Screen.tickY + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
						}
						else if (myMenu->Menu_Form[i].Numbers)
						{
							Draw_menu_line_Numbers(myMenu->Menu_Form[i].Title, myMenu->Menu_Form[i].Current, myMenu->_Screen.lineWidth, myMenu->_Screen.lineHeight, myMenu->_Screen.lineTop + (i - myMenu->Low) * myMenu->_Screen.lineTobSpace, myMenu->_Screen.lineLeft, myMenu->_Screen.textLeft, myMenu->_Screen.Numberlr, false, false, false);
							AddSprite("commonmenu", "arrowleft", myMenu->_Screen.ArrowtickSizeX, myMenu->_Screen.ArrowtickSizeY, myMenu->_Screen.tickX + myMenu->_Screen.ArrowAlr, (myMenu->_Screen.ArrowH + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
							AddSprite("commonmenu", "arrowright", myMenu->_Screen.ArrowtickSizeX, myMenu->_Screen.ArrowtickSizeY, myMenu->_Screen.tickX + myMenu->_Screen.ArrowBlr + (Get_Int_Length(myMenu->Menu_Form[i].Current) * myMenu->_Screen.NumGap), (myMenu->_Screen.ArrowH + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
						}
						else
							Draw_menu_line(myMenu->Menu_Form[i].Title, myMenu->_Screen.lineWidth, myMenu->_Screen.lineHeight, myMenu->_Screen.lineTop + (i - myMenu->Low) * myMenu->_Screen.lineTobSpace, myMenu->_Screen.lineLeft, myMenu->_Screen.textLeft, false, false, false);
					}
					else
					{
						if (myMenu->Menu_Form[i].TickBox)
						{
							Draw_menu_line(myMenu->Menu_Form[i].Title, myMenu->_Screen.lineWidth, myMenu->_Screen.lineHeight, myMenu->_Screen.lineTop + (i - myMenu->Low) * myMenu->_Screen.lineTobSpace, myMenu->_Screen.lineLeft, myMenu->_Screen.textLeft, true, false, false);
							if (myMenu->Menu_Form[i].Current == 1)
								AddSprite("commonmenu", "shop_box_tickb", myMenu->_Screen.tickSizeX, myMenu->_Screen.tickSizeY, myMenu->_Screen.tickX, (myMenu->_Screen.tickY + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
							else
								AddSprite("commonmenu", "shop_box_blankb", myMenu->_Screen.tickSizeX, myMenu->_Screen.tickSizeY, myMenu->_Screen.tickX, (myMenu->_Screen.tickY + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
						}
						else if (myMenu->Menu_Form[i].Numbers)
						{
							Draw_menu_line_Numbers(myMenu->Menu_Form[i].Title, myMenu->Menu_Form[i].Current, myMenu->_Screen.lineWidth, myMenu->_Screen.lineHeight, myMenu->_Screen.lineTop + (i - myMenu->Low) * myMenu->_Screen.lineTobSpace, myMenu->_Screen.lineLeft, myMenu->_Screen.textLeft, myMenu->_Screen.Numberlr, true, false, false);
							AddSprite("commonmenu", "arrowleft", myMenu->_Screen.ArrowtickSizeX, myMenu->_Screen.ArrowtickSizeY, myMenu->_Screen.tickX + myMenu->_Screen.ArrowAlr, (myMenu->_Screen.ArrowH + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
							AddSprite("commonmenu", "arrowright", myMenu->_Screen.ArrowtickSizeX, myMenu->_Screen.ArrowtickSizeY, myMenu->_Screen.tickX + myMenu->_Screen.ArrowBlr + (Get_Int_Length(myMenu->Menu_Form[i].Current) * myMenu->_Screen.NumGap), (myMenu->_Screen.ArrowH + i - myMenu->Low) * myMenu->_Screen.tickMulti, 0.0f);
						}
						else
							Draw_menu_line(myMenu->Menu_Form[i].Title, myMenu->_Screen.lineWidth, myMenu->_Screen.lineHeight, myMenu->_Screen.lineTop + (i - myMenu->Low) * myMenu->_Screen.lineTobSpace, myMenu->_Screen.lineLeft, myMenu->_Screen.textLeft, true, false, false);
					}
				}

				MeunDescrition(myMenu, Descrip, false);
			}

			if (myMenu->waitTime < InGameTime())
			{
				bool bEnt, bDel, bUp, bDown, bLeft, bRight, bShutDown;
				get_button_state(&bEnt, &bDel, &bUp, &bDown, &bLeft, &bRight, &bShutDown);

				if (bShutDown || ButtonDown(199, true))
				{
					Menu_Index = 0;
					Close_Menu = true;
				}
				else if (ButtonDown(199, true))
					Close_Menu = true;
				else if (bDel || ButtonDown(45, true))
				{
					menu_beep();
					myMenu->_Exit = true;
				}
				else
				{
					if (bEnt || ButtonDown(21, true))
					{
						menu_beep();
						myMenu->_Activate = true;
						myMenu->waitTime = InGameTime() + 150;
					}
					else
					{
						if (bUp || ButtonDown(27, true))
						{
							if (myMenu->Scroling)
							{
								if (myMenu->Low > 0)
								{
									myMenu->Low--;
									myMenu->High--;
								}

								if (myMenu->Index == 0)
								{
									myMenu->Index = (int)myMenu->Menu_Form.size();
									if (myMenu->Index > 6)
									{
										myMenu->High = myMenu->Index;
										myMenu->Low = myMenu->High - 7;
									}
								}
								myMenu->Index--;
							}
							else
							{
								if (myMenu->Index == 0)
									myMenu->Index = (int)myMenu->Menu_Form.size();
								myMenu->Index--;
							}
							myMenu->waitTime = InGameTime() + 150;
						}
						else if (bDown || ButtonDown(19, true))
						{
							myMenu->Index++;
							if (myMenu->Scroling)
							{
								if (myMenu->Index == (int)myMenu->Menu_Form.size())
								{
									myMenu->Index = 0;
									myMenu->High = 7;
									myMenu->Low = 0;
								}
								else if (myMenu->Index == myMenu->High && myMenu->High < (int)myMenu->Menu_Form.size())
								{
									myMenu->Low++;
									myMenu->High++;
								}
							}
							else
							{
								if (myMenu->Index == (int)myMenu->Menu_Form.size())
									myMenu->Index = 0;
							}
							myMenu->waitTime = InGameTime() + 150;
						}
						else if (bLeft || ButtonDown(47, true))
						{
							myMenu->_Left = true;
							myMenu->Menu_Form[myMenu->Index].Current--;
							if (myMenu->Menu_Form[myMenu->Index].Current < myMenu->Menu_Form[myMenu->Index].Min)
								myMenu->Menu_Form[myMenu->Index].Current = myMenu->Menu_Form[myMenu->Index].Max;

							if (Menu_interval > 0)
								Menu_interval--;
							myMenu->waitTime = InGameTime() + Menu_interval;
						}
						else if (bRight || ButtonDown(46, true))
						{
							myMenu->_Right = true;
							myMenu->Menu_Form[myMenu->Index].Current++;
							if (myMenu->Menu_Form[myMenu->Index].Current > myMenu->Menu_Form[myMenu->Index].Max)
								myMenu->Menu_Form[myMenu->Index].Current = myMenu->Menu_Form[myMenu->Index].Min;

							if (Menu_interval > 0)
								Menu_interval--;
							myMenu->waitTime = InGameTime() + Menu_interval;
						}
						else
							Menu_interval = 150;
					}
				}
			}
		}
	}

	std::string CaptureScreenText()
	{
		std::string output = "";
		GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", "", "", "", "", 64);
		while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
			WAIT(1);
		if (GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
		{
			const char* text = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();

			output = text;
		}
		return output;
	}
}
